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

void orders_open_door_timed(int last_floor);

int orders_update_last_Floor(int last_Floor);

int orders_set_direction(int direction, int last_Floor, int next_floor);

int orders_set_direction_defined_floor(int direction);

int orders_set_direction_undefined_floor(int last_floor, int next_floor);

int orders_set_next_floor(int last_floor, int direction);

bool orders_set_stop();

void orders_open_door();