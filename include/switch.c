#include "switch.h"
void switch_init(Switch_Config*s){gpio_pinMode(s->port,s->pin,INPUT);if(s->pullup)gpio_pinWrite(s->port,s->pin,HIGH);}
uint8_t switch_read(Switch_Config*s){return gpio_pinRead(s->port,s->pin)==s->active_level;}
