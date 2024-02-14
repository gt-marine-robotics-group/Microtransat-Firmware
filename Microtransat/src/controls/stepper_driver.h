#include "board_layout.h"


void stepper_driver_open();

void stepper_driver_close(); 

int stepper_driver_read(); 

void stepper_driver_write(int num_steps);

void stepper_driver_update();
