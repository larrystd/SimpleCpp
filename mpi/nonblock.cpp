/*MPI进程间点对点非阻塞通信*/
#include "mpi.h" /*MPI头函数，提供了MPI函数和数据类型定义*/
#include <stdio.h>

int main(int argc, char** argv)
{
    int rank;   //进程标识
    int size;   //进程总数
    int senddata;   //待发送数据缓存
    int recvdata;   //待接收数据缓存
    int flag_s, flag_r; //通信状态标志，0为通信未完成，1位通信已完成
    MPI_Status status_s, status_r;  //status object (Status)
    MPI_Request handle_s, handle_r; //MPI request (handle)

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*初始化数据*/
    senddata = rank + 1;
    recvdata = 0;
    flag_s = 0;
    flag_r = 0;

    if(rank == 0){
        /*----------------------------MPI_Isend详解--------------------------*/
        //功能：
        //  进行点对点非阻塞进程通信（消息发送）
        //参数：
        //  MPI_Isend(数据发送缓存地址，数据个数，数据类型，目标进程标识，
        //  消息标志，通信域，消息发送请求句柄地址）
        MPI_Isend(&senddata, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &handle_s);  //向1号进程发送消息

        /*----------------------------MPI_Irecv详解--------------------------*/
        //功能：
        //  进行点对点非阻塞进程通信（消息接收）
        //参数：
        //  MPI_Irecv(数据接收缓存地址，数据个数，数据类型，数据来源进程标识，
        //  消息标志，通信域，消息接收请求句柄地址）
        MPI_Irecv(&recvdata, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &handle_r);  //接收1号进程发来的消息

        //flag=0;//采用循环等待的方法等待非阻塞发送的完成，其实是阻塞之后才继续执行
        while (flag_s == 0) {
            /*-------------------------MPI_Test详解-------------------------*/
            //功能：
            //  1.A call to MPI_TEST returns flag = true if the operation 
            //  identified by request is complete
            //  如果当前检测的请求完成的话，返回通信状态标志位为true
            //  2.One is allowed to call MPI_TEST with a null or inactive
            //  request argument. In such a case the operation returns with
            //  flag = true and empty status.
            //  如果检测一个空的或未激活的通信请求，则标志位返回true，检测的
            //  通信状态信息返回空
            //  3.The functions MPI_WAIT and MPI_TEST can be used to complete
            //  both sends and receives
            //  MPI_WAIT和MPI_TEST即可用于检测消息发送状态也可用于消息接收状态
            //参数：
            //  MPI_Test(请求句柄，消息标志，检测的当前请求[发送或接收]的通信状态）
            MPI_Test(&handle_s, &flag_s, &status_s);    //其实是阻塞检测监听消息发送状态，发送完成，返回flag_s为true，否则为false
        }
        //采用循环等待的方法等待非阻塞接收的完成
        while (flag_r == 0) {
            MPI_Test(&handle_r, &flag_r, &status_r);    //监听消息接收状态，接收完成，返回flag_s为true，否则为false
        }
        printf("rank %d send ok,send = %d\n", rank, senddata);

        printf("rank %d recv ok,recv = %d\n", rank, recvdata);
    }
    else if(rank == 1){
            MPI_Isend(&senddata, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &handle_s);  //向0号进程发送消息
            MPI_Irecv (&recvdata, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &handle_r); //接收0号进程发来的消息
            //采用循环等待的方法等待非阻塞发送的完成
            while(flag_s == 0){
                MPI_Test(&handle_s, &flag_s, &status_s);    //监听消息发送状态，发送完成，返回flag_s为true，否则为false
            }
            //采用循环等待的方法等待非阻塞接收的完成
            while(flag_r == 0){
                MPI_Test(&handle_r, &flag_r, &status_r);    //监听消息接收状态，接收完成，返回flag_s为true，否则为false
            }
            printf("rank 1 send ok,send = %d\n",senddata);

            printf("rank 1 recv ok,recv = %d\n",recvdata);
    }
    MPI_Finalize(); /*MPI的结束函数*/
    return (0);
}