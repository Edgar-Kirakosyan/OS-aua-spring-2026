#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 5

void *square(void *arg)
{
    int n = *(int *)arg;

    printf("Square of %d is %d\n", n, n * n);
    return NULL;
}

int main(void)
{
    int numbers[SIZE] = {1, 2, 3, 4, 5};
    pthread_t threads[SIZE];

    for (int i = 0; i < SIZE; i++) {
        if (pthread_create(&threads[i], NULL, square, &numbers[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");
    return 0;
}

