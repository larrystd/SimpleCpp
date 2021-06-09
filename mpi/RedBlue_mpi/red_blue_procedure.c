#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

#include <mpi.h>

/*
white = 0, red = 1, blue = 2,
red or blue just moved in = 3 and
red or blue (in the first row or column) just moved out = 4
*/

#define WHITE 0
#define RED 1
#define BLUE 2
#define IN 3
#define OUT 4

#define MASTER_RANK 0
#define SLAVE_FIRST_RANK 1


int empty_result = 0;
#define RESULT_UNIT_LEN 3
#define RESULT_EMPTY (&empty_result)
#define RESULT_COUNT(r) ((r)[0])
#define RESULT_INDEX(r, i) ((r)[(i) * RESULT_UNIT_LEN + 1])
#define RESULT_NOT_ENOUGH -1
#define RESULT_RED(r, i) ((r)[(i) * RESULT_UNIT_LEN + 1 + 1])
#define RESULT_BLUE(r, i) ((r)[(i) * RESULT_UNIT_LEN + 1 + 2])
#define RESULT_REQUIRED_LENGTH(count) ((count) * RESULT_UNIT_LEN + 1)
#define RESULT_LENGTH(r) RESULT_REQUIRED_LENGTH(RESULT_COUNT(r))

#define SYNC_OK 0
#define SYNC_STOP 1

#define iter_slave(i, n) for(i = SLAVE_FIRST_RANK; i < n; i++)


void print_usage(char const* const message, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, message);

	vfprintf(stderr, message, arg_ptr);

	va_end(arg_ptr);

	printf("\n");

	// TODO: print usage
}

int parse_argument(int is_master, int argc, char* argv[], int* n, int* t, float* c, int* max_iters)
{
	int i;
	int flags[4] = {0,0,0,0};
	char* arguments[] = {
		"n",
		"t",
		"c",
		"max_iters"
	};

	for (i = 1; i < argc - 1; i += 2)
	{
		if (strcmp(argv[i], "-n") == 0)
		{
			*n = atoi(argv[i + 1]);
			flags[0] = 1;
		}
		else if (strcmp(argv[i], "-t") == 0)
		{
			*t = atoi(argv[i + 1]);
			flags[1] = 1;
		}
		else if (strcmp(argv[i], "-c") == 0)
		{
			*c = (float)atof(argv[i + 1]);
			flags[2] = 1;
		}
		else if (strcmp(argv[i], "-max_iters") == 0)
		{
			*max_iters = atoi(argv[i + 1]);
			flags[3] = 1;
		}
		else
		{
			if (is_master)
			{
				print_usage("Unknown argument \"%s\"", argv[i]);
			}
			return 0;
		}
	}

	// Make sure all arguments are set
	for (i = 0; i < 4; i++)
	{
		if (!flags[i])
		{
			if (is_master)
			{
				print_usage("Argument \"%s\" not set!", arguments[i]);
			}
			return 0;
		}
	}

	return 1;
}


int** board_init(int n)
{
	int count = n * n;
	int* board_flat = malloc(sizeof(int) * count);
	int** board = malloc(sizeof(int*) * n);
	int i;

	// build 2d-array
	board[0] = board_flat;
	for (i = 1; i < n; i++)
	{
		board[i] = &board_flat[i * n];
	}

	// init board
	for (i = 0; i < count; i++)
	{
		// after that the board will be filled as 0 1 2 0 1 2 0 1 2 ...
		// so is roughly 1/3 cells in read, 1/3 in white and 1/3 in blue
		board_flat[i] = i % 3;
	}

	// then we shuffle the board to get a random order
	srand(time(NULL));
	if (count > 1)
	{
		for (i = 0; i < count - 1; i++)
		{
			int j = i + rand() / (RAND_MAX / (count - i) + 1);
			int t = board_flat[j];
			board_flat[j] = board_flat[i];
			board_flat[i] = t;
		}
	}

	return board;
}


/*
 * Create sub chessboard with two extra rows
 * with following structure:
 * 
 * -----------------------------------------
 * |          | 0 | 1 | 2 | ... | cols - 1 |
 * |----------+---+---+---+-----+----------|
 * |-1        | last row from prev process |
 * |----------+----------------------------|
 * | 0        |                            |
 * |----------+                            |
 * | 1        |                            |
 * |----------+                            |
 * | ...      |  rows for current process  |
 * |----------+                            |
 * | rows - 2 |                            |
 * |----------+                            |
 * | rows - 1 |                            |
 * |----------+----------------------------|
 * | rows     |first row from prev process |
 * -----------------------------------------
 */
