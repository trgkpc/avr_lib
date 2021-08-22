#pragma once
#include <stdint.h>
#include <avr/io.h>

struct PWM
{
    PWM()
    {
    }

    virtual void set(uint8_t) = 0;
};

struct PWM0A : PWM
{
    PWM0A() : PWM()
    {
        TCCR0A = (0b01 << 6) + (TCCR0A & (0x3c)) + (0b00);
        TCCR0B = (TCCR0B & 0xf0) + (0 << 3) + (0b001);
    }

    void set(uint8_t compare) override
    {
        OCR0A = compare;
    }
};
