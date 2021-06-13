/*
洗牌算法是将原来的数组进行打散，使原数组的某个数在打散后的数组中的每个位置上等概率的出现

Inside-Out Algorithm 算法的基本思想是从前向后扫描数据，\
把位置i的数据随机插入到前i个（包括第i个）位置中（假设为k），\
然后把位置k的数字替换位置i的数字。
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;
void Inside_Out_Shuffle(const vector<int>&arr,vector<int>& res)
{
	res.assign(arr.size(),0);
	copy(arr.begin(),arr.end(),res.begin());
	int k;
	for (int i=0;i<arr.size();++i)
	{
		srand((unsigned)time(NULL));
		k=rand()%(i+1);
		res[i]=res[k];
		res[k]=arr[i];
	}
}