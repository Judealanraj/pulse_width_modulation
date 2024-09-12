#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include "mypcm.h" 
void intToBinary(int n, int bits, char *binaryString) {   //function to change integer to binary
    for (int i = bits - 1; i >= 0; i--) {
        binaryString[i] = (n & 1) ? '1' : '0';
        n >>= 1;
    }
    binaryString[bits] = '\0';
}
float analog_signal_generator(asignal signal, int t)
{
	float x_t = signal.A * sin(signal.omega * t + signal.sigma);        //find analog value
	//printf("%f\n",x_t);
	return x_t;
}
void sampler(float *samples, int interval, asignal signal)
{
	int itterations=signal.duration/interval;         //calculating iterations
	for(int i=0;i<itterations+1;i++){         
		*(samples + i) = analog_signal_generator(signal, i*interval);       //genarate analog signal values and put in samples array
		//printf("%f\n",analog_signal_generator(signal, i*interval));
	}
}
void quantizer(float *samples, int *pcmpulses, int encoderbits, float A)
{
    int num_samples= sizeof(samples)-3;      
	int no_of_levels= pow(2, encoderbits);    //calculate number of levels
	for (int i = 0; i < num_samples+1; i++) {
		int a =(int)floor(
            (*(samples + i) - (-1 * A)) * no_of_levels / (A - (-1 * A))
        );
		*(pcmpulses + i) = a;            // calculate pulse values and put in pcm puls array
		//printf("%d\n",a);
	}
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	int num_samples= sizeof(pcmpulses)-3;
	char binaryString[encoderbits + 1];
	for (int i = 0; i < num_samples+1; i++) {
		//printf("%d",*(pcmpulses+i));
		intToBinary(*(pcmpulses+i), encoderbits, binaryString);
		printf("%s",binaryString);                                     //find the encoded binary array and print it
	}
}



