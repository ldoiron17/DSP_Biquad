#include <stdio.h>
#include <stdlib.h>
#include "ece486_biquad.h"


//Comments? what are those?


//Function that creates one biquad strucutre type
//allocates the required memory for coeffecient arrays and returns
//a pointer to the new ECE486_BIQUAD_T data type that was instaniated 
//Note that it is assumed that a[][0] = 1 if it is not 1 this code will fail

ECE486_BIQUAD_T *ece486_init_biquad(int sections,float g, float a[][2], float b[][3]){

	// make space for the ECE486_BIQUAD_T struct	
	ECE486_BIQUAD_T *s = (ECE486_BIQUAD_T *) calloc(1,sizeof(ECE486_BIQUAD_T));
	
	s->scl_fctr = g;
	s->ptr = 0;
	s->y_ptr = 0;
	s->y = 0.0;
	


	//Make space for the two coefficient arrays a b and w
	s->a = (float **) calloc(sections, sizeof(float));
    	s->b = (float **) calloc(sections, sizeof(float));
	s->w = (float **) calloc(sections, sizeof(float));

	//allocate memory for the second dimension of both a and b
	//as well as fill the allocated memory with the inputs
	//note that s.sections is assigned in this manner by use of a for
	//loop increment variable, like a muh fuckin boss
	for( s->sections = 0; s->sections < sections; (s->sections)++){
		s->a[s->sections] = (float *) calloc(2, sizeof(float));
    		s->b[s->sections] = (float *) calloc(3, sizeof(float));

		//allocate space for y and w arrays to hold current and two previous values
		//for calculation of y(n)
		s->w[s->sections] = (float *) calloc(3, sizeof(float));


		int i = 0;
		for(i=0; i<2; i++){
			s->a[s->sections][i] = a[s->sections][i];
			s->b[s->sections][i] = b[s->sections][i];
		}
			s->b[s->sections][i] = b[s->sections][i];
	}

  	
	return s;

}

float ece486_calc_biquad(ECE486_BIQUAD_T *s, float x){
	
	int i;
	//assign x to first value of y
	s->y = x;

	for(i = 0; i < s->sections; i++){
		
		printf("s.ptr = %d\n", s->ptr);
	
		int j = 0;
		printf("intial y is : %f\n", s->y);
		//calculate w(n)
		s->w[i][s->ptr] = ( (s->y) - (s->a[i][0])*(s->w[i][(s->ptr + 2)%3]) -
	 	(s->a[i][1])*(s->w[i][(s->ptr + 1)%3]) );

		printf("w[%d][%d] = %f\n", i, s->ptr,  s->w[i][s->ptr]);
		printf("w[%d][%d] = %f\n", i, (s->ptr + 2)%3, s->w[i][(s->ptr + 2)%3]);
		printf("w[%d][%d] = %f\n", i, (s->ptr + 1)%3, s->w[i][(s->ptr + 1)%3]);
		
		//calculate y(n)
		s->y = ( (s->b[i][0])*(s->w[i][s->ptr]) + (s->b[i][1])*(s->w[i]
		[(s->ptr + 2)%3]) +(s->b[i][2])*(s->w[i][(s->ptr + 1)%3]) );
		

		printf("y[%d] = %f\n", i, s->y);
	}

	//increment circular buffer ptrs
	s->ptr = (s->ptr + 1)%3;
	printf("s.ptr = %d\n", s->ptr);
	

	//Scale y(n) by g
	s->y *= s->scl_fctr;


	return s->y;

}

void destroy_biquad(ECE486_BIQUAD_T *s){
	
	int i;
	for(i=0; i<s->sections; i++){
		free(s->a[i]);
		free(s->b[i]);
		free(s->w[i]);
	}
	free(s->a);
	free(s->b);
	free(s->w);
	free(s);
	s = NULL;
}
