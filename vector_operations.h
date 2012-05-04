vector sum(vector v1, vector v2);
vector mult_scalar(vector v, double scalar);
void set(vector *x, vector y);
double module(vector v);
double distance(vector x, vector y);
double angle_x(vector v);
double angle_y(vector v);
double angle_z(vector v);
vector trilinear_interpolation(vector v0, vector_field field);
#ifndef PI
#define PI 3.141592653589793
#endif
