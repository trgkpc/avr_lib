#pragma once
#include <avr/io.h>

struct AbstLED
{
    AbstLED()
    {
    }

    virtual void on() = 0;
    virtual void off() = 0;
    virtual void toggle() = 0;
};

#define DDRX    _SFR_IO8(DDRX_ADDR)
#define PORTX   _SFR_IO8(PORTX_ADDR)
#define PINX   _SFR_IO8(PINX_ADDR)
#define LED_BIT (1<<(id))
template <uint8_t DDRX_ADDR, uint8_t PORTX_ADDR, uint8_t PINX_ADDR, uint8_t id>
struct LED : AbstLED
{
    LED()
    {
        DDRX |= LED_BIT;
        PORTX &= ~LED_BIT;
    }

    void on() override
    {
        PORTX |= LED_BIT;
    }

    void off() override
    {
        PORTX &= ~LED_BIT;
    }

    void toggle() override
    {
        PINX = LED_BIT;
    }
};

#include "address/led.hpp"
