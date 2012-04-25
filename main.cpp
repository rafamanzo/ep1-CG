#include<stdlib.h>
#include "vector_field.h"
#include "input.h"

int main(int argc, char *argv[]){
  vector_field field;
  
  if(argc != 2)
    return -1;
    
  parseFile(argv[1], &field);
  
  return 0;
}
