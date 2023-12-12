#include "mbed.h"
#include "main.h"
#include "F429_Mega_Shell_Header.h"
#include "BP_4KHz_Fc_35KHz_Fs_5N.h"
#include "math.h"
#include <cstdint>

 
int x =0;
#define DAC_FS      1200

#define ADC_FS      1200

  //alex
    uint32_t j = 0;
    uint32_t l = 0;
    //uint32_t beatcount = 0;
    float threshold = 0.0;
    float sumT = 0;
    float sumA = 0;
    float heartrate = 0;
    float amp[5];
    int index[5];
    double val;
    //alex

AnalogOut dac_test_out(PA_4);
AnalogOut dac_threshold(PA_5);

Thread process_Data;

//UnbufferedSerial serial(USBTX,USBRX,115200);

AnalogIn ain(PA_6);

Ticker adc_tick;

 float y = 12.086447;

void process();

void adc_tick_isr();

 
double a1[3]={1.000000000, -1.862275270, 0.958550747};
double b1[3]={1.000000000, -1.902113033, 1.000000000};

double a2[3]={1.000000000, -1.584145964, 0.958550747};
double b2[3]={1.000000000, -1.618033989, 1.000000000};

double a3[3]={1.000000000, -1.150949414, 0.958550747};
double b3[3]={1.000000000, -1.175570505, 1.000000000};

double a4[5]={1.000000000,-3.687207406,5.118965371,-3.176238088,0.744480189};
double b4[5]={0.013397512,-0.000000000,-0.026795024,-0.000000000,0.013397512};

 
class IIRFilter{

private:

 

    unsigned int num_coeffs;

    double* x;

    double* y;

    double* a;

    double* b;

    double acc=0.0;

    double bcc=0.0;

    int write_index=0;

    

public:

 

    IIRFilter(int n, double* aa, double* bb){

        this->num_coeffs = n;

        x = (double*)malloc(sizeof(double)*n);

        y = (double*)malloc(sizeof(double)*n);

        a = (double*)malloc(sizeof(double)*n);

        b = (double*)malloc(sizeof(double)*n);

 

        for(int i=0;i<n;i++){

            this->a[i] = aa[i];

            this->b[i] = bb[i];

            this->x[i] = 0.0;

            this->y[i] = 0.0;

        }

    }

    ~IIRFilter(){

        free(a);

        free(b);

        free(x);

        free(y);

    }

 

    double compute(double sample){

        x[write_index] =sample;

        acc = 0.0;

        bcc = b[0]*x[write_index];

        uint8_t k=write_index <= 0 ? (num_coeffs-1) : write_index-1;

 

        for(uint8_t r =1;r<num_coeffs;r++){

            acc =  acc+ (a[r] * y[k]);

            bcc = bcc + b[r] * x[k];

            k = k <= 0 ? (num_coeffs-1) : k-1;

        }

 

        y[write_index] = bcc-acc;

        write_index = write_index >= (num_coeffs-1) ? 0 : write_index+1;

        return y[write_index];

    }

};

IIRFilter notch_60Hz(3,a1,b1);
IIRFilter notch_120Hz(3,a2,b2);
IIRFilter notch_180Hz(3,a3,b3);
IIRFilter bandpass(5,a4,b4);

 

int main()

{
    printf("float %f\n", y);

    process_Data.start(process);

    adc_tick.attach_us(adc_tick_isr, (us_timestamp_t) (1000000.0f/(float)ADC_FS));

 

    while (true) {

        ThisThread::sleep_for(osWaitForever);

    }

}

void adc_tick_isr(){

    val = (double)ain;
    process_Data.flags_set(1);

    //process(val);

}

 

void process(){
    ThisThread::flags_wait_any(1);
    ThisThread::flags_clear(1);

    val = (val - 0.5);
    
    double yn1 = notch_60Hz.compute(val);
    double xn2 = yn1;
   // + 0.5;

    double yn2 = notch_120Hz.compute(xn2);
    double xn3 = yn2;

    double yn3 = notch_180Hz.compute(xn3);
    double xn4 = yn3;

    float yn4 = bandpass.compute(xn4);
    dac_test_out = yn4+0.2; 
  //alex
  buff[j] = (yn4*yn4);        //square value to magnify peaks and remove negative values
    //printf("buff %d = %5.3f,\tThreshold = %5.3f\n", j, buff[j], threshold);
    int c = j-1;
    int d = j-2;
    if(buff[j]>threshold) {                     //test if value is over threshold
        float a = buff[c]-buff[d];
        float b = buff[c]-buff[j];
        //printf("a = %5.3f  b = %5.3f\n",a,b);
        if((a>0)&&(b>0)) {                      //test if value is a peak
            amp[l] = buff[c];                   //record in circular buffer
            index[l] = (c);

            //printf("j-1 = %d,\tbuff j-1 = %5.3f,\tbeatcount = %d,\tamp  = %5.3f,\tindex = %d\n", c, buff[c], l,  amp[l], index[l]);

            l = (l+1) % 5;                      //update index
           // printf("peak detected: %5.3f\n", buff[c]);
            
            for(int i=0; i<5; i++) {            
                sumT += amp[i];
            }
            threshold = (sumT/5)*0.5;               //calculate average of last 5 peaks and set threshold
            sumT = 0;

            for(int i=4; i>0; i--) {
                sumA += (((index[i] - index[i-1]) + buffSize) % buffSize);          //calculate averge period of last 5 peaks
            }

            heartrate = ((1/((sumA/5)*(1.0/Fs)))*60)*0.8;                   //calculate heart rate in BPM
            sumA = 0;   
        }
    } 
    if(j%1200 == 0){
            printf("\x1b[%d;100HHeartrate = %3.1f BPM\n", x++, heartrate);          //print heartrate every second
    }
    j = (j+1) % buffSize;                   //update buffer index

    //alex
}

    