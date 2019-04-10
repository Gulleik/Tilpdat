#include "channels.h"
#include "elev.h"
#include "io.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define TIMER_THRESHOLD 3000

static clock_t m_modul_timer;

void timer_start_timer(){
    m_modul_timer = clock();
}



bool timer_check_timer(){
    clock_t difference = clock() - m_modul_timer;
    int msec = difference *1000/ CLOCKS_PER_SEC;
    if(msec > TIMER_THRESHOLD){
        return true;
    }
    return false;
}


