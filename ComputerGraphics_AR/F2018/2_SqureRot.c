/*****************************************************
 * Program: LinePattern.c                            *
 * Purpose: To draw rotation square based vectors    * 
 * Compile and build:                                *
 *         gcc -lGU -lGLU -lglut                     *  
*****************************************************/ 
#include<GL/glut.h>
#include<stdio.h>
#define MAX_LEVEL 35
#define LAMBDA 0.1
void mydisplay()
{
float
p1x=1.0f,p1y=1.0f,p2x=1.0f,p2y=0.0f,p3x=0.0f,p3y=0.0f,p4x=0.0f,p4y=
1.0f;
int i=0;
glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity();
glTranslatef(-0.5f,-0.5f,0.0f);
glFlush();
sleep(1);
for(i=0;i<MAX_LEVEL;i++)
{
glBegin(GL_LINES);
//-------------------------
glVertex2f(p1x,p1y);
glVertex2f(p2x,p2y);
//-------------------------
glVertex2f(p2x,p2y);
glVertex2f(p3x,p3y);
//-------------------------
glVertex2f(p3x,p3y);
glVertex2f(p4x,p4y);
//-------------------------
glVertex2f(p4x,p4y);
glVertex2f(p1x,p1y);
//-------------------------
p1x=p1x + (LAMBDA * (p2x-p1x));
p1y=p1y + (LAMBDA * (p2y-p1y));
p2x=p2x + (LAMBDA * (p3x-p2x));
p2y=p2y + (LAMBDA * (p3y-p2y));
p3x=p3x + (LAMBDA * (p4x-p3x));
p3y=p3y + (LAMBDA * (p4y-p3y));
p4x=p4x + (LAMBDA * (p1x-p4x));
p4y=p4y + (LAMBDA * (p1y-p4y));
glEnd();
glFlush();
usleep(50000);
}
}
int main(int argc, char** argv)
{
glutInit(&argc,argv);
glutCreateWindow("Harry: Vector Based Rotation Square");
glutDisplayFunc(mydisplay);
glutMainLoop();
}

