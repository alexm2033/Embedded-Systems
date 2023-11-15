#include "uop_msb.h"
#include <chrono>
using namespace uop_msb;

//Used this to 
Ticker tick;
osThreadId_t mainThreadID;
Thread t1;

DigitalOut backLight(LCD_BKL_PIN,0);
LCD_16X2_DISPLAY disp;

void isr();
void ldr_Average();


int main(void)
{ 
    mainThreadID = ThisThread::get_id();
    tick.attach(isr, 1ms);

    t1.start(ldr_Average);
    t1.set_priority(osPriorityRealtime);
    t1.join();
  
    while (true) {
        ThisThread::sleep_for(1000ms);
    }
    
}   

void isr() {
    //osSignalSet(mainThreadID, 1);
    t1.flags_set(1);
}

void ldr_Average() {

     AnalogIn ldr(AN_LDR_PIN);
     double x, y = 0.0;
     int count = 0;
     while (true) {
        ThisThread::flags_wait_all(1);
        ThisThread::flags_clear(1);

        x = ldr.read();
        count += 1;
        y += x;
        
        if(count == 1000) {
            y /= 1000;
            printf("ave = %f\n", y);
            disp.cls();
            backLight = 1;
            disp.locate(0, 2);
            disp.printf("LDR average");
            disp.locate(1, 4);
            disp.printf("%f", y);
            count = 0;
            y = 0;
        }
     }
}