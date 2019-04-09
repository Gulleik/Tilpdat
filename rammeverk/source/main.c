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



int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    int state = 0;
    int direction = 0;
    int last_Floor = 0;
    int next_floor = 0;

    while(1){
        
        
        switch (state) {
            case IDLE:
               last_Floor = orders_update_last_Floor(last_Floor);
                
               if(queue_add_to_queue(last_Floor) && (elev_get_floor_sensor_signal() != -1)){
                   state = REACHED_FLOOR;
               }
                 
               else if (elev_get_floor_sensor_signal() == -1){
                   next_floor = queue_next_floor(last_Floor, direction);
                   direction = queue_next_action_undefined_floor(direction, last_floor, next_floor);
               }
               
               else {
                    direction = queue_next_action(direction);
               }
    
               if(direction!=0){
                   state = ELEV_MOVE;
               }
               if (orders_set_stop()) {
                     state = STOP_PRESSED;           
                }
                break;
        
            case ELEV_MOVE:
                orders_start_elev(direction);
                queue_add_to_queue(last_Floor);
                set_floor_light();
                last_Floor = orders_update_last_Floor(last_Floor);
                if(queue_check_floor(direction)){
                    state = REACHED_FLOOR;
                }
                if (orders_set_stop()) {
                     state = STOP_PRESSED;          
                }
                break;

            case REACHED_FLOOR:
                elev_set_motor_direction(DIRN_STOP);
                queue_remove_from_queue();
                orders_open_door(last_Floor);
                state = IDLE;
                if (orders_set_stop()) {
                     state = STOP_PRESSED;       
                }
                break;

            case STOP_PRESSED:
                elev_set_motor_direction(DIRN_STOP);
                direction = 0;
                queue_reset_queue();
                orders_reset_stop();
                state = IDLE;
                if (orders_set_stop()) {
                     state = STOP_PRESSED;           
                }
                break;
        }
        
    }


    return 0;
}

