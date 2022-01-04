import collections
import math
import random
import sys
import time
import os
import numpy as np
import torch
from torch import nn 
import torch.utils.data as Data
import d2lzh as d2l

sys.path.append(".") 
print (torch.__version__)

with open("/home/larry/programs/Python/nlp/ptb/ptb.train.txt", "r") as f: # 小型文本语料库, 用来训练词向量模型
    lines = f.readlines()
    raw_dataset = [st.split() for st in lines]
# test
print("# train sentences: %d" % len(raw_dataset))
for st in raw_dataset[:3]:
    print("# tokens:", len(st), st[:5])
    
# 只保留出现5次以上的单词
counter = collections.Counter(
    [tk for st in raw_dataset for tk in st]
)   # 返回一个list形式的pair, 保留各种tk和tk出现的次数
counter = dict(filter(lambda x: x[1]>=5, counter.items())) # items()返回可遍历的元组(形成dict)
idx_to_token = [tk for tk,_ in counter.items()] # token
token_to_idx = {tk: idx for idx, tk in enumerate(idx_to_token)} # enumerate返回(idx, token)的元组列表, idx->token的频率
dataset = [[token_to_idx[tk] for tk in st if tk in token_to_idx] for st in raw_dataset]

num_tokens = sum([len(st) for st in dataset])
print("#tokens: %d" % num_tokens)
print("# counter: ", list(counter.items())[:5]) #.item()返回类型为dict_items, 需要用list转为列表方可slice
print("# example idx_to_token: ", idx_to_token[:5]) # idx为索引->token
print("# example token_to_idx: ", list(token_to_idx.items())[:5]) # token->idx
print("# example dataset: ", dataset[:5]) # 用idx表示的token

def discard(idx): # 频率越大, counter越大, 越容易被删除
    return random.uniform(0,1) < 1-math.sqrt(
        1e-4 / counter[idx_to_token[idx]] * num_tokens
    )
subsampled_dataset = [[tk for tk in st if not discard(tk)] for st in dataset] # 根据出现频率, 判定是否剔除。不会删除的个数
print("#tokens: %d" % (sum([len(st) for st in subsampled_dataset])))

def compare_counts(token):
    return "# %s: before=%d, after=%d" % (token, sum(
        [st.count(token_to_idx[token]) for st in dataset]
    ), sum(
        [st.count(token_to_idx[token]) for st in subsampled_dataset]
    ))
    
print ("before and after, compare the: ", compare_counts("the"))
print ("before and after, compare the: ", compare_counts("join"))

# 提取中心词和背景词
def get_centers_and_contexts(dataset, max_window_size):
    centers, contexts = [], []
    for st in dataset:
        # 每个句子至少俩词才可能组成中心词-背景词
        if len(st) < 2:
            continue
        centers += st
        for center_i in range(len(st)):
            window_size = random.randint(1, max_window_size) # 背景窗口大小不确定
            indices = list(range(max(0, center_i - window_size),
                                min(len(st), center_i+1+window_size)
                                ))
            indices.remove(center_i) # 中心词排除在背景词外
            contexts.append([st[idx] for idx in indices])
    return centers, contexts

tiny_dataset = [list(range(7)), list(range(7, 10))]

for center, context in zip(*get_centers_and_contexts(tiny_dataset, 2)):  # zip将返回的centers, contexts打包成元组。*是解包, 因为函数返回的是元组
    print ("center", center, "has contexts", context)
    
all_centers, all_contexts = get_centers_and_contexts(subsampled_dataset, 5)  # 返回中心词和背景词, 中心词为一维列表, 背景词是二维列表

def get_negatives(all_contexts, sampling_weights, K):  # 负采样
    all_negatives, neg_candidates, i = [], [], 0
    population = list(range(len(sampling_weights)))
    for contexts in all_contexts: # contexts为每个中心词对应的背景词
        negatives = []
        while len(negatives) < len(contexts)*K: # 每个中心词, 提取的负样本不超过背景词的K倍
            if i == len(neg_candidates):
                i, neg_candidates = 0, random.choices(population, sampling_weights, k=int(1e5))
            neg, i = neg_candidates[i], i+1
            if neg not in set(contexts):  # 不再contexts背景词的词语可以放到噪声词中
                negatives.append(neg)
                
        all_negatives.append(negatives)
    return all_negatives

sampling_weights = [counter[w]**0.75 for w in idx_to_token]  # 设置采样概率
all_negatives = get_negatives(all_contexts, sampling_weights, 5)            

class MyDataset(torch.utils.data.Dataset):
    # 读取中心词, 背景词, 负样本词
    def __init__(self, centers, contexts, negatives):
        assert len(centers) == len(contexts)==len(negatives)
        self.centers = centers
        self.contexts = contexts
        self.negatives = negatives
    def __getitem__(self, index):  # []
        return (self.centers[index],
                self.contexts[index],
                self.negatives[index])
    
    def __len__(self):
        return len(self.centers)


