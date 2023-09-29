#include "mbed.h"

// Hardware Definitions
#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2
#define USER_GRN_PIN  PB_0
#define USER_BLUE_PIN PB_7
#define USER_RED_PIN  PB_14
// Objects
// DigitalOut grn(TRAF_GRN1_PIN);
// DigitalOut yel(TRAF_YEL1_PIN);
// DigitalOut red(TRAF_RED1_PIN,1);
BusOut leds(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN);
BusOut leds_B(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN, USER_GRN_PIN, USER_BLUE_PIN, USER_RED_PIN);

int main()
{
    while (true) {
        leds_B = 0;   //Binary 000
        wait_us(500000);
        leds_B = 63;   //Binary 111111
        wait_us(500000);    

        for (int i=0; i<8; i++)
        {
            leds = i;
            wait_us(500000);
        }
    }
}


