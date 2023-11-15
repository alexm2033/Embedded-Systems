#include "uop_msb.h"
using namespace uop_msb;

#include "string.h"
#include <stdio.h>
#include <ctype.h>
#include "sample_hardware.hpp"

#define SWITCH1_RELEASE 1

void thread1();
void thread2();
void switchISR();

InterruptIn btnA(BTN1_PIN);
InterruptIn btnB(BTN2_PIN);



const uint32_t TIMEOUT_mS = 30000;

//Threads
Thread t1;
Thread t2;

//Class type
class message_t {
public:    
    float fValue;    
    int sw1State;
    int sw2State;
    
    //Constructor
    message_t(float f, int s1, int s2) {
        fValue = f;
        sw1State = s1;
        sw2State = s2;    
    }
};
 
//Memory Pool - with capacity for 16 message_t types
MemoryPool<message_t, 16> mpool;

//Message queue - matched to the memory pool
Queue<message_t, 16> queue;

// Call this on precise intervals
void switchISR() {
    t2.flags_set(1);
    Watchdog::get_instance().kick();
}

//Normal priority thread (consumer)
void thread1() 
{      
    while (true) {
        message_t* payload;

        //Block on the queue
        bool ok = queue.try_get_for(10s, &payload);
        
        //Check status
        if (ok) {
            //Make a copy
            message_t msg(payload->fValue, payload->sw1State, payload->sw2State);
            //We are done with this, so give back the memory to the pool
            mpool.free(payload);
            
            //Echo to the terminal
            printf("Float Value: %.2f\t",    msg.fValue);
            printf("SW1: %u\t",              msg.sw1State);
            printf("SW2: %u\n\r",            msg.sw2State);
        } else {
            //TODO: Handle timeout
            printf("Timeout!\n");
        }
             
    } //end while
}

void thread2() {
    while(true) {

        ThisThread::flags_wait_all(1);
        ThisThread::sleep_for(100ms);
        ThisThread::flags_clear(1);
            //Read sample - make a copy
        float sample = 0.01f*(float)(rand() % 100);

        //Grab switch state
        uint32_t switch1State = buttonA;
        uint32_t switch2State = buttonB;

        
        //Allocate a block from the memory pool (non blocking)
        message_t* message = mpool.try_alloc();
        if (message == NULL) {
            //Out of memory
            redLED = 1;
            return;   
        }
        
        //Fill in the data
        message->fValue = sample;
        message->sw1State = switch1State;
        message->sw2State = switch2State;
        
        //Write to queue
        bool ok = queue.try_put(message);    //Note we are sending the "pointer"
        
        //Check if succesful
        if (!ok) {
            redLED = 1; 
            mpool.free(message);
            return;
        }
    }
}


// Main thread
int main() {
    Watchdog &watchdog = Watchdog::get_instance();
    watchdog.start(TIMEOUT_mS);

    redLED    = 0;
    yellowLED = 0;
    greenLED  = 0;

    ThisThread::sleep_for(100ms);

    redLED    = 1;
    yellowLED = 1;
    greenLED  = 1;

    ThisThread::sleep_for(500ms);

    redLED    = 0;
    yellowLED = 0;
    greenLED  = 0;

    watchdog.start(TIMEOUT_mS);

    btnA.fall(&switchISR);
    btnB.fall(&switchISR);
          
    //Start message
    printf("Welcome\n");           
   
    // //Hook up interrupts   
    // Ticker timer; 
    // timer.attach(&switchISR, 100ms);
               
    //Threads
    t1.start(thread1);
    t2.start(thread2);
    
    printf("Main Thread\n");
    while (true) {
        ThisThread::sleep_for(5s);
        puts("Main Thread Alive");
    }
}

