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
#include <unistd.h>

#define UpperBD 3
#define Xe 200
#define Ye  200
#define Ze  200
#define Rho  sqrt(sq(Xe) + sq(Ye) + sq(Ze))
#define PI 3.1415926
#define D_focal 20

typedef struct {
	float X[] = {};
	float Y[] = {};
	float Z[] = {};
} pworld;

typedef struct {
	float X[] = {};
	float Y[] = {};
	float Z[] = {};
} pviewer;

typedef struct{
	float X[] = {};
	float Y[] = {};
} pperspective;


void mydisplay()
{
float p1x=0.0f,p1y=1.0f;    //the window coordinates (-1.0, 1.0)
float p2x=0.0f,p2y=-1.0f;
float p3x=1.0f,p3y=0.0f;
float p4x=-1.0f,p4y=0.0f;

glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity(); 

/* Line starts */
glBegin(GL_LINES); 
glVertex2f(p1x,p1y);  
glVertex2f(p2x,p2y);

glVertex2f(p3x, p3y);
glVertex2f(p4x, p4y);
glEnd();
/* Line Ends */


// #define Pheta = PI/4.0;
// #define Phi = 
/* World to viewer */
pworld world;
pviewer viewer;
pperspective perspective;

sPheta = Ye / sqrt(sq(Xe) + sq(Ye));
cPheta = Xe / sqrt(sq(Xe) + sq(Ye));
sPhi = sqrt(sq(Xe) + sq(Ye)) / Rho;
cPhi = Ze / Rho;

for(int i = 0; i <= UpperBD; i++)
{
	viewer[i].X = -sPheta * world[i].X; + cPheta * world[i].y;
	viewer[i].Y = -cPheta * cPhi * world[i].X 
				   - cPhi * sPheta * world[i].Y
				   + sPhi * world[i].Z;
	viewer[i].Z = -sPhi * cPheta * world[i].X 
				   - sPhi * cPheta * world[i].Y
				   -cPheta * world[i].Z + Rho;
	perspective[i].X = (D_focal / viewer[i].Z) * viewer[i].X;
	perspective[i].Y = (D_focal / viewer[i].Z) * viewer[i].Y;
	cout << perspective[i].X << endl;
	cout << perspective[i].Y << endl;

}



glFlush();
usleep(50);
}
int main(int argc, char** argv)
{
glutInit(&argc,argv);
glutCreateWindow("William");
glutDisplayFunc(mydisplay);
glutMainLoop();
}