def batchify(data):
    # len(c)+len(c)大小可能不一, 因此需要设置填充， mask实际数据设置1, 0填充部分设置为0
    max_len = max(len(c) + len(n) for _,c,n in data)
    centers,contexts_negatives,masks,labels = [],[],[],[]
    for center, context, negative in data:
        cur_len = len(context) + len(negative)
        centers += [center]
        contexts_negatives += [context+negative+[0]*(max_len - cur_len)]
        masks += [[1]*cur_len + [0]*(max_len - cur_len)]
        labels += [[1]*len(context) + [0]*(max_len - len(context))]
    
    return (torch.tensor(centers).view(-1, 1),  # view相当于resize, 中心词
            torch.tensor(contexts_negatives),   # 背景词+负样本
            torch.tensor(masks), # mask, 背景词+负样本部分mask=1
            torch.tensor(labels)) # 只有背景词部分label=1
    
batch_size = 512
num_works = 4
dataset = MyDataset(all_centers, all_contexts, all_negatives)
data_iter = Data.DataLoader(dataset, batch_size, shuffle=True, collate_fn=batchify, num_workers=4)
for batch in data_iter:
    for name, data in zip(["centers", "context_negatives", "masks", "labels"], batch):
        print (name, "shape: ", data.shape)
    break


# 模型
embed = nn.Embedding(num_embeddings=20, embedding_dim=4) # 表示词向量, 随机初始化

x = torch.tensor([[1,2,3], [4,5,6]], dtype=torch.long)
print(embed(x))

X = torch.ones((2,1,4))
Y = torch.ones((2,4,6))
print(torch.bmm(X,Y)) # 加了一层batch的两矩阵相乘

def skip_gram(center, contexts_and_negatives, embed_v, embed_u):
    u = embed_u(center)
    v = embed_v(contexts_and_negatives)  #u,v两个向量就是要训练的向量, embed_v就是要施加的函数
    pred = torch.bmm(v, u.permute(0,2,1)) # permute维度换位, 起到transpose的结果。u换位相当于vT
    return pred

# 对输入的inputs, targets，mask求交叉熵损失
class SigmoidBinaryCrossEntropyLoss(nn.Module):
    def __init__(self):
        super(SigmoidBinaryCrossEntropyLoss, self).__init__()
    def forward(self, inputs, targets, mask=None):
        """
            input - (batch_size, len)
            target same shape as input     
        """
        inputs, targets = inputs.float(), targets.float()
        mask = mask.float()
        res = nn.functional.binary_cross_entropy_with_logits(
            inputs, targets, reduction='none', weight=mask
        ) # 只在mask=1的部分计算
        return res.mean(dim=1)
loss = SigmoidBinaryCrossEntropyLoss()

pred = torch.tensor([[1.5, 0.3, -1, 2], [1.1, -0.6, 2.2, 0.4]])
label = torch.tensor([[1, 0, 0, 0], [1,1, 0, 0]])
mask = torch.tensor([[1,1,1,1], [1,1,1,0]])
print (loss(pred, label, mask) * mask.shape[1]/mask.float().sum(dim=1))  # mask.float().sum(dim=1)对dim=1的维度运算, 结果为[4,3], 这句就是按照行计算


def sigmd(x):
    return -math.log(1/(1+math.exp(-x)))
print ("%.4f" % ((sigmd(1.5) + sigmd(-0.3) + sigmd(1) + sigmd(-2)) / 4))

embed_size = 100
net = nn.Sequential(
    nn.Embedding(num_embeddings=len(idx_to_token),
                 embedding_dim=embed_size),
    nn.Embedding(num_embeddings=len(idx_to_token),
                 embedding_dim=embed_size)
)


def train(net, lr, num_epoch):
    device = "cpu"
    net = net.to(device)
    optimizer = torch.optim.Adam(net.parameters(), lr = lr)
    for epoch in range(num_epoch):
        start, l_sum, n = time.time(), 0.0, 0
        for batch in data_iter:
            center, context_negative, mask, label = [d.to(device) for d in batch] # 得到数据, 中心词, 背景词+负样本, mask, label
            pred = skip_gram(center, context_negative, net[0], net[1]) # net[0]训练center, net[1]训练context_negative
            l = (
                loss(pred.view(label.shape), label, mask) *
                mask.shape[1]/mask.float().sum(dim=1)
            ).mean()  # 平均损失
            optimizer.zero_grad() # 不要累加上次训练的梯度
            l.backward() # 梯度下降
            optimizer.step() #优化器更新参数
            l_sum += l.cpu().item()
            n += 1
        print ("epoch %d, loss %.2f, time %.2f" %(epoch+1, l_sum/n, time.time()-start))

train(net, 0.01, 10)

def get_similar_tokens(query_tokens, k, embed):
    W = embed.weight.data
    x = W[token_to_idx[query_tokens]]  # token->idx->embedding
    cos = torch.matmul(W, x)/(
        torch.sum(W*W, dim=1) * (torch.sum(x*x) + 1e-9)
    ).sqrt() # 余弦相似度, W的每一行(代表一个单词)和x求余弦相似度
    _, topk = torch.topk(cos, k=k+1) # 最有可能属于的k+1个类别
    topk = topk.cpu().numpy()
    
    for i in topk[1:]: # 除了query_tokens以外
        print ("cosine sim=%.3f: %s" %(cos[i], idx_to_token[i]))
get_similar_tokens("chip", 3, net[0])