#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

double calcLoop(int iterations);

int main() {
    double numInCircle;
    double cpu_time_used;
    int iterations = 100000000;

    clock_t start, end;
    srand(time(NULL));

    pthread_t id_1;
    pthread_t id_2;

    start = clock();

    // iteration function
    numInCircle = calcLoop(iterations);

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    double pi = 4 * (numInCircle / iterations);
    printf("Approximation of Pi: %f\n\n", pi);
    printf("iterations: %u\n", iterations);
    printf("CPU time used: %f secs\n", cpu_time_used);

    return 0;
}

double calcLoop(int iterations) {
    double x;
    double y;
    double distance = 0.0;
    double numInCircle = 0.0;
    for (int i = 0; i < iterations; i++) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        distance = sqrt((x*x) + (y*y));
        if (distance < 1) {     // inside the circle
            numInCircle++;
        }
    }
    return numInCircle;
}
