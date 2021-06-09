#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>



/*
create a matrix, first create an array of length n*m, and then use a two-dimensional matrix pointer to point to the beginning
*/

float** create_matrix(int n, int m){
    float* flat = malloc(n * m * sizeof(float));
	float** matrix = malloc(n * sizeof(float*));
	int i;

	memset(flat, 0, n * m * sizeof(float));

	for (i = 0; i < n; i++)
	{
		matrix[i] = &flat[i * m];
	}

	return matrix;
}

/*
Create upper triangular matrix
Compressed storage using ptr
*/

float** create_triangle_matrix(int columns, int rows)
{
	int total = (columns * 2 - rows + 1) * rows / 2;
	float* flat = malloc(total * sizeof(float));
	float** mt = malloc(rows * sizeof(float*));
	int i, j = 0;

	for (i = 0; i < rows; i++)
	{
		mt[i] = &flat[j];
		j += columns;
		columns--;
	}

	return mt;
}


/*
Calculate the inner product of two vector
*/
float product(float* row1, float* row2, int m)
{
	float result = 0;
	int i;

	for (i = 0; i < m; i++)
	{
		result += row1[i] * row2[i];
	}

	return result;
}

/*
The block divided by each process, calculate the inner product of the vector inside the block
*/

void product_in_block(float** block, int rows, int m, float** results)
{
	int i, j;

	for (i = 0; i < rows - 1; i++)
	{
		for (j = i + 1; j < rows; j++)
		{
			results[i][j - i - 1] = product(block[i], block[j], m); // result形式是个上三角矩阵
		}
	}
}

