/*
leetcode 2022. 将一维数组转变成二维数组
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** construct2DArray(int* original, int originalSize, int m, int n, int* returnSize, int** returnColumnSizes){
    if (originalSize != m*n) {
        *returnSize = 0;
        return NULL;
    }

    *returnSize = m;
    int** result = (int **)malloc(sizeof(int *) * m);
    *returnColumnSizes = (int* )malloc(sizeof(int) *m);

    for (int i = 0; i < m; i ++) {
        result[i] = (int *)malloc(sizeof(int) * n);
        (*returnColumnSizes)[i] = n;
    }

    for (int i = 0; i < originalSize; i += n) {
        memcpy(result[i/n], original+i, sizeof(int)*n);
    }

    return result;

}

int main() {
    int originalSize = 4;
    int nums[] = {1,2,3,4};
    //int* nums = (int* )malloc(sizeof(int) * originalSize);
    int m = 2, n = 2;

    int returnSize;

    int* returnColumnSize;

    
    int* original = &nums[0];

    int** result = construct2DArray(original, originalSize, m, n, &returnSize, &returnColumnSize);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}