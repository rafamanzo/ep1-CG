#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "vector_field.h"
#include "draw.h"
#include "sphere.h"
#include "vector_operations.h"

#define FATOR 0.08

vector_field field;
spheres s;
int start;
int vec;
int left_button = 0;
int right_button = 0;
double eye_x = 6.0;
double eye_y = -6.0;
double eye_z = -10.0;
int mouse_start_x, mouse_start_y;
GLfloat delta_time, now, last_time, deltaT;
GLfloat slowMotionRatio = 4.0f;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

static void resize(int width, int height){
    glViewport(0, 0, width, height);
    gluLookAt(0.0, 0.0, 0.0, eye_x, eye_y, eye_z, 0.0, 1.0, 0.0);
}

static void plot_vectors(){
  int i, j, k;
  double mod, max_legth, ratio;

  if( start == 0 )
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  max_legth = sqrt(pow(field.d_x, 2) + pow(field.d_y, 2) + pow(field.d_z, 2));
  glColor3d(0,0,1);
  ratio = 800/600;

  for(k = 0; k < field.n_z; k++){
    for(j = 0; j < field.n_y; j++){
      for(i = 0; i < field.n_x; i++){
        mod = module(field.vectors[i][j][k]);
        if( mod > max_legth )
          mod = max_legth;
        glPushMatrix();
         glTranslated((-field.n_x/2+i)*FATOR,(-field.n_y/2+j)*FATOR,(-field.n_z/2+k)*FATOR);
          glRotated(angle_y(field.vectors[i][j][k]),0,1,0);
          glRotated(-angle_x(field.vectors[i][j][k]),1,0,0); 
          glRotated(angle_z(field.vectors[i][j][k]),0,0,1);
          //printf("%f %f %f\n",angle_x(field.vectors[i][j][k]),angle_y(field.vectors[i][j][k]),angle_z(field.vectors[i][j][k]));
         glutSolidCone(0.03,mod*FATOR,16,16);
        glPopMatrix();
       }
    }
 }
 if(start == 0)
  glutSwapBuffers();
}

static void plot_spheres(){
  int i, j, k;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  if(vec == 1)
      plot_vectors();
  glColor3d(1,0,0);
  for(k = 0; k < field.n_z; k++){
    for(j = 0; j < field.n_y; j++){
      for(i = 0; i < field.n_x; i++){
         go_spheres(&s,i,j,k,deltaT, field);
         glPushMatrix();
           glTranslated(s.all[i][j][k].x*FATOR,s.all[i][j][k].y*FATOR,s.all[i][j][k].z*FATOR);
           glutSolidSphere(s.r*FATOR*0.5,16,16);
         glPopMatrix();
      }
    }
  }
  glutSwapBuffers();
}

void initial_condition(){
  delta_time = 0.0f;
  now = 0.0f;
  deltaT = 0.0f;
  start = 0;
  vec = 0;
  start_spheres(field, &s);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  last_time = glutGet(GLUT_ELAPSED_TIME);
  glutSwapBuffers();
}

void key_pressed (unsigned char key, int x, int y) {  

  if( key == 'v'){
    if( vec == 0){
      plot_vectors();
      vec = 1;
    }
    else
      vec = 0;
  }
  else if(key == 's')
    start = 1;
  else if(key == 'p')
    start = 0;
  else if(key == 'r')
    initial_condition();
}

void mouse_click(int button, int state, int x, int y){
  if(state == GLUT_DOWN){
    if(button == GLUT_LEFT_BUTTON){
      left_button = 1;
    }else if(button == GLUT_RIGHT_BUTTON){
      right_button = 1;
    }
    mouse_start_x = x;
    mouse_start_y = y;
  }else{
    if(button == GLUT_LEFT_BUTTON){
      left_button = 0;
    }else if(button == GLUT_RIGHT_BUTTON){
      right_button = 0;
    }
  }
}

void mouse_move(int x, int y){
  if(left_button == 1){
    eye_x += (mouse_start_x - x)*FATOR;
    eye_y += (mouse_start_y - y)*FATOR;
  }else if(right_button == 1){
    eye_z += (mouse_start_y - y)*FATOR;
  }
  
  mouse_start_x = x;
  mouse_start_y = y;
  
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 0.0, eye_x, eye_y, eye_z, 0.0, 1.0, 0.0);
  if(vec == 1)
    plot_vectors();
  if(start == 1)
    plot_spheres();
}

void idle(){
  if( start == 1){
    now = glutGet(GLUT_ELAPSED_TIME);    
    deltaT = (now - last_time) / 1000.0f;
    last_time = now;
    deltaT /= slowMotionRatio;
    last_time = now;
    glutPostRedisplay();  
  }
}

void draw_main(int argc, char *argv[], vector_field *f){

  field = *f;

  glutInit(&argc, argv);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(0,0);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Simulador");

  initial_condition();

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

  /* Coordenas como em http://www.flashandmath.com/advanced/t1player10/system.jpg */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotated(180,0,1,0); 
  glRotated(180,0,0,1);  
  glPushMatrix();

  glutReshapeFunc(resize);
  glutDisplayFunc(plot_spheres);
  glutKeyboardFunc(key_pressed);
  glutMotionFunc(mouse_move);
  glutMouseFunc(mouse_click);
  glutIdleFunc(idle);
  glutMainLoop();
}
