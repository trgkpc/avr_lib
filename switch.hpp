#pragma once
#include <avr/io.h>
#include <stdbool.h>

struct AbstSWITCH
{
    AbstSWITCH()
    {
    }

    virtual void update() = 0;
    virtual bool operator()() = 0;
    virtual bool upper() = 0;
    virtual bool downer() = 0;
    virtual uint8_t time() = 0;
};

#define DDRX    _SFR_IO8(DDRX_ADDR)
#define PORTX   _SFR_IO8(PORTX_ADDR)
#define PINX   _SFR_IO8(PINX_ADDR)
#define SWITCH_BIT (1<<(id))
constexpr uint8_t LOCK_TIME = 20;
template <uint8_t DDRX_ADDR, uint8_t PORTX_ADDR, uint8_t PINX_ADDR, uint8_t id>
struct SWITCH : AbstSWITCH
{
    SWITCH()
        : lock_time(0), push_time(0), status(false), last(false)
    {
        DDRX &= ~LED_BIT;
        PORTX |= LED_BIT;
    }

    void update() override
    {
        last = status;
        status = !(PINX & SWITCH_BIT);
        if(lock_time > 0){
            status = last;
            lock_time--;
        }else if(last^status){
            lock_time = LOCK_TIME;
        }

        if(status){
            push_time++;
        }else{
            push_time = 0;
        }
    }

    bool operator()() override
    {
        return status;
    }

    bool upper() override
    {
        bool edge = last^status;
        return edge&status;
    }

    bool downer() override
    {
        bool edge = last^status;
        return edge&last;
    }

    uint8_t time() override
    {
        return push_time;
    }


private:
    uint8_t lock_time;
    uint8_t push_time;
    bool status;
    bool last;
};

#include "address/switch.hpp"
