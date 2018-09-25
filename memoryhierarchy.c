#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char do_something_with_read(char read){
    vread=read*2
    return Vread;
}

float time_read_byte(char* buffer, int buffer_size) {

    /*randomly generate choice to access in buffer*/
    const int BILLION = 1000000000;

    int r = rand();
    // int search_value = buffer_size * (r/RAND_MAX);



    /*make array of random byte locations to read in a loop while timing*/

    //create array of order of bytes to search

    int* order = malloc(buffer_size*sizeof(int8_t)); //this 
    if(!order) {
        perror("Didn't allocate memory correctly (order)");
        exit(-1);
    }

    for (int i=0; i < buffer_size; i++){
        int r = rand() % buffer_size;
        order[i] = r;
    }
    // for (int j=0; j<10; j++){
    //     int bs=order[j];
    //     printf("Order %i ",bs );
    // }
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    volatile char read;
    for (int i = 0; i < buffer_size; i++) {
        r=rand();
        read = buffer[order[r]];
        vread=do_something_with_read(read);
    }
    volatile char 
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    float t = BILLION*(end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 

    float time_per_byte = t/buffer_size;


    return time_per_byte;

}

void run_a_bunch() {

    const int NUMBER_RUNS = 10;

    for (int buffer_size = 1024; buffer_size <= 67108864; buffer_size = buffer_size<<1){

        float sum = 0;

        // char* buffer = calloc(buffer_size,sizeof(char));

        char* buffer =malloc(sizeof(char)*buffer_size);
        if (!buffer){
            perror("Didn't allocate memory correctly (buffer)");

        }
        for (int i = 0; i < NUMBER_RUNS; i++) {
            float t = time_read_byte(buffer, buffer_size);
            //printf("%f\n",t);
            sum = sum + t;

        }

        float average = sum/NUMBER_RUNS;
        printf("buffer size: %d, average time: %f\n",buffer_size,average);
        free(buffer);
        
    }
}


/*hypothesis for why it gets faster per byte as the buffer size increases:
because we have the same number of iterations each time, it's biasing itself 
also, before, it was taking the same amount of time:
-could it be loading sequentially into memory? for example, it has the array with 1024 things,
and then it just adds the "new" 1024 array onto the old one to create the 2048 array?????

that would be the most efficient thing for memory to do, I think, so it would do that.


another problem with this:
-so the malloc call doesn't change the actual runtime of the code



*/



int main() {

    run_a_bunch();

    return(0);
}
