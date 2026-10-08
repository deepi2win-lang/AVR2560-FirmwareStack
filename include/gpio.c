#include "gpio.h"
void gpio_portMode(GPIO_Port p,uint8_t m){volatile uint8_t*r=(volatile uint8_t*)p.ddr_address;*r=m;}
void gpio_portWrite(GPIO_Port p,uint8_t v){volatile uint8_t*r=(volatile uint8_t*)p.port_address;*r=v;}
uint8_t gpio_portRead(GPIO_Port p){volatile uint8_t*r=(volatile uint8_t*)p.pin_address;return *r;}
void gpio_pinMode(GPIO_Port p,uint8_t b,uint8_t m){volatile uint8_t*r=(volatile uint8_t*)p.ddr_address;if(m)*r|=(uint8_t)(1U<<b);else *r&=(uint8_t)~(1U<<b);}
void gpio_pinWrite(GPIO_Port p,uint8_t b,uint8_t v){volatile uint8_t*r=(volatile uint8_t*)p.port_address;if(v)*r|=(uint8_t)(1U<<b);else *r&=(uint8_t)~(1U<<b);}
uint8_t gpio_pinRead(GPIO_Port p,uint8_t b){volatile uint8_t*r=(volatile uint8_t*)p.pin_address;return (uint8_t)((*r>>b)&1U);}
void gpio_pinToggle(GPIO_Port p,uint8_t b){volatile uint8_t*r=(volatile uint8_t*)p.port_address;*r^=(uint8_t)(1U<<b);}
