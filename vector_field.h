typedef struct vec{
  double x;
  double y;
  double z;
} vector;

typedef struct vf{
  vector ***vectors;
  double d_x;
  double d_y;
  double d_z;
  int n_x;
  int n_y;
  int n_z;
  double max;
} vector_field;
