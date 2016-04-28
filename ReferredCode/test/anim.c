#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

int factor=100; // factor the animation is slowed down by

double dx = 0;

void animate(double speed);

static double ftime(void) {
    struct timeval t;
    gettimeofday(&t, NULL);

    return 1.0*t.tv_sec + 1e-6*t.tv_usec;
}

static double last_T;

static void idle(void) {
  const double now_T = ftime();
  const double delta_T = now_T - last_T;
  last_T = now_T;

  const double speed = delta_T * 60;

  animate(speed);

  glutPostRedisplay();
}

void animate(double speed) {
  if (dx > 1.5) {
    dx = -1.5;
  }
  else {
    dx += speed/factor;
  }
  glutPostRedisplay();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.5);

  glBegin(GL_POLYGON);
    glVertex2d(-0.5+dx, 0.5);
    glVertex2d(-0.5+dx, -0.5);
    glVertex2d(0.5+dx, -0.5);
    glVertex2d(0.5+dx, 0.5);
  glEnd();

  glutSwapBuffers();
}

void initialize(void) {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glShadeModel(GL_SMOOTH);
}

void main(int argc, char *argv[]) {

  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(500, 500);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);

  initialize();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutPostRedisplay();

  glutMainLoop();
}
