typedef struct sph{
  double x;
  double y;
  double z;
} sphere;

typedef struct sphs{
  sphere ***all;
  double r;
} spheres;

void start_spheres(vector_field, spheres*);
void set_sphere(spheres*,int, int, int, double, double, double);
void go_spheres(spheres *,int,int,int, double, vector_field);
