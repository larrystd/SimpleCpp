#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include "red_blue.h"

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

void usage(char const *const message, ...) {
    va_list arg_ptr;
    va_start(arg_ptr, message);

    vfprintf(stderr, message, arg_ptr);

    va_end(arg_ptr);

    fprintf(stderr, "\n");

    fprintf(stderr, "Please run the application in the following format:\n");
    fprintf(stderr, "red_blue [thread num] [grid size] [tile size] [threshold (float)] [maximum iterations]\n");
    fprintf(stderr, "Required: [grid size] %% [tile size] = 0; 1 <= [thread num] <= [grid size] / [tile size]\n");
    fprintf(stderr, "\n");
}

int **create_board(int n) {
    int count = n * n;
    int *board_flat = malloc(sizeof(int) * count);
    int **board = malloc(sizeof(int *) * n);
    int i;

    // build 2d-array
    board[0] = board_flat;
    for (i = 1; i < n; i++) {
        board[i] = &board_flat[i * n];
    }

    return board;
}

int **board_init(int n) {
    int count = n * n;
    int i;
    int **board = create_board(n);

    // init board
    for (i = 0; i < count; i++) {
        // after that the board will be filled as 0 1 2 0 1 2 0 1 2 ...
        // so is roughly 1/3 cells in read, 1/3 in white and 1/3 in blue
        board[0][i] = i % 3;
    }

    // then we shuffle the board to get a random order
    srand(time(NULL));
    if (count > 1) {
        for (i = 0; i < count - 1; i++) {
            int j = i + rand() / (RAND_MAX / (count - i) + 1);
            int t = board[0][j];
            board[0][j] = board[0][i];
            board[0][i] = t;
        }
    }

    return board;
}


/*
 * Calculate how may rows should process X takes
 */
int row_count_for_process(int process_count, int row_count, int tile_row, int current_id) {
    int tile_count = row_count / tile_row;
    int remain = tile_count % process_count;
    int base = tile_count / process_count;

    int row = base * tile_row;

    if (current_id < remain) {
        row += tile_row;
    }

    return row;
}

void do_red(int **board, int row_start, int row_end, int n) {
    for (int i = row_start; i <= row_end; i++) {
        if (board[i][0] == RED && board[i][1] == WHITE) {
            board[i][0] = OUT;
            board[i][1] = IN;
        }

        for (int j = 1; j < n; j++) {
            int right = (j + 1) % n;

            if (board[i][j] == RED && board[i][right] == WHITE) {
                board[i][j] = WHITE;
                board[i][right] = IN;
            } else if (board[i][j] == IN) {
                board[i][j] = RED;
            }
        }
        if (board[i][0] == IN) {
            board[i][0] = RED;
        } else if (board[i][0] == OUT) {
            board[i][0] = WHITE;
        }
    }
}

void do_blue(int **board, int col_start, int col_end, int n) {
    for (int j = col_start; j <= col_end; j++) {
        if (board[0][j] == BLUE && board[1][j] == WHITE) {
            board[0][j] = OUT;
            board[1][j] = IN;
        }

        for (int i = 1; i < n; i++) {
            int below = (i + 1) % n;

            if (board[i][j] == BLUE && board[below][j] == WHITE) {
                board[i][j] = WHITE;
                board[below][j] = IN;
            } else if (board[i][j] == IN) {
                board[i][j] = BLUE;
            }
        }
        if (board[0][j] == IN) {
            board[0][j] = BLUE;
        } else if (board[0][j] == OUT) {
            board[0][j] = WHITE;
        }
    }
}


int
count_tiles(int **board, int col_start, int col_end, int row_count, int tile_row, double threshold, result_t *result) {
    double c = threshold * tile_row * tile_row;
    int result_count = 0;
    int start_index = col_start / tile_row;
    int tile_per_row = row_count / tile_row;

    for (int i = 0; i < row_count; i += tile_row) {
        int tile_index = start_index + i / tile_row * tile_per_row;

        for (int j = col_start; j <= col_end; j += tile_row) {
            int red = 0, blue = 0;

            for (int k = 0; k < tile_row; k++) {
                for (int l = 0; l < tile_row; l++) {
                    switch (board[i + k][j + l]) {
                        case RED:
                            red++;
                            break;
                        case BLUE:
                            blue++;
                            break;
                    }
                }
            }

            if (red < c) {
                red = RESULT_COLOR_INSUFFICIENT;
            }

            if (blue < c) {
                blue = RESULT_COLOR_INSUFFICIENT;
            }

            if (red != RESULT_COLOR_INSUFFICIENT || blue != RESULT_COLOR_INSUFFICIENT) {
                result[tile_index].red = red;
                result[tile_index].blue = blue;

                result_count++;
            }

            tile_index++;
        }
    }

    return result_count;
}

void *process_thread(void *arg) {
    thread_context *ctx = (thread_context *) arg;
    parameters *params = ctx->params;
    thread_sync *sync = ctx->sync;

    int n = params->n;
    int t = params->t;
    int max_iters = params->max_iters;
    double c = params->c;

    int **board = ctx->board;
    int start = ctx->start;
    int end = ctx->end;

    int iter_count = 0;
    do {
        do_red(board, start, end, n);
        barrier_wait(&sync->barrier);
        do_blue(board, start, end, n);

        int result_count = count_tiles(board, start, end, n, t, c, sync->full_results); // Calculate results

        pthread_mutex_lock(&sync->mutex);
        sync->result_count += result_count; // Merge result
        pthread_mutex_unlock(&sync->mutex);
        barrier_wait(&sync->barrier);
    } while (iter_count++ <= max_iters && sync->result_count == 0);

    return NULL;
}


