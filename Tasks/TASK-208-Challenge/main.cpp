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

uint8_t X = 0;
uint8_t Y = 0;

// THE CODE BELOW IS NOT A SOLUTION
//
// IT IS FUNDAMENTALLY FLAWED (AND INCOMPLETE)
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
      
        if((SW2.read() == 1) && (X == 0)) {
            tmr_R.start();
            X = 1;
        }
        
         if((X == 1) && (tmr_R.elapsed_time() > 5000us)) {
            tmr_R.stop();
            X = 2;
        }

         if((SW2.read() == 0) && (X == 2)) {
            tmr_R.start();
            X = 3;
        }

         if((X == 3) && (tmr_R.elapsed_time() > 5000us)) {
            tmr_R.stop();
            X = 0;
            ledRed = !ledRed;
        }

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





