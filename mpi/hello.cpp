/*
MPI 环境必须以以下代码来初始化
MPI_Init(
    int* argc,
    char*** argv)

在 MPI_Init 的过程中，所有 MPI 的全局变量或者内部变量都会被创建。
举例来说，一个通讯器 communicator 会根据所有可用的进程被创建出来（进程是我们通过 mpi 运行时的参数指定的），然后每个进程会被分配独一无二的秩 rank。

*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // 初始化 MPI 环境
    MPI_Init(NULL, NULL);

    // 通过调用以下方法来得到所有可以工作的进程数量
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // 得到当前进程的秩
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // 得到当前进程的名字
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // 打印一条带有当前进程名字，秩以及
    // 整个 communicator 的大小的 hello world 消息。
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    // 释放 MPI 的一些资源
    MPI_Finalize();
}