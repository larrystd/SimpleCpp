#include <iostream>
#include <vector>

/*
从概念上讲，归并排序的工作原理如下：

先将未排序的列表划分为n个子列表，每个子列表包含一个元素（一个元素的列表被认为是排序的）。
反复合并子列表以产生新的排序子列表，直到只剩一个子列表。这将是排序列表。

# 归并排序中的思路
需要有中间数组进行中间赋值
MergeSort(arr[], l,  r)
If r > l
     1. 找到数组中的中间点，把数组分为两部分
             middle m = (l+r)/2
     2. 对数组的左部分调用MergeSort 函数  
             Call mergeSort(arr, l, m)
     3. 对数组的右部分调用MergeSort 函数 
             Call mergeSort(arr, m+1, r)
     4. 合并2,3中的两部分
             Call merge(arr, l, m, r)
*/

using namespace std;

class Sort {
public:
    void printArray(vector<int>& array) const {
        for (vector<int>::iterator iter = array.begin(); iter != array.end(); iter++){
            cout << *iter<<" ";
        }
    }
    void merge_sort(vector<int>& input) {
        vector<int> order_array(input.size());
        merge_sort_(input, 0, input.size()-1, order_array);
        printArray(input);
        
    }

    void merge_sort_(vector<int>& unorder_array, int start, int end, vector<int>& order_array) {
        if (start < end) {
            int mid = (start + end) / 2;
            merge_sort_(unorder_array, start, mid, order_array);
            merge_sort_(unorder_array, mid+1, end, order_array);
            merge_array(unorder_array, start, mid, end, order_array);
        }
  }  

  void merge_array(vector<int>& unorder_array, int start, int mid, int end, vector<int>& order_array) {
      int i, j;
      int k=0;
      for (i = start, j = mid+1; i <= mid && j <= end; k++) {
          if (unorder_array[i] > unorder_array[j]) {
              order_array[k] = unorder_array[j];
              j++;
          }else {
               order_array[k] = unorder_array[i];
               i++;
          }
      }

      while (i <= mid){
          order_array[k++] = unorder_array[i];
          i++;
      }
      while (j <= end){
          order_array[k++] = unorder_array[j];
          j++;
      }

      for (int i = 0; i < k; i ++) {
        unorder_array[start + i] = order_array[i];
    }
  }
};

int main(){
    Sort *s = new Sort();

    vector<int> array = {5,6,1,7,2,5,3,4,1,4};
    s->merge_sort(array);

    return 0;
}