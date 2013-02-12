/* Appropriate file header comments... */

//#include "fir_filter.h"
#include "ece486_fir.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){

	float h[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	float x[4] = {2.0,3.0,7.0,4.0};
	float y[4];

	int length = sizeof(h)/sizeof(float);
	printf("%d\n", length);
	ECE486_FIR_T *s = ece486_init_fir(h, length);
	int i = 0;
	for(i = 0; i<length; i++){	
		//printf("s.h[%d] = %f\n", i, s->h[i]);	
	}
	
	for(i = 0; i<4; i++){
		y[i] = ece486_calc_fir(s, x[i]);	
		printf("y[%d] = %f\n", i, y[i]);	
	}
	ece486_destroy_fir(s);

	
	for(i = 0; i<length; i++){	
		printf("s.h[%d] = %f\n", i, s->h[i]);	
	}

return 0;
}
