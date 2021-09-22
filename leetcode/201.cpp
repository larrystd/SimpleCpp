/// 201 数字范围按位与

/*
给你两个整数 left 和 right ，表示区间 [left, right] ，返回此区间内所有数字 按位与 的结果（包含 left 、right 端点）。

 

示例 1：


*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {

        if (left == right)
            return left;
        
        int result = 0;
        int bits = 0;
        for (int i = 31; i >= 0; i--) {
            if (right >> i & 1){
                if (left < 1<<i)
                    return 0;
                bits = i; 
                break;
            }
        }

        for (int i = bits; i >= 0; i--) {
            if ((left>>i & 1) == (right>>i & 1)){
                result += (left>>i & 1)<<i;
                
            }else{
                break;
            }
        }

        return result;
    }
};

int main() {
    Solution solu;
    cout << solu.rangeBitwiseAnd(10, 11)<<endl;
    return 0;
}