#ifndef BLOCK_H__
#define BLOCK_H__

#include "barrier.h"

#define COLOR_SUFFICIENT -1

typedef struct{
    int red;
    int blue;
}result_t;  // store the result

typedef struct {
    int n, t, max_iters;
    int p;
    double c;
} parameters;   // store user defined parameters

typedef struct {
    barrier_t barrier;
    pthread_mutex_t mutex;

    int tiles_thres;    // Whether the tile responsible for the thread exceeds
    result_t *full_results;
} thread_sync;  // use barrier to thread sync

typedef struct {
    thread_sync *sync;
    parameters *params;

    int id;
    int **board;
    int start;
    int end;
} thread_block; //thread process block

#endif
