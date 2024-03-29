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


//kømatrise
static int queue_matrix[N_FLOORS][N_BUTTONS] = {
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0}
};

//legger ordre til i køen
bool queue_add_to_queue(int last_floor){
    if(elev_check_order()){
        int i = elev_get_floor();
        if(i == last_floor && (elev_get_floor_sensor_signal() != -1)){
            return true;
        }
        const int j = elev_get_button_type();
        queue_matrix[i][j] = 1;
        elev_set_button_lamp(j, i, 1);
    }
    return false;
}
//fjerner ordre fra køen
void queue_remove_from_queue(int direction){
    int i = elev_get_floor_sensor_signal();
    int j;
    for(j=0; j<N_BUTTONS;j++){
            queue_matrix[i][j] = 0;
            if(i != -1){
                if(!(j == BUTTON_CALL_UP && i == N_FLOORS - 1)){
                    if(!(j == BUTTON_CALL_DOWN && i == 0)){
                        elev_set_button_lamp(j, i, 0);

                    }
                }
            }
    }

}

//sjekker om det er noen ordre over nåværende posisjon
bool queue_check_orders_above(int req_floor){
    int floor;
    if (elev_get_floor_sensor_signal() == -1){
        floor = req_floor;
    }
    else{
        floor = elev_get_floor_sensor_signal();
    }
    
    
    if (floor == 3){
        return false;
    }
    int i;
    int j;
    for (i = floor+1; i < N_FLOORS; i++){
        for(j = 0; j < N_BUTTONS; j++){
            if (queue_matrix[i][j]){
                return true;
            }
        }
    }
    return false;


}

//sjekker om det er noen ordre under nåværende posisjon
bool queue_check_orders_below(int req_floor){
    int floor;
    if (elev_get_floor_sensor_signal() == -1){
        floor = req_floor;
    }
    else{
        floor = elev_get_floor_sensor_signal();
    }

    if (floor == 0){
        return false;
    }
    int i;
    int j;
    for (i = floor-1; i > -1; i--){
        for(j = 0; j < N_BUTTONS; j++){
            if (queue_matrix[i][j]){
                return true;
            }
        }
    }

    return false;
}

//sjekker om vi skal stoppe i en etasje vi passerer
bool queue_check_floor(int direction){
    int floor = elev_get_floor_sensor_signal();
    int j;
    for(j = 0;j < N_BUTTONS;j++){
        if(floor != -1){
            if(queue_matrix[floor][j]){
                if ((j == 1 && direction == 1 && queue_check_orders_above(floor))){
                     return false;
               }
                if ((j == 0 && direction == -1 && queue_check_orders_below(floor) && !(queue_matrix[floor][j+1]))){
                      return false;
                
                }
                return true;
            }
        }
    }
    return false;
}

//fjerner alle elementer fra køen
void queue_reset_queue(){
    int i;
    int j;
    for(i = 0; i<N_FLOORS;i++){
        for(j=0;j<N_BUTTONS;j++){
            if(!(j ==0 && i == 3)){
                if(!(j==1 && i == 0)){
                    elev_set_button_lamp(j,i,0);
                    queue_matrix[i][j] = 0;
                 }
            }
        }
    }
}