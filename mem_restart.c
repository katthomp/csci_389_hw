#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
volatile int read;
const int BILLION=1000000000;
const int START_SIZE_BYTES = 1024;
const int END_SIZE_BYTES = 67108864;
float time_read_byte(char* order, int buffer_size){
    u_int64_t r=rand()%buffer_size;
    long double sum=0;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(int j=0;j<buffer_size;++j){
        read=order[(j+r)%buffer_size];
        // printf("read %i", read);
        sum+=read;
        if (read ==BILLION){
        printf("This is not supposed to happen");
        exit(-1);
        }
        // if (read){
        //     printf("Something is Very Wrong");
        //     printf("sum %Lf",sum/10000);
        //     exit(-1);
        // }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);
    
    float t=(BILLION*(end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec);
    float time_per_byte = t/buffer_size;
    return time_per_byte;
} 

int run_many(){
    int NUMBER_RUNS = 100;
    for (int buffer_size=START_SIZE_BYTES; buffer_size<=END_SIZE_BYTES;buffer_size = buffer_size<<1){
        printf("HELP ME");
        float average=0;
        char* order = calloc(buffer_size,sizeof(char));
            if(!order) {
            perror("Didn't allocate memory correctly (order)");
            exit(-1);
        }
        char* buffer = calloc(buffer_size, sizeof(char));
        if(!buffer) {
        perror("Didn't allocate memory correctly (buffer)");
        exit(-1);
    }   
        for (int i=0; i<buffer_size; ++i){
            float r=rand()%buffer_size;
            // printf("read %f", r);
            order[i]=r;
            // printf("r %f",r);
            r=rand()%buffer_size;
        }
        for (int i=0; i<NUMBER_RUNS; ++i){
            average=average+time_read_byte(order, buffer_size); 
            // printf("PLEASE  %f \n", average);  
        }
        // printf("read %d",read);  
        printf("buffer size (KB): %d, average time (ns): %f\n \n",buffer_size/1024,average/NUMBER_RUNS); 
    
    free(order);
    free(buffer);
    
}
return read;}
int main(){
    read=run_many();
    // printf("read %d",read);
    return read;
}
///Users/kathythompson/cs-virtualmachine/school_stuff/college/csci_389/csci_389_hw/mem_restart.c
