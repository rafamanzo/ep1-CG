#include<stdlib.h>
#include <GL/glut.h>
#include "vector_field.h"
#include "input.h"
#include "window.h"

int main(int argc, char *argv[]){
  VectorField vf;
  
 if(argc != 2)
   return -1;
    
 parseFile(argv[1], &vf);
 
 Window win(vf);
 
 return 0;
}
