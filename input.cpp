#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "vector_field.h"
#include "input.h"

void parseFile(char *file, VectorField *vf){
  FILE *fp;
  double d_x, d_y, d_z;
  int i, j, k, n_x, n_y, n_z;
  vector aux;
  fp = fopen(file, "r");
  
  fscanf(fp, "%d", &n_x);
  fscanf(fp, "%d", &n_y);
  fscanf(fp, "%d", &n_z);
  
  fscanf(fp, "%lf", &d_x);
  fscanf(fp, "%lf", &d_y);
  fscanf(fp, "%lf", &d_z);
    
  VectorField vf_aux(d_x, d_y, d_z, n_x, n_y, n_z);  
  
  for(k = 0; k < n_z; k++){
    for(j = 0; j < n_y; j++){
      for(i = 0; i < n_x; i++){
        fscanf(fp, "%lf", &aux.x);
        fscanf(fp, "%lf", &aux.y);
        fscanf(fp, "%lf", &aux.z);
        
        vf_aux.setVector(i, j, k, aux);
      }
    }
  }
  
  *vf = vf_aux;
}
