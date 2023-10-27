#pragma once
#include <stdint.h>

unsigned time_count=0;

void set_timer(uint64_t msec);
// millisecond


void handle_time_interrupt();
