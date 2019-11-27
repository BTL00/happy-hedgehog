#ifndef _MOVEMENTC_
#define _MOVEMENTC_

#include "gpiohs.h"
#include <stdlib.h>

void prepare_gpio_for_tb6612() {

	gpiohs_set_drive_mode(3, GPIO_DM_OUTPUT);
    gpiohs_set_drive_mode(4, GPIO_DM_OUTPUT);
    gpiohs_set_drive_mode(5, GPIO_DM_OUTPUT);
    gpiohs_set_drive_mode(6, GPIO_DM_OUTPUT);

    gpiohs_set_pin(3, GPIO_PV_LOW);
    gpiohs_set_pin(4, GPIO_PV_LOW);
    gpiohs_set_pin(5, GPIO_PV_LOW);
    gpiohs_set_pin(6, GPIO_PV_LOW);
}


void move_forward() {
 gpiohs_set_pin(3, GPIO_PV_HIGH);
 gpiohs_set_pin(4, GPIO_PV_LOW);
 gpiohs_set_pin(5, GPIO_PV_LOW);
 gpiohs_set_pin(6, GPIO_PV_HIGH);

}

void move_backward() {

 gpiohs_set_pin(3, GPIO_PV_LOW);
 gpiohs_set_pin(4, GPIO_PV_HIGH);
 gpiohs_set_pin(5, GPIO_PV_HIGH);
 gpiohs_set_pin(6, GPIO_PV_LOW);

}

void turn_right() {
 gpiohs_set_pin(3, GPIO_PV_HIGH);
 gpiohs_set_pin(4, GPIO_PV_LOW);
 gpiohs_set_pin(5, GPIO_PV_LOW);
 gpiohs_set_pin(6, GPIO_PV_LOW);


}


void turn_left() {
 gpiohs_set_pin(1, GPIO_PV_LOW);
 gpiohs_set_pin(2, GPIO_PV_LOW);
 gpiohs_set_pin(3, GPIO_PV_LOW);
 gpiohs_set_pin(4, GPIO_PV_HIGH);

}
void stop() {
 gpiohs_set_pin(1, GPIO_PV_HIGH);
 gpiohs_set_pin(2, GPIO_PV_HIGH);
 gpiohs_set_pin(3, GPIO_PV_HIGH);
 gpiohs_set_pin(4, GPIO_PV_HIGH);

}
#endif