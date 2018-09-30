#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
volatile char read;
const int BILLION=1000000000;
const int START_SIZE_BYTES = 1024;
const int END_SIZE_BYTES = 67108864;
float time_read_byte(char* order, int buffer_size){
    int r=0;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(int j=0;j<buffer_size;++j){
        read=order[r];
        r=(j+r+read)&buffer_size;
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);
    if (read==-1 || r==-1){
        printf("This is not supposed to happen");
    }
    float t=(BILLION*(end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec);
    float time_per_byte = t/buffer_size;
    return time_per_byte;
} 

void run_many(){
    float average;
    int NUMBER_RUNS = 10;
    for (int buffer_size=START_SIZE_BYTES; buffer_size<=END_SIZE_BYTES;buffer_size = buffer_size<<1){
        float average=0;
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
        for (int i=0; i<buffer_size; ++i){
            float r=rand()%buffer_size;
            order[i]=r;
        }
    
        for (int i=0; i<NUMBER_RUNS; ++i){
            average+=time_read_byte(order, buffer_size);   
        }  
        printf("buffer size (KB): %d, average time (ns): %f\n \n",buffer_size/1024,average/NUMBER_RUNS); 
    free(order);
    free(buffer);
}
return;}
int main(){
    run_many();
    
    
    return 0;
}
