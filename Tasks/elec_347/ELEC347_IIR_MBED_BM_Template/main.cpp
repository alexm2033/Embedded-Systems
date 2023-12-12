#include "mbed.h"
#include "main.h"
#include "F429_Mega_Shell_Header.h"
#include <chrono>
#include <cstdint>
#include "BP_4KHz_Fc_35KHz_Fs_5N.h"
using namespace std;
using namespace chrono;

//MBED Class Instances follows
DigitalOut SampLED(LED1);              //Digital Output  (GREEN LED is PB_3, D13 You can use an Oscilloscope on This pin to confirm sample rate)

AnalogIn  Ain(PA_6);                    //Analog Input (Signal Input 0 to +3 Volts)
AnalogOut Aout(PA_4);                   //Analog Output (Signal Input 0 to +3 Volts)

Ticker sample_timer;

// B - Numerator coefficients
float b0 = 0.0025;//0.0134;
float b1 = -0.0;
float b2 = -0.0050;//-0.0268;
float b3 = -0.0;
float b4 = 0.0025;//0.0134;

// A - Denominator coefficients
float a0 = 1.0000; 
float a1 = -3.8111;//-3.6872; 
float a2 = 5.4887;//5.1190; 
float a3 = -3.5404;//-3.1762; 
float a4 = 0.8632;//0.7445;

//Ticker routine PROTOTYPE to service samples from Analogue IP and port to Analogue Output
void sampler(void);

int main() {
   printf("ELEC347 IIR Demo\n");
   myLCD.cls();
   myLCD.printf("ELEC347 IIR Demo");
   float sample_rate=(1.0/Fs)*1000000.0;
    //long long sample_rate=(1/Fs)*1000; //Calculate the number of uS required for a Frequency Sampling Rate
                                          //Fs held in init.h
    sample_timer.attach_us(&sampler,(int)sample_rate);
                                          //Ticker Instance serviced by routine at a repeat rate in microseconds
    //sample_timer.attach(&sampler, milliseconds(sample_rate));

    while(1) {
          sleep();
    }
}

//Ticker routine to service samples from Analogue IP and port to Analogue Output
void sampler(void)
{
    SampLED = ON;       //LED Indicates start of sampling

    xn=Ain;               //Input ADC. N.B. ADC in MBED is 0.0 to 1.0 float!!!!!!

    centreTap = xn*b0 + xnm1*b1 + xnm2*b2 + xnm3*b3 + xnm4*b4;  //IIR Filter

    yn = centreTap*a0 - a1*ynm1 - a2*ynm2  - a3*ynm3 - a4*ynm4; //Result in yn
  
    Aout=yn+0.5f;       //Output resultant to DAC. Again MBED uses 0.0 to 1.0 float!!!!!! and Offset to give 0 to 3V3 range

    uint32_t count = 0;
    uint8_t beatCount = 0;
    buff[count] = yn;
    //count  = (count+1) % 2400;
    float a = buff[count]-buff[count-1];
    float b = buff[count]-buff[count+1];

    if((a<0)&&(b<0)) {
        beats[beatCount].amp = yn;
        beats[beatCount].index = beatCount;
        beatCount = (beatCount+1 % 3);
    }
    

    printf("xn=%3.5f, xnm1=%3.5f, xnm2=%3.5f, xnm3=%3.5f, xnm4=%3.5f\n", xn, xnm1, xnm2, xnm3, xnm4);
    printf("yn=%3.5f, ynm1=%3.5f, ynm2=%3.5f, ynm3=%3.5f, ynm4=%3.5f\n", yn, ynm1, ynm2, ynm3, ynm4);
  
  	//THESE NEED TO BE LOADED IN THIS ORDER OTHERWISE ALL xnm VALUES WILL BECOME THE SAME AS xn
    xnm4 = xnm3;
    xnm3 = xnm2;
    xnm2 = xnm1;
    xnm1 = xn;	
	
    //THESE NEED TO BE LOADED IN THIS ORDER OTHERWISE ALL ynm VALUES WILL BECOME THE SAME AS yn
    ynm4 = ynm3;
    ynm3 = ynm2;
    ynm2 = ynm1;
    ynm1 = yn;

    SampLED = OFF;      //LED Indicates end of sampling
}