int main(int argc, char** argv){
    int i, j;	// count
    int my_rank, num_procs, prev_rank, next_rank;	// rank

    int is_master, is_parall;
    int vectors_per_proc;
    int max_columns, iter_count;

    int results_nbs;   // Upper triangular matrix, number of elements
    int proc_results_nbs;   // The amount calculation allocated by each process
    float** result_matrix = NULL;   // the triangular matrix as the result
    float** proc_matrix;    // Part of the result triangular matrix calculated by each process
    

    int m, n;   // m is the number of elements in the vector, n is the number of vectors
    float** matrix = NULL;  // origin matrix
    float** block_left = NULL;	// left block, mean rows
    float** block_right = NULL;	// right block, maybe need transfer from other process
   
    MPI_Request *requests = NULL;   // Communication handle
	MPI_Status *statuses = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    is_master = my_rank == 0;   // judge is_master
    is_parall = num_procs > 1;
    prev_rank = is_master ? num_procs-1 : my_rank -1;
    next_rank = (my_rank + 1) % num_procs;
    
    #define pp(process) ((process) > my_rank ? (process) - 1 : (process))

    int current_iter = 1;

    if (argc < 3)
	{
		if (is_master)
		{
			usage("Too few arguments (2 required, %d provided).", argc - 1);
		}
		MPI_Finalize();
	    return 0;
	}

    m = atoi(argv[1]);  // 列数
	n = atoi(argv[2]);

    if (n % num_procs != 0)
	{
		if (is_master)
		{
			usage("n, the columns of matrix also argv[2], should divides num of process.");
		}
		MPI_Finalize();
	    return 0;
	}

	// Init
    vectors_per_proc = n / num_procs;
    iter_count = (num_procs + 1) / 2;
	max_columns = iter_count * vectors_per_proc - 1;  //?

    block_left = create_matrix(vectors_per_proc, m);
	block_right = create_matrix(vectors_per_proc, m);

    requests = (MPI_Request*)malloc((num_procs - 1) * sizeof(MPI_Request));
	statuses = (MPI_Status*)malloc((num_procs - 1) * sizeof(MPI_Status));


    for(i = 0; i < num_procs - 1; i++)	// except master process, number is num_procs -1
	{
		requests[i] = MPI_REQUEST_NULL; // Init request
	}

    if (is_master){
        matrix = create_matrix(n,m);

        for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				matrix[i][j] = (float)((double)rand() / RAND_MAX * 10.0);		// Randomly generate a matrix of numbers from 0 to 100
			}
		}
        results_nbs = n * (n-1) / 2;

        if (is_parall){ // 需要传递信息
            result_matrix = create_triangle_matrix(n - 1, n - 1);	// 创建结果三角矩阵
            memcpy(block_left[0], matrix[0], vectors_per_proc * m * sizeof(float));   // 给master
            // send upper block
            for (i = 1; i < num_procs; i++)
			{
                // int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm, MPI_Request *request)
				MPI_Isend(matrix[i * vectors_per_proc], vectors_per_proc * m, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &requests[i-1]);
			}
            // int MPI_Waitall(int count,MPI_Request *requests, MPI_Status *status)
            MPI_Waitall(num_procs - 1, requests, statuses);

            memcpy(block_right[0], matrix[vectors_per_proc], vectors_per_proc * m * sizeof(float));
			for (i = 1; i < num_procs; i++)
			{
				j = (i + 1) % num_procs;
				MPI_Isend(matrix[j * vectors_per_proc], vectors_per_proc * m, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &requests[i-1]);
			}
        }

    }else{
		// Receive initial left and right block
		// 接收master传输的信息
		MPI_Recv(block_left[0], vectors_per_proc * m, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[0]);
		MPI_Recv(block_right[0], vectors_per_proc * m, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[0]);
	}

    if (is_parall){ // 不区分节点
        proc_results_nbs = n * (n - 1) / 2 / num_procs;  // 每个进程计算个数
        proc_matrix = create_triangle_matrix( vectors_per_proc,max_columns);
    
        // 当前进程内部计算
        product_in_block(block_left, vectors_per_proc, m, proc_matrix);


        while (1)
		{
			// Calculate among left and right
			for(int i = 0; i < vectors_per_proc; i++)
			{
				for(int j = 0; j < vectors_per_proc; j++)
				{
					proc_matrix[i][j - i + vectors_per_proc * current_iter - 1] = product(block_left[i], block_right[j], m);
				}
			}

			current_iter++;
			if (current_iter < iter_count)
			{
				// Shift right blocks
				MPI_Wait(&requests[pp(prev_rank)], &statuses[pp(prev_rank)]);
				MPI_Isend(block_right[0], vectors_per_proc * m, MPI_FLOAT, prev_rank, 0, MPI_COMM_WORLD, &requests[pp(prev_rank)]);
				MPI_Recv(block_right[0], vectors_per_proc * m, MPI_FLOAT, next_rank, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[pp(next_rank)]);
			}
			else
			{
				break;
			}
		}

        // Merge results to master
		// 执行信息合并
		if (is_master)
		{
			printf("Merging results...\n");
			
			// Receive results and merge
			current_iter = 0;
			int normal_count = n - 1;
			while (1)
			{
				// Merge
				int current_max_columns = max_columns;
				for (i = 0; i < vectors_per_proc; i++)
				{
					// Normal order
					for (j = 0; j < normal_count && j < current_max_columns; j++)
					{
						result_matrix[i + current_iter * vectors_per_proc][j] = proc_matrix[i][j];
					}

					// Handle wrapped cells
					for (j = normal_count; j < current_max_columns; j++)
					{
						result_matrix[j - normal_count][n - 2 - j] = proc_matrix[i][j];
					}

					current_max_columns--;
					normal_count--;
				}

				current_iter++;
				if (current_iter < num_procs)
				{
					MPI_Recv(proc_matrix[0], proc_results_nbs, MPI_FLOAT, current_iter, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[pp(i)]);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			// Send results to master processor
			MPI_Wait(&requests[pp(0)], &statuses[pp(0)]);
			MPI_Send(proc_matrix[0], proc_results_nbs, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
		}
	}

}