#include "uop_msb.h"
#include <cstring>
using namespace uop_msb;

// Inputs
DigitalIn SWB(USER_BUTTON); // THIS IS THE BLUE BUTTON
DigitalIn SW2(BTN1_PIN);    // SW2
DigitalIn SW3(BTN2_PIN);    // SW3

// Outputs
DigitalOut ledRed(TRAF_RED1_PIN);
DigitalOut ledYel(TRAF_YEL1_PIN);
DigitalOut ledGrn(TRAF_GRN1_PIN);

// Timers (modified version from Timer)
TimerCompat tmr_debounceB;
TimerCompat tmr_debounce2;
TimerCompat tmr_debounce3;
TimerCompat tmr_flash;

// Switch states
typedef enum {
  WAIT_FOR_PRESS,
  WAITING_1,
  WAIT_FOR_REL,
  WAITING_2
} SWITCH_STATE;

SWITCH_STATE sw_stateB = WAIT_FOR_PRESS;
SWITCH_STATE sw_state2 = WAIT_FOR_PRESS;
SWITCH_STATE sw_state3 = WAIT_FOR_PRESS;

int flash_interval = 500;

int main() {
  // Start flashing timer
  tmr_flash.start();

  while (true) {

    // READ INPUTS **WITHOUT** BLOCKING
    long long flash_time = tmr_flash.read_ms();
    int sw2 = SW2.read();
    int sw3 = SW3.read();
    int swB = SWB.read();
    long long sw2_time = tmr_debounce2.read_ms();
    long long sw3_time = tmr_debounce3.read_ms();
    long long swB_time = tmr_debounceB.read_ms();
    
    //printf("\nserial monitor working\n");

    // Update yellow LED state and mealy outputs
    if (flash_time > flash_interval) {
      ledYel = !ledYel;
      tmr_flash.reset();
    }

    // Update switch2 state machine and mealy outputs
    switch (sw_state2) {

    case WAIT_FOR_PRESS:
      if (SW2 == 1) {
        sw_state2 = WAITING_1;
        tmr_debounce2.start();
        ledGrn = !ledGrn;
      }
      break;
    case WAITING_1:
      if (sw2_time >= 300) {
        sw_state2 = WAIT_FOR_REL;
        tmr_debounce2.stop();
        tmr_debounce2.reset();
      }
      break;

    case WAIT_FOR_REL:
      if (SW2 == 0) {
        sw_state2 = WAITING_2;
        tmr_debounce2.start();
      }
      break;
    case WAITING_2:
      if (sw2_time >= 300) {
        sw_state2 = WAIT_FOR_PRESS;
        tmr_debounce2.stop();
        tmr_debounce2.reset();
      }
      break;

    default:
      sw_state2 = WAIT_FOR_PRESS;
    }

    // Update switch3 state machine and mealy outputs
    // VERY REPETETIVE CODE!
    switch (sw_state3) {

    case WAIT_FOR_PRESS:
      if (sw3 == 1) {
        sw_state3 = WAITING_1;
        tmr_debounce3.start();
        ledRed = !ledRed;
      }
      break;
    case WAITING_1:
      if (sw3_time >= 300) {
        sw_state3 = WAIT_FOR_REL;
        tmr_debounce3.stop();
        tmr_debounce3.reset();
      }
      break;

    case WAIT_FOR_REL:
      if (sw3 == 0) {
        sw_state3 = WAITING_2;
        tmr_debounce3.start();
      }
      break;
    case WAITING_2:
      if (sw3_time >= 300) {
        sw_state3 = WAIT_FOR_PRESS;
        tmr_debounce3.stop();
        tmr_debounce3.reset();
      }
      break;

    default:
      sw_state3 = WAIT_FOR_PRESS;
    }

    switch (sw_stateB) {
    
    case WAIT_FOR_PRESS:
        if (swB == 1) {
            sw_stateB = WAITING_1;
            tmr_debounceB.start();
            //printf("state 1\n");
        }
        break;
    
    case WAITING_1:
        if(swB_time >= 300) {
            sw_stateB = WAIT_FOR_REL;
            tmr_debounceB.stop();
            tmr_debounceB.reset();
            //printf("state 2\n");
        }
        break;

    case WAIT_FOR_REL:
        if (swB == 0) {
            sw_stateB = WAITING_2;
            tmr_debounceB.start();
           // printf("state 3\n");
        }
        break;

    case WAITING_2:
        if(swB_time >= 300) {
            sw_stateB = WAIT_FOR_PRESS;
            tmr_debounceB.stop();
            tmr_debounceB.reset();
            printf("Please enter desired delay time in ms\n");
            scanf("%d", &flash_interval);                       //entering a character breaks the code
            printf("You entered correct integer values. The value was %dms\n", flash_interval);
        }
        break;
    
    default:
        sw_stateB = WAIT_FOR_PRESS;
    }
  }
}
