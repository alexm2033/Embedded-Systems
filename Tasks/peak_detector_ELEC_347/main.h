#define ON  1
#define OFF 0

unsigned short ADC_DATA;
float centreTap1 = 0.0;
float centreTap2 = 0.0;
float centreTap3 = 0.0;
float centreTap4 = 0.0;
//ALL unsigned short VALUES HAVE BEEN CHANGED TO FLOATS OTHERWISE THE COEFFICIENT MULTIPLICATIONS WILL BE ROUNDED TO THE NEAREST INTEGER WHICH IN SOME CASES IS ZERO.
float xn_1   = 0.0;  		
float xnm1_1 = 0.0;
float xnm2_1 = 0.0;
float xnm3_1 = 0.0;
float xnm4_1 = 0.0;

float xn_2   = 0.0;  		
float xnm1_2 = 0.0;
float xnm2_2 = 0.0;
float xnm3_2 = 0.0;
float xnm4_2 = 0.0;

float xn_3   = 0.0;  		
float xnm1_3 = 0.0;
float xnm2_3 = 0.0;
float xnm3_3 = 0.0;
float xnm4_3 = 0.0;

float xn_4   = 0.0;  		
float xnm1_4 = 0.0;
float xnm2_4 = 0.0;
float xnm3_4 = 0.0;
float xnm4_4 = 0.0;

float yn_1   = 0.0;
float ynm1_1 = 0.0;
float ynm2_1 = 0.0;
float ynm3_1 = 0.0;
float ynm4_1 = 0.0;

float yn_2   = 0.0;
float ynm1_2 = 0.0;
float ynm2_2 = 0.0;
float ynm3_2 = 0.0;
float ynm4_2 = 0.0;

float yn_3   = 0.0;
float ynm1_3 = 0.0;
float ynm2_3 = 0.0;
float ynm3_3 = 0.0;
float ynm4_3 = 0.0;

float yn_4   = 0.0;
float ynm1_4 = 0.0;
float ynm2_4 = 0.0;
float ynm3_4 = 0.0;
float ynm4_4 = 0.0;

int buffSize = 3000;
float buff[3000] = {0};


// struct peak {
//     float amp = 0.0;
//     int index = 0;
// };

// peak beats[5];