/**********************************************************************************/
/* Note: This code was re-arranged to fit Digital Image Processing Class, further */
/*       reference is given below:                                                */
/* OpenGL to display a bmp image.                                                 */ 
/* note: compilation and built:                                                   */
/* 1. gcc bmp.c readBMP.c -o bmp.o -lGL -lGLU -lglut                              */  
/* 2. be sure to have both program bmp.c and readBMP.c and                        */
/*    readBMP.h in the same directory.                                            */
/* last update: Nov 2018                                                          */ 
/**********************************************************************************/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>  
#include <stdlib.h>
#include "readBMP.h"

int window;
Image *image;
int n,m; 
char *filename;

/*******************************************/
//get image data
/*******************************************/
void getImage() {
image = (Image *) malloc(sizeof(Image));
if (image == NULL) {
printf("Error allocating space for the image");
exit(-1);
}
if (!ImageLoad(filename, image)) {
exit(-2);
}    
}

/********************************************/
// display image
/********************************************/ 
void display()
{
glClear(GL_COLOR_BUFFER_BIT);
glRasterPos2i(0,0);
//draw image
glDrawPixels(n,m,GL_RGB, GL_UNSIGNED_BYTE, image->data);
glFlush();
//10
}

/*********************************************/
// reshape
/*********************************************/
void reshape(int width, int height)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0, (GLfloat) n, 0.0, (GLfloat) m);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glViewport(0,0,width,height);
}

/**********************************************/
// main module 
/**********************************************/
int main(int argc, char **argv)
{
//Get the filename from command line
switch (argc) {
case 1:
printf("Usage: program__name <image filename>\n");
exit(-1);
case  2: 
filename = argv[1];
break;
default:
printf("usage: program_name <image filename>\n");
}

// Intialize GLUT
glutInit(&argc, argv);

// Confiure GLUT
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
getImage(image);  

//get image size
n = image->sizeX;
m = image->sizeY;
glutInitWindowSize(n, m);
glutInitWindowPosition(0,0);
glutCreateWindow("Image display lab");
glClearColor(1.0, 1.0, 1.0, 1.0); 

// call back funtions
glutDisplayFunc(display);
glutReshapeFunc(reshape);

//Pass control to GLUT
glutMainLoop();
return(0);
}
