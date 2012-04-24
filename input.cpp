#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "vector_field.h"
#include "input.h"

void parseFile(char *file, int *n_x, int *n_y, int *n_z, double *d_x, double *d_y, double *d_z, vector_field *field){
  FILE *fp;
  int i, j, k;
  fp = fopen(file, "r");
  
  fscanf(fp, "%d", n_x);
  fscanf(fp, "%d", n_y);
  fscanf(fp, "%d", n_z);
  
  fscanf(fp, "%lf", d_x);
  fscanf(fp, "%lf", d_y);
  fscanf(fp, "%lf", d_z);
    
  *field = (vector_field) malloc( (*n_x)*(*n_y)*(*n_z)*sizeof(vector) );
  
  for(k = 0; k < *n_z; k++){
    for(i = 0; i < *n_x; i++){
      for(j = 0; j < *n_y; j++){
        fscanf(fp, "%lf", &(((*field)[offset(*n_x, *n_y, i, j, k)]).x));
        fscanf(fp, "%lf", &(((*field)[offset(*n_x, *n_y, i, j, k)]).y));
        fscanf(fp, "%lf", &(((*field)[offset(*n_x, *n_y, i, j, k)]).z));
      }
    }
  }
}
