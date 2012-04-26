#include <GL/glut.h>
#include <math.h>
#include "vector_field.h"
#include "vector_operations.h"
#include "window.h"

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

Window::Window(VectorField vf){
  int argc = 0;
  char *argv;
  
  _vf = vf; 

  glutInit(&argc, &argv);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(0,0);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Simulador");

  /* Coloração e profundidade */
  glClearColor(1,1,1,1);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  /* Fim */ 

  glutReshapeFunc(resize);
  glutDisplayFunc(plot_vectors);
  glutIdleFunc(idle);
  glClearColor(1,1,1,1);
}

void Window::loop(){
  glutMainLoop();
}

void Window::resize(int width, int height){
    const float ar = (float) width / (float) height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void Window::plot_vectors(){
  //const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  //const double a = t*90.0;
  int i, j, k;
  double mod, max_leght;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(1,0,0);
  max_leght = sqrt(pow(_vf.getDx(), 2) + pow(_vf.getDy(), 2) + pow(_vf.getDz(), 2));

  for( i=0; i < _vf.getNx(); i++){
      for( j=0; j < _vf.getNy(); j++){
          for( k=0; k < _vf.getNz(); k++){
            mod = module(_vf.getVector(i,j,k));
            if( mod > max_leght )
              mod = max_leght;

            glPushMatrix();
              /* esse 0.1 deve ser definido caso a caso */
              glTranslated(_vf.getDx()-0.1*i,_vf.getDy()-j*0.1,_vf.getDz()-k*0.1);
              /* Achar a ordem correta */
              glRotated(angle_x(_vf.getVector(i, j, k)),1,0,0);
              glRotated(angle_z(_vf.getVector(i, j, k)),0,0,1);
              glRotated(angle_y(_vf.getVector(i, j, k)),0,1,0);
              glutSolidCone(0.03,mod*0.1,slices,stacks);
            glPopMatrix();
          }
      }
  }
  glutSwapBuffers();
}

