#include "include/sleepTimer.h"
#include<stdlib.h>



void doSleep(size_t cnt,scheduler* schedule,SleepTimer* sleeper){
    size_t wake_ticks=sleeper->systicks+cnt;
    lock(sleeper->mutex_id);
    while(sleeper->systicks<wake_ticks){
        wait_(sleeper->mutex_id,schedule,sleeper->cond_id);
    }
    unlock(sleeper->mutex_id);
}



void updateGlobalTicks(scheduler* schedule,SleepTimer* sleeper){
    // notifyAll()
    sleeper->systicks++;
    notifyAll_(schedule,sleeper->cond_id);
}



void initSleepTimer(SleepTimer* new_sleep_timer){
    new_sleep_timer->cond_id=condCreate();
    new_sleep_timer->mutex_id=mutexCreate();
    new_sleep_timer->systicks=0;
    return;
}