#include <avr/interrupt.h>
#ifndef F_CPU
#  error "#define F_CPU needed"
#endif

#define CALLBACK_CYCLE 1000

void init(){
    // タイマ設定
    uint32_t b[8] = {0,1,8,32,64,128,256,1024};
    uint8_t i=0;
    uint32_t T = 0;
    while(i < 7 && T < F_CPU){
        i++;
        T = b[i]*0xff*CALLBACK_CYCLE;
    }
    T = F_CPU;
    T /= (CALLBACK_CYCLE * b[i]);
    if(T > 0xff){
        T = 0xff;
    }
    TCCR2A = 2;             // CTC動作
    TCCR2B = i;             // 分周設定
    OCR2A = (uint8_t) T;    // 周期設定
    OCR2B = OCR2A/2;        // センサークロック
    TIMSK2 = 0b110;         // 割り込み許可
    sei();
}

void SensorCallback();
void MainCallback();

ISR(TIMER2_COMPA_vect)
{
    MainCallback();
}

ISR(TIMER2_COMPB_vect)
{
    SensorCallback();
}
