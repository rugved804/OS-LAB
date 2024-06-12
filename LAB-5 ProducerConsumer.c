                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              #include <stdlib.h>
#include <stdio.h>

#define BufferSize 10

int buffer[BufferSize];
int in = 0, out = 0;

int maxP, maxC;
int empty = BufferSize, full = 0, mutex = 1;

void wait(int *S)
{
    while (*S <= 0);
    (*S)--;
}

void signal(int *S)
 {
    (*S)++;
}

void producer()
{
    int pItems = 0;
    while (pItems < maxP)
    {
        int item = rand();
        wait(&empty);
        wait(&mutex);
        buffer[in] = item;
        printf("Producer produced item %d at %d\n", item, in);
        in = (in + 1) % BufferSize;
        signal(&mutex);
        signal(&full);
        pItems++;
    }
}

void consumer()
{
    int cItems = 0;
    while (cItems < maxC)
    {
        wait(&full);
        wait(&mutex);
        int item = buffer[out];
        printf("Consumer consumed item %d from %d\n", item, out);
        out = (out + 1) % BufferSize;
        signal(&mutex);
        signal(&empty);
        cItems++;
    }
}

int main()
{
    printf("Enter maximum items each producer can produce: ");
    scanf("%d", &maxP);

    printf("Enter maximum items each consumer can consume: ");
    scanf("%d", &maxC);
    producer();
    consumer();
    return 0;
}
