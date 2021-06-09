//
// Created by Noisyfox on 2017/5/17.
// Simple Barrier implementation
//
#include "barrier.h"

void barrier_init(barrier_t *barrier, int count) {
    barrier->count = count;
    barrier->current = 0;
    barrier->phase = 0;

    pthread_mutex_init(&barrier->mutex, NULL);
    pthread_cond_init(&barrier->cond, NULL);
}

void barrier_destroy(barrier_t *barrier) {
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);
}

void barrier_wait(barrier_t *barrier) {
    pthread_mutex_lock(&barrier->mutex);

    barrier->current++;
    if (barrier->current >= barrier->count) {
        barrier->phase++;
        barrier->current = 0;
        pthread_cond_broadcast(&barrier->cond);
    } else {
        unsigned int phase = barrier->phase;
        do {
            pthread_cond_wait(&barrier->cond, &barrier->mutex);
        } while (phase == barrier->phase);  // 直到执行完这一轮
    }

    pthread_mutex_unlock(&barrier->mutex);
}
