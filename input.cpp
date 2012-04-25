#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "vector_field.h"
#include "input.h"

void parseFile(char *file, vector_field *field){
  FILE *fp;
  int i, j, k;
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
    
  
  for(k = 0; k < (*field).n_z; k++){
    for(j = 0; j < (*field).n_y; j++){
      for(i = 0; i < (*field).n_x; i++){
        fscanf(fp, "%lf", &(((*field).vectors[i][j][k]).x));
        fscanf(fp, "%lf", &(((*field).vectors[i][j][k]).y));
        fscanf(fp, "%lf", &(((*field).vectors[i][j][k]).z));
      }
    }
  }
}
