#ifndef __TRAFFICLIGHT__
#define __TRAFFICLIGHT__

#include "mbed.h"
#include <chrono>
using namespace chrono;

#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2
#define TRAF_GRN2_PIN PC_9
#define TRAF_YEL2_PIN PC_8
#define TRAF_RED2_PIN PC_7
#define BTN1_PIN PG_0 
#define BTN2_PIN PG_1
#define BTN3_PIN PG_2 // No pull down
#define BTN4_PIN PG_3 // No pull down
#define pp PinName redPin, PinName yellowPin, PinName greenPin


typedef enum {WAIT_FOR_PRESS, DEBOUNCE_1, WAIT_FOR_REL, DEBOUNCE_2} Switch_State;

//extern chrono::milliseconds flashspeed;
extern long long flashspeed;

class TrafficLight 
{
    public:
    typedef enum {STOP, READY, GO, WARNING} LIGHT_STATE;
    

    private:
    DigitalOut redLED;
    DigitalOut yellowLED;
    DigitalOut greenLED;
    
    Ticker t;
    LIGHT_STATE State;

    void yellowFlashISR();
    void flashYellow(bool flash);
    void updateOutput();
    

    public:
    //Constructor
    TrafficLight(PinName redPin = TRAF_RED1_PIN, PinName yellowPin = TRAF_YEL1_PIN, PinName greenPin=TRAF_GRN1_PIN); 

    //Destructor
    ~TrafficLight();

    //reset to red
    void stop();

    //change flash spped
    void Set_Flash_Speed();

    //display flash speed in ms
    void Get_Flash_Speed();

    void buttonResponse(int x);

    //Advance the traffic lights to the next state
    LIGHT_STATE nextState();

};

extern TrafficLight lights;
extern TrafficLight::LIGHT_STATE s;
#endif