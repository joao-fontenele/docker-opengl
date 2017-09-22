#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define PI 3.14159

int factor = 20;
double lastTime;
double dx = 0.;

void bico() {
  glBegin(GL_TRIANGLES);
  glColor3f(0, 1, 0);
  glVertex3f(3.0, 6.0, 0);
  glVertex3f(4.0, 8.0, 0);
  glVertex3f(5.0, 6.0, 0);
  glEnd();
}

void corpo() {
  glBegin(GL_QUADS);
  glColor3f(0, 0, 1);
  glVertex3f(3.0, 1.0, 0);
  glVertex3f(5.0, 1.0, 0);
  glVertex3f(5.0, 6.0, 0);
  glVertex3f(3.0, 6.0, 0);
  glEnd();
}

void asaEsquerda() {
  glBegin(GL_TRIANGLES);
  glColor3f(1, 0, 0);
  glVertex3f(1.5, 1.0, 0);
  glVertex3f(3.0, 1.0, 0);
  glVertex3f(3.0, 3.0, 0);
  glEnd();
}

void asaDireita() {
  glBegin(GL_TRIANGLES);
  glColor3f(1, 0, 0);
  glVertex3f(5.0, 1.0, 0);
  glVertex3f(6.5, 1.0, 0);
  glVertex3f(5.0, 3.0, 0);
  glEnd();
}

void desenharFoguete() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glTranslatef(dx / 2., dx, 0.);

  bico();
  corpo();
  asaEsquerda();
  asaDireita();
  glFlush();
}

void draw() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0., 20., 0., 20.);

  glRotatef(-20, 0., 0., 1.);

  desenharFoguete();

  glutSwapBuffers();
}

double fTime() {
  struct timeval t;
  gettimeofday(&t, NULL);

  return 1.0 * t.tv_sec + 1e-6 * t.tv_usec;
}

void animate(double speed) {
  if (dx > 20) {
    dx = 0.;
  } else {
    dx += speed / factor;
  }
  glutPostRedisplay();
}

void idle() {
  double now = fTime();
  double delta = now - lastTime;
  lastTime = now;

  double speed = delta * 60;

  animate(speed);
  glutPostRedisplay();
}

void keyboardCb(unsigned char key, int x, int y) {
  if (key == 27) {
    exit(0);
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowSize(500, 500);
  glutCreateWindow("Default viewport spans the whole interface window");

  glutKeyboardFunc(keyboardCb);
  glutDisplayFunc(draw);
  glutIdleFunc(idle);
  glutPostRedisplay();
  glutMainLoop();

  return 0;
}
