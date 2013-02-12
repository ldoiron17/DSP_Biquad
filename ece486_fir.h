/*****************************************************************

 file: ece486_fir.h
 Description:  Subroutines to implement a FIR Filter in real-time.
	       Multiple subroutine calls are used to calculate the output
               of an FIR filter
	             y(n) = x(n) * h(n)
	       where x(n) is the nth input sample, and the values of h(n) 
	       obtained from an array of fixed values, and "*" denotes 
               discrete-time convolution.

 Implementation:
   Filters are implemented using three function calls:
     ece486_init_fir()   is called once, and is used to initialize the array
                  of filter coefficients h(n), allocate any required memory,
		    and perform any other required initialization.
     ece486_calc_fir()   is called multiple times -- once for every input sample.
                  It returns the filter output sample y(n).
     ece486_destroy_fir() is called once at the end of the program, and is used
                  to deallocate any memory which was allocated by ece486_init_fir().

  Function Prototypes and parameters:

    	#include "fir_filter.h"
	ECE486_FIR_T *ece486_init_fir(float *filter_coefs, int n_coef);

	   Inputs:
		filter_coefs	pointer to the array of values for h(n)
        			filter_coefs[i] should contain the impulse
				response of the filter at time "i", for 
				i=0, 1, 2, ..., n_coef-1
				The filter_coefs array is NOT modified by
				ece486_init_fir(), ece486_calc_fir(), or
				ece486_destroy_fir().

		n_coef  	Number of samples in the impulse response array

	   Returned:
		The function returns a pointer to a "ECE486_FIR_T" data type
		(which is defined in "ece486_fir.h")
		
	float ece486_calc_fir( ECE486_FIR_T *s, float x );

	   Inputs:
		s	pointer to ECE486_FIR_T, as provided by ece486_init_fir().  The
                      contents of the structure s are modified by each called
                      to ece486_calc_fir()
		x	Input sample value:

	   Returned:
		The function returns the FIR filter output sample y(n).

                      i=n_coef-1
		y(n) =    sum     ( h[i] x(n-i) )
			  i=0

		where x(n) is the value of "x" for the current call, x(n-1)
		is the value of "x" from the previous call, x(n-2) is the 
		value of "x" from call before that, and so on.  
		
  	void ece486_destroy_fir(ECE486_FIR_T *s);   
  	   Inputs:
	   	s	pointer to ECE486_FIR_T, as provided by ece486_init_fir()
	   No value is returned.
        
*******************************************************************/ 






typedef struct {
	int length, ptr;
	float *h;
	float *x;
} ECE486_FIR_T;


//PROTOYPES
ECE486_FIR_T *ece486_init_fir(float *filter_coefs, int n_coef);


float ece486_calc_fir(ECE486_FIR_T *s, float x );

void ece486_destroy_fir(ECE486_FIR_T *s);




