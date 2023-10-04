#include "uop_msb.h"
#include <cstdint>
using namespace uop_msb;

// Inputs
DigitalIn SW2(BTN1_PIN);
DigitalIn SW3(BTN2_PIN);

// Outputs
DigitalOut ledRed(TRAF_RED1_PIN);
DigitalOut ledYel(TRAF_YEL1_PIN);
DigitalOut ledGrn(TRAF_GRN1_PIN);

// Timers (modified version from Timer)
TimerCompat tmr_Y;
TimerCompat tmr_R;
TimerCompat tmr_G;

//declare 2 varibles to track the state of the code
uint8_t X = 0;
uint8_t Y = 0;

// THE CODE BELOW IS A SOLUTION
//
// IT WAS FUNDAMENTALLY FLAWED (AND INCOMPLETE)
//
//

int main()
{
    //Start timers
    tmr_Y.start();
    tmr_G.start();
    tmr_R.start();


    while (true) {
      
        if(tmr_Y.elapsed_time() > 500000us) {
            ledYel = !ledYel;
            tmr_Y.reset();
        }
      
        //test switch to see if it has been pressed, test state variable to ensure that switch has just been pressed
        if((SW2.read() == 1) && (X == 0)) {         
            tmr_R.start();          //Start timer to debounce
            X = 1;                  //increment state variable to indicate that state is press debouncing
        }
        
        //test state variable and test if set debounce time has been reached 5ms
         if((X == 1) && (tmr_R.elapsed_time() > 5000us)) {
            tmr_R.stop();           //stop timer
            X = 2;                  //increment state variable to indicate that switch has been pressed
        }

        //test switch to see if it has been released, test state variable 
         if((SW2.read() == 0) && (X == 2)) {
            tmr_R.start();          //start debounce timer
            X = 3;                  //increment state variable to release debiunceing
        }

        //test state variable is in debounce, test elapsed time is 5ms
         if((X == 3) && (tmr_R.elapsed_time() > 5000us)) {
            tmr_R.stop();           //stop timer
            X = 0;                  //reset state variable to waiting for press
            ledRed = !ledRed;       //toggle red led once swutch has been pressed and released
        }

        //comments for switch 2 are equally applicable to switch 3
        if((SW3.read() == 1) && (Y == 0)) {
            tmr_G.start();
            Y = 1;
        }
        
         if((Y == 1) && (tmr_G.elapsed_time() > 5000us)) {
            tmr_G.stop();
            Y = 2;
        }

         if((SW3.read() == 0) && (Y == 2)) {
            tmr_G.start();
            Y = 3;
        }

         if((Y == 3) && (tmr_G.elapsed_time() > 5000us)) {
            tmr_G.stop();
            Y = 0;
            ledGrn = !ledGrn;
        }
    }
}





