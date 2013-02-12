/* Appropriate file header comments... */

//#include "fir_filter.h"
#include "ece486_fir.h"
#include <stdio.h>
#include <stdlib.h>

ECE486_FIR_T *ece486_init_fir(float *filter_coefs, int n_coef) {
	

	// make space for the ECE486_FIRT struct	
	ECE486_FIR_T *s = (ECE486_FIR_T *) calloc(1,sizeof(ECE486_FIR_T));
	
	s->ptr = 0;

	//Make space for the impulse array and input array
	s->h = (float *) calloc(n_coef, sizeof(float));
    	s->x = (float *) calloc(n_coef, sizeof(float));

	//Assign impulse arrays to the allocated space s.h
	for( s->length = 0; s->length < n_coef; (s->length)++){
		s->h[s->length] = filter_coefs[s->length];
	}
  	
	return s;
	
}

float ece486_calc_fir( ECE486_FIR_T *s, float x ) {
    

	float out=0;
	int i=0;
	
	printf("s.length = %d\n", s->length);

   	//enter newest input into array
	s->x[s->ptr]= x;  
	
   	//magic convolution of magicality
    	//integer used to access h(n) stanard access because it is not a circular buffer
	int j = 0;
	for(i=s->length; i > 0; i--){
		out += ((s->x[(s->ptr + i)%s->length])*(s->h[j]));
		printf("%f = [%f]*[%f]\n", out, (s->x[(s->ptr + i)%s->length]), (s->h[j]));
		j++;
	}
	s->ptr = (s->ptr + 1)%s->length;

/*
	////////////Non circular buffer code/////////////////
	//make room for new x value, shift array
    
	for(i=s->length-1;i>0;i--){
		s->x[i]=s->x[i-1];
	}

   	//enter newest input into array

	s->x[0]= x;  
	
   	//magic convolution of magicality
    
	for(i=0; i < s->length; i++){
		out += ((s->x[i])*(s->h[i]));
	}
*/
	return out;

}


void ece486_destroy_fir(ECE486_FIR_T *s) {
    printf("destroying...\n");
    free(s->x);
    free(s->h);
    free(s);
    s = NULL;

}

