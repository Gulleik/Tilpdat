#include "channels.h"
#include "elev.h"
#include "io.h"

#include <assert.h>
#include <stdlib.h>

void init(){
    int floor = elev_get_floor_sensor_signal(void)
    while(floor != 0){
        elev_set_motor_direction(DIRN_DOWN);
    }
     elev_set_motor_direction(DIRN_STOP);
}
}