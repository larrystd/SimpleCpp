/*
 * @Author: your name
 * @Date: 2021-03-11 09:03:31
 * @LastEditTime: 2021-03-11 11:43:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /SimpleCode/Leetcode/leetcode50.cpp
 */
//即计算 x 的 n 次幂函数（即，xn）
/*
思想，折半乘法
当n为偶数，直接循环x = x*x;
当n为奇数，
例如10 , 5 , 2 ,
x^2 x^2
*/

class Solution {
public:
    double myPow(double x, int n) {
        double res = 1.0;
        for(int i = n; i != 0; i /= 2){
            if(i % 2){      // 这时候i为奇数
                res *= x;
            }
            x *= x;
        }
        return  n < 0 ? 1 / res : res;      
    }
};
