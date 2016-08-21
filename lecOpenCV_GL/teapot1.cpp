//-----------------------------------------------------------------------
//	File:		sample1.cpp
//	Description:	A simple OpenGL sample program
//	Programmer:	Pooja Nath
//	For:		CMSC 427 - Computer Graphics
//	Date:		Feb 2004
//
//	This is a basic OpenGL/GLUT program, which renders a teapot.
//	Hitting the keyboard charatcers 'a' and 'l' rotate the teapot
//	about the Y (vertical) axis.  Hitting 'q' quits the program.
//-----------------------------------------------------------------------

#include <cstdlib>			// standard definitions
#include <iostream>			// C++ I/O
#include <cstdio>			// C I/O (for sprintf) 
#include <cmath>			// standard definitions

#include <GL/glut.h>			// GLUT
#include <GL/glu.h>			// GLU
#include <GL/gl.h>			// OpenGL

using namespace std;			// make std accessible

double rotAngle = 10;			// rotation angle (BEWARE: Global)

//-----------------------------------------------------------------------
// init
//	Sets up some default OpenGL values.
//-----------------------------------------------------------------------

void init()
{
    glClearColor(0, 0, 0, 0);		// background color
    glClearDepth(1.0);			// background depth value

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000);	// setup a perspective projection

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(				// set up the camera
		0.0, 0.0, 5.0,		// eye position
		0.0, 0.0, 0.0,		// lookat position
		0.0, 1.0, 0.0);		// up direction

    glEnable(GL_DEPTH_TEST);		// enable hidden surface removal

    glEnable(GL_LIGHTING);		// enable lighting
    glEnable(GL_LIGHT0);		// enable
	
    float lpos[] = { 5, 5, 5, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);

    // glShadeModel(GL_FLAT);		// flat shading
    glShadeModel(GL_SMOOTH);		// smooth shading
}

//-----------------------------------------------------------------------
// display callback function
//	This is called each time application needs to redraw itself.
//	Most of the opengl work is done through this function.
//-----------------------------------------------------------------------

void display()
{
    glClear(
	GL_COLOR_BUFFER_BIT |		// clear the frame buffer (color)
	GL_DEPTH_BUFFER_BIT);		// clear the depth buffer (depths)

    glPushMatrix();			// save the current camera transform

    glRotated(rotAngle, 0, 1, 0);	// rotate by rotAngle about y-axis


    glEnable(GL_COLOR_MATERIAL);	// specify object color
    glColor3f(1.0, 0.1, 0.1);		// redish

    glutSolidTeapot(1);			// draw the teapot

    glPopMatrix();			// restore the modelview matrix
    glFlush();				// force OpenGL to render now

    glutSwapBuffers();			// make the image visible
}

//-----------------------------------------------------------------------
// keyboard callback function
//	This is called whenever a keyboard key is hit.
//-----------------------------------------------------------------------

void keyboard(unsigned char k, int x, int y)
{
    switch (k)
    {
    case 'a':
	rotAngle += 5;			// increase rotation by 5 degrees
	break;
    case 'l':
	rotAngle -= 5;			// decrease rotation by 5 degrees
	break;
    case 'q':
	exit(0);			// exit
    }

    glutPostRedisplay();		// redraw the image now
}

//-----------------------------------------------------------------------
//  usage
//	Explain how to use program.
//-----------------------------------------------------------------------

void usage()
{
    cout << "\n\
-----------------------------------------------------------------------\n\
  CMSC 427 Sample Program.\n\
  Inputs:\n\
    a:              Rotate counterclockwise\n\
    l:              Rotate clockwise\n\
    q:              Quit\n\
  You may need to place the cursor over the graphics window for\n\
  keyboard input to be processed.\n\
-----------------------------------------------------------------------\n";
    cout.flush();
}

//-----------------------------------------------------------------------
// main program
//	Where everything begins.
//-----------------------------------------------------------------------

int main()
{
    usage();				// explain how to use
    glutInitDisplayMode(		// initialize GLUT
		GLUT_DOUBLE |		// use double buffering
		GLUT_DEPTH |		// request memory for z-buffer
		GLUT_RGB );		// set RGB color mode

    glutCreateWindow("GLUT Example");	// create the window

    glutDisplayFunc(display);		// call display() to redraw window
    glutKeyboardFunc(keyboard);		// call keyboard() when key is hit

    init();				// our own initializations

    glutMainLoop();			// let GLUT take care of everything
    return 0; 
}

