#include "include/kernel.h"
#include "include/thread.h"
#include <stdlib.h>



volatile ThreadID global_tid =1;
uint32_t *global_gp;
struct TCB** threadArray;



// run before main.c need to change the ctr0.s
TStatus OSinitialize(uint32_t *gp){
    threadArray=malloc(sizeof(void*)*MAX_THREAD_NUM);
    // struct TCB* mainThread;

    global_gp=gp;
    if(global_gp==0){
        return STATUS_FAILURE;
    }
    else{
        return STATUS_SUCCESS;
    }
}


ThreadID threadCreate(TContextEntry entry,void *param,uint32_t memsize,ThreadPriority prio){
    if(entry==NULL){
        return INVALD_THREAD_ID;
    }else{
        if(current_thread_num>=MAX_THREAD_NUM){
            // number of threads exceeds current 
            return INVALD_THREAD_ID;
        }
        else{
            struct TCB* new_thread=malloc(sizeof(TCB));
            uint8_t *sb=malloc(memsize);
            new_thread->entry=entry;
            new_thread->param=param;
            new_thread->memory_size=memsize;
            new_thread->tid=global_tid;
            new_thread->stack_base=sb;
            new_thread->state=INIT;
            new_thread->priority=prio;
            threadArray[global_tid]=new_thread;
            current_thread_num++;
            global_tid++;
            return new_thread->tid;
        }
    }
}


TStatus threadDelete(ThreadID tid){
    if(threadArray[tid]==NULL){
        return STATUS_INVALD_ID;
    }
    struct TCB* currThread= threadArray[tid];
    if(currThread->state!=FINISHED){
        return STATUS_INVALD_ID;
    }else{
        current_thread_num--;
        free(currThread->stack_base);
        free(currThread);
        threadArray[tid]=NULL;
        return STATUS_SUCCESS;
    }
}

TStatus threadActivate(ThreadID tid){
    if(threadArray[tid]==NULL){
        
    }
}

TStatus threadTerminate(ThreadID tid,ThreadReturn retval){

}

TStatus threadWait(ThreadID tid,ThreadReturn* retvalref,Tick timeout){

}

ThreadID threadId(){

}

ThreadStatus threadState(ThreadID tid){

}

TStatus threadSleep(Tick tick){

}