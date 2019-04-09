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
            //TILSTAND NÅR HEISEN STÅR I RO
            case IDLE:

                //går til stoppstate om stopknappen er trykket inn
                if (elev_get_stop_signal()) {
                    state = STOP_PRESSED;           
                }
                //åpner døren om heisen er i etasjen den kalles til
                if(queue_add_to_queue(last_Floor)){
                   state = REACHED_FLOOR;
                }
                //setter retning og går i kjørstate   
                direction = orders_set_direction(direction, last_Floor, next_floor);
                if(direction!=0){
                   state = ELEV_MOVE;
                }
                break;

            //TILSTAND NÅR HEISEN BEVEGER SEG
            case ELEV_MOVE:
                //starter heis i riktig retning
                orders_start_elev(direction);
                queue_add_to_queue(last_Floor);

                //opdaterer lys, forrige og neste etasje og evt stopperom heisen passerer en etasje
                if(elev_get_floor_sensor_signal() != -1){
                    set_floor_light();

                    //sjekker om vi skal stoppe i en etasje vi passerer
                    if(queue_check_floor(direction)){
                        state = REACHED_FLOOR;
                    }   
                    last_Floor = orders_update_last_Floor(last_Floor);
                    next_floor = orders_set_next_floor( last_Floor, direction);
                }
                //går til stoppstate om stopknappen er trykket inn
                if (elev_get_stop_signal()) {
                     state = STOP_PRESSED;          
                }
                break;

            //TILSTAND SOM INNTREFFER NÅR VI NÅR EN ETASJE VI SKAL STOPPE I
            case REACHED_FLOOR:
                last_Floor = orders_update_last_Floor(last_Floor);
                elev_set_motor_direction(DIRN_STOP);
                set_floor_light();
                queue_remove_from_queue();
                orders_open_door_timed(last_Floor);
                state = IDLE;

                //går til stoppstate om stopknappen er trykket inn
                if (elev_get_stop_signal()) {
                     state = STOP_PRESSED;       
                }
                break;

            //TILSTAND OM STOP HAR BLITT TRYKKET INN
            case STOP_PRESSED:
                elev_set_stop_lamp(1);
                elev_set_motor_direction(DIRN_STOP);
                if(elev_get_floor_sensor_signal() != -1){
                    orders_open_door();
                }
                direction = 0;
                queue_reset_queue();
                if (!elev_get_stop_signal()){
                    state = IDLE;
                    elev_set_stop_lamp(0);
                    if(elev_get_floor_sensor_signal() != -1){
                        orders_open_door_timed(last_Floor);
                    }
                }
                break;
        }
        
    }


    return 0;
}

//gullis er løk