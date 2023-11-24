#define Fs	35000       //Frequency of Sample Rate in Hz
//#define Fs  1200
#define N		5           //Number of Nodes N

//coefficients for demo code filter
// B - Numerator coefficients
float b0 = 0.0201;
float b1 = 0.0;
float b2 = -0.0402;
float b3 = 0.0;
float b4 = 0.0201;

// A - Denominator coefficients
float a0 =    1.0000; 
float a1 =  	-2.5494; 
float a2 =   	3.2024; 
float a3 = 		-2.0359; 
float a4 =		0.6414;


//coefficients for tElec 347 c/w bandpass filter 0.25 Hz -> 40 Hz

// B - Numerator coefficients
float b0 = 0.0134;
float b1 = 0.0;
float b2 = -0.0268;
float b3 = 0.0;
float b4 = 0.0134;

// A - Denominator coefficients
float a0 = 1.0000; 
float a1 = -3.6872; 
float a2 = 5.1190; 
float a3 = -3.1762; 
float a4 = 0.7445;


