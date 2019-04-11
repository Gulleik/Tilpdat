/**
* @file
* @brief Library of functions for linking orders and elevator functionality
*/


/**
 * @brief Sets the floor light for the last visited floor.
*/
void orders_set_floor_light();


/**
 * @brief Starts the elevator in the direction defined by the input parameter.
 * @param direction: The direction the elevator should be moving.
*/
void orders_start_elev(int direction);

/**
 * @brief Opens the door for three seconds while recieving orders.
 * @param last_floor: last floor elevator visited in case the elevator ain't at a new one
*/
void orders_open_door_timed(int last_floor);

/**
 * @brief Update last_floor depending on which floor the elevator was in last.
 * @param last_floor: Last floor elevator visited in case the elevator ain't at a new one.
 * @return the last floor the elevator was at.
*/
int orders_update_last_floor(int last_floor);


/**
 * @brief Finds the direction which the elevator should be moving next.
 * @param direction: The last direction the elevator was moving.
 * @param last_floor: Last floor elevator visited in order to see if elevator still is in the same floor
 * @param next_floor: The floor the elevator was originally headed to in case its stopped between two floors
 * @return 1 if direction should be upwards, 0 if the elevator should be standing still, and -1 if the elevator should be moving downwards
*/
int orders_set_direction(int direction, int last_floor, int next_floor);

/**
 * @brief Finds the direction which the elevator should be moving next.
 * @param last_floor: Last floor elevator visited.
 * @param direction: Direction the elevator is headed
 * @return the next floor the elevator is headed to.
*/
int orders_get_next_floor(int last_floor, int direction);

/**
 * @brief Sets door lamp according to input value.
 * @param value: value defining if door lamp should be turned on or off
*/
void orders_set_door_lamp(int value);

