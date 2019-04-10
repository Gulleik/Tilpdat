/**
* @file
* @brief A simple library for doing operations on memory
* buffers consisting of integers
*/


typedef enum state_machine { 
    IDLE = 0,
    ELEV_MOVE = 1,
    REACHED_FLOOR = 2,
    STOP_PRESSED = 3
} elev_state_t;


/**
 * @brief Removes all orders from current floor from the queue matrix.
*/
void queue_remove_from_queue();


/**
 * @brief If the elevator is at a defined floor it checks if there is any orders above, 
 * if not it checks if there is any orders above the requested floor
 * @param req_floor: Requested floor, only used if the elevator is in an undefined state
 * @return true if there is an order to be handeled above, false if there are no orders.
*/
bool queue_check_orders_above(int req_floor);

/**
 * @brief If the elevator is at a defined floor it checks if there is any orders below, 
 * if not it checks if there is any orders below the requested floor
 * @param req_floor: Requested floor, only used if the elevator is in an undefined state
 * @return true if there is an order to be handeled below, false if there are no orders.
*/
bool queue_check_orders_below(int req_floor);

/**
 * @brief Checks the queue matrix to see if the elevator should stop at the floor its passing.
 * @param direction: Direction which the elevator is moving.
 * @return true if there is an order to be handeled on the floor, false if not.
*/
bool queue_check_floor(int direction);

/**
 * @brief Deletes all orders fromthe queue matrix
*/
void queue_reset_queue();

/**
 * @brief Updates the programs queue matrix with an incoming order.
 * @param last floor: Last floor elevator visited in order to see if elevator still is in the same floor
 * @return true if on same floor as last floor and false if not
*/
bool queue_add_to_queue(int last_floor);
