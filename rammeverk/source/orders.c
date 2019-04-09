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
void orders_open_door_timed(int last_Floor){
    timer_start_timer();
    elev_set_door_open_lamp(1);
    while(!timer_check_timer()){
        queue_add_to_queue(last_Floor);
        if(elev_get_stop_signal()){
            break;
        }
    }
    elev_set_door_open_lamp(0);
}

//bestemmer direction om vi er i en definert tilstand
int orders_set_direction_defined_floor(int direction){

    int floor = elev_get_floor_sensor_signal();
    //hvis heisen er på vei opp, sjekker neste action
    if(direction == 1){
        if(queue_check_orders_above(floor)){
            return 1;
        }
        else if(queue_check_orders_below(floor)){
                return -1;
        }
        else{
            return 0;
        }
    }
    //hvis heisen er på vei ned, sjekker neste action
    else{
        if(queue_check_orders_below(floor)){
            return -1;
        }
        else if(queue_check_orders_above(floor)){
                return 1;
        }
        else{
                return 0;
        }
    }
}

//bestemmer direction om vi er i en udefinert tilstand
int orders_set_direction_undefined_floor(int last_floor, int next_floor){
    if (last_floor < next_floor){
        if (queue_check_orders_above(last_floor)){
            return 1;
        }
        else if (queue_check_orders_below(next_floor)){
            return -1;
        }
        else{
            return 0;
        }
    }
    else if (last_floor > next_floor){
        if (queue_check_orders_above(next_floor)){
            return 1;
        }
        else if (queue_check_orders_below(last_floor)){
            return -1;
        }
        else{
            return 0;
        }
    }
    return 0;
}

//opdaterer siste etasje heisen var i
int orders_update_last_Floor(int last_Floor){
    if(elev_get_floor_sensor_signal() != -1){
        last_Floor = elev_get_floor_sensor_signal();
    }
    return last_Floor;
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
    if(direction == 1){
        elev_set_motor_direction(DIRN_UP);      
    }
    else if(direction ==-1 ){
        elev_set_motor_direction(DIRN_DOWN);
    }
    else{
         elev_set_motor_direction(DIRN_STOP);
    }
}

//bestemmer retning heisen skal gå i
int orders_set_direction(int direction, int last_Floor, int next_floor){
    if (elev_get_floor_sensor_signal() == -1){
        direction = orders_set_direction_undefined_floor( last_Floor, next_floor);
        return direction;
    }
    else if (elev_get_floor_sensor_signal() != -1) {
        direction = orders_set_direction_defined_floor(direction);
        return direction;
    }
    else{
        return 0;
    }
}

//bestemmer hvilken etasje heisen er på vei mot
int orders_set_next_floor(int last_floor, int direction){
    if (direction == 1){
        return last_floor + 1;
    }
    else if (direction == - 1){
        return last_floor - 1;
    }
    return last_floor;
}

//åpner døren
void orders_open_door(){
    elev_set_door_open_lamp(1);
}
