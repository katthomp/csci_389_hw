#include <stdio.h>
#include <time.h>

float time_read_byte(N) {
    int buffer_exp = 1024;

    /* make a buffer of size N of characters*/
    


    struct timespec start;
struct timespec end;
clock_gettime(CLOCK_MONOTONIC_RAW, &start);

/*read a byte here*/

/*randomly generate choice to access in buffer*/

clock_gettime(CLOCK_MONOTONIC_RAW, &end);
float t; 
t = BILLION*(end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 

    buffer_exp = buffer_exp<<1;

}
