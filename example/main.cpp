#define F_CPU 1000000
#include "firmware/led.hpp"
#include "firmware/switch.hpp"
#include "firmware/pwm.hpp"
#include "firmware/callback.hpp"
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <util/delay.h>
#include <avr/interrupt.h>

auto led_green = LED_D0();
auto switch1 = SWITCH_D1();
auto pwm = PWM0A();

int main(void)
{
    uint8_t t = 0;

    while(1){
    }
}

void SensorCallback()
{
    switch1.update();
}

void MainCallback()
{
    if(switch1()){
        led_green.on();
    }else{
        led_green.off();
    }
}
