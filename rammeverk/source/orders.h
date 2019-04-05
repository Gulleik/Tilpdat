#include "channels.h"
#include "elev.h"
#include "io.h"
#include "timer.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


void orders_set_order(elev_button_type_t button, int req_floor);

void set_floor_light();

bool orders_check_reached_floor(int req_floor);

void orders_start_elev(int direction);

void orders_open_door();

int orders_set_stop();

int orders_reset_stop();