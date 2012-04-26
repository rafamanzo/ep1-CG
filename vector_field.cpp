#include<stdlib.h>
#include "vector_field.h"
#include "vector_operations.h"

VectorField::VectorField(){
  _n_x = _n_y = _n_y = 0;
  _d_x = _d_y = _d_z = 0;
  
  _field = NULL;
}

VectorField::VectorField(double d_x, double d_y, double d_z, int n_x, int n_y, int n_z){
  int i, j, k;
  
  _n_x = n_x;
  _n_y = n_y;
  _n_y = n_y;
  
  _d_x = d_x;
  _d_y = d_y;
  _d_z = d_z;
  
  _field = (vector ***) malloc( (_n_x) * sizeof(vector **) );
  for(i = 0; i < _n_x; i++){
    _field[i] = (vector **) malloc( (_n_y) * sizeof(vector *) );
    for(j = 0; j < _n_y; j++)
      _field[i][j] = (vector *) malloc( (_n_z) * sizeof(vector) );
  }
}

double VectorField::getDx(){
  return _d_x;
}


double VectorField::getDy(){
  return _d_y;
}


double VectorField::getDz(){
  return _d_z;
}

int VectorField::getNx(){
  return _n_x;
}

int VectorField::getNy(){
  return _n_y;
}

int VectorField::getNz(){
  return _n_z;
}

vector VectorField::getVector(int x, int y, int z){
  return _field[x][y][z];
}

void VectorField::setVector(int x, int y, int z, vector v){
  set(&_field[x][y][z], v);
}
