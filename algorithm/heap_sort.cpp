/*
通俗来讲，二叉树在按层序遍历时在遇到第一个NULL指针即作为结尾的二叉树就可以称之为完全二叉树。
根节点下标为0，若父节点相应数组下标为i，则其左孩子相应数组下标为2*i+1，右孩子为2*i+2.

第i个序号的结点的数，那么他的父结点序号就是(i-1)/2，它的孩子结点就为2i+1与2i+2。

最后一个非叶节点编号，size/2
*/

#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

void adjust(int arr[], int len, int index)
{
    int left = 2*index + 1; //左子节点
    int right = 2*index + 2;
    int maxIdx = index;
    if(left<len && arr[left] > arr[maxIdx]) 
        maxIdx = left;
    if(right<len && arr[right] > arr[maxIdx]) 
        maxIdx = right;  // maxIdx是3个数中最大数的下标
    if(maxIdx != index)                 // 如果maxIdx的值有更新
    {
        swap(arr[maxIdx], arr[index]);
        adjust(arr, len, maxIdx);       // 自顶向下，递归调整其他不满足堆性质的部分
    }

}
void heapSort(int arr[], int size)
{
    // 调整二叉堆，成为大顶堆
    for(int i=size/2 - 1; i >= 0; i--)  // 对每一个非叶结点进行堆调整(从最后一个非叶结点开始)
    {
        adjust(arr, size, i);
    }

    // 堆排序
    for(int i = size - 1; i >= 1; i--)
    {
        swap(arr[0], arr[i]);           // 将当前最大的放置到数组末尾
        adjust(arr, i, 0);              // 将未完成排序的部分继续进行堆排序
    }
}

int main()
{
    int array[8] = {8, 1, 14, 3, 21, 5, 7, 10};
    heapSort(array, 8);
    for(auto it: array)
    {
        cout<<it<<endl;
    }
    return 0;
}