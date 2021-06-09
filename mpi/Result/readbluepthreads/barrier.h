
// Simple Barrier implementation

#ifndef BARRIER_H__
#define BARRIER_H__

#include <pthread.h>

typedef struct {
    int proc_count; // process number
    int current;    // when current>count, it mean collection thread
    unsigned int phase;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} barrier_t;

void barrier_init(barrier_t *barrier, int proc_count);

void barrier_destroy(barrier_t *barrier);

void barrier_wait(barrier_t *barrier);  // 

#endif //BARRIER_H__
