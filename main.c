#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define NUM_OF_THREADS 16
#define TOTAL_ITERATIONS 100000000

void *calcLoop(void *params);

// will be used to pass parameters to threads
typedef struct {
    double retVal;
    int numIt;
} parameters;

int main() {
    double cpu_time_used;
    int iterationsPerThread = TOTAL_ITERATIONS / NUM_OF_THREADS;
    clock_t start, end;
    srand(time(NULL));

    pthread_t workers[NUM_OF_THREADS];

    parameters *params;
    params = (parameters*) malloc(NUM_OF_THREADS * sizeof (parameters));

    // set the num of iterationsPerThread for each thread in their structs
    for (int i = 0; i < NUM_OF_THREADS; i++) {
        (params+i)->numIt = iterationsPerThread;
    }

    start = clock();

    // create NUM_OF_THREADS threads
    for (int i = 0; i < NUM_OF_THREADS; i++) {
        pthread_create(&workers[i], NULL, calcLoop, (params+i));
    }
    // threads will automatically join when they're done
    for (int i = 0; i < NUM_OF_THREADS; i++) {
        pthread_join(workers[i], NULL);
    }

    // performance monitoring
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // sum each of the thread totals
    double totalInCircle = 0.0;
    for (int i = 0; i < NUM_OF_THREADS; i++) {
        totalInCircle += (params+i)->retVal;
    }

    double pi = 4 * (totalInCircle / TOTAL_ITERATIONS);
    printf("Approximation of Pi: %f\n\n", pi);
    printf("Total Iterations: %u\n", TOTAL_ITERATIONS);
    printf("Number of threads: %d\n", NUM_OF_THREADS);
    printf("iterationsPerThread: %u\n", iterationsPerThread);
    printf("CPU time used: %f secs\n", cpu_time_used);

    // don't forget to free malloced memory
    free(params);
    return 0;
}

// thread function to approximate pi
// Throw darts at a box that has a circle in it.
// The ratio of the darts in to the darts out is
// approximately pi. Only do quadrant 2 and then
// multiply by 4 at the end.
void *calcLoop(void *params) {
    parameters *p = (parameters *)params;
    double x;
    double y;
    double distance = 0.0;
    double numInCircle = 0.0;
    for (int i = 0; i < p->numIt; i++) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        distance = sqrt((x*x) + (y*y));
        if (distance < 1) {     // inside the circle
            numInCircle++;
        }
    }
    p->retVal = numInCircle;
    pthread_exit(0);
}
