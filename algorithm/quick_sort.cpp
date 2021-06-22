#include <iostream>
#include <vector>

using namespace std;

class Sort {
public:
    void printArray(vector<int>& array) const {
        for (vector<int>::iterator iter = array.begin(); iter != array.end(); iter++){
            cout << *iter<<" ";
        }
    }

    void quick_sort(vector<int>& input) {
        vector<int> order_array(input.size());
        quick_sort_(input, 0, input.size()-1);
        printArray(input);
        
    }

    void quick_sort_(vector<int>& array, int start, int end) {

    if (start < end){       // 推出标准
        int i = start, j = end;
        int tmp = array[start];

        while (i < j) {
            while (i < j && array[j] >= tmp) {
                j--;
            }
            if (i < j) {
                array[i++] = array[j];
            }
            while (i < j && array[i] < tmp) {
                i++;
            }
            if (i < j) {
                array[j--] = array[i];
            }
        }

        array[i] = tmp;

        quick_sort_(array, start,i-1);
        quick_sort_(array, i+1, end);
        }

    }
};


int main(){
    Sort *s = new Sort();

    vector<int> array = {5,6,1,7,2,5,3,4,1,4};
    s->quick_sort(array);

    return 0;
}