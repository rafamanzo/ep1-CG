#include<stdlib.h>
#include "vector_field.h"
#include "input.h"

int main(int argc, char *argv[]){
  vector_field field;
  int n_x, n_y, n_z;
  double d_x, d_y, d_z;
  
  if(argc != 2)
    return -1;
    
  parseFile(argv[1], &n_x, &n_y, &n_z, &d_x, &d_y, &d_z, &field);
  
  return 0;
}
