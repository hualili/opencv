/*****************************************************
 * Program: line.c   Coded by: Harry Li              *
 * Version: x1.0;    status: tested;                 *
 * Compile and build:                                *
 * gcc main.cpp -o main.o -lGL -lGLU -lglut          *
 * Date: Jun 5, 2014                                 * 
 * Purpose: Graphics Demo.                           *  
 *****************************************************/ 
#include<GL/glut.h>
#include<stdio.h>
void mydisplay()
{
float p1x=1.0f,p1y=1.0f;    //the window coordinates (-1.0, 1.0)
float p2x=-1.0f,p2y=-1.0f;
glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity(); 
glBegin(GL_LINES); 
glVertex2f(p1x,p1y);  
glVertex2f(p2x,p2y);
glEnd();
glFlush();
usleep(50);
}
int main(int argc, char** argv)
{
glutInit(&argc,argv);
glutCreateWindow("Harry: test");
glutDisplayFunc(mydisplay);
glutMainLoop();
}

