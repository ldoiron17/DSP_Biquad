#include <stdio.h>
#include <stdlib.h>
#include "ece486_biquad.h"

int main(void){
	
	float a[3][2] = {{4.0, 5.0}, {-7.0, 2.0}, {4.0, 9.0}};
	float b[3][3] = {{-2.0,9.0,6.0}, {4.0,3.0,-1.0}, {5.0,-6.0,3.0}};	
	float x[5] = {3.0, 6.0, 7.0 ,9.0, -4.0};	
	float y[5];


	ECE486_BIQUAD_T *s = ece486_init_biquad(3, 3.0, a, b);	
	int i;
	for(i = 0; i <5; i++){
		y[i] = ece486_calc_biquad(s, x[i]);	
		printf("y[%d] = %f\n\n", i, y[i]);
	
	}
	printf("s.sections = %d\n", s->sections);
	printf("s.scl_fctr = %f\n", s->scl_fctr);
	
	
	destroy_biquad(s);
	return 0;
}
