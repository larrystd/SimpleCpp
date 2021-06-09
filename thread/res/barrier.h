//
// Created by Noisyfox on 2017/5/17.
// Simple Barrier implementation
//

#ifndef RED_BLUE_BARRIER_H
#define RED_BLUE_BARRIER_H

#include <pthread.h>

typedef struct {
    int count;
    int current;
    unsigned int phase;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} barrier_t;

void barrier_init(barrier_t *barrier, int count);

void barrier_destroy(barrier_t *barrier);

void barrier_wait(barrier_t *barrier);

#endif //RED_BLUE_BARRIER_H
