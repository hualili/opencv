/*****************************************************
 * Program: cube_leeyu.c   Coded by: Lee-Yu Lai      *           
 * Version: x1.0;                                    *
 * Compile and build:                                *
 * Mac: gcc test.cpp -o test.o -framework OpenGL -framework GLUT*
 * Date: Oct 3, 2019                                 * 
 * Purpose: Cube Demo.                           *  
 *****************************************************/

//For Mac
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <math.h>

#define UpperBD 51
#define PI      3.1415926
#define Num_pts 10

float Xe = 225.0f;
float Ye = 175.0f;
float Ze = 200.0f;

float Rho = sqrt(pow(Xe,2) + pow(Ye,2) + pow(Ze,2));
float D_focal = 1.5f; 

typedef struct {
    float X[UpperBD];
    float Y[UpperBD];
    float Z[UpperBD];
} pworld;

typedef struct {
    float X[UpperBD];
    float Y[UpperBD];
    float Z[UpperBD];
} pviewer;

typedef struct{
    float X[UpperBD];
    float Y[UpperBD];
} pperspective;

typedef struct{
    float X[30];
    float Y[30];
} letter;

void mydisplay()
{
    // define x-y coordinate
    float p1x=-1.0f,  p1y= 0.0f;
    float p2x= 1.0f,  p2y= 0.0f;
    float p3x= 0.0f,  p3y= 1.0f;
    float p4x= 0.0f,  p4y=-1.0f;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    pworld  world;
    pworld cube;
    pviewer viewer;
    pviewer cubeviewer;
    pperspective perspective;
    pperspective cubeperspective;
    letter letterL;
    letter arrow;
    
    //define the x-y-z world coordinate
    world.X[0] = 0.0;    world.Y[0] =  0.0;   world.Z[0] =  0.0;    // origin
    world.X[1] = 50.0;   world.Y[1] =  0.0;   world.Z[1] =  0.0;    // x-axis
    world.X[2] = 0.0;    world.Y[2] =  50.0;  world.Z[2] =  0.0;    // y-axis
    world.X[3] = 0.0;    world.Y[3] =  0.0;   world.Z[3] =  50.0;   // z-axis

    cube.X[0] = 100.0;    cube.Y[0] =  100.0;   cube.Z[0] =  110.0;
    cube.X[1] = 0.0;    cube.Y[1] =  100.0;   cube.Z[1] =  110.0;
    cube.X[2] = 0.0;    cube.Y[2] =  0.0;   cube.Z[2] =  110.0;
    cube.X[3] = 100.0;    cube.Y[3] =  0.0;   cube.Z[3] =  110.0;
    cube.X[4] = 100.0;    cube.Y[4] =  100.0;   cube.Z[4] =  10.0;
    cube.X[5] = 0.0;    cube.Y[5] =  100.0;   cube.Z[5] =  10.0;
    cube.X[6] = 0.0;    cube.Y[6] =  0.0;   cube.Z[6] =  10.0;
    cube.X[7] = 100.0;    cube.Y[7] =  0.0;   cube.Z[7] =  10.0;
    
    
    world.X[4] = 60.0;     world.Y[4] = -50.0;    world.Z[4] = 0.0;//p4 of box
    world.X[5] = 60.0;     world.Y[5] = 50.0;    world.Z[5] = 0.0; //p5 of box
    
    world.X[6] = 60.0;     world.Y[6] = 50.0;    world.Z[6] = 100.0;//p6 of box
    world.X[7] = 60.0;     world.Y[7] = -50.0;    world.Z[7] = 100.0;//p7 of box. Pi
        
    letterL.X[0] = 10.0; letterL.Y[0] = 10.0;
    letterL.X[1] = 20.0; letterL.Y[1] = 10.0;
    letterL.X[2] = 20.0; letterL.Y[2] = 40.0;
    letterL.X[3] = 40.0; letterL.Y[3] = 10.0;
    letterL.X[4] = 50.0; letterL.Y[4] = 10.0;
    letterL.X[5] = 30.0; letterL.Y[5] = 50.0;
    letterL.X[6] = 50.0; letterL.Y[6] = 90.0;
    letterL.X[7] = 40.0; letterL.Y[7] = 90.0;
    letterL.X[8] = 20.0; letterL.Y[8] = 60.0;
    letterL.X[9] = 20.0; letterL.Y[9] = 90.0;
    letterL.X[10] = 10.0; letterL.Y[10] = 90.0;
    letterL.X[11] = 50.0; letterL.Y[11] = 10.0;
    letterL.X[12] = 80.0; letterL.Y[12] = 10.0;
    letterL.X[13] = 90.0; letterL.Y[13] = 20.0;
    letterL.X[14] = 90.0; letterL.Y[14] = 80.0;
    letterL.X[15] = 80.0; letterL.Y[15] = 90.0;
    letterL.X[16] = 50.0; letterL.Y[16] = 90.0;
    letterL.X[17] = 60.0; letterL.Y[17] = 20.0;
    letterL.X[18] = 70.0; letterL.Y[18] = 20.0;
    letterL.X[19] = 80.0; letterL.Y[19] = 30.0;
    letterL.X[20] = 80.0; letterL.Y[20] = 70.0;
    letterL.X[21] = 70.0; letterL.Y[21] = 80.0;
    letterL.X[22] = 60.0; letterL.Y[22] = 80.0;

    for(int i = 8; i<31; i++){
        world.X[i] = 60;
        world.Y[i] = letterL.X[i-8] - 50.0;
        world.Z[i] = letterL.Y[i-8];
    }
    
    arrow.X[0] = 0.0; arrow.Y[0] = 25.0;
    arrow.X[1] = 0.0; arrow.Y[1] = 75.0;
    arrow.X[2] = 60.0; arrow.Y[2] = 75.0;
    arrow.X[3] = 60.0; arrow.Y[3] = 85.0;
    arrow.X[4] = 90.0; arrow.Y[4] = 50.0;
    arrow.X[5] = 60.0; arrow.Y[5] = 15.0;
    arrow.X[6] = 60.0; arrow.Y[6] = 25.0;
    
    for(int j = 0; j<7; j++){
        world.X[31 + j] = arrow.X[j];
        world.Y[31 + j] = arrow.Y[j];
        world.Z[31 + j] = 150.0;
    }
    arrow.X[7] = 0.0; arrow.Y[7] = 25.0;
    arrow.X[8] = 0.0; arrow.Y[8] = 75.0;
    arrow.X[9] = 60.0; arrow.Y[9] = 75.0;
    arrow.X[10] = 60.0; arrow.Y[10] = 85.0;
    arrow.X[11] = 90.0; arrow.Y[11] = 50.0;
    arrow.X[12] = 60.0; arrow.Y[12] = 15.0;
    arrow.X[13] = 60.0; arrow.Y[13] = 25.0;
    
    for(int k = 0; k<7; k++){
        world.X[38 + k] = arrow.X[k];
        world.Y[38 + k] = arrow.Y[k];
        world.Z[38 + k] = 140.0;
    }
    
    
    float sPheta = Ye / sqrt(pow(Xe,2) + pow(Ye,2));
    float cPheta = Xe / sqrt(pow(Xe,2) + pow(Ye,2));
    float sPhi = sqrt(pow(Xe,2) + pow(Ye,2)) / Rho;
    float cPhi = Ze / Rho;
    
    
    //47 = normal vector, 46 = A, 45 = Ps, 7 = top left box vertex
    world.X[45] = -200.0; world.Y[45] = 50.0; world.Z[45] = 200.0; // Ps (point source)
    world.X[46] = 0; world.Y[46] = 0; world.Z[46] = 0; // arbitrary vector A on x-y plane
    world.X[47] = 0; world.Y[47] = 0; world.Z[47] = 1; // normal vector for x-y
    
    
    float temp = (world.X[47]*(world.X[46]-world.X[45]))
                +(world.Y[47]*(world.Y[46]-world.Y[45]))
                +(world.Z[47]*(world.Z[46]-world.Z[45]));
    float lambda = temp / ((world.X[47]*(world.X[45]-world.X[7]))
                           +(world.Y[47]*(world.Y[45]-world.Y[7]))
                           +(world.Z[47]*(world.Z[45]-world.Z[7])));
    float lambda_2 = temp / ((world.X[47]*(world.X[45]-world.X[6]))
                             +(world.Y[47]*(world.Y[45]-world.Y[6]))
                             +(world.Z[47]*(world.Z[45]-world.Z[6])));
    
    world.X[48] = world.X[45] + lambda*(world.X[45] - world.X[7]); // x component for Intersection point for p7
    world.Y[48] = world.Y[45] + lambda*(world.Y[45] - world.Y[7]); // y component for Intersection point for p7
    world.Z[48] = 0.0;
    
    world.X[49] = world.X[45] + lambda_2*(world.X[45] - world.X[6]);  // x component for intersection point for p6
    world.Y[49] = world.Y[45] + lambda_2*(world.Y[45] - world.Y[6]);  // x component for intersection point for p6
    world.Z[49] = 0.0;
    
    float xMin = 1000.0, xMax = -1000.0;
    float yMin = 1000.0, yMax = -1000.0;
    
    for(int i = 0; i <= UpperBD; i++)
    {
        viewer.X[i] = -sPheta * world.X[i] + cPheta * world.Y[i];
        viewer.Y[i] = -cPheta * cPhi * world.X[i]
        - cPhi * sPheta * world.Y[i]
        + sPhi * world.Z[i];
        viewer.Z[i] = -sPhi * cPheta * world.X[i]
        - sPhi * cPheta * world.Y[i]
        -cPheta * world.Z[i] + Rho;
    }
    
    for(int i = 0; i <= UpperBD; i++)
    {
        perspective.X[i] = 100 * viewer.X[i] / viewer.Z[i] ;
        perspective.Y[i] = 100 * viewer.Y[i] / viewer.Z[i] ;

    }

        for(int i = 0; i <= 7; i++)
    {
        cubeviewer.X[i] = -sPheta * cube.X[i] + cPheta * cube.Y[i];
        cubeviewer.Y[i] = -cPheta * cPhi * cube.X[i]
        - cPhi * sPheta * cube.Y[i]
        + sPhi * cube.Z[i];
        cubeviewer.Z[i] = -sPhi * cPheta * cube.X[i]
        - sPhi * cPheta * cube.Y[i]
        -cPheta * cube.Z[i] + Rho;
    }
    
    for(int i = 0; i <= 7; i++)
    {
        cubeperspective.X[i] = D_focal * cubeviewer.X[i] / cubeviewer.Z[i] ;
        cubeperspective.Y[i] = D_focal * cubeviewer.Y[i] / cubeviewer.Z[i] ;

    }
    
    glBegin(GL_LINES);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(perspective.X[0],perspective.Y[0]);
    glVertex2f(perspective.X[1],perspective.Y[1]);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(perspective.X[0],perspective.Y[0]);
    glVertex2f(perspective.X[2],perspective.Y[2]);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(perspective.X[0],perspective.Y[0]);
    glVertex2f(perspective.X[3],perspective.Y[3]);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(cubeperspective.X[0],cubeperspective.Y[0]);
    glVertex2f(cubeperspective.X[1],cubeperspective.Y[1]);

    glVertex2f(cubeperspective.X[1],cubeperspective.Y[1]);
    glVertex2f(cubeperspective.X[2],cubeperspective.Y[2]);

    glVertex2f(cubeperspective.X[2],cubeperspective.Y[2]);
    glVertex2f(cubeperspective.X[3],cubeperspective.Y[3]);

    glVertex2f(cubeperspective.X[3],cubeperspective.Y[3]);
    glVertex2f(cubeperspective.X[0],cubeperspective.Y[0]);

    glVertex2f(cubeperspective.X[4],cubeperspective.Y[4]);
    glVertex2f(cubeperspective.X[5],cubeperspective.Y[5]);

    glVertex2f(cubeperspective.X[5],cubeperspective.Y[5]);
    glVertex2f(cubeperspective.X[6],cubeperspective.Y[6]);

    glVertex2f(cubeperspective.X[6],cubeperspective.Y[6]);
    glVertex2f(cubeperspective.X[7],cubeperspective.Y[7]);

    glVertex2f(cubeperspective.X[7],cubeperspective.Y[7]);
    glVertex2f(cubeperspective.X[4],cubeperspective.Y[4]);

    glVertex2f(cubeperspective.X[0],cubeperspective.Y[0]);
    glVertex2f(cubeperspective.X[4],cubeperspective.Y[4]);

    glVertex2f(cubeperspective.X[1],cubeperspective.Y[1]);
    glVertex2f(cubeperspective.X[5],cubeperspective.Y[5]);

    glVertex2f(cubeperspective.X[2],cubeperspective.Y[2]);
    glVertex2f(cubeperspective.X[6],cubeperspective.Y[6]);

    glVertex2f(cubeperspective.X[3],cubeperspective.Y[3]);
    glVertex2f(cubeperspective.X[7],cubeperspective.Y[7]);
       
    glEnd();
    glFlush();
    //sleep(5000);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutCreateWindow("132 transformation pipeline");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
}