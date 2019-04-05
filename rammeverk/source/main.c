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

    while(1){
        
        
        switch (state) {
            case IDLE:
               queue_add_to_queue();
               direction = queue_next_action(direction);
               if(direction!=0){
                   state = ELEV_MOVE;
               }
                break;
        
            case ELEV_MOVE:
                orders_start_elev(direction);
                queue_add_to_queue();
                set_floor_light();
                if(queue_check_floor(direction)){
                    state = REACHED_FLOOR;
                }
                break;

            case REACHED_FLOOR:
                elev_set_motor_direction(DIRN_STOP);
                queue_remove_from_queue();
                orders_open_door();
                state = IDLE;
                break;

            case STOP_PRESSED:
                break;
        }
        

        // Stop elevator and exit program if the stop button is pressed
        if (orders_set_stop()) {
            elev_set_motor_direction(DIRN_STOP);
            orders_reset_stop();
        }
        
        

    }


    return 0;
}



 /*   if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");


    while (1) {

        if (orders_check_order()){
            int floor = get_floor();
            int button_type = get_button_type();
            orders_set_order(button_type, floor);
        }
        

        // Stop elevator and exit program if the stop button is pressed
        if (orders_set_stop()) {
            elev_set_motor_direction(DIRN_STOP);
            orders_reset_stop();
        }
        
    }*/