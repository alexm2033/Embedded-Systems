#include "mbed.h"
#include "uop_msb.h"
#include "TrafficLight.h"
#include <chrono>
#include <iostream>
using namespace uop_msb;

TrafficLight lights;
DigitalIn sw(USER_BUTTON);
DigitalIn btn3(BTN3_PIN);

BusInOut switches(USER_BUTTON, BTN1_PIN, BTN2_PIN,BTN3_PIN);

TrafficLight::LIGHT_STATE s;

TimerCompat tmr_Db;

//Switch_State switch_Blue = WAIT_FOR_PRESS;
Switch_State buttons = WAIT_FOR_PRESS;

//chrono::milliseconds flashspeed = 200ms;
long long flashspeed = 200;

int main() {
switches.input();
btn3.mode(PinMode::PullDown);

    while(true) {

        long long swB_time = tmr_Db.read_ms();

        switch(buttons) {

        case WAIT_FOR_PRESS:
            if((switches == 1)||(switches==2)||(switches==4)||(switches==8)){
                int state_of_switches = switches;
                buttons = DEBOUNCE_1;
                tmr_Db.start();
                lights.buttonResponse(state_of_switches);                
            }
            break;

        case DEBOUNCE_1:
            if(swB_time > 300) {
                buttons = WAIT_FOR_REL;
                tmr_Db.stop();
                tmr_Db.reset();
            }
            break;

        case WAIT_FOR_REL:
            if(switches == 0) {
                buttons = DEBOUNCE_2;
                tmr_Db.start();
            }
            break;

        case DEBOUNCE_2:
            if(swB_time > 300) {
                buttons = WAIT_FOR_PRESS;
                tmr_Db.stop();
                tmr_Db.reset();
            }
            break;

        default:
            buttons = WAIT_FOR_PRESS;
        }
    }
}

