typedef struct vec{
  double x;
  double y;
  double z;
} vector;

class VectorField {
  public:
    VectorField();
    VectorField(double d_x, double d_y, double d_z, int n_x, int n_y, int n_z);
    double getDx();
    double getDy();
    double getDz();
    int getNx();
    int getNy();
    int getNz();
    vector getVector(int x, int y, int z);
    void setVector(int x, int y, int z, vector v);
  private:
    vector ***_field;
    double _d_x;
    double _d_y;
    double _d_z;
    int _n_x;
    int _n_y;
    int _n_z;
};
