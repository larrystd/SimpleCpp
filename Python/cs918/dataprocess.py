import random
import os
import json
from pandas import DataFrame
import nltk
import string
from nltk.corpus import stopwords

DATAROOT = "/home/larry/programs/Python/cs918/semeval-tweets"
from tqdm import tqdm
def read_imdb(folder='train', filepath="/S1/CSCL/tangss/Datasets/aclImdb"):  # 本函数已保存在d2lzh_pytorch包中方便以后使用
    data = []
    
    for label in ['pos', 'neg']:
        folder_name = os.path.join(data_root, folder, label)
        for file in tqdm(os.listdir(folder_name)): # 可迭代对象用进度条tqdm
            with open(os.path.join(folder_name, file), 'rb') as f:
                review = f.read().decode('utf-8').replace('\n', '').lower() # pos, neg目录下的文件每个文件表示话(用来情感分析)
                data.append([review, 1 if label == 'pos' else 0])
    
    random.shuffle(data)
    return data

def textprocess(text):
    lower = text.lower()
    remove = str.maketrans('','',string.punctuation) 
    without_punctuation = lower.translate(remove)  # 
    
    tokens = nltk.word_tokenize(without_punctuation)
    without_stopwords = [w for w in tokens if not w in stopwords.words('english')] #去除停用词
    s = nltk.stem.SnowballStemmer('english')  #参数是选择的语言, 获得词干stem
    
    cleaned_text = [s.stem(ws) for ws in without_stopwords]
    return cleaned_text
    

def readfile(datatype="train", filepath="twitter-training-data.txt"):
    data = []
    with open(filepath, "rb") as f:
        lines = f.readlines()
        for line in lines:
            # 读取为二进制格式, 解码为文本格式
            content = line.decode('utf-8').replace('\n','').replace('"','').lower().split('\t')
            
            content[2] = textprocess(content[2])
            data.append([content[2], 1 if content[1] == 'positive' else 0])
    
    return data 


data_root = os.path.join(DATAROOT, "twitter-training-data.txt")
train_data = readfile('train', data_root)
print(train_data[:10])

data=DataFrame(train_data)#这时候是以行为标准写入的
data.columns = ["content", "label"]
# print(data)
data.to_csv("data.csv")

