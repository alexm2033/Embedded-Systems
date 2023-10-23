#include "mbed.h"
#include "uop_msb.h"
#include "TrafficLight.h"
using namespace uop_msb;

TrafficLight lights;
DigitalIn sw(USER_BUTTON);
DigitalIn sw2(BTN1_PIN);

TrafficLight::LIGHT_STATE s;

TimerCompat tmr_DbB;
TimerCompat tmr_Db2;

Switch_State switch_Blue = WAIT_FOR_PRESS;
Switch_State switch_2 = WAIT_FOR_PRESS; 

// int main()
// {
//     while (true) {

//         //Wait for switch press
//         while (sw==0);

//         //Update lights
//         s = lights.nextState();

//         //Debounce switch
//         wait_us(300000);

//         //Wait for switch release
//         while (sw==1);

//         //Switch debounce
//         wait_us(300000);
        
//     }
// }

int main() {

    while(true) {

        int swB = sw.read();
        int btn2 = sw2.read();
        long long swB_time = tmr_DbB.read_ms();
        long long btn2_time = tmr_Db2.read_ms();

        switch(switch_Blue) {

        case WAIT_FOR_PRESS:
            if(swB == 1) {
                switch_Blue = DEBOUNCE_1;
                tmr_DbB.start();
                s = lights.nextState();
            }
            break;

        case DEBOUNCE_1:
            if(swB_time > 300) {
                switch_Blue = WAIT_FOR_REL;
                tmr_DbB.stop();
                tmr_DbB.reset();
            }
            break;

        case WAIT_FOR_REL:
            if(swB == 0) {
                switch_Blue = DEBOUNCE_2;
                tmr_DbB.start();
            }
            break;

        case DEBOUNCE_2:
            if(swB_time > 300) {
                switch_Blue = WAIT_FOR_PRESS;
                tmr_DbB.stop();
                tmr_DbB.reset();
            }
            break;

        default:
            switch_Blue = WAIT_FOR_PRESS;
        }

        switch(switch_2) {

        case WAIT_FOR_PRESS:
            if(btn2 == 1) {
                switch_2 = DEBOUNCE_1;
                tmr_Db2.start();
                lights.stop();
            }
            break;

        case DEBOUNCE_1:
            if(btn2_time > 300) {
                switch_2 = WAIT_FOR_REL;
                tmr_Db2.stop();
                tmr_Db2.reset();
            }
            break;

        case WAIT_FOR_REL:
            if(btn2 == 0) {
                switch_2 = DEBOUNCE_2;
                tmr_Db2.start();
            }
            break;

        case DEBOUNCE_2:
            if(btn2_time > 300) {
                switch_2 = WAIT_FOR_PRESS;
                tmr_Db2.stop();
                tmr_Db2.reset();
            }
            break;

        default:
            switch_2 = WAIT_FOR_PRESS;
        }

    }
}

