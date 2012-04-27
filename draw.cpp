#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "draw.h"
#include "vector_operations.h"

vector_field field;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
  const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

  const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
  const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
  const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat high_shininess[] = { 100.0f };

int teste = 1;


static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void plot_vectors(){
  //const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  //const double a = t*90.0;
  int i, j, k;
  double mod, max_leght;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(0,0,1);
  max_leght = sqrt(pow(field.d_x, 2) + pow(field.d_y, 2) + pow(field.d_z, 2));

  if(teste){/* Plota apenas uma vez e some */
  for(k = 0; k < field.n_z; k++){
    for(j = 0; j < field.n_y; j++){
      for(i = 0; i < field.n_x; i++){
            mod = module(field.vectors[i][j][k]);
            if( mod > max_leght )
              mod = max_leght;

            glPushMatrix();
              printf("v = (%f,%f,%f) |v| = %f\n",field.vectors[i][j][k].x,field.vectors[i][j][k].y,field.vectors[i][j][k].z,module(field.vectors[i][j][k]));
              /* esse 0.1 deve ser definido caso a caso */
              glTranslated(/*field.d_x*/-0.1*i,/*field.d_y*/-j*0.1,/*field.d_z*/-k*0.1);
             	printf("ry = (%f)\n",angle_y(field.vectors[i][j][k]));
              glRotated(-angle_y(field.vectors[i][j][k]),0,0,1);
              printf("rx = (%f)\n",angle_x(field.vectors[i][j][k]));
              glRotated(angle_z(field.vectors[i][j][k]),0,1,0);
              //printf("rz = (%f)\n",angle_z(field.vectors[i][j][k]));
              //glRotated(angle_z(field.vectors[i][j][k]),0,0,1);
              glutSolidCone(0.03,mod*0.1,16,16);

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

void draw_main(int argc, char *argv[], vector_field *f){

  field = *f;

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

  glMatrixMode(GL_MODELVIEW);   
  glLoadIdentity();
  glTranslatef(0.7,0.7,0);


  glutReshapeFunc(resize);
  glutDisplayFunc(plot_vectors);
//  glutKeyboardFunc(key);
  glutIdleFunc(idle);

 
  glutMainLoop();
}
