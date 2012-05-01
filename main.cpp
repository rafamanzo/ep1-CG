#include "vector_field.h"
#include "draw.h"
#include "input.h"

int main(int argc, char *argv[]){
  vector_field f;

  if(argc != 2)
    return -1;
    
  parseFile(argv[1], &f);
	draw_main(argc, argv,&f);

  return 0;
}
