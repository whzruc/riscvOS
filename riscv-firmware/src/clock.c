#include "clock.h"

extern volatile char *VIDEO_MEMORY;
unsigned int x=0;

#define TICK_NUM 100



void set_timer(uint64_t msec){
    

}

void handle_time_interrput(){

    set_timer(10);
    if((++time_count%TICK_NUM)==0){
        VIDEO_MEMORY[x]='A';
        x++;
    }
}