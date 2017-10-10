#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define PI 3.14159
#define STEPS 200

typedef struct point {
    float x, y, z;
} Point;

int pointsSize = 4;
Point points[4] = {
  {125.0, 125.0, 0.0}, // p0, start of the curve
  {250.0, 250.0, 0.0}, // p1, end of the curve
  {10.0, 62.0, 0.0}, // t0, tangent for p0
  {200.0, 145.0, 0.0} // t1, tangent for p1
};

int selectedPoint = -1; // no selectedPoint

int windowX = 600;
int windowY = 600;
int maxX = 300;
int maxY = 300;

float distance(Point *p0, Point *p1) {
  return sqrt(
    pow(p0->x - p1->x, 2)
    + pow(p0->y - p1->y, 2)
    + pow(p0->z - p1->z, 2)
  );
}

void keyboardCb(unsigned char key, int x, int y) {
  if (key == 27) {
    exit(0);
  }
}

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

void drawHermiteCurve(Point *p0, Point *p1, Point *t0, Point *t1, int steps) {
  int i = 0; // current step
  float s = 0.0; // interpolation step helper
  float s2 = 0.0; // s ** 2
  float s3 = 0.0; // s ** 3
  float h1 = 0.0; // basis hermite function
  float h2 = 0.0; // basis hermite function
  float h3 = 0.0; // basis hermite function
  float h4 = 0.0; // basis hermite function
  float px = 0.0; // interpolated coordinate
  float py = 0.0; // interpolated coordinate
  float pz = 0.0; // interpolated coordinate

  glBegin(GL_LINE_STRIP);

  for (i = 0; i <= steps; i++) {
    // get the interpolation step helper based on the current step
    s = (float) i / (float) steps;

    s2 = s * s;
    s3 = s2 * s;

    // calculate the 4 basis hermite funtions
    h1 =   2.0 * s3 - 3.0 * s2 + 1.0;
    h2 = - 2.0 * s3 + 3.0 * s2;
    h3 =          s3 - 2.0 * s2 + s;
    h4 =          s3        - s2;

    // calculate the interpolated point
    px = h1 * p0->x + h2 * p1->x + h3 * t0->x + h4 * t1->x;
    py = h1 * p0->y + h2 * p1->y + h3 * t0->y + h4 * t1->y;
    pz = h1 * p0->z + h2 * p1->z + h3 * t0->z + h4 * t1->z;

    glVertex3f(px, py, pz);
  }

  glEnd();
}

void draw() {
  float pRadius = 1.7;
  Point p0 = points[0];
  Point p1 = points[1];
  Point t0 = points[2];
  Point t1 = points[3];
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glColor3f(1.0, 1.0, 1.0);
  glLineWidth(1.5);
  drawHermiteCurve(&p0, &p1, &t0, &t1, 30);

  if (selectedPoint == 0) {
      glColor3f(1.0, 0.0, 0.0);
  } else {
      glColor3f(1.0, 1.0, 1.0);
  }
  displayCircle(p0.x, p0.y, pRadius, STEPS);
  if (selectedPoint == 1) {
      glColor3f(1.0, 0.0, 0.0);
  } else {
      glColor3f(1.0, 1.0, 1.0);
  }
  displayCircle(p1.x, p1.y, pRadius, STEPS);

  glColor3f(0.0, 0.0, 1.0);

  glBegin(GL_LINES);
  glVertex3f(p0.x, p0.y, p0.z);
  glVertex3f(t0.x, t0.y, t0.z);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(p1.x, p1.y, p1.z);
  glVertex3f(t1.x, t1.y, t1.z);
  glEnd();

  if (selectedPoint == 2) {
      glColor3f(1.0, 0.0, 0.0);
  } else {
      glColor3f(0.0, 0.0, 1.0);
  }
  displayCircle(t0.x, t0.y, pRadius, STEPS);

  if (selectedPoint == 3) {
      glColor3f(1.0, 0.0, 0.0);
  } else {
      glColor3f(0.0, 0.0, 1.0);
  }
  displayCircle(t1.x, t1.y, pRadius, STEPS);

  glFlush();
}

void convertMouseToOrtho(int x, int y, Point *mouseCoords) {
  mouseCoords->x = (float) (x * maxX) / (float) windowX;
  mouseCoords->y = (float) ((windowY - y) * maxY) / (float) windowY;
}

int getClosestPoint(Point *ref, Point *points, int pointsSize) {
  int i = 0;
  int closestPoint = 0;
  float closestDistance = distance(ref, &points[0]);
  float currentDistance = 0.0;

  for (i = 1; i < pointsSize; i++) {
    currentDistance = distance(ref, &points[i]);
    if (currentDistance < closestDistance) {
      closestDistance = currentDistance;
      closestPoint = i;
    }
  }

  return closestPoint;
}

void mouseHandler(int button, int state, int x, int y) {
  // switch(button) {
  // case GLUT_LEFT_BUTTON:   printf("left\n");   break;
  // case GLUT_MIDDLE_BUTTON: printf("middle\n"); break;
  // case GLUT_RIGHT_BUTTON:  printf("right\n");  break;
  // }
  //
  // switch(state) {
  // case GLUT_DOWN:   printf("down\n");   break;
  // case GLUT_UP: printf("up\n"); break;
  // }
  Point mouseCoords = {0.0, 0.0, 0.0};
  convertMouseToOrtho(x, y, &mouseCoords);

  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      selectedPoint = getClosestPoint(&mouseCoords, points, pointsSize);
    } else if (state == GLUT_UP) {
      if (selectedPoint >= 0 && selectedPoint <= 3) {
        points[selectedPoint].x = mouseCoords.x;
        points[selectedPoint].y = mouseCoords.y;
      }

      // reset selected point on mouse up
      selectedPoint = -1;
    }

    glutPostRedisplay();
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

  glutInitWindowSize(windowX, windowY);
  glutCreateWindow("Hermite curves");
  gluOrtho2D(0.0, maxX, 0.0, maxY);
  glMatrixMode(GL_PROJECTION);

  glutKeyboardFunc(keyboardCb);
  glutMouseFunc(mouseHandler);
  glutDisplayFunc(draw);
  glutMainLoop();

  return 0;
}
