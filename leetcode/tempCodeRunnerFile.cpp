#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int countValidWords(string sentence) {
        int left = 0;
        int right = 0;
        int len = sentence.size();
        int result = 0;
        while (right < len && sentence[right] == ' ')
                right++;
        left = right;

        while (left < len) {
            while (right < len && sentence[right] != ' ') {
                right ++;
            }
            //int space_index = right;
            //right--;
            bool isvalid = true;
            if (sentence[left] != '-' && sentence[right-1] != '-') {
                int num_conn = 0;
                while (left < right-1) {
                    if (sentence[left] == '-' && num_conn > 0) {
                        isvalid = false;
                        break;
                    }
                    if(sentence[left] != '-' && sentence[left] < 'a' || sentence[left] > 'z') {
                        isvalid = false;
                        break;
                    }
                    if (sentence[left] == '-')
                        num_conn ++;
                    left++;
                }
                if (isvalid && (sentence[left]>='a' || sentence[left] <'z')) {
                    result++;
                }else if (isvalid && (sentence[left] < '0' && sentence[left]>'9') && sentence[left-1] ！= '-')
                    result++;
            }
            while (right < len && sentence[right] == ' ')
                right++;
            left = right;
        }

        return result;
    }
};