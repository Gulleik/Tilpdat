




typedef enum state_machine { 
    IDLE = 0,
    ELEV_MOVE = 1,
    REACHED_FLOOR = 2,
    STOP_PRESSED = 3
} elev_state_t;



void queue_remove_from_queue();

bool queue_check_orders_above();

bool queue_check_orders_below();

int queue_next_action(int direction);

bool queue_check_floor(int direction);

void queue_reset_queue();

bool queue_add_to_queue(int last_floor);