#include "uop_msb.h"
#include "SwitchTimerLedManager.hpp"
#include "FlashingLED.hpp"
#include <chrono>
#include <cstring>
#include <ratio>
#include <string>
#include <iostream>
#include <cstdlib>


using namespace uop_msb;
using namespace chrono;
using namespace std;

//Dual Digit 7-segment Display
LatchedLED disp(LatchedLED::SEVEN_SEG);

//State machines 
SwitchTimerLedManager fsm1(BTN1_PIN, SwitchTimerLedManager::UP);
SwitchTimerLedManager fsm2(BTN2_PIN, SwitchTimerLedManager::DOWN);
FlashingLED ledGreen(TRAF_GRN1_PIN, 250ms);
FlashingLED ledYellow(TRAF_YEL1_PIN, 350ms);
FlashingLED ledRed(TRAF_RED1_PIN, 450ms);

static UnbufferedSerial serial_port(USBTX, USBRX);

string read();

string st = {"word"};
string on = {"on"};
int main()
{
    while(1){
    char buf[] = {"hello"};
    string s = buf;
    cout<<s<<endl;
    wait_us(500000);
    cout<< "type a word"<<endl;
    st = read();
    cout<<st<<endl;
    cout<<st[0]<<endl;
    cout<<st[1]<<endl;
    cout<<st[2]<<endl;
    
    if(st[1]=='n') {
        cout<<"st = "<<st<<endl;
    }
    else {
        cout<<"error"<<endl;
       //cerr<<st<<endl;
    }
    wait_us(500000);
    }
}


string read() {
    char buff[10] ={0};
    unsigned char i =0;
    char c = 0;

    while(c != '\r') {
        serial_port.read(&c, 1);
        buff[i++] = c;
    }
    string out = buff;
    return out;

}
    // //This is to be displayed and is shared between two state machines
    // int count = 0;

    // //Turn ON the 7-segment display
    // disp.enable(true);
    // disp = 0;
    
    // while (true) {

    //     // **********
    //     //Poll inputs
    //     // **********
    //     fsm1.readInputs();
    //     fsm2.readInputs();
    //     ledGreen.readInputs();
    //     ledYellow.readInputs();
    //     ledRed.readInputs();

    //     // **************
    //     // UPDATE "STATE" 
    //     // **************
    //     fsm1.updateState(count);
    //     fsm2.updateState(count);
    //     ledGreen.updateState();
    //     ledYellow.updateState();
    //     ledRed.updateState();

    //     // UPDATE OUTPUTS
    //     disp = count;
  
    // }
//}





