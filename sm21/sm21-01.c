#include <pthread.h>
#include <stdio.h>


enum
{
	TC = 10
};

void* cal (void* ptr)
{
    int c = *(int*) ptr;
    printf("%d\n",c);
    return NULL;
}

int main()
{
	int counts[TC] = {0};
    pthread_t threads[TC] = {0};
    size_t count = 0;
    while (count < TC)
    {
        counts[count] = count;
        pthread_create(&threads[count], NULL, cal, &counts[count]);
        pthread_join(threads[count], NULL);
        ++count;
    }
}
