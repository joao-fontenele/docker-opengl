#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define PI 3.14159
#define STEPS 200
#define PADDLE_HEIGHT 15.0
#define PADDLE_WIDTH 70.0
#define PADDLE_MOVE 1.0
#define MAX_Y 500
#define MAX_X 700

long double fTime() {
  struct timeval t;
  gettimeofday(&t, NULL);

  return 1.0 * t.tv_sec + 1e-6 * t.tv_usec;
}

int p1UpPressed = 0;
int p2UpPressed = 0;
int p1DownPressed = 0;
int p2DownPressed = 0;

int frames = 0;
long double lastRender;

float p1Y = (float) MAX_Y / 2.0;
float p2Y = (float) MAX_Y / 2.0;
float maxPY = MAX_Y - (PADDLE_WIDTH / 2.0);
float minPY = 0 + PADDLE_WIDTH / 2.0;

typedef struct point {
    float x, y, z;
} Point;

void displayCircle(GLdouble centerX, GLdouble centerY, GLdouble radius, GLint points) {
    GLint i = 0;
    GLdouble theta;
    glBegin(GL_POLYGON);
    for (i = 0; i < points; i++) {
        theta = 2 * PI * i / points;
        glVertex2f(centerX + radius * cos(theta), centerY + radius * sin(theta));
    }
    glEnd();
}

void drawPaddle(player) {
  float pY = p1Y;
  float pX = 0.0;

  if (player == 1) {
    pY = p2Y;
    pX = MAX_X - PADDLE_HEIGHT;
  }

  float halfWidth = PADDLE_WIDTH / 2.0;

  float topLeftY = pY + halfWidth;
  float topRightY = topLeftY;
  float topLeftX = pX;
  float topRightX = pX + PADDLE_HEIGHT;

  float bottomRightY = pY - halfWidth;
  float bottomRightX = topRightX;
  float bottomLeftY = bottomRightY;
  float bottomLeftX = pX;

  glBegin(GL_QUADS);
  glColor3f(0, 0, 1);
  glVertex3f(topLeftX, topLeftY, 0.0);
  glVertex3f(topRightX, topRightY, 0.0);
  glVertex3f(bottomRightX, bottomRightY, 0.0);
  glVertex3f(bottomLeftX, bottomLeftY, 0.0);
  glEnd();
}

void draw() {
  printf("\ndrawing");
  long double now = fTime();
  lastRender = now;

  glClear(GL_COLOR_BUFFER_BIT);
  drawPaddle(0);
  drawPaddle(1);

  glFlush();
}

void moveRoutine() {
  if (p1UpPressed) {
    p1Y += PADDLE_MOVE;
      if (p1Y > maxPY) {
        p1Y = maxPY;
      }
  }

  if (p1DownPressed) {
    p1Y -= PADDLE_MOVE;
      if (p1Y < minPY) {
        p1Y = minPY;
      }
  }

  if (p2UpPressed) {
    p2Y += PADDLE_MOVE;
      if (p2Y > maxPY) {
        p2Y = maxPY;
      }
  }

  if (p2DownPressed) {
    p2Y -= PADDLE_MOVE;
      if (p2Y < minPY) {
        p2Y = minPY;
      }
  }
}

void idle() {
  long double now = fTime();
  long double delta = now - lastRender;

  if (delta > 0.048) {
    printf("\ndelta = %Lf\n", delta);
    moveRoutine();
    glutPostRedisplay();
  }
}

void keyInputPressed(unsigned char key, int x, int y) {
  switch(key) {
    case 27:
      exit(0);
      break;
    case 'w':
      p1UpPressed = 1;
      break;
    case 's':
      p1DownPressed = 1;
      break;
    case 'i':
      p2UpPressed = 1;
      break;
    case 'k':
      p2DownPressed = 1;
      break;
    case ' ':
      printf("loooool\n");
    default:
      break;
  }
}

void keyInputReleased(unsigned char key, int x, int y) {
  switch(key) {
    case 'w':
      p1UpPressed = 0;
      break;
    case 's':
      p1DownPressed = 0;
      break;
    case 'i':
      p2UpPressed = 0;
      break;
    case 'k':
      p2DownPressed = 0;
      break;
    default:
      break;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

  glutInitWindowSize(MAX_X, MAX_Y);
  glutCreateWindow("Pong");
  gluOrtho2D(0.0, MAX_X, 0.0, MAX_Y);
  glMatrixMode(GL_PROJECTION);

  glutKeyboardUpFunc(keyInputReleased);
  glutKeyboardFunc(keyInputPressed);
  glutDisplayFunc(draw);
  glutIdleFunc(idle);
  glutMainLoop();

  return 0;
}
