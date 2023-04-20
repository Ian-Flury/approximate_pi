#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

double calcLoop(int iterations);


int main() {
    clock_t start, end;
    double cpu_time_used;

    // Seed the random number generator with the current time
    srand(time(NULL));

    pthread_t id_1;
    pthread_t id_2;


    double numInCircle = 0;

    unsigned long int allPoints = 4000000000;

    start = clock();



    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    double pi = 4 * (numInCircle / allPoints);
    printf("Approximation of Pi: %f\n\n", pi);
    printf("iterations: %u\n", allPoints);
    printf("CPU time used: %.0f secs\n", cpu_time_used);

    return 0;
}

double calcLoop(int iterations) {
    double x;
    double y;
    double distance = 0.0;
    double numInCircle;
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