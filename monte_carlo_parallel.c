#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define UPPER_BOUND 10
#define LOWER_BOUND 0

double f_value(double x);

int main(int argc, char* args[]) {
    unsigned long num_points = 500000000;
    double result, sum = 0, point;
    double error, deviation, average, diff_squared = 0;
    time_t t;
    double start, end;

    start = omp_get_wtime();
  
    printf("Usage: ./mct [num_points]\n");
    if (argc == 2) {
        num_points = atoi(args[1]);
        printf("Number of points: %lu\n", num_points);
    }
    else {
        printf("Number of points not specified, default number of points is used: 500000000\n");
    }

    double *buffer = (double*)malloc(sizeof(double) * num_points);
    unsigned int seed = (unsigned int) time(NULL);

    #pragma omp parallel for private(point) reduction(+:sum)
    for (unsigned long i = 0; i < num_points; i++) {
        point = (double)rand_r(&seed) / (RAND_MAX / (UPPER_BOUND - LOWER_BOUND));
        buffer[i] = f_value(point);
        sum += buffer[i];
    }

    result = ((double)(UPPER_BOUND - LOWER_BOUND) / num_points) * sum;
    printf("Monte Carlo Estimate: %lf\n", result);

    average = (double)sum / num_points;
    #pragma omp parallel for reduction(+:diff_squared)
    for (unsigned long i = 0; i < num_points; i++) {
        diff_squared += pow((buffer[i] - average), 2);
    }
    
    deviation = sqrt((double)diff_squared/num_points);
    error = (double)deviation / sqrt(num_points);
    printf("Error (Standard error): %lf\n", error);

    end = omp_get_wtime();
    printf("Elapsed time: %lf\n", ((double) (end - start)));

    free(buffer);
    return 0;
}

//return function value in x of function x^3
double f_value(double x){
    return (x * x * x);
}
