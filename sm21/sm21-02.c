#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


void* handler (void* _)
{
    int num = 0;
    while (scanf("%d", &num) == 1)
    {
        pthread_t thread = 0;
        pthread_create(&thread, NULL, &handler, NULL);
        pthread_join(thread, NULL);
        printf("%d\n", num);
    }
    return NULL;
}

int main(void)
{
    pthread_t threads = 0;
    pthread_create(&threads, NULL, &handler, NULL);
    pthread_join(threads, NULL);

    return 0;
}
