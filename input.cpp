#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "vector_field.h"
#include "vector_operations.h"
#include "input.h"

void parseFile(char *file, vector_field *field){
  FILE *fp;
  int i, j, k;
  double mod;

  fp = fopen(file, "r");
  
  fscanf(fp, "%d", &((*field).n_x));
  fscanf(fp, "%d", &((*field).n_y));
  fscanf(fp, "%d", &((*field).n_z));
  
  fscanf(fp, "%lf", &((*field).d_x));
  fscanf(fp, "%lf", &((*field).d_y));
  fscanf(fp, "%lf", &((*field).d_z));
    
  (*field).vectors = (vector ***) malloc( ((*field).n_x) * sizeof(vector **) );
  for(i = 0; i < ((*field).n_x); i++){
    (*field).vectors[i] = (vector **) malloc( ((*field).n_y) * sizeof(vector *) );
    for(j = 0; j < ((*field).n_y); j++)
      (*field).vectors[i][j] = (vector *) malloc( ((*field).n_z) * sizeof(vector) );
  }
  (*field).max = -1.0;
  (*field).min = (*field).d_x+(*field).d_y+(*field).d_z;
  
  for(k = 0; k < (*field).n_z; k++){
    for(j = 0; j < (*field).n_y; j++){
      for(i = 0; i < (*field).n_x; i++){
        fscanf(fp, "%lf", &(((*field).vectors[i][j][k]).x));
        fscanf(fp, "%lf", &(((*field).vectors[i][j][k]).y));
        fscanf(fp, "%lf", &(((*field).vectors[i][j][k]).z));
        mod = module((*field).vectors[i][j][k]);
	      if(  mod > (*field).max )
		      (*field).max = mod;
 	      else if(  mod < (*field).min && mod > 0.0)
		      (*field).min = mod;
//        printf("MAX %f MIN %f\n",(*field).max,(*field).min);
      }
    }
  }
}
