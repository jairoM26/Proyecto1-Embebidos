#ifndef _GPIO_H
#define _GPIO_H

void setup_io();
void configure_pin(int pin);
void set_pin(int pin,int value);
int get_pin(int pin);


#endif
