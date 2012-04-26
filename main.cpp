#include<stdlib.h>
#include "vector_field.h"
#include "vector_operations.h"
#include "input.h"
#include <GL/glut.h>
#include <math.h>

vector_field field;
static int slices = 16;
static int stacks = 16;
int teste=1;

static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void){
  const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glPushMatrix();
        glTranslated(0,0,-10);
        glScaled(8,6,8);    
        glutWireCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1.2,-6);
        //glRotated(60,1,0,0);
        //glRotated(a,0,0,1);

              glutSolidCone(1,1,slices,stacks); 
   glPopMatrix();

    glutSwapBuffers();
}


static void plot_vectors(){
  //const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  //const double a = t*90.0;
  int i, j, k;
  double mod, max_leght;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(1,0,0);
  max_leght = sqrt(pow(field.d_x, 2) + pow(field.d_y, 2) + pow(field.d_z, 2));

  if(teste){/* Plota apenas uma vez e some */
  for( i=0; i < field.n_x; i++){
      for( j=0; j < field.n_y; j++){
          for( k=0; k < field.n_z; k++){
            mod = module(field.vectors[i][j][k]);
            if( mod > max_leght )
              mod = max_leght;

            glPushMatrix();
              /* esse 0.1 deve ser definido caso a caso */
              glTranslated(field.d_x-0.1*i,field.d_y-j*0.1,field.d_z-k*0.1);
              /* Achar a ordem correta */
              glRotated(angle_x(field.vectors[i][j][k]),1,0,0);
              glRotated(angle_z(field.vectors[i][j][k]),0,0,1);
              glRotated(angle_y(field.vectors[i][j][k]),0,1,0);
              glutSolidCone(0.03,mod*0.1,slices,stacks);
            glPopMatrix();
          }
      }
  }
  glutSwapBuffers();teste=0;}
}

static void idle(void)
{
  glutPostRedisplay();
}

int main(int argc, char *argv[]){

  const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
  const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

  const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
  const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
  const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat high_shininess[] = { 100.0f };
  
  if(argc != 2)
    return -1;
    
  parseFile(argv[1], &field);
  
  glutInit(&argc, argv);
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
//  glutKeyboardFunc(key);
  glutIdleFunc(idle);
  glClearColor(1,1,1,1);
 
    glutMainLoop();

    return EXIT_SUCCESS;


  return 0;
}
