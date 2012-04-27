#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "draw.h"
#include "vector_operations.h"
#define FATOR 0.1


vector_field field;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
  const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

  const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
  const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
  const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat high_shininess[] = { 100.0f };

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
  int i, j, k;
  double mod, max_legth;

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  max_legth = sqrt(pow(field.d_x, 2) + pow(field.d_y, 2) + pow(field.d_z, 2));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(0,0,1);

  for(k = 0; k < field.n_z; k++){
    for(j = 0; j < field.n_y; j++){
      for(i = 0; i < field.n_x; i++){
        mod = module(field.vectors[i][j][k]);
        if( mod > max_legth )
          mod = max_legth;

        glPushMatrix();
              /* esse FATOR deve ser definido caso a caso */
        glTranslated(field.d_x-i,field.d_y-j,field.d_z-k);
          glRotated(angle_y(field.vectors[i][j][k]),0,1,0); 
          glRotated(angle_x(field.vectors[i][j][k]),1,0,0);
          glRotated(angle_z(field.vectors[i][j][k]),0,0,1);
          glutSolidCone(0.03,mod,16,16);
        glPopMatrix();
       }
    }
 }
  glutSwapBuffers();
}

// ALTERAR
static void clear(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

static void plot_spheres(){
  int i, j, k;
  double radius;
 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(1,0,0);
  radius = fmax(fmax(field.d_x,field.d_y),field.d_z)*FATOR;  

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  for(k = 0; k < field.n_z; k++){
    for(j = 0; j < field.n_y; j++){
      for(i = 0; i < field.n_x; i++){
         glPushMatrix();
           glTranslated(field.d_x-i,field.d_y-j,field.d_z-k);
           glutSolidSphere(radius,16,16);
         glPopMatrix();
      }
    }
  }
  glutSwapBuffers();
}

static void plot_cube(){

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor3d(0,0,1);

  glPushMatrix();
    glTranslated(-2,2,-6);
    glutWireCube(fmax(fmax(field.n_x,field.n_y),field.n_z));
  glPopMatrix();
}

void key_pressed (unsigned char key, int x, int y) {  

  if( key == 'v')
    plot_vectors();
  else if(key == 's')
    plot_spheres();
  else if(key == 'c')
    plot_cube();
  else if(key == 'l')
    clear();
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

  glutReshapeFunc(resize);
  glutDisplayFunc(clear);
  glutKeyboardFunc(key_pressed);
  glutMainLoop();
}