void print_results(result_t *results, int total, int t) {
    const float tile_block = t * t;

    int has_result = 0;

    for (int i = 0; i < total; i++) {
        int red = results[i].red;
        int blue = results[i].blue;

        if (red != RESULT_COLOR_INSUFFICIENT || blue != RESULT_COLOR_INSUFFICIENT) {
            has_result = 1;

            printf("Tile No.%d, color: ", i);

            if (red != RESULT_COLOR_INSUFFICIENT) {
                printf("red(%.2f%%) ", red / tile_block * 100);
            }

            if (blue != RESULT_COLOR_INSUFFICIENT) {
                printf("blue(%.2f%%) ", blue / tile_block * 100);
            }

            printf("\n");
        }
    }

    if (!has_result) {
        printf("max_iters exceed! No result found!\n");
    }
}


int main(int argc, char *argv[]) {
    parameters params;

    // Read user input
    if (argc < 6) {
        usage("Too few arguments (5 required, %d provided).", argc - 1);
        goto _exit;
    }

    params.p = atoi(argv[1]);
    params.n = atoi(argv[2]);
    params.t = atoi(argv[3]);
    params.c = atof(argv[4]);
    params.max_iters = atoi(argv[5]);

    if (params.n % params.t != 0) {
        usage("Illegal arguments: [grid size] %% [tile size] != 0");
        goto _exit;
    }

    if (params.p < 1) {
        usage("Illegal arguments: [thread num] < 1");
        goto _exit;
    }

    if (params.p > params.n / params.t) {
        usage("Illegal arguments: [thread num] > [grid size] / [tile size]");
        goto _exit;
    }

    int **board = board_init(params.n); // Create a random board

    int tile_count = params.n * params.n / params.t / params.t;

    result_t *full_results_paral = NULL;

    if (params.p > 1) {
        // Multi-threading computation
        int **board_copy = create_board(params.n);
        memcpy(board_copy[0], board[0], params.n * params.n * sizeof(int));

        // Allocate async context
        thread_sync sync;
        thread_context *context = malloc(params.p * sizeof(thread_context));
        pthread_t *threads = malloc((params.p - 1) * sizeof(pthread_t));
        full_results_paral = malloc(tile_count * sizeof(result_t));
        for (int i = 0; i < tile_count; i++) {
            full_results_paral[i].red = RESULT_COLOR_INSUFFICIENT;
            full_results_paral[i].blue = RESULT_COLOR_INSUFFICIENT;
        }
        sync.result_count = 0;
        sync.full_results = full_results_paral;

        // Init thread contexts
        barrier_init(&sync.barrier, params.p);
        pthread_mutex_init(&sync.mutex, NULL);
        int rp = 0;
        for (int i = 0; i < params.p; i++) {
            thread_context *ctx = &context[i];
            ctx->sync = &sync;
            ctx->params = &params;
            ctx->board = board_copy;
            ctx->id = i;
            ctx->start = rp;
            rp += row_count_for_process(params.p, params.n, params.t, i);
            ctx->end = rp - 1;
        }

        // Start threads
        for (int i = 1; i < params.p; i++) {
            pthread_create(&threads[i - 1], NULL, process_thread, &context[i]);
        }
        process_thread(&context[0]); // This thread runs as t0

        // Wait for all thread exit
        for (int i = 0; i < params.p - 1; i++) {
            pthread_join(threads[i], NULL);
        }

        // Output results from full_results_paral
        printf("Results from parallism computation:\n");
        print_results(full_results_paral, tile_count, params.t);
        printf("\n");

        // Release data
        free(context);
        free(threads);
        free(board_copy);
        barrier_destroy(&sync.barrier);
        pthread_mutex_destroy(&sync.mutex);
    }

    // Serial computation
    result_t *full_results_seq = malloc(tile_count * sizeof(result_t));
    for (int i = 0; i < tile_count; i++) {
        full_results_seq[i].red = RESULT_COLOR_INSUFFICIENT;
        full_results_seq[i].blue = RESULT_COLOR_INSUFFICIENT;
    }

    int iter_count = 0;
    while (iter_count++ <= params.max_iters) {
        do_red(board, 0, params.n - 1, params.n);
        do_blue(board, 0, params.n - 1, params.n);

        // Calculate results
        if (count_tiles(board, 0, params.n - 1, params.n, params.t, params.c, full_results_seq) > 0) {
            break;
        }
    }
    printf("Results from serial computation:\n");
    print_results(full_results_seq, tile_count, params.t);

    if (full_results_paral) {
        // Compare results
        printf("\n");
        printf("Checking results...\n");
        int diff = 0;
        for (int i = 0; i < tile_count; i++) {
            if (full_results_seq[i].red != full_results_paral[i].red ||
                full_results_seq[i].blue != full_results_paral[i].blue) {

                diff = 1;

                printf("Tile %d is different!\n", i);
            }
        }
        if (!diff) {
            printf("All correct!\n");
        }

        free(full_results_paral);
    }

    free(board);
    free(full_results_seq);

    _exit:
    return 0;
}
