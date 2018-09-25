#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float time_read_byte(char* buffer, int buffer_size) {

    /*randomly generate choice to access in buffer*/
    const int BILLION = 1000000000;
    srand(12);

    int r = rand();
    int search_value = buffer_size * (r/RAND_MAX);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    char read = buffer[search_value];

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    float t = BILLION*(end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 


    return t;

}

void run_a_bunch() {

    for (int buffer_size = 1024; buffer_size <= 67108864; buffer_size = buffer_size<<1){

        float sum = 0;

        char* buffer = calloc(buffer_size,sizeof(char));

        for (int i = 0; i < 100; i++) {
            float t = time_read_byte(buffer, buffer_size);
            //printf("%f\n",t);
            sum = sum + t;

        }

        float average = sum/100;
        printf("buffer size: %d, average time: %f\n",buffer_size,average);
        free(buffer);
        
    }
}

int main() {

    run_a_bunch();

    return(0);
}
