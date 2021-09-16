#include <cstdio>
#include <string.h>

///////////////////////////////////////////////////////////////
//功能:   伽罗瓦域内的乘法运算  GF(128)
//参数:   Num_L           输入的左参数
//      Num_R           输入的右参数
//返回值:计算结果
char GaloisMultiplication(unsigned char Num_L, unsigned char Num_R)
{
    //定义变量
    unsigned char Result = 0;       //伽罗瓦域内乘法计算的结果
 
    while (Num_L)
    {
        //如果Num_L最低位是1就异或Num_R，相当于加上Num_R * 1
        if (Num_L & 0x01)
        {
            Result ^= Num_R;
        }
 
        //Num_L右移一位，相当于除以2
        Num_L = Num_L >> 1;
 
        //如果Num_R最高位为1
        if (Num_R & 0x80)
        {
            //左移一位相当于乘二
            Num_R = Num_R << 1;     //注：这里会丢失最高位，但是不用担心
 
            Num_R ^= 0x1B;  //计算伽罗瓦域内除法Num_R = Num_R / (x^8(刚好丢失最高位) + x^4 + x^3 + x^1 + 1)
        }
        else
        {
            //左移一位相当于乘二
            Num_R = Num_R << 1;
        }
    }
    return Result;
}

const unsigned char MixArray[4][4] =
{
    0x02, 0x03, 0x01, 0x01,
    0x01, 0x02, 0x03, 0x01,
    0x01, 0x01, 0x02, 0x03,
    0x03, 0x01, 0x01, 0x02
};
 
int MixColum(unsigned char(*PlainArray)[4])
{
    int ret = 0;
    //定义变量
    unsigned char ArrayTemp[4][4];
 
    //初始化变量
    memcpy(ArrayTemp, PlainArray, 16);
 
    //矩阵乘法 4*4
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            PlainArray[i][j] =
                GaloisMultiplication(MixArray[i][0], ArrayTemp[0][j]) ^
                GaloisMultiplication(MixArray[i][1], ArrayTemp[1][j]) ^
                GaloisMultiplication(MixArray[i][2], ArrayTemp[2][j]) ^
                GaloisMultiplication(MixArray[i][3], ArrayTemp[3][j]);
        }
    }
    return ret;
}

int main() {
    /*
    unsigned char arr[4] = {
        {'1A', 'F2', '4D', '97'},
        {'2B', '4C' ,'90' ,'EC'},
        {'3C', 'E7', '4A', 'C3'},
        {'4D', '8C', 'D8' ,'95'},
    }
    */
    unsigned char arr[4][4] = {
        0x1A, 0xF2, 0x4D, 0x97,
        0x2B, 0x4C ,0x90 ,0xEC,
        0x3C, 0xE7, 0x4A, 0xC3,
        0x4D, 0x8C, 0xD8 ,0x95,
    };

    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j++) {
            printf("%x ", arr[i][j]);
        }
        printf("\n");
    }

    MixColum(arr);
        for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j++) {
            printf("%x ", arr[i][j]);
        }
        printf("\n");
    }
}