int** create_sub_board(int rows, int cols)
{
	int count = (rows + 2) * cols;
	int* board_flat = malloc(sizeof(int) * count);
	int** board = malloc(sizeof(int*) * (rows + 2));
	int i;

	memset(board_flat, 0, sizeof(int) * count);

	// build 2d-array
	board[0] = board_flat;
	for (i = 1; i < rows + 2; i++)
	{
		board[i] = &board_flat[i * cols];
	}

	return &board[1];
}


void print_board(int** board, int row_count, int col_count, int include_overflow)
{
	int i, j;

	if (include_overflow)
	{
		for (j = 0; j < col_count; j++)
		{
			printf(" %d ", board[-1][j]);
		}
		printf("\n");

		for (j = 0; j < col_count; j++)
		{
			printf("---");
		}
		printf("\n");
	}

	for (i = 0; i < row_count; i++)
	{
		for (j = 0; j < col_count; j++)
		{
			printf(" %d ", board[i][j]);
		}
		printf("\n");
	}

	if (include_overflow)
	{
		for (j = 0; j < col_count; j++)
		{
			printf("---");
		}
		printf("\n");

		for (j = 0; j < col_count; j++)
		{
			printf(" %d ", board[row_count][j]);
		}
		printf("\n");
	}
	printf("\n");
}


/*
 * Calculate how may rows should process X takes
 */
int row_count_for_process(int process_count, int row_count, int tile_row, int current_id)
{
	int tile_count = row_count / tile_row;
	int remain = tile_count % process_count;
	int base = tile_count / process_count;

	int row = base * tile_row;

	if (current_id < remain)
	{
		row += tile_row;
	}

	return row;
}


void do_red(int** sub_board, int row_count, int col_count)
{
	int i, j;

	for (i = 0; i < row_count; i++)
	{
		if (sub_board[i][0] == RED && sub_board[i][1] == WHITE)
		{
			sub_board[i][0] = OUT;
			sub_board[i][1] = IN;
		}

		for (j = 1; j < col_count; j++)
		{
			int right = (j + 1) % col_count;

			if (sub_board[i][j] == RED && sub_board[i][right] == WHITE)
			{
				sub_board[i][j] = WHITE;
				sub_board[i][right] = IN;
			}
			else if (sub_board[i][j] == IN)
			{
				sub_board[i][j] = RED;
			}
		}
		if (sub_board[i][0] == IN)
		{
			sub_board[i][0] = RED;
		}
		else if (sub_board[i][0] == OUT)
		{
			sub_board[i][0] = WHITE;
		}
	}
}


void do_blue(int** sub_board, int row_count, int col_count)
{
	int i, j;

	for (j = 0; j < col_count; j++)
	{
		if (sub_board[-1][j] == BLUE && sub_board[0][j] == WHITE)
		{
			sub_board[0][j] = IN;
		}

		for (i = 0; i < row_count; i++)
		{
			int below = i + 1;

			if (sub_board[i][j] == BLUE && sub_board[below][j] == WHITE)
			{
				sub_board[i][j] = WHITE;
				sub_board[below][j] = IN;
			}
			else if (sub_board[i][j] == IN)
			{
				sub_board[i][j] = BLUE;
			}
		}
	}
}


/*
 * The first element of the return value is the tile count N,
 * then the following N elements are the tile (index, color) pair.
 */
