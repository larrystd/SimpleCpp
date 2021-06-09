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
create a matrix, first create an array of length n*m, and then use a two-dimensional matrix pointer to point to the beginning
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
    for (i = 0; i < rows; i++)
	{
		for (j = i; j < rows; j++)
		{
			results[i][j - i] = product(block[i], block[j], m);
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

int pp(int process, int myrank){
	if (process > myrank)
		return process-1;
	else
		return process;
}

int main(int argc, char** argv)
{
	int my_rank, num_procs, prev_rank, next_rank; // rank
	int *indices = NULL;
	int is_master, has_parallism;
	int m, n;

	float** full_matrix = NULL;
	int rows_per_block, max_columns, iter_count;

	int i, j;
    int count = 0;

    MPI_Request *requests = NULL;
	MPI_Status *statuses = NULL;
	float** block_left = NULL;
	float** block_right = NULL;

	int final_result_count = 0;	// Upper triangular matrix, number of elements
	float** final_result = NULL; // // the triangular matrix as the result
	float** final_result_serial = NULL;

	int proc_result_nbs = 0;	// // The amount calculation allocated by each process
	float** proc_result = NULL; // Part of the result triangular matrix calculated by each process

	int current_iter = 1;

	srand(time(NULL));

	// Init MPI and process id
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	is_master = my_rank == 0;		// judge is_master
	has_parallism = num_procs > 1;
	prev_rank = is_master ? num_procs - 1 : my_rank - 1;
	next_rank = (my_rank + 1) % num_procs;

	if (num_procs % 2 != 1)
	{
		if (is_master)
		{
			usage("Process number must be odd!");
		}
		MPI_Finalize();
	    return 0;
	}
	// Read user input
	if (argc < 3)
	{
		if (is_master)
		{
			usage("Too few arguments (2 required, %d provided).", argc - 1);
		}
		MPI_Finalize();
	    return 0;
	}

	m = atoi(argv[1]);
	n = atoi(argv[2]);

	if (n % num_procs != 0)
	{
		if (is_master)
		{
			usage("Illegal arguments.");
		}
		MPI_Finalize();
	    return 0;
	}
	rows_per_block = n / num_procs;
	iter_count = (num_procs + 1) / 2;
	max_columns = iter_count * rows_per_block;

	block_left = create_matrix(rows_per_block, m);
	block_right = create_matrix(rows_per_block, m);

	requests = (MPI_Request*)malloc((num_procs - 1) * sizeof(MPI_Request));
	statuses = (MPI_Status*)malloc((num_procs - 1) * sizeof(MPI_Status));
	indices = (int*)malloc((num_procs - 1) * sizeof(int));

	for(i = 0; i < num_procs - 1; i++)
	{
		requests[i] = MPI_REQUEST_NULL;
	}


	// Below, information transfer, master transfers information,

	if (is_master){
		// Generate matrix
		full_matrix = create_matrix(n, m);
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				//full_matrix[i][j] = (float)((double)rand());	
                full_matrix[i][j] = (float)(i+1);		// init matrix
			}
		}

		final_result_count = n * (n + 1) / 2;

		if (has_parallism)		// number of process > 1
		{
			final_result = create_triangle_matrix(n , n );	// Create a triangular matrix

			/*Send left blocks to other processors
			void *memcpy(void *dest, const void *src, size_t n)
			Assign the first row of matrix to block_left[0]
			Only the address and len are needed in the c language to give continuous space
            
			*/
			memcpy(block_left[0], full_matrix[0], rows_per_block * m * sizeof(float));	// master block left
			// master send message to other process
            for (i = 1; i < num_procs; i++)
			{
				MPI_Isend(full_matrix[i * rows_per_block], rows_per_block * m, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &requests[pp(i,my_rank)]);
			}
			MPI_Waitall(num_procs - 1, requests, statuses);

			// Send right blocks to other processors
			memcpy(block_right[0], full_matrix[rows_per_block], rows_per_block * m * sizeof(float));
			for (i = 1; i < num_procs; i++)
			{
				j = (i + 1) % num_procs;
				MPI_Isend(full_matrix[j * rows_per_block], rows_per_block * m, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &requests[pp(i,my_rank)]);
			}
		}
	}
	else{
		// Receive initial left and right block from master
		MPI_Recv(block_left[0], rows_per_block * m, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[pp(0,my_rank)]);
		MPI_Recv(block_right[0], rows_per_block * m, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[pp(0,my_rank)]);
	}

	// Parallel computing, no distinction
	if (has_parallism){

		if (is_master){
			printf("Performing parallism computation...\n");
		}
		proc_result_nbs = n * (n + 1) / 2 / num_procs;
		proc_result = create_triangle_matrix(max_columns,rows_per_block);

		// First calculate the products inside left blocks
		product_in_block(block_left, rows_per_block, m, proc_result);

		// Here starts the computation iters
		while (1)
		{
			// Calculate among left and right
			for(i = 0; i < rows_per_block; i++)
			{
				for(j = 0; j < rows_per_block; j++)
				{
					proc_result[i][j - i + rows_per_block * current_iter] = product(block_left[i], block_right[j], m);
				}
			}
			current_iter++;
            // iter_count = (num_procs + 1) / 2;
            // left unchanged, right multiplied by it
			if (current_iter < iter_count)
			{
				// maybe need other process transfer right blocks
				MPI_Wait(&requests[pp(prev_rank,my_rank)], &statuses[pp(prev_rank,my_rank)]);
				MPI_Isend(block_right[0], rows_per_block * m, MPI_FLOAT, prev_rank, 0, MPI_COMM_WORLD, &requests[pp(prev_rank,my_rank)]);
				MPI_Recv(block_right[0], rows_per_block * m, MPI_FLOAT, next_rank, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[pp(next_rank,my_rank)]);
			}
			else
			{
				break;
			}
		}
		// Merge results to master
		if (is_master)
		{
			printf("Done!\n Merging results...\n");
			
			// Receive results and merge
			current_iter = 0;
			int normal_count = n;
			while (1)
			{
				// Merge
				int current_max_columns = max_columns;
				for (i = 0; i < rows_per_block; i++)
				{
					// Normal order
					for (j = 0; j < normal_count && j < current_max_columns; j++)
					{
						final_result[i + current_iter * rows_per_block][j] = proc_result[i][j];
					}

					// Handle wrapped cells
					for (j = normal_count; j < current_max_columns; j++)
					{
						final_result[j - normal_count][n - j] = proc_result[i][j];
					}

					current_max_columns--;
					normal_count--;
				}

				current_iter++;
				if (current_iter < num_procs)
				{
					MPI_Recv(proc_result[0], proc_result_nbs, MPI_FLOAT, current_iter, MPI_ANY_TAG, MPI_COMM_WORLD, &statuses[pp(i,my_rank)]);  // 接收消息
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			// Send results to master
			MPI_Wait(&requests[pp(0,my_rank)], &statuses[pp(0,my_rank)]);
			MPI_Send(proc_result[0], proc_result_nbs, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
		}
	}

	if (is_master)
	{
		if (has_parallism)
		{
			printf("Done.\n");
			// Print out results
			printf("Results of parallism computation:\n");
			print_results(final_result, n, n );

			printf("\n");
		}

		// Do serial computation

		printf("Performing serial computation...\n");
		final_result_serial = create_triangle_matrix(n , n);
		product_in_block(full_matrix, n, m, final_result_serial);
		printf("Done.\n");

		printf("Results from serial computation:\n");
		// Print out results from serial computation
		print_results(final_result_serial, n, n);

		if (has_parallism)
		{
			// Compare results
			printf("\n");
			printf("Checking results...\n");

			int all_match = 1;
			for (i = 0; i < final_result_count; i++)
			{
				if (final_result_serial[0][i] != final_result[0][i])
				{
					all_match = 0;
					break;
				}
			}

			if (all_match)
			{
				printf("Parallel and serial computation are consistent!\n");
			}
			else
			{
				printf("Not consistent!!\n");
			}
		}
	}
    return 0;
}
