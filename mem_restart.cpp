#include <iostream>
#include <ctime>
#include <vector>
#include <string>
volatile int read;
const int BILLION=1000000000;
const int START_SIZE_BYTES = 1024;
const int END_SIZE_BYTES = 67108864;
float time_read_byte(std::vector<char> buffer, std::vector <int> order, int buffer_size){
    u_int64_t r=rand()%buffer_size;
    long double sum=0;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(int j=0;j<buffer_size;++j){
        read=buffer[order[j]];
        // if (read ==BILLION){
        // printf("This is not supposed to happen");
        // exit(-1);
        // }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);
    float t=(BILLION*(end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec);
    float time_per_byte = t/buffer_size;
    return time_per_byte;
} 

int run_many(){
    int NUMBER_RUNS = 40;
    for (int buffer_size=START_SIZE_BYTES; buffer_size<=END_SIZE_BYTES;buffer_size = buffer_size<<1){
       float average=0;
        std::vector <int> order (buffer_size);
        //     if(order==NULL) {
        //     perror("Didn't allocate memory correctly (order)");
        //     exit(-1);
        // }
        std::vector <char> buffer (buffer_size);
    //     if(buffer==NULL) {
    //     perror("Didn't allocate memory correctly (buffer)");
    //     exit(-1);
    // }   
        for (int i=0; i<buffer_size; ++i){
            int r=rand()%buffer_size;
            // printf("read %f", r);
            order[i]=r;
            // printf("r %f",r);
        }
        for (int i=0; i<NUMBER_RUNS; ++i){
            average=average+(time_read_byte(buffer, order, buffer_size)); 
            // printf("PLEASE  %f \n", average);  
        }
        int buff_kb=buffer_size/1024;
        average=average/NUMBER_RUNS;
        // printf("read %d",read);  
        std::cout<<"buffer size (KB): "<<buff_kb<<" average time (ns): "<<average<<" \n"<<std::endl; 
    
    
}
return read;}
int main(){
    read=run_many();
    std::cout<<"read "<<read<<std::endl;
    return read;
}
///Users/kathythompson/cs-virtualmachine/school_stuff/college/csci_389/csci_389_hw/mem_restart.c