int* count_tiles(int** sub_board, int row_count, int col_count, int tile_row, int c)
{
	int i, j, k, l;
	int tile_index = 0;
	int max_tile_count = row_count * col_count / tile_row / tile_row;
	int* re = RESULT_EMPTY;

	for (i = 0; i < row_count; i += tile_row)
	{
		for (j = 0; j < col_count; j += tile_row)
		{
			int red = 0, blue = 0;

			for (k = 0; k < tile_row; k++)
			{
				for (l = 0; l < tile_row; l++)
				{
					switch (sub_board[i + k][j + l])
					{
					case RED:
						red++;
						break;
					case BLUE:
						blue++;
						break;
					}
				}
			}

			if(red < c)
			{
				red = RESULT_NOT_ENOUGH;
			}

			if(blue < c)
			{
				blue = RESULT_NOT_ENOUGH;
			}

			if (red != RESULT_NOT_ENOUGH || blue != RESULT_NOT_ENOUGH)
			{
				if (re == RESULT_EMPTY)
				{
					re = malloc(RESULT_REQUIRED_LENGTH(max_tile_count) * sizeof(int));
					RESULT_COUNT(re) = 0;
				}

				RESULT_INDEX(re, RESULT_COUNT(re)) = tile_index;
				RESULT_RED(re, RESULT_COUNT(re)) = red;
				RESULT_BLUE(re, RESULT_COUNT(re)) = blue;
				RESULT_COUNT(re)++;
			}

			tile_index++;
		}
	}

	return re;
}


void merge_result(int* current_result, int offset, int* full_result)
{
	int* re;
	int i;

	if (RESULT_COUNT(current_result) <= 0)
	{
		return;
	}

	for(i = 0; i < RESULT_COUNT(current_result); i++)
	{
		RESULT_INDEX(full_result, RESULT_COUNT(full_result)) = RESULT_INDEX(current_result, i) + offset;
		RESULT_RED(full_result, RESULT_COUNT(full_result)) = RESULT_RED(current_result, i);
		RESULT_BLUE(full_result, RESULT_COUNT(full_result)) = RESULT_BLUE(current_result, i);
		RESULT_COUNT(full_result)++;
	}
}


void print_result(int* result, int t)
{
	int i;
	const float tile_block = t * t;

	if (RESULT_COUNT(result) > 0)
	{
		printf("Found %d tile(s):\n", RESULT_COUNT(result));
		for (i = 0; i < RESULT_COUNT(result); i++)
		{
			printf("Tile No.%d, color: ", RESULT_INDEX(result, i));
			if(RESULT_RED(result, i) != RESULT_NOT_ENOUGH)
			{
				printf("red(%.2f%%) ", RESULT_RED(result, i) / tile_block * 100);
			}
			if (RESULT_BLUE(result, i) != RESULT_NOT_ENOUGH)
			{
				printf("blue(%.2f%%) ", RESULT_BLUE(result, i) / tile_block * 100);
			}

			printf("\n");
		}
	}
	else
	{
		printf("max_iters exceed! No result found!\n");
	}
}


void sequential_computation(int** board_orig, int n, int t, int c, int max_iters)
{
	int** board = create_sub_board(n, n);
	int iter_count = 0;
	int* result = RESULT_EMPTY;

	memcpy(board[0], board_orig[0], sizeof(int) * n * n);

	while(iter_count++ <= max_iters && RESULT_COUNT(result) <= 0)
	{
		do_red(board, n, n);

		memcpy(board[-1], board[n - 1], sizeof(int) * n);
		memcpy(board[n], board[0], sizeof(int) * n);

		do_blue(board, n, n);

		result = count_tiles(board, n, n, t, c);
	}

	print_result(result, t);
}


