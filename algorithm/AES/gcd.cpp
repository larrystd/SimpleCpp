//输入两个正整数r0>r1，输出计算结果
int gcd(int r0, int r1)
{
    int r=0;
    while(r1 != 0)
    {
        r = r0 % r1;
        r0 = r1;
        r1 = r;
    }
    return r0;
}