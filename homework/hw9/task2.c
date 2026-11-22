#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

int numbers[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

typedef struct {
    int thread_num;
    int start;      
    int end;
    int sum; 
} Range;


void *partial_sum(void *arg)
{
    Range *r = (Range *)arg;

    r->sum = 0;
    for (int i = r->start; i < r->end; i++) {
        r->sum += numbers[i];
    }

    printf("Thread %d (pthread ID: %lu): sum of elements %d to %d = %d\n",
           r->thread_num, (unsigned long)pthread_self(),
           r->start, r->end - 1, r->sum);
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    int mid = SIZE / 2;

    Range first  = {1, 0,   mid,  0};
    Range second = {2, mid, SIZE, 0};

    if (pthread_create(&t1, NULL, partial_sum, &first) != 0 ||
        pthread_create(&t2, NULL, partial_sum, &second) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Total sum = %d\n", first.sum + second.sum);
    return 0;
}

