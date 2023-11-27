#include <stdint.h>
#include<stdlib.h>
#include<string.h>
#include "api.h"




void simple_medium_sprite(int16_t x, int16_t y, int16_t z);


// void memory_test(){

// }
// volatile int global = 42;


void thread1(void *){
    while (1)
    {   
        // VIDEO_MEMORY[pos1]='A';
        // VIDEO_MEMORY[pos2]=' ';
        /* code */
        // switch
        // thread_yield()
        // lock(mid);
        // simple_medium_sprite_green(0,0,0);
        VIDEO_MEMORY[pos1]='A';
        VIDEO_MEMORY[pos2]=' ';
        // unlock(mid);
        // thread_yield();
    }
    // explict
    thread_exit();
    return;
}
void thread2(void *){
    while (1)
    {
        /* code */
        // thread_yield();
        // lock(mid);
        VIDEO_MEMORY[pos2]='B';
        VIDEO_MEMORY[pos1]=' ';
        // simple_medium_sprite_red(0,0,0);
        // unlock(mid);
        // thread_yield();
    }
    thread_exit();
    return;
}

void memory_test(){
    // char *Buffer=malloc(32);
    char *Buffer=malloc(32);
    strcpy(Buffer,"OS TEST");
    strcpy((char *)(VIDEO_MEMORY),Buffer);

}

void video_test(){
    simple_medium_sprite_red(0,0,0);
    // setSmallSprite()
    
}

void thread_test(){
    ThreadID t1=thread_create(thread1,NULL,THREAD_MEMORY,High);
    ThreadID t2=thread_create(thread2,NULL,THREAD_MEMORY,High);
    // startFirstThread(sched);
    uint32_t* global_gp=get_gp();
}


int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;
    int countdown =1;

    *MODE_REGISTER=0;
    VIDEO_MEMORY[2]='H';
    MutexId mid=initLock();
    // gp?
    // memory_test();
    // thread_test();
    video_test();

    while (1) {

    }
    return 0;
}
