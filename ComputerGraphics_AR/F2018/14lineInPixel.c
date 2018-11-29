/*****************************************************
 * Program: lineInPixel.c   Coded by: Harry Li       *
 * Version: x1.0;    status: tested;                 *
 * Compile and build:                                *
 * gcc main.cpp -o main.o -lGL -lGLU -lglut          *
 * Date: Jun 5, 2014                                 * 
 *       last update, Nov. 27, 2018                  * 
 * Purpose: drawing line in pixel                    *  
 * ref: https://stackoverflow.com/questions/20832087/how-can-i-specify-vertices-in-pixels-in-opengl
 *****************************************************/ 
#include<GL/glut.h>
#include<stdio.h>

void mydisplay()
{
#include <unistd.h>

glMatrixMode(GL_PROJECTION);     // Set openGL projection matrix
glOrtho(0, 800, 0, 600, -1, 1);  // ortho projection to 800x600 resolution
glMatrixMode(GL_MODELVIEW);      // Restore the default matrix mode

float p1x=10.0f,  p1y=10.0f;  //x-axis    
float p2x=600.0f, p2y=10.0f;    

float p3x=10.0f, p3y=10.0f;   //y-axis  
float p4x=10.0f, p4y=450.0f; 

glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity(); 
glBegin(GL_LINES); 
glColor3f(1.0, 0.0, 0.0); 
glVertex2f(p1x,p1y);  
glVertex2f(p2x,p2y);
glColor3f(0.0, 1.0, 0.0); 
glVertex2f(p3x,p3y);  
glVertex2f(p4x,p4y);
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


