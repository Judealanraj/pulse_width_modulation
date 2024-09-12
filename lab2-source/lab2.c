#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "mypcm.h"
#include "mypcm.c"


// function prototypes
void run(asignal * inputsignal);


void run(asignal * inputsignal) {
    float  interval;
    int encoderbits;
    printf("Enter input parameters (A omega sigma duration interval encoderbits): ");
    scanf("%f %f %f %f %f %d", &inputsignal->A, &inputsignal->omega, &inputsignal->sigma, &inputsignal->duration, &interval, &encoderbits);
	// get values for input signal parameters and assign them
    int num_samples = (int)inputsignal->duration / interval;  //calculate number of intervals
	float* samples = (float*)malloc((num_samples+1)*sizeof(float));  //allocate space for samples array
	int* pcmpulses = (int*)malloc((num_samples+1)*sizeof(int));      //allocate space for pcmpuls array
	int* dsignal = (int*)malloc((num_samples+1)*sizeof(int));        //allocate space for dsignal array
	sampler(samples, interval, *inputsignal);
	quantizer(samples, pcmpulses, encoderbits, inputsignal->A);
	encoder(pcmpulses,dsignal,encoderbits);
}
int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here

    free(inputsignal);
	return 0;
}



