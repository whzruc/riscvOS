#include "include/scheduler.h"



TStatus initScheduler(scheduler* schedule){
    schedule->ready=createQueue(MAX_QUEUE_NUM);
    schedule->finished=createQueue(MAX_QUEUE_NUM);
    schedule->current_tid=0;// main?
    schedule->next_tid=0;

};

void switchThreadStateTo(ThreadID tid, const ThreadStatus new_state){
    struct TCB* current=threadArray[tid];
    current->state=new_state;
}

// get the tid for running
ThreadID schedule(scheduler* schedule){

    // struct Process next=dequeue;
    enqueue(schedule->ready,schedule->current_tid);
    schedule->next_tid=dequeue(schedule->ready);
    // schedule->next_tid=(schedule->current_tid+1)%current_thread_num;

    if(schedule->next_tid==-1){
        schedule->next_tid=schedule->current_tid;
    }
    
    switchThreadStateTo(schedule->next_tid,RUNNING);
    
    return schedule->next_tid;
    

}