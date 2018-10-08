#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


// u_int32_t do_something_with_read(u_int32_t r){
//     r=rand()%buffer_size;
    
//     // clock_gettime(CLOCK_MONOTONIC_RAW, &start);

//     // clock_gettime(CLOCK_MONOTONIC_RAW, &end);
//     return r;
// }
// void print_sum(float sum){
//     printf("(from print_sum) sum %f",sum);
//     return;
// }

char read;

float time_read_byte(int buffer_size, char* order, char* buffer) {

    /*randomly generate choice to access in buffer*/
    const int BILLION = 1000000000;
    // int search_value = buffer_size * (r/RAND_MAX);

    /*make array of random byte locations to read in a loop while timing*/

    //create array of order of bytes to search

     //this 
    u_int32_t r;

    for (int i=0; i < buffer_size; i++){
        r = rand() % (buffer_size);
        order[i] = r;
        // assert(r >= 0);
    }
    // for (int j=0; j<10; j++){
    //     int bs=order[j];
    //     printf("Order %i ",bs );
    // }
    struct timespec start, end;
    
    // char vread;
    
    r=(rand())%buffer_size;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int i = 0; i < buffer_size; ++i) {
        // r=(u_int32_t) time (NULL)&buffer_size;
        r=(r+i+(read&4))%buffer_size;
        read += buffer[r];
        // if (i<buffer_size-8){
        //     read = order[r+1];
        //     read = order[r+2];
        //     read = order[r+3];
        //     read = order[r+4];
        //     read = order[r+5];
        //     read = order[r+6];
        //     read = order[r+7];
        // }
        
        
        // r= (r+read+i) & buffer_size;

        //need to create a way of editing the array each time, so that we pick a value at random
        //however, make sure that it's getting each value
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    // print_sum(chksum);
    float t=(BILLION*(end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec);
    float time_per_byte = t/buffer_size;

    if (read == -1) {
        printf("ha!");
    }

    return time_per_byte;

}


void run_a_bunch() {

    int NUMBER_RUNS = 10;
    int counter=10;
    int count=1;
    for (int buffer_size = 512; buffer_size <= 67108864; buffer_size = buffer_size<<1){

        float sum = 0;
        
        
        if (count%3==0 && NUMBER_RUNS<=1){
            NUMBER_RUNS=NUMBER_RUNS/(10*counter);
            counter+=10;
            
        }
        // char* buffer = calloc(buffer_size,sizeof(char));
        char* order = calloc(buffer_size,sizeof(char));
            if(!order) {
        perror("Didn't allocate memory correctly (order)");
        exit(-1);
        }
        char* buffer =calloc(buffer_size, sizeof(char));
            if(!buffer) {
        perror("Didn't allocate memory correctly (buffer)");
        exit(-1);
        }
        for (int i = 0; i < NUMBER_RUNS; i++) {
            float t = time_read_byte(buffer_size, order, buffer);
            //printf("%f\n",t);
            sum = sum + t;

        }
        count+=1;
        float average = sum/NUMBER_RUNS;
        // printf(average);
        printf("buffer size: %d, average time: %f\n \n",buffer_size,average);
        free(order);
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

    return read;
}
/* 
References:

https://stackoverflow.com/questions/21369381/measuring-cache-latencies

https://softwareengineering.stackexchange.com/questions/302354/memory-cache-performance-in-working-with-arrays-in-c



*/
