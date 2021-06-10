#include <pthread.h>
#include <sched.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define pt(x) p##thread_mutex_##x

struct Elem
{
    int iter;

    size_t acc_indx1;
    size_t acc_indx2;

    double acc_sum1;
    double acc_sum2;
    double *accs;

    pthread_mutex_t *m;
};


void *calc(void *ptr)
{
    struct Elem *it = (struct Elem *) ptr;
    struct Elem *temp_it = (struct Elem *) ptr;

    size_t c = 0;
    while (it->iter > c)
    {
        pt(lock(&it->m[it->acc_indx2]));
        pt(lock(&it->m[it->acc_indx1]));
        it->accs[it->acc_indx2] += it->acc_sum2;
        it->accs[it->acc_indx1] += it->acc_sum1;
        pt(unlock(&it->m[it->acc_indx1]));
        pt(unlock(&it->m[it->acc_indx2]));
        ++c;
    }



    temp_it->iter = 0;

    temp_it->acc_indx1 = 0;
    temp_it->acc_indx2 = 0;

    temp_it->acc_sum1 = 0;
    temp_it->acc_sum2 = 0;
    temp_it->accs = NULL;

    temp_it->m = NULL;

    return NULL;
}

int main(void)
{
    pthread_attr_t hap;
    size_t cnt = 0;
    size_t threads = 0;
    scanf("%lu %lu", &cnt, &threads);

    size_t sz_double = sizeof(double) * cnt;
    size_t sz_pt__t = sizeof(pt(t)) * cnt;
    size_t sz_pthread_t = sizeof(pthread_t) * threads;
    size_t sz_elem = sizeof(struct Elem) * threads;

    double *accs = calloc(1, sz_double);
    pt(t) *m = calloc(1, sz_pt__t);
    pthread_t *idcs = calloc(1, sz_pthread_t);
    struct Elem *elements = calloc(1, sz_elem);

    size_t c = 0;
    while (cnt > c)
    {
        pt(init(&m[c], NULL));
        accs[c] = 0;
        ++c;
    }

    pthread_attr_init(&hap);
    pthread_attr_setstacksize(&hap, sysconf(_SC_THREAD_STACK_MIN));

    c = 0;
    while (threads > c)
    {
        if (scanf("%u %lu %lg %lu %lg",  &elements[c].iter, &elements[c].acc_indx1, &elements[c].acc_sum1, &elements[c].acc_indx2, &elements[c].acc_sum2) != 5) return 0;

        if (elements[c].acc_indx2 < elements[c].acc_indx1)
        {
            double temp = elements[c].acc_sum1;
            elements[c].acc_sum1 = elements[c].acc_sum2;
            elements[c].acc_sum2 = temp;

            size_t temp2 = elements[c].acc_indx1;
            elements[c].acc_indx1 = elements[c].acc_indx2;
            elements[c].acc_indx2 = temp2;
        }

        elements[c].accs = accs;
        elements[c].m = m;

        pthread_create(&idcs[c], &hap, calc, &elements[c]);

        ++c;
    }

    c = 0;
    while (threads > c)
    {
        pthread_join(idcs[c], NULL);
        ++c;
    }

    c = 0;
    while (cnt > c)
    {
        printf("%.10g\n", accs[c]);
        ++c;
    }

    pthread_attr_destroy(&hap);
    free(idcs);
    free(accs);
    free(elements);
    free(m);

    return 0;
}
