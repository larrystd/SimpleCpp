/*
大顶堆排序
输入的数组其实就是一个堆
调整二叉堆，从非叶子节点开始，调整二叉堆
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BinaryHeap {
public:
    void adjustHeap(vector<int>& arr, int len, int index) {
        int max_index = index;
        int left_index = 2*index+1;
        int right_index = 2*index+2;
        if (left_index < len && arr[left_index] > arr[max_index]) 
            max_index = left_index;
        if (right_index < len && arr[right_index] > arr[max_index])
            max_index = right_index;
        
        if(max_index != index)               
        {
            swap(arr[max_index], arr[index]);
            adjustHeap(arr, len, max_index);      
        }
    }

    void heapSort(vector<int>& arr) {
        for (int i = arr.size()/2; i >=0; i--) {
            adjustHeap(arr, arr.size(), i);
        }

        // 排序
        for (int i = arr.size()-1; i >=1; i--) {
            swap(arr[i], arr[0]);
            adjustHeap(arr, i, 0);
        }
    }

    int findKMax(vector<int>& arr, int k) {
        for (int i = arr.size()/2; i >=0; i--) {
            adjustHeap(arr, arr.size(), i);
        }

        // 排序
        int i;
        //int flag = arr.size() - k;
        for (i = arr.size() - 1; i >= (arr.size() - k) && i > -10; i--){
            cout <<  (arr.size() - k)<<" ";
            cout << i << " ";
            cout << (i >= (arr.size() - k) )<<" ";
            cout << (i >= 0 )<<endl;
            swap(arr[0], arr[i]);
            adjustHeap(arr, i, 0);
        }
        return arr[i+1];
    }
};

int main()
{
    BinaryHeap b_h;
    vector<int> array = {1};
    cout << b_h.findKMax(array, 1) <<endl;
    return 0;
}

