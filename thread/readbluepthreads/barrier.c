
#include "barrier.h"

void barrier_init(barrier_t *barrier, int proc_count) {
    barrier->proc_count = proc_count;
    barrier->current = 0;
    barrier->phase = 0;
    // init mutex and cond
    pthread_mutex_init(&barrier->mutex, NULL);
    pthread_cond_init(&barrier->cond, NULL);
}

// destroy mutex and cond
void barrier_destroy(barrier_t *barrier) {
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);
}

void barrier_wait(barrier_t *barrier) {
    pthread_mutex_lock(&barrier->mutex);

    barrier->current++;     // once process into it, current+1
    if (barrier->current >= barrier->proc_count) {  // it means all process
        barrier->current = 0;
        barrier->phase++;
        pthread_cond_broadcast(&barrier->cond);
    } else {
        unsigned int phase = barrier->phase;    // signal
        do {
            pthread_cond_wait(&barrier->cond, &barrier->mutex); // wait other process
        } while (phase == barrier->phase);  // 
    }

    pthread_mutex_unlock(&barrier->mutex);
}
