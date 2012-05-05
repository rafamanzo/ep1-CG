#include <stdio.h>
#include <stdlib.h>
#include "vector_field.h"
#include "sphere.h"
#include <math.h>
#include "vector_operations.h"

void start_spheres(vector_field field, spheres *s){
  int i, j, k;

  (*s).all = (sphere ***) malloc(field.n_x*sizeof(sphere **));
  for(i = 0; i < field.n_x; i++){
    (*s).all[i] = (sphere **) malloc(field.n_y*sizeof(sphere *));
    for(j = 0; j < field.n_y; j++)
      (*s).all[i][j] = (sphere *) malloc(field.n_z*sizeof(sphere));
	}
  for(k = 0; k < field.n_z; k++)
    for(j = 0; j < field.n_y; j++)
      for(i = 0; i < field.n_x; i++)
        set_sphere(s,i,j,k,-field.n_x/2+i,-field.n_y/2+j,-field.n_z/2+k);

  (*s).r = fmax(fmax(field.d_x,field.d_y),field.d_z);
}

void set_sphere(spheres *s,int i, int j, int k, double x, double y, double z){
  (*s).all[i][j][k].x = x;
  (*s).all[i][j][k].y = y;
  (*s).all[i][j][k].z = z;
}

void go_spheres(spheres *s, int i, int j,  int k, double t, vector_field field){
  vector v, v0;
  double mod;

  v0.x = (*s).all[i][j][k].x;
  v0.y = (*s).all[i][j][k].y;
  v0.z = (*s).all[i][j][k].z;

  v = trilinear_interpolation(v0, field);
  mod = module(v);
	
  if( v.x != 0.0 ) 
    (*s).all[i][j][k].x += t*mod*cos(angle_x(v)*PI/180);
  if( (*s).all[i][j][k].x > field.n_x )
   (*s).all[i][j][k].x = field.n_x;
  else if( (*s).all[i][j][k].x < -(field.n_x) )
   (*s).all[i][j][k].x = -(field.n_x);

  if( v.y != 0.0 )
    (*s).all[i][j][k].y -= t*mod*cos(angle_y(v)*PI/180);
  if( (*s).all[i][j][k].y > field.n_y )
   (*s).all[i][j][k].y = field.n_y;
  else if( (*s).all[i][j][k].y < -field.n_y )
   (*s).all[i][j][k].y = -(field.n_y);

  if( v.z != 0.0 )
    (*s).all[i][j][k].z += t*mod*cos(angle_z(v)*PI/180);
  if( (*s).all[i][j][k].z > field.n_z )
   (*s).all[i][j][k].z = field.n_z;
  else if( (*s).all[i][j][k].z < -(field.n_z) )
   (*s).all[i][j][k].z = -(field.n_z);
}

