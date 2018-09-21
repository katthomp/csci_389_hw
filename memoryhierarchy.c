#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float time_read_byte(buffer, buffer_size) {

/*randomly generate choice to access in buffer*/
srand(12);

int r = rand();
int search_value = buffer_size * (r/RAND_MAX)

struct timespec start, end;
clock_gettime(CLOCK_MONOTONIC_RAW, &start);

char read = buffer[search_value];

clock_gettime(CLOCK_MONOTONIC_RAW, &end);
float t = BILLION*(end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 

return t

}

float run_a_bunch() {

    for (int buffer_size = 1024, buffer_size <  10^26, buffer_size<<1){

        char* buffer = calloc(buffer_size,size_of(char));

        for (int i = 0, i < 100, i++) {
            float t = time_read_byte(buffer, buffer_size);
            printf(t)

        }

        free(buffer);

        return(0);
    }

}
