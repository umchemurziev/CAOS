#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

enum {
    NUM_OPS = 1000000,
    NUM_THREADS = 3,
    NUM_DELTA = 100
};

volatile double array[NUM_THREADS];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* func (void* idx) {
    int index = *(int*)idx;
    //printf("%d\n", index);
    for (int i = 0; i < NUM_OPS; i++) {
        pthread_mutex_lock(&m);
        array[index] += (double)((index+1) * NUM_DELTA);
        array[(index + 1) % NUM_THREADS] -= (double)((index + 1) * NUM_DELTA + 1);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() {
    pthread_t thread_id[NUM_THREADS];
    int indexes[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        indexes[i] = i;
        pthread_create(&thread_id[i], NULL, func, &indexes[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(thread_id[i], NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%.10g\n", array[i]);
    }
    return 0;
}

// Решение взято с семинара
