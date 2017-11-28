#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define PI 3.14159
#define UPDATE_RATE 48
#define STEPS 200
#define PADDLE_HEIGHT 15.0
#define PADDLE_WIDTH 70.0
#define PADDLE_MOVE 14.0
#define BALL_RADIUS 8.0
#define BALL_SPEED_FACTOR 1.05
#define BALL_INITIAL_SPEED 9.0
#define MAX_Y 500
#define MAX_X 700

int isStarted = 0;

int p1Score = 0;
int p2Score = 0;

int p1UpPressed = 0;
int p2UpPressed = 0;
int p1DownPressed = 0;
int p2DownPressed = 0;

float p1Y = (float) MAX_Y / 2.0;
float p2Y = (float) MAX_Y / 2.0;
float maxPY = MAX_Y - (PADDLE_WIDTH / 2.0);
float minPY = 0 + PADDLE_WIDTH / 2.0;

// ball starts at the center of p1 paddle
float ballX = PADDLE_HEIGHT + BALL_RADIUS;
float ballY = (float) MAX_Y / 2.0;
float ballVx = BALL_INITIAL_SPEED;
float ballVy = BALL_INITIAL_SPEED;

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

void drawBall() {
  displayCircle(ballX, ballY, BALL_RADIUS, 25);
}

void drawBitmapString(float x, float y, char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

void drawScore() {
  char str[10];
  sprintf(str, "%d - %d", p1Score, p2Score);
  drawBitmapString(MAX_X / 2.0 - 5, MAX_Y - 20.0, str);
}

void draw() {
  glClear(GL_COLOR_BUFFER_BIT);
  drawPaddle(1); // draw p1
  drawPaddle(2); // draw p2

  drawBall();
  drawScore();

  glutSwapBuffers();
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

  if (!isStarted) {
    ballY = p1Y;
  }
}

int isColliding() {
  float halfWidth = PADDLE_WIDTH / 2.0;
  if (ballX <= PADDLE_HEIGHT) {
    if (ballY <= p1Y + halfWidth && ballY >= p1Y - halfWidth) {
      ballX = PADDLE_HEIGHT;
      ballVx = -ballVx;
      return 1;
    }
  }

  if (ballX >= MAX_X - PADDLE_HEIGHT) {
    if (ballY <= p2Y + halfWidth && ballY >= p2Y - halfWidth) {
      ballX = MAX_X - PADDLE_HEIGHT;
      ballVx = -ballVx;
      return 2;
    }
  }

  return 0;
}

void ballRoutine() {
  ballX += ballVx;
  ballY += ballVy;
  float maxBallY = MAX_Y - BALL_RADIUS;
  float maxBallX = MAX_X - BALL_RADIUS;

  if (isColliding()) {
    ballVx *= BALL_SPEED_FACTOR;
    ballVy *= BALL_SPEED_FACTOR;
  }

  // player 2 score
  if (ballX < BALL_RADIUS) {
      p2Score += 1;
      ballX = BALL_RADIUS;
      ballVx = -ballVx;
  }

  // player 1 score
  if (ballX > maxBallX) {
      p1Score += 1;
      ballX = maxBallX;
      ballVx = -ballVx;
  }

  if (ballY < BALL_RADIUS) {
      ballY = BALL_RADIUS;
      ballVy = -ballVy;
  }

  if (ballY > maxBallY) {
      ballY = maxBallY;
      ballVy = -ballVy;
  }
}

void routines() {
  if (isStarted) {
    ballRoutine();
  }
  moveRoutine();
  glutPostRedisplay();
  glutTimerFunc(UPDATE_RATE, routines, 1);
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
      isStarted = 1;
       break;
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
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE);
  glEnable(GL_MULTISAMPLE);

  glutInitWindowSize(MAX_X, MAX_Y);
  glutCreateWindow("Pong");
  gluOrtho2D(0.0, MAX_X, 0.0, MAX_Y);
  glMatrixMode(GL_PROJECTION);

  glutKeyboardUpFunc(keyInputReleased);
  glutKeyboardFunc(keyInputPressed);
  glutDisplayFunc(draw);
  glutTimerFunc(UPDATE_RATE, routines, 1);
  glutMainLoop();

  return 0;
}
