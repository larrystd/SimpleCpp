// test_predict.cpp


// 使用if-else会增加分支预测的你NSU

// 一般的，使用位运算或者表结构来代替复杂度高的if-else可以提高计算速度
#include <algorithm>
#include <ctime>
#include <iostream>

int main() {
    const unsigned ARRAY_SIZE = 50000;
    int data[ARRAY_SIZE];
    const unsigned DATA_STRIDE = 256;   // data_stride
    for (unsigned c = 0; c < ARRAY_SIZE; ++c) {
        data[c] = std::rand() % DATA_STRIDE;
    }

    // std::sort(data, data+ARRAY_SIZE);    // 加上这行，计算4s，不加这行15s。原因在于排序数组在if条件判断会根据历史记录提高分支预测的准确度
    

    {
        clock_t start = clock();
        long long sum = 0;
        for (unsigned i = 0; i < 100000; ++i) {
            for (unsigned c = 0; c < ARRAY_SIZE; ++c) {
                if (data[c] >= 128)
                    sum += data[c];
            }
        }

        double elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;

        std::cout << elapsedTime << "\n";
        std::cout << "sum = "<<sum << "\n";
    }

    return 0;
}