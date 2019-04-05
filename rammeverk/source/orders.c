#include "channels.h"
#include "elev.h"
#include "io.h"
#include "timer.h"
#include "orders.h"
#include "queue.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


//åpner dør i 3sek
void orders_open_door(){
    timer_start_timer();
    elev_set_door_open_lamp(1);
    while(!timer_check_timer()){
        queue_add_to_queue();
    }
    elev_set_door_open_lamp(0);
}

//setter stopplys
int orders_set_stop(){
    if (elev_get_stop_signal()){
        elev_set_stop_lamp(1);
        return 1;
    }
    return 0;
}

//resetter stopplys
int orders_reset_stop(){
    while(elev_get_stop_signal());
    elev_set_stop_lamp(0);
    return 0;
}

//tenner etasjelys i riktig etasje
void set_floor_light(){
    int flooor = elev_get_floor_sensor_signal();
    if(flooor != -1){
        elev_set_floor_indicator(flooor);
    };
}

//sjekker om vi er i ønsket etasje
bool orders_check_reached_floor(int req_floor){
    int present_floor = elev_get_floor_sensor_signal();
    if(req_floor == present_floor){
        return true;
    }
    else{
        return false;
    }
}

//starter heisen i riktig retning
void orders_start_elev(int direction){
    if(direction == 1 && !(orders_set_stop())){
        elev_set_motor_direction(DIRN_UP);      
    }
    else if(direction ==-1 && !(orders_set_stop())){
        elev_set_motor_direction(DIRN_DOWN);
    }
    else{
         elev_set_motor_direction(DIRN_STOP);
    }
    orders_reset_stop();
}

void orders_set_order(elev_button_type_t button, int req_floor){

    //finner ut hvor vi er og hvor vi skal
    while(!elev_get_button_signal(button, req_floor)){
        while(elev_get_stop_signal());
    }

    //starter heisen i riktig retning
    orders_start_elev(req_floor);

    bool reached_floor = orders_check_reached_floor(req_floor);
    while(!reached_floor && !elev_get_stop_signal()) {
        reached_floor = orders_check_reached_floor(req_floor);
        set_floor_light();
    }
    
    elev_set_motor_direction(DIRN_STOP);
    elev_set_button_lamp(button,req_floor,0);
    orders_open_door();
}




