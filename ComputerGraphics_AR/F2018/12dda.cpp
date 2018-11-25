//-----------------------------------------------------------*
//  12dda.cpp                                                *
//  cmpe163_092718_labsample                                 *
//  purpose : demo of diffuse reflection                     *
//  date    : nov 2018                                       *
//  status  : debug                                          *
//  note    ：this code is modified from DK for CMPE 163     *
//            class for diffuse reflection demo.             *
//  compilation and build:                                   *
//  g++ -Wall 11diffuse.cpp -o main.o -lGL -lGLU -lglut -lm  *
//-----------------------------------------------------------*
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double X1, Y1, X2, Y2;

float round_value(float v)
{
  return floor(v + 0.5);
}
void LineDDA(void)
{
  double dx=(X2-X1);
  double dy=(Y2-Y1);
  double steps;
  float xInc,yInc,x=X1,y=Y1;
  /* Find out whether to increment x or y */
  steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps;

  /* Clears buffers to preset values */
  glClear(GL_COLOR_BUFFER_BIT);

  /* Plot the points */
  glBegin(GL_POINTS);
  /* Plot the first point */
  glVertex2d(x,y);
  int k;
  /* For every step, find an intermediate vertex */
  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    /* printf("%0.6lf %0.6lf\n",floor(x), floor(y)); */
    glVertex2d(round_value(x), round_value(y));
  }
  glEnd();

  glFlush();
}
void Init()
{
  /* Set clear color to white */
  glClearColor(0.0,0.0,0.0,0);
  /* Set fill color to black */
  glColor3f(1.0,1.0,0.0);
  /* glViewport(0 , 0 , 640 , 480); */
  /* glMatrixMode(GL_PROJECTION); */
  /* glLoadIdentity(); */
  gluOrtho2D(0 , 640 , 0 , 480);
}
int main(int argc, char **argv)
{
  printf("Enter two end points of the line to be drawn:\n");
  printf("\n************************************");
  printf("\nEnter Point1 X1:\n");
  scanf("%lf",&X1);
  printf("\nX1: %lf\n",X1);

  printf("\nEnter Point1 Y1:\n");
  scanf("%lf",&Y1);
  printf("\nY1: %lf\n",Y1);

  printf("\nEnter Point2 X2:\n");
  scanf("%lf",&X2);
  printf("\nX2: %lf\n",X2);

  printf("\nEnter Point2 Y2:\n");
  scanf("%lf",&Y2);
  printf("\nY2: %lf\n",Y2);

  /* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("DDA_Line");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(LineDDA);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}
