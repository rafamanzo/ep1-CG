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
        set_sphere(s,i,j,k,-i+field.d_x,-j+field.d_y,-k+field.d_z);

  (*s).r = fmax(fmax(field.d_x,field.d_y),field.d_z);
}

void set_sphere(spheres *s,int i, int j, int k, double x, double y, double z){
  (*s).all[i][j][k].x = x;
  (*s).all[i][j][k].y = y;
  (*s).all[i][j][k].z = z;
}

void go_spheres(spheres *s, int i, int j,  int k, double t, vector_field field){
  vector v, v0;

  v0.x = (*s).all[i][j][k].x;
  v0.y = (*s).all[i][j][k].y;
  v0.z = (*s).all[i][j][k].z;

  v = trilinear_interpolation(v0, field);
  printf("\nANTES: v=(%f,%f,%f)\n",(*s).all[i][j][k].x,(*s).all[i][j][k].y,(*s).all[i][j][k].z);
  (*s).all[i][j][k].x += t*v.x;
  (*s).all[i][j][k].y += t*v.y;
  (*s).all[i][j][k].z += t*v.z;
  printf("DEPOIS: v=(%f,%f,%f)\n",(*s).all[i][j][k].x,(*s).all[i][j][k].y,(*s).all[i][j][k].z);
}
