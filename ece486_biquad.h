//Comments

typedef struct {
	int sections;
	float scl_fctr;
	float **a, **b, y, **w;
	int ptr, y_ptr;
} ECE486_BIQUAD_T;

ECE486_BIQUAD_T *ece486_init_biquad(int sections,float g, float a[][2], float b[][3]);

float ece486_calc_biquad(ECE486_BIQUAD_T *s, float x);

void destroy_biquad(ECE486_BIQUAD_T *s);

