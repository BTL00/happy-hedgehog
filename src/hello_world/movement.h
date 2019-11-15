#ifndef _MOVEMENTH_
#define _MOVEMENTH_


#ifdef __cplusplus
extern "C" {
#endif

void prepare_gpio_for_tb6612();
void move_forward();
void move_backward();
void turn_right();
void turn_left();
void stop();

#ifdef __cplusplus
}
#endif

#endif