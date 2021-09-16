#include <iostream>
#include <cstdio>
using namespace std;


int EEA(int r0, int r1)
{
    int mod = r0;
    int r = 0;
    int t0 = 0;
    int t1 = 1;
    int t = t1;
    int q = 0;
 
    //0不存在乘法逆元
    if (r1 == 0)
    {
        return 0;
    }
 
    while (r1 != 1)
    {
        q = r0 / r1;
 
        r = r0 - q * r1;
 
        t = t0 - q * t1;
 
        r0 = r1;
        r1 = r;
        t0 = t1;
        t1 = t;
    }
 
    //结果为负数
    if (t < 0)
    {
        t = t + mod;
    }
 
    return t;
}

//获取最高位
int GetHighestPosition(unsigned short Number)
{
    int i = 0;
    while (Number)
    {
        i++;
        Number = Number >> 1;
    }
    return i;
}
 
 
//GF(2^8)的多项式除法
unsigned char Division(unsigned short Num_L, unsigned short Num_R, unsigned short *Remainder)
{
    unsigned short r0 = 0;
    unsigned char  q = 0;
    int bitCount = 0;
 
    r0 = Num_L;
 
    bitCount = GetHighestPosition(r0) - GetHighestPosition(Num_R);
    while (bitCount >= 0)
    {
        q = q | (1 << bitCount);
        r0 = r0 ^ (Num_R << bitCount);
        bitCount = GetHighestPosition(r0) - GetHighestPosition(Num_R);
    }
    *Remainder = r0;
    return q;
}
 
 
 
//GF(2^8)多项式乘法
short Multiplication(unsigned char Num_L, unsigned char Num_R)
{
    //定义变量
    unsigned short Result = 0;      //伽罗瓦域内乘法计算的结果
 
    for (int i = 0; i < 8; i++)
    {
        Result ^= ((Num_L >> i) & 0x01) * (Num_R << i);
    }
 
    return Result;
}
 
/// 伽罗瓦域的扩展欧几里得
int EEA_V2(int r0, int r1)
{
    int mod = r0;
    unsigned short r = 0;
    int t0 = 0;
    int t1 = 1;
    int t = t1;
    int q = 0;
 
    if (r1 == 0)
    {
        return 0;
    }
 
    while (r1 != 1)
    {
        //q = r0 / r1;
        /// 伽罗瓦域除法
        q = Division(r0, r1, &r);
        /// 加减法变成异或
        r = r0 ^ Multiplication(q, r1);
        /// 
        t = t0 ^ Multiplication(q, t1);
 
        r0 = r1;
        r1 = r;
        t0 = t1;
        t1 = t;
    }
 
    if (t < 0)
    {   
        /// 加减法变异或
        t = t ^ mod;
    }
 
    return t;
}

int main() {
    int r0 = 283;
    int r1 = 0xb5;
    int res = EEA_V2(r0, r1);

    cout << EEA_V2(r0, r1)<<endl;
    printf("%x\n", res);


    return 0;
}

