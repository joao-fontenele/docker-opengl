#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define PI 3.14159

float distance = 1.0; // camera distance to the center

float angleXY = 90.0;
float angleZ = 0.0;

void draw() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);

  glutWireTeapot(0.5);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(distance * sin(angleXY), distance * cos(angleXY), distance * cos(angleZ),
            0.0, 0.0, 0.0,
            0.0, 1, 0);

  glFlush();
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y) {
  if (key == GLUT_KEY_LEFT) {
    angleXY -= 5.0;
    if (angleXY < 0.0) {
      angleXY = 360.0;
    }
  } else if (key == GLUT_KEY_RIGHT) {
    angleXY += 5.0;
    if (angleXY > 360.0) {
      angleXY = 0.0;
    }
  } else if (key == GLUT_KEY_DOWN) {
    angleZ -= 5.0;
    if (angleZ < 0.0) {
      angleZ = 360.0;
    }
  } else if (key == GLUT_KEY_UP) {
    angleZ += 5.0;
    if (angleZ > 360.0) {
      angleZ = 0.0;
    }
  }

  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);

  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);

  glutCreateWindow("Teapot Look At");
  glutDisplayFunc(draw);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

  glutSpecialFunc(specialKeyInput);
  glutMainLoop();

  return 0;
}
