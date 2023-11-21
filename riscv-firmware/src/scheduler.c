#include "include/scheduler.h"



TStatus initScheduler(scheduler* schedule){
    schedule->ready=createPriorityQueue(MAX_QUEUE_NUM);
    schedule->finished=createQueue(MAX_QUEUE_NUM);
    schedule->current_tid=0;// main?
    schedule->next_tid=0;

};

void switchThreadStateTo(ThreadID tid, const ThreadStatus new_state){
    struct TCB* current=threadArray[tid];
    current->state=new_state;
}

// get the tid for running
void schedule(scheduler* schedule){
    schedule->next_tid=extractMin(schedule->ready);
    if(schedule->next_tid==-1){
        schedule->next_tid=schedule->current_tid;
    }
    
    switchThreadStateTo(threadArray[schedule->next_tid],RUNNING);
    
    if(schedule->next_tid!=schedule->current_tid){
        ContextSwitch(&threadArray[schedule->current_tid]->sp,threadArray[schedule->next_tid]->sp);
    }

}