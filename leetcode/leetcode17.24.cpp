#include <iostream>


class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        vector<int> ans(4);//   最大子矩阵的左上角和右下角的行列坐标
        int N = matrix.size(); // 行数
        int M = matrix[0].size();
        vector<int> b(M,0); /// 记录段和
        int sum;
        int maxsum=INT_MIN;//记录最大值

        int top, left;

        for(int i=0; i<N; i++){     //以i为上边，从上而下扫描
            for(int t=0;t<M;t++ ) // b[t]清空
                b[t]=0;  

            for(int j=i;j<N;j++){    //子矩阵的下边
                sum = 0;//从头开始求dp
                for(int k=0;k<M;k++){
                    b[k] += matrix[j][k];   // 只是不断增加其高，也就是下移矩阵下边，所有这个矩阵每列的和只需要加上新加的哪一行的元素

                    if (sum > 0){    // sum>0 , 把左边也加上
                        sum += b[k];
                    }
                    else{   // sum <= 0需要更新坐标
                        sum = b[k];
                        top=i;   //上边界
                        left=k;   // 左边界
                    }
                    if( sum > maxsum){
                        maxsum = sum;
                        ans[0]=top;//更新答案
                        ans[1]=left;
                        ans[2]=j;   // 下边界
                        ans[3]=k;   // 右边界
                    }
                }
            }
        }
        return ans;
    }
};