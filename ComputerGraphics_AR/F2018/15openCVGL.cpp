/*------------------------------------------------------*
 * Program: openCVGL.cpp;         Date: March 2016;     *
 * Purpose:                                             *
 *   Demo for OpenCV and OpenGL applicatons.            *
 * Reference:                                           * 
 * last update: Nov 2018                                * 
 *------------------------------------------------------*/
// For OpenCV 2.X use this import statement: 
//#include <opencv/cv.h>

/* 
g++ -ggdb `pkg-config --cflags opencv` -o `basename openCVGL.cpp .cpp` openCVGL.cpp `pkg-config --libs opencv` -lGL -lGLU -lglut -lm -lstdc++
*/

#include <opencv2/opencv.hpp>   //for OpenCV 3.x  
#include <opencv/highgui.h>     //for OpenCV 3.x  

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <cstdio>

cv::VideoCapture *cap = NULL;
int width = 640;
int height = 480;
cv::Mat image;

/*------------ function displaying x,y,z coordinate system ----------*/     
void drawAxes(float length)
{
  glPushAttrib(GL_POLYGON_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT) ;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) ;
  glDisable(GL_LIGHTING) ;

  glBegin(GL_LINES) ;
  glColor3f(1,0,0) ;       //x: red  
  glVertex3f(0,0,0) ;
  glVertex3f(length,0,0);

  glColor3f(0,1,0) ;       //y: blue  
  glVertex3f(0,0,0) ;
  glVertex3f(0,length,0);  

  glColor3f(0,0,1) ;       //z: green  
  glVertex3f(0,0,0) ;
  glVertex3f(0,0,length);
  glEnd() ;

  glPopAttrib() ;
}

/*---------------- display --------------*/ 
void display()
{
  glClear( GL_COLOR_BUFFER_BIT ); // clear window  
  // cv::Mat stores data, has to flip it before displaying it
  cv::Mat tempimage;
  /*
  flip(image, image, 0);  // vertically 
  flip(image, image, +1); // horizontally 

  // or 90 degree clock wise 
  transpose(image, image);
  flip(image, image, +1);

  // or 90 degree counter clock wise 
  transpose(image, image);
  flip(image, image, 0);
  */ 
  cv::flip(image, tempimage, 0);
  glDrawPixels(tempimage.size().width,tempimage.size().height,GL_BGR,GL_UNSIGNED_BYTE,tempimage.ptr());

  //set viewport
  glViewport(0, 0, tempimage.size().width, tempimage.size().height);

  //set projection matrix using intrinsic camera params
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /*
  void gluPerspective(GLdouble fovy,  GLdouble aspect,  GLdouble zNear,  GLdouble zFar);
  */  
  gluPerspective(60, tempimage.size().width*1.0/tempimage.size().height, 1, 20); 

  //you will have to set modelview matrix using extrinsic camera params
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  /*gluLookAt (cameraX, cameraY, cameraZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ);
   https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluLookAt.xml
  */  
  gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);  //(upX, upY, upZ) = (0, 1, 0) always 

  //now that the camera params have been set, draw your 3D shapes
  //first, save the current matrix
  glPushMatrix();
    //move to the position where you want the 3D object to go
    glTranslatef(0, 0, 0); //this is an arbitrary position for demonstration
    //you will need to adjust your transformations to match the positions where
    //you want to draw your objects(i.e. chessboard center, chessboard corners)
    glutSolidTeapot(0.2);
    glutSolidSphere(.3, 100, 100);
    drawAxes(1.0);
  glPopMatrix();
  

  // show the rendering on the screen
  glutSwapBuffers();

  // post the next redisplay
  glutPostRedisplay();
}

void reshape( int w, int h )
{
  // set OpenGL viewport (drawable area)
  glViewport( 0, 0, w, h );
}

void mouse( int button, int state, int x, int y )
{
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
    {

    }
}

void keyboard( unsigned char key, int x, int y )
{
  switch ( key )
    {
    case 'q':
      // quit when q is pressed
      exit(0);
      break;

    default:
      break;
    }
}

void idle()
{
  // grab a frame from the camera
  (*cap) >> image;
}

int main( int argc, char **argv )
{
  int w,h;

  if ( argc == 1 ) {
    // start video capture from camera
    cap = new cv::VideoCapture(0);
  } else if ( argc == 2 ) {
    // start video capture from file
    cap = new cv::VideoCapture(argv[1]);
  } else {
    fprintf( stderr, "usage: %s [<filename>]\n", argv[0] );
    return 1;
  }

  // check that video is opened
  if ( cap == NULL || !cap->isOpened() ) {
    fprintf( stderr, "could not start video capture\n" );
    return 1;
  }

  // get width and height
  w = (int) cap->get( CV_CAP_PROP_FRAME_WIDTH );
  h = (int) cap->get( CV_CAP_PROP_FRAME_HEIGHT );
  // On Linux, there is currently a bug in OpenCV that returns 
  // zero for both width and height here (at least for video from file)
  // hence the following override to global variable defaults: 
  width = w ? w : width;
  height = h ? h : height;

  // initialize GLUT
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  glutInitWindowPosition( 20, 20 );
  glutInitWindowSize( width, height );
  glutCreateWindow( "OpenGL / OpenCV Example" );

  // set up GUI callback functions
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutMouseFunc( mouse );
  glutKeyboardFunc( keyboard );
  glutIdleFunc( idle );

  // start GUI loop
  glutMainLoop();

  return 0;
}
