/*
给你一个字符串 date ，按 YYYY-MM-DD 格式表示一个 现行公元纪年法 日期。请你计算并返回该日期是当年的第几天。

通常情况下，我们认为 1 月 1 日是每年的第 1 天，1 月 2 日是每年的第 2 天，依此类推。每个月的天数与现行公元纪年法（格里高利历）一致。
*/
#include <string>
#include <array>
#include <iostream>

using namespace std;


class Solution {
public:
    int dayOfYear(string date) {
        int size = date.size();
        int year, month, day;
        int offset1 = date.find('-', 0);
        int offset2 = date.find('-', offset1+1);

        year = atoi(date.substr(0, offset1).data());
        month = atoi(date.substr(offset1+1, offset2-offset1-1).data());
        day = atoi(date.substr(offset2+1, size - offset2-1).data());

        array<int, 12> kDays;
        kDays[0] = 31;
        kDays[1] = isLeapYear(year) ? 29: 28;
        kDays[2] = 31;
        kDays[3] = 30;
        kDays[4] = 31;
        kDays[5] = 30;
        kDays[6] = 31;
        kDays[7] = 31;
        kDays[8] = 30;
        kDays[9] = 31;
        kDays[10] = 30;
        kDays[11] = 31;

        int result = 0;
        for (int i = 1; i <= month-1; i++) {
            result += kDays[i-1];
        }
        result += day;
        return result;
    }
    // 是否为闰年
    bool isLeapYear(int year) { // 对于整百年份必须是400倍数, 不是整百年份只需要是4的倍数
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
};

int main() {
    Solution solu;
    cout << solu.dayOfYear("2019-08-09")<<endl;

    return 0;
}