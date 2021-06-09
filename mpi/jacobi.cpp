#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int m = 10;
    int n = 10;
    int a[m][n];
    int b[m][n];
    int i, j, k;

    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            a[i][j] =  rand() / (RAND_MAX + 1.0) * 10 * (i + j) ;
        }
    }

    int size, rank;
    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 每个进程计算的行数，为了简单这里假设正好可以除尽
    int gap = (m - 2) / size;

    int start = gap * rank + 1; // 从第一行开始算
    int end = gap * (rank + 1); // 结尾坐标

    // 迭代10次，计算时忽略了 0，n-1 行 和 0，n-1 列
    for(k = 0; k < 10; k++) {
        // 从右侧邻居获得数据(计算后的结果)
        if(rank < size - 1) {   // 左侧的rank
            MPI_Recv(&a[end+1][0], n, MPI_INT, rank + 1, 100, MPI_COMM_WORLD, &status);
        }
        // 向左侧邻居发送数据
        if(rank > 0) {
            MPI_Send(&a[start][0], n, MPI_INT, rank - 1, 100, MPI_COMM_WORLD);
        }
        // 向右侧邻居发送数据
        if(rank < size - 1) {
            MPI_Send(&a[end][0], n, MPI_INT, rank + 1, 99, MPI_COMM_WORLD);
        }
        // 从左侧邻居获得数据
        if(rank > 0 ) {
            MPI_Recv(&a[start - 1][0], n, MPI_INT, rank - 1, 99, MPI_COMM_WORLD, &status);  
        }
        for(i = start; i <= end; i++) {
            for(j = 1; j < m -1; j++) {

                b[i][j] = 0.25 * (a[i-1][j] + a[i+1][j] + a[i][j+1] + a[i][j-1]);     
            }
        }
        for(i = start; i <= end; i++) {
            for(j = 1; j < n - 1; j++) {
                a[i][j] = b[i][j];
            }
        }
    }

    // 这里按照顺序输出结果
    for(k = 0; k< size; k++) {
        MPI_Barrier(MPI_COMM_WORLD);

        if(rank == k) {
            for(i = start; i <= end; i++) {
                for(j = 1; j < n-1; j++) {
                    printf("a[%d][%d] is %-4d ", i, j, a[i][j]);
                }

                printf("\n");
            }
        }
    }

    MPI_Finalize();
    return 0;
}
/*
int main(){
    mpi_jacobi();
    return 0;
}
*/
