#include<stdlib.h> 
#include<math.h>
#include "vector_field.h"
#include "vector_operations.h"
#ifndef PI
#define PI 3.141592653589793
#endif

double angle_x(vector v){
    return acosf(v.x/module(v))*180/PI;
}

double angle_y(vector v){
    return acosf(v.y/module(v))*180/PI;
}

double angle_z(vector v){
    return acosf(v.z/module(v))*180/PI;
}


vector sum(vector v1, vector v2){
  vector sum;
  
  sum.x = v1.x + v2.x;
  sum.y = v1.y + v2.y;
  sum.z = v1.z + v2.z;
  
  return sum;
}

vector mult_scalar(vector v, double scalar){
  vector mult;
  
  mult.x = v.x*scalar;
  mult.y = v.y*scalar;
  mult.z = v.z*scalar;
  
  return mult;
}

void set(vector *x, vector y){
  (*x).x = y.x;
  (*x).y = y.y;
  (*x).z = y.z;
}

double module(vector v){
  return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double distance(vector x, vector y){
  return module(sum(x, mult_scalar(y, -1.0)));
}

vector nearest_neighbour(vector v0, VectorField vf){
  int x, y, z;
  vector zero;
  
  zero.x = zero.y = zero.z = 0.0;
  
  if( (v0.x - floor(v0.x)) > 0.5 && v0.x < (vf.getNx() - 1))
    x = (int) ceil(v0.x);
  else
    x = (int) floor(v0.x);
    
  if( (v0.y - floor(v0.y)) > 0.5 && v0.y < (vf.getNy() - 1))
    y = (int) ceil(v0.y);
  else
    y = (int) floor(v0.y);
    
  if( (v0.z - floor(v0.z)) > 0.5 && v0.z < (vf.getNz() - 1))
    z = (int) ceil(v0.z);
  else
    z = (int) floor(v0.z);

  if(x >= vf.getNx() || y >= vf.getNy() || z >= vf.getNz() || x < 0 || y < 0 || z < 0)
    return zero;
  else
    return vf.getVector(x, y, z);
}

vector trilinear_interpolation(vector v0, VectorField vf){
  int x1, y1, z1, x0, y0, z0, xd, yd, zd;
  vector zero, i1, i2, j1, j2, w1, w2;
  
  zero.x = zero.y = zero.z = 0.0;
  
  x1 = ceil(v0.x);
  y1 = ceil(v0.y);
  z1 = ceil(v0.z);
  x0 = floor(v0.x);
  y0 = floor(v0.y);
  z0 = floor(v0.z);
  
  if(x1 >= vf.getNx() || y1 >= vf.getNy() || z1 >= vf.getNz() || x0 < 0 || y0 < 0 || z0 < 0){
    return nearest_neighbour(v0, vf);
  }else{
    xd = (v0.x - x0)/(x1 - x0);
    yd = (v0.y - y0)/(y1 - y0);
    zd = (v0.z - z0)/(z1 - z0);
    
    set(&i1, sum( mult_scalar(vf.getVector(x0, y0, z0), (1.0 - zd)), mult_scalar(vf.getVector(x0, y0, z1), zd) ) );
    set(&i2, sum( mult_scalar(vf.getVector(x0, y1, z0), (1.0 - zd)), mult_scalar(vf.getVector(x0, y1, z1), zd) ) );
    set(&j1, sum( mult_scalar(vf.getVector(x1, y0, z0), (1.0 - zd)), mult_scalar(vf.getVector(x1, y0, z1), zd) ) );
    set(&j2, sum( mult_scalar(vf.getVector(x1, y1, z0), (1.0 - zd)), mult_scalar(vf.getVector(x1, y1, z1), zd) ) );
    
    set(&w1, sum( mult_scalar(i1, (1.0 - yd)), mult_scalar(i2, yd) ) );
    set(&w2, sum( mult_scalar(j1, (1.0 - yd)), mult_scalar(j2, yd) ) );
    
    return sum( mult_scalar(w1, (1.0 - xd)), mult_scalar(w2, xd) );
  }
}