int main(int argc, char* argv[])
{
	int my_id, num_procs, prev_id, next_id;
	int is_master;

	// User defined parameters
	int n, t, max_iters;
	float c;
	int max_color_count;

	int** full_chessboard; // for master process only, full_chessboard[row][col]
	int** my_rows; // the rows for current process, my_rows[row][col]
	int row_count; // row count for current process

	int max_tile_count_in_process;
	int* slave_result = RESULT_EMPTY; // the result from slave for one single round
	int* full_result = RESULT_EMPTY; // the result from all processes (include itself) for one single round

	int i, j;
	int iter_count = 0;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

	is_master = my_id == MASTER_RANK;
	prev_id = is_master ? num_procs - 1 : my_id - 1;
	next_id = (my_id + 1) % num_procs;

	// First parse arguments
	if (!parse_argument(is_master, argc, argv, &n, &t, &c, &max_iters))
	{
		goto _exit;
	}

#define tile_count(process) row_count_for_process((num_procs), n, t, process) * n / t / t

	max_color_count = (int)ceilf(t * t * c / 100.0f);
	max_tile_count_in_process = tile_count(MASTER_RANK);

	if (is_master)
	{
		slave_result = malloc(sizeof(int) * RESULT_REQUIRED_LENGTH(max_tile_count_in_process));
		full_result = malloc(sizeof(int) * RESULT_REQUIRED_LENGTH(n * n / t / t));
		RESULT_COUNT(full_result) = 0;
	}

	// Init some process-related vars
	row_count = row_count_for_process(num_procs, n, t, my_id);
	my_rows = create_sub_board(row_count, n);

	// Initialize the chessboard
	if (is_master)
	{
		// The master process take charge of generating chessboard
		// and send them to other process(es).

		full_chessboard = board_init(n);

		printf("Original chessboard:\n");
		print_board(full_chessboard, n, n, 0);

		// First allocate rows for itself
		for (i = 0; i < row_count; i++)
		{
			memcpy(my_rows[i], full_chessboard[i], sizeof(int) * n);
		}

		// Next, send rows to slave processes
		iter_slave(j, num_procs)
		{
			int k = row_count_for_process(num_procs, n, t, j);

			MPI_Send(full_chessboard[i], k * n, MPI_INT, j, 0, MPI_COMM_WORLD);

			i += k;
		}
	}
	else
	{
		// Slave processes receive rows from master process.
		MPI_Recv(my_rows[0], row_count * n, MPI_INT, MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	}

	printf("Chessboard at process %d:\n", my_id);
	print_board(my_rows, row_count, n, 0);

	// Now the step starts:
	while (iter_count++ <= max_iters)
	{
		int* tiles_finish;

		// First, move red blocks
		do_red(my_rows, row_count, n);

		printf("Chessboard at process %d after red move:\n", my_id);
		print_board(my_rows, row_count, n, 0);

		// Then we need to sync with all processes
		// Thanks to the genius MPI_Sendrecv() so we won't get a dead lock!
		MPI_Sendrecv(my_rows[0], n, MPI_INT, prev_id, 0, my_rows[row_count], n, MPI_INT, next_id, 0, MPI_COMM_WORLD, &status);
		MPI_Sendrecv(my_rows[row_count - 1], n, MPI_INT, next_id, 0, my_rows[-1], n, MPI_INT, prev_id, 0, MPI_COMM_WORLD, &status);

		printf("Chessboard at process %d after row exchange:\n", my_id);
		print_board(my_rows, row_count, n, 1);

		// Next we move blue blocks
		do_blue(my_rows, row_count, n);

		printf("Chessboard at process %d after blue move:\n", my_id);
		print_board(my_rows, row_count, n, 0);

		// Count the number of red and blue in each tile and check if the computation can be terminated
		tiles_finish = count_tiles(my_rows, row_count, n, t, max_color_count);

		if (is_master)
		{
			int final_result = SYNC_OK;
			int index_offset = 0;
			merge_result(tiles_finish, index_offset, full_result);
			index_offset += tile_count(MASTER_RANK);

			// Read result of this round from slaves
			iter_slave(i, num_procs)
			{
				MPI_Recv(slave_result, RESULT_REQUIRED_LENGTH(max_tile_count_in_process), MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

				merge_result(slave_result, index_offset, full_result);

				index_offset += tile_count(i);
			}

			// Notify slaves if they need to exit
			if (RESULT_COUNT(full_result) > 0)
			{
				// Got result! Exit guys!
				final_result = SYNC_STOP;
			}

			MPI_Bcast(&final_result, 1, MPI_INT, MASTER_RANK, MPI_COMM_WORLD);

			if (final_result == SYNC_STOP)
			{
				break;
			}
		}
		else
		{
			int round_notify;

			// Send result of this round to master
			MPI_Send(tiles_finish, RESULT_LENGTH(tiles_finish), MPI_INT, MASTER_RANK, 0, MPI_COMM_WORLD);

			// Wait for notify from master
			MPI_Bcast(&round_notify, 1, MPI_INT, MASTER_RANK, MPI_COMM_WORLD);

			if (round_notify == SYNC_STOP)
			{
				// master told you to stop!
				break;
			}
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);

	if (is_master)
	{
		print_result(full_result, t);

		// perform a sequential computation
		sequential_computation(full_chessboard, n, t, max_color_count, max_iters);
	}

_exit:
	MPI_Finalize();
	return 0;
}
