/*****************************************************
 * Program: line.c   Coded by: Harry Li              *
 * Version: x1.0;    status: tested;                 *
 * Compile and build:                                *
 * gcc main.cpp -o main.o -lGL -lGLU -lglut          *
 * Date: Jun 5, 2014                                 * 
 * Purpose: Graphics program to prepare visulization *
 *          of Bresenham circle.                     *  
 *****************************************************/ 
#include<GL/glut.h>
#include<stdio.h>

// 
void mydisplay()
{

//define virtex for the square 
float p1x=1.0f,p1y=1.0f;  
float p2x=1.0f,p2y=0.0f;
float p3x=0.0f,p3y=0.0f; 
float p4x=0.0f,p4y=1.0f;  

int r; 
float grid, float_r;      
int i; 

//define the x-y axis  
float px1x=0.0f,px1y=0.5f, px2x=1.0f, px2y=0.5f;   
float px3x=0.5f,px3y=0.0f, px4x=0.5f, px4y=1.0f;   

glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity();
glTranslatef(-0.5f,-0.5f,0.0f);
glFlush();
sleep(1);

//-------draw square----------------------// 
glBegin(GL_LINES);
//draw square
glVertex2f(p1x,p1y);  
glVertex2f(p2x,p2y);
glVertex2f(p2x,p2y);
glVertex2f(p3x,p3y);
glVertex2f(p3x,p3y);
glVertex2f(p4x,p4y);
glVertex2f(p4x,p4y);
glVertex2f(p1x,p1y);
glEnd();

//-------draw x-y axis-------------------//  
glBegin(GL_LINES);
glVertex2f(px1x,px1y); 
glVertex2f(px2x,px2y);
glVertex2f(px3x,px3y);
glVertex2f(px4x,px4y);
glEnd();

//-------draw grids-------------------//  
float_r = 20.0; 
r =  float_r; 
grid = 1.0/(2*float_r);   


glBegin(GL_LINES);
for (i=0; i < r; i++) {
glVertex2f(px1x,px1y+i*grid);  //x direction, upper half   
glVertex2f(px2x,px2y+i*grid);
glVertex2f(px1x,px1y-i*grid);  //x direction, lower half   
glVertex2f(px2x,px2y-i*grid);
glVertex2f(px3x+i*grid,px3y);  //y direction, right half   
glVertex2f(px4x+i*grid,px4y);
glVertex2f(px3x-i*grid,px3y);  //y direction, left half   
glVertex2f(px4x-i*grid,px4y);
}
glEnd();

//-------draw grid polygon----------------//
glBegin(GL_POLYGON);
glVertex2f(px1x, px1y);
//px1y = px1y + grid; 
glVertex2f(px1x, px1y);
glVertex2f(px1x, px1y+grid);
glVertex2f(px1x+grid, px1y+grid);
glVertex2f(px1x+grid, px1y);
glEnd();

//-------draw dot----------------//
/*

glBegin(GL_POLYGON);
glVertex2f(-0.5, 0.0);
glVertex2f(-0.0, 0.0);
glVertex2f(0.0, -0.5);
glVertex2f(-0.5,-0.5);
glEnd();
*/

glFlush();
usleep(50);

}
int main(int argc, char** argv)
{
glutInit(&argc,argv);
glutCreateWindow("Harry: testing pattern: square");
glutDisplayFunc(mydisplay);
glutMainLoop();
}

