#include "include/kernel.h"
#include "include/thread.h"
#include "include/scheduler.h"
#include "include/memory.h"
#include <stdlib.h>



volatile ThreadID global_tid =1;
uint32_t *global_gp;
struct TCB** threadArray;
struct scheduler* sched;




// run before main.c need to change the ctr0.s
TStatus OSinitialize(uint32_t *gp){
    threadArray=kmalloc(sizeof(void*)*MAX_THREAD_NUM);
    // struct TCB* mainThread;
    initScheduler(sched);

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
            struct TCB* new_thread=kmalloc(sizeof(TCB));
            uint8_t *sb=kmalloc(memsize);
            new_thread->entry=entry;
            new_thread->param=param;
            new_thread->memory_size=memsize;
            new_thread->tid=global_tid;
            new_thread->stack_base=sb;
            new_thread->state=INIT;
            new_thread->priority=prio;
            ThreadPointers[global_tid]=
            ContextInitialize(
                (TStackRef)(ThreadStack[global_tid - 1] + memsize),
                (TContextEntry)entry,(void *)param);
            new_thread->sp=ThreadPointers[global_tid];
            current_thread_num++;
            global_tid++;
            return new_thread->tid;
        }
    }
}


TStatus threadDelete(ThreadID tid){
    if(tid>=MAX_THREAD_NUM){
        return STATUS_INVALD_ID;
    }
    struct TCB* cur_thread= threadArray[tid];
    if(cur_thread->state!=FINISHED){
        return STATUS_INVALD_ID;
    }else{
        current_thread_num--;
        kfree(cur_thread->stack_base);
        kfree(cur_thread);
        threadArray[tid]=NULL;
        return STATUS_SUCCESS;
    }
}

TStatus threadActivate(ThreadID tid){
    if(tid>=MAX_THREAD_NUM){
        return STATUS_INVALD_ID;
    }
    struct TCB* act_thread=threadArray[tid];
    act_thread->state=READY;
    enqueue(sched->ready,act_thread->tid);
}

TStatus threadTerminate(ThreadID tid,ThreadReturn retval){
    if(tid>=MAX_THREAD_NUM){
        return STATUS_INVALD_ID;
    }
    struct TCB* curr_thread=threadArray[tid];

    curr_thread->state=FINISHED;
    curr_thread->ret_val=retval;
    if(sched->current_tid==tid){
        schedule(sched);
    }
    return STATUS_SUCCESS;
}

TStatus threadWait(ThreadID tid,ThreadReturn* retvalref,Tick timeout){

}

ThreadID threadId(){
    return sched->current_tid;
}

ThreadStatus threadState(ThreadID tid){
    return threadArray[tid]->state;
}

TStatus threadSleep(Tick tick){

}

void set_timer(uint64_t timestamp){


    uint64_t h=MTIME_HIGH<<32;
    uint64_t l=MTIME_LOW;
    uint64_t cmp_h=MTIMECMP_HIGH<<32;
    uint64_t cmp_l=MTIME_LOW;
    uint64_t now=h|l;
    uint64_t NewCompare=cmp_h |cmp_l;

    if(NewCompare<=now){
        // when current time arrives the set time
        // unkown clock frequency not accurate timer
        NewCompare+=timestamp;
    }
    MTIMECMP_HIGH = NewCompare>>32;
    MTIMECMP_LOW = NewCompare;


}

void handle_time_interrupt(){

    set_timer(1000);

    if (current_thread_num >= 2)
    {
        uint32_t mepc = csr_mepc_read();
        // printf("\n");
        TInterruptState PrevState = SuspendInterrupts();
        int t1, t2;
        t1 = running_thread_pointer;
        // t2 = (running_thread_pointer + 1) % current_thread_num;
        // running_thread_pointer = t2;
        t2=schedule(sched);
        if(t1!=t2){
            ContextSwitch(&ThreadPointers[t1], ThreadPointers[t2]);
        }
        csr_write_mepc(mepc);
        ResumeInterrupts(PrevState);
    }
    

}

