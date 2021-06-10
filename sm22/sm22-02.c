#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

unsigned long long last_prime = 0;

int is_prime(unsigned long long n) {
    if (n == 1 || !(n % 2)) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }

    for (unsigned long long i = 3; i * i <= n; i += 2) {
        if (!(n % i)) {
            return 0;
        }
    }
    return 1;
}

void *func(void *base_ptr) {
    unsigned long long base = *(unsigned long long *) base_ptr;

    while (1) {
        if (is_prime(base)) {
            pthread_mutex_lock(&m);
            last_prime = base;
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
        }
        ++base;
    }

    return NULL;
}

int main() {
    unsigned long long base;
    int count;

    scanf("%llu %d", &base, &count);

    pthread_t thread_id;

    pthread_create(&thread_id, NULL, func, &base);

    unsigned long long last_printed = 0;
    for (int i = 0; i < count; ++i) {
        pthread_mutex_lock(&m);
        while (last_printed == last_prime) pthread_cond_wait(&c, &m);
        pthread_mutex_unlock(&m);

        printf("%llu\n", last_prime);
        last_printed = last_prime;
    }
}

//  Решение взято с семинара
