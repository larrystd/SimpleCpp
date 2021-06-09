/*
利用mpi并行计算求向量内积
*/

#include<stdio.h>
#include<string.h>
#include<mpi.h>
#pragma warning(disable : 4996)
#define MAX_STRING 100
using namespace std;
#include <fstream>
#include <iostream>

int Find_bin(double x, double *bin_maxes, int bin_count) {
	for (int i = 0; i < bin_count; ++i) {
		if (x < bin_maxes[i]) return i;
	}
	return bin_count; // 越界
}

int main(void) {
	double *local_vec1, *local_vec2;
	int len;
	double scalar, local_sum = 0;
	int comm_sz;
	int my_rank;
	int divided_len;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);    // 得到进程个数 comm_sz
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);    // 当前进程的rank
	// 假设 n % comm_sz = 0 整除
	// 只有一个线程的时候不操作，直接退出
	if (comm_sz <= 1) {
		MPI_Finalize();
		return 0;
	}

	if (my_rank == 0) {
		ifstream cin("input.txt");
		cin >> len; // 输入数据长度
		local_vec1 = new double[len];
		local_vec2 = new double[len];

        // 输入数据
		for (int i = 0; i < len; ++i) cin >> local_vec1[i];
		for (int i = 0; i < len; ++i) cin >> local_vec2[i];
		cin >> scalar;

        // 每个进程分得的数据长度
		divided_len = len / comm_sz; 
		double * sub_vec = new double[divided_len];
		// 发送子串长度
        // int MPI_Send(type* buf, int count, MPI_Datatype, int dest, int tag, MPI_Comm comm) 
        // 进程编号为0~N-1
		for (int i = 1; i < comm_sz; ++i) {
			MPI_Send(&divided_len, 1, MPI_INT, i, 3, MPI_COMM_WORLD);
		}

		// 发送第一个串
        // 每个进程法长为divided_len的一小段
		int target = 1;
		for (int i = divided_len; i < len; i += divided_len) {
			for (int j = 0; j < divided_len; ++j) {
				sub_vec[j] = local_vec1[j + i];
			}
			MPI_Send(sub_vec, divided_len, MPI_DOUBLE, target, 0, MPI_COMM_WORLD);
			target++;
		}
		// 发送第二个串
		target = 1;
		for (int i = divided_len; i < len; i += divided_len) {
			for (int j = 0; j < divided_len; ++j) {
				sub_vec[j] = local_vec2[j + i];
			}
			MPI_Send(sub_vec, divided_len, MPI_DOUBLE, target, 1, MPI_COMM_WORLD);
			target++;
		}
		// 发送因子
		for (int i = 1; i < target; ++i) {
			MPI_Send(&scalar, 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD);
		}
		
		// 计算本地的数据
		for (int i = 0; i < divided_len; ++i) {
			local_sum += (local_vec1[i] * local_vec2[i]);
			local_vec1[i] *= scalar;
			local_vec2[i] *= scalar;    // 向量数乘法
		}

		// 接受第一个串
		target = 1;
		for (int i = divided_len; i < len; i += divided_len) {
			MPI_Recv(sub_vec, divided_len, MPI_DOUBLE, target, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			for (int j = 0; j < divided_len; ++j) {
				 local_vec1[j + i] = sub_vec[j];
			}
			target++;
		}
		// 接受第二个串
		target = 1;
		for (int i = divided_len; i < len; i += divided_len) {
			MPI_Recv(sub_vec, divided_len, MPI_DOUBLE, target, 1, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			for (int j = 0; j < divided_len; ++j) {
				local_vec2[j + i] = sub_vec[j];
			}
			target++;
		}
		// 接受部分和
		for (int i = 1; i < target; ++i) {
			MPI_Recv(&scalar, 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			local_sum += scalar;
		}

		// 输出

		for (int i = 0; i < len; ++i) {
			cout << local_vec1[i] << " ";
		}cout << endl;

		for (int i = 0; i < len; ++i) {
			cout << local_vec2[i] << " ";
		}cout << endl;

		cout << local_sum << endl;

		delete[] sub_vec;
		delete[] local_vec1;
		delete[] local_vec2;
	} // 运算的子节点
	else {
		MPI_Recv(&divided_len, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		local_vec1 = new double[divided_len];
		local_vec2 = new double[divided_len];
		MPI_Recv(local_vec1, divided_len, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);   //等待接收第一个串
		MPI_Recv(local_vec2, divided_len, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		MPI_Recv(&scalar, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

		for (int i = 0; i < divided_len; ++i)
		{
			local_sum += local_vec1[i] * local_vec2[i];
			local_vec1[i] *= scalar;
			local_vec2[i] *= scalar;
		}
		MPI_Send(local_vec1, divided_len, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		MPI_Send(local_vec2, divided_len, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
		MPI_Send(&local_sum, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
		delete[] local_vec1;
		delete[] local_vec2;
	}
	MPI_Finalize();

	return 0;
}