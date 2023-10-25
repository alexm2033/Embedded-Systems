#include "TrafficLight.h"
#include <iostream>

DigitalInOut grn2LED(TRAF_GRN2_PIN, PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 1);
DigitalInOut red2LED(TRAF_RED2_PIN, PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 1);
DigitalInOut yel2LED(TRAF_YEL2_PIN, PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 1);
//Contructor
TrafficLight::TrafficLight(PinName redPin, PinName yellowPin, PinName greenPin) 
                                                        : redLED(redPin), yellowLED(yellowPin), greenLED(greenPin)
{
    // These objects are already initialised in the member initialisation list above
    redLED = 1;
    yellowLED = 0;
    greenLED = 0;
    // Timer off
    flashYellow(false);
}

//Destructor
TrafficLight::~TrafficLight()
{
    redLED = 1;
    yellowLED = 0;
    greenLED = 0;
} 

void TrafficLight::stop() {
    State = STOP;
    updateOutput();
}

void TrafficLight::Set_Flash_Speed() {
    cout<<"input flashspeed in ms"<<endl;
    cin>>flashspeed;
    updateOutput();
}

void TrafficLight::Get_Flash_Speed() {
    cout<<"Current flash interval is "<<flashspeed<<"ms"<<endl;
}

// possible responses to switch activation
void TrafficLight::buttonResponse(int x) {
switch(x) {

    case 1:
        s = lights.nextState();
        break;

    case 2:
        lights.stop(); 
        break;

    case 4:
        lights.Set_Flash_Speed();
        break;

    case 8:
        lights.Get_Flash_Speed();
        break;
    } 
                                  
}
           
// Interrupt Service Routine (ISR)
void TrafficLight::yellowFlashISR() {
    yellowLED = !yellowLED;
}

// Private member function to switch flasher on or off
void TrafficLight::flashYellow(bool flash) {
    t.detach(); //Turn off ticker
    if (flash) {
        //Turn on ticker ..... Hmmm, interrupts!
        //t.attach(callback(this, &TrafficLight::yellowFlashISR), 200ms);
        t.attach(callback(this, &TrafficLight::yellowFlashISR), chrono::milliseconds(flashspeed) );
    }
}

// Moore Machine - update outputs
void TrafficLight::updateOutput()
{
    switch (State)
    {
        case STOP:
            flashYellow(false);
            redLED = 1;
            yellowLED = 0;
            greenLED = 0;
            break;
        case READY:
            flashYellow(false);
            redLED = 1;
            yellowLED = 1;
            greenLED = 0;
            break;
        case GO:
            flashYellow(false);
            redLED = 0;
            yellowLED = 0;
            greenLED = 1;
            break;
        case WARNING:
            redLED = 0;
            flashYellow(true);
            greenLED = 0;
            break;                
    }       
}

// Moore machine - next state logic
TrafficLight::LIGHT_STATE TrafficLight::nextState()
{
    // Update State
    switch (State)
    {
        case STOP:
            State = READY;
            break;
        case READY:
            State = GO;
            break;
        case GO:
            State = WARNING;
            break;
        case WARNING:
            State = STOP;
            break;
    }

    //As it says
    updateOutput();

    //Return the current state (for information)
    return State; 
} 