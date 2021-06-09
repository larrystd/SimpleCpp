#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

void usage(char const* const message, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, message);

	vfprintf(stderr, message, arg_ptr);

	va_end(arg_ptr);

	fprintf(stderr, "\n");

	fprintf(stderr, "Please run the application in the following format:\n");
	fprintf(stderr, "mpirun -np [proc num] inner_product [M] [N]\n");
	fprintf(stderr, "Required: [N] %% [proc num] = 0; [proc num] %% 2 = 1\n");
	fprintf(stderr, "\n");
}

/*
 * Create a matrix with n rows and m columns
 实际是将n*m的数组重新整理成矩阵
 */
float** create_matrix(int n, int m)
{
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

// 创建一个三角矩阵
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

// 求解上三角矩阵
void product_in_block(float** block, int rows, int m, float** results)
{
	int i, j;

	for (i = 0; i < rows - 1; i++)
	{
		for (j = i + 1; j < rows; j++)
		{
			results[i][j - i - 1] = product(block[i], block[j], m);
		}
	}
}

void print_results(float** results, int max_columns, int rows)
{
	int i, j;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < max_columns; j++)
		{
			printf("%.2f ", results[i][j]);
		}
		max_columns--;
		printf("\n");
	}
}

int main(int argc, char** argv)
{
	int my_id, num_procs, prev_id, next_id;
	MPI_Request *requests = NULL;
	MPI_Status *statuses = NULL;
	int *indices = NULL;
	int count = 0;
	int is_master, has_parallism;
	int m, n;
	float** full_matrix = NULL;
	int rows_per_block, max_columns, iter_count;
	int i, j;
	float** block_left = NULL;
	float** block_right = NULL;
	int final_results_count = 0;
	float** final_results = NULL;
	float** final_results_serial = NULL;
	int processor_results_count = 0;
	float** processor_results = NULL;
	int current_iter = 1;

	srand(time(NULL));

	// Init MPI and process id
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

	is_master = my_id == 0;		// master
	has_parallism = num_procs > 1;
	prev_id = is_master ? num_procs - 1 : my_id - 1;
	next_id = (my_id + 1) % num_procs;

	if (num_procs % 2 != 1)
	{
		if (is_master)
		{
			usage("Process number must be odd!");
		}
		goto _exit;
	}

	// Read user input
	if (argc < 3)
	{
		if (is_master)
		{
			usage("Too few arguments (2 required, %d provided).", argc - 1);
		}
		goto _exit;
	}
	m = atoi(argv[1]);
	n = atoi(argv[2]);

	if (n % num_procs != 0)
	{
		if (is_master)
		{
			usage("Illegal arguments.");
		}
		goto _exit;
	}

	rows_per_block = n / num_procs;
	iter_count = (num_procs + 1) / 2;
	max_columns = iter_count * rows_per_block - 1;

	block_left = create_matrix(rows_per_block, m);
	block_right = create_matrix(rows_per_block, m);

	requests = (MPI_Request*)malloc((num_procs - 1) * sizeof(MPI_Request));
	statuses = (MPI_Status*)malloc((num_procs - 1) * sizeof(MPI_Status));
	indices = (int*)malloc((num_procs - 1) * sizeof(int));

	for(i = 0; i < num_procs - 1; i++)
	{
		requests[i] = MPI_REQUEST_NULL;
	}


	// 以下，信息传递，master传递信息，
#define pp(process) ((process) > my_id ? (process) - 1 : (process))

	if (is_master){
		// Generate matrix
		full_matrix = create_matrix(n, m);
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				//full_matrix[i][j] = (float)((double)rand() / RAND_MAX * 100.0);		// 随机生成矩阵
                full_matrix[i][j] = (float)(i+1);		// 随机生成矩阵
			}
		}

		final_results_count = n * (n - 1) / 2;

		if (has_parallism)		// number of process > 1
		{
			final_results = create_triangle_matrix(n - 1, n - 1);	// 创建一个三角矩阵

			// Send left blocks to other processors
			// void *memcpy(void *dest, const void *src, size_t n)
			// 第一行矩阵赋给block_left[0]
			// c语言中只需要地址和len就可以赋予连续的空间
            // 设置master
			memcpy(block_left[0], full_matrix[0], rows_per_block * m * sizeof(float));
			// 传输给其他进程
            for (i = 1; i < num_procs; i++)
			{
				MPI_Isend(full_matrix[i * rows_per_block], rows_per_block * m, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &requests[pp(i)]);
			}


			MPI_Waitall(num_procs - 1, requests, statuses);

			// Send right blocks to other processors
			memcpy(block_right[0], full_matrix[rows_per_block], rows_per_block * m * sizeof(float));
			for (i = 1; i < num_procs; i++)
			{
				j = (i + 1) % num_procs;
				MPI_Isend(full_matrix[j * rows_per_block], rows_per_block * m, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &requests[pp(i)]);
			}
		}
	}
	else{
		// Receive initial left and right block
		// 接收master传输的信息
		MPI_Recv(block_left[0], rows_per_block * m, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[pp(0)]);
		MPI_Recv(block_right[0], rows_per_block * m, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[pp(0)]);
	}

	// 接下来是计算，不区分master
	if (has_parallism)
	{
		if (is_master)
		{
			printf("Performing parallism computation...\n");
		}

		processor_results_count = n * (n - 1) / 2 / num_procs;
		processor_results = create_triangle_matrix(max_columns,rows_per_block);

		// First calculate the products inside left blocks
		product_in_block(block_left, rows_per_block, m, processor_results);

        printf("First Results from processor %d:\n", my_id);
		print_results(processor_results, max_columns, rows_per_block);
		printf("\n");
		// Here starts the computation iters
		while (1)
		{
			// Calculate among left and right
			for(i = 0; i < rows_per_block; i++)
			{
				for(j = 0; j < rows_per_block; j++)
				{
					processor_results[i][j - i + rows_per_block * current_iter - 1] = product(block_left[i], block_right[j], m);
				}
			}
            printf("%d Results from processor %d:\n",current_iter, my_id);
		    print_results(processor_results, max_columns, rows_per_block);
		    printf("\n");
			current_iter++;
            // iter_count = (num_procs + 1) / 2;
            // left不变，修改right
			if (current_iter < iter_count)
			{
				// Shift right blocks
				MPI_Wait(&requests[pp(prev_id)], &statuses[pp(prev_id)]);
				MPI_Isend(block_right[0], rows_per_block * m, MPI_FLOAT, prev_id, 0, MPI_COMM_WORLD, &requests[pp(prev_id)]);
				MPI_Recv(block_right[0], rows_per_block * m, MPI_FLOAT, next_id, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[pp(next_id)]);
			}
			else
			{
				break;
			}
		}
		printf("Results from processor %d:\n", my_id);
		print_results(processor_results, max_columns, rows_per_block);
		printf("\n");

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
				for (i = 0; i < rows_per_block; i++)
				{
					// Normal order
					for (j = 0; j < normal_count && j < current_max_columns; j++)
					{
						final_results[i + current_iter * rows_per_block][j] = processor_results[i][j];
					}

					// Handle wrapped cells
					for (j = normal_count; j < current_max_columns; j++)
					{
						final_results[j - normal_count][n - 2 - j] = processor_results[i][j];
					}

					current_max_columns--;
					normal_count--;
				}

				current_iter++;
				if (current_iter < num_procs)
				{
					MPI_Recv(processor_results[0], processor_results_count, MPI_FLOAT, current_iter, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[pp(i)]);
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
			MPI_Send(processor_results[0], processor_results_count, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
		}
	}

	if (is_master)
	{
		if (has_parallism)
		{
			printf("Done.\n");
			// Print out results
			printf("Results from parallism computation:\n");
			print_results(final_results, n - 1, n - 1);

			printf("\n");
		}

		// Do serial computation

		printf("Performing serial computation...\n");
		final_results_serial = create_triangle_matrix(n - 1, n - 1);
		product_in_block(full_matrix, n, m, final_results_serial);
		printf("Done.\n");

		printf("Results from serial computation:\n");
		// Print out results from serial computation
		print_results(final_results_serial, n - 1, n - 1);

		if (has_parallism)
		{
			// Compare results
			printf("\n");
			printf("Checking results...\n");

			int all_match = 1;
			for (i = 0; i < final_results_count; i++)
			{
				if (final_results_serial[0][i] != final_results[0][i])
				{
					all_match = 0;
					break;
				}
			}

			if (all_match)
			{
				printf("All correct!\n");
			}
			else
			{
				printf("Error!\n");
			}
		}
	}

_exit:
	MPI_Finalize();
	    return 0;
}
