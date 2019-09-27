//
//  main.cpp
//  cmpe163_092718_labsample
//  
//  gcc main.cpp -o main.o -lGL -lGLU -lglut 

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>
#include <unistd.h>
#include <math.h>

#define UpperBD 51
#define PI      3.1415926
#define Num_pts 10

float Xe = 100.0f;
float Ye = 100.0f;
float Ze = 100.0f;

float Rho = sqrt(pow(Xe,2) + pow(Ye,2) + pow(Ze,2));
float D_focal = 20.0f; 

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
    pviewer viewer;
    pperspective perspective;
    letter letterL;
    letter arrow;
    
    //define the x-y-z world coordinate
    world.X[0] = 0.0;    world.Y[0] =  0.0;   world.Z[0] =  0.0;    // origin
    world.X[1] = 50.0;   world.Y[1] =  0.0;   world.Z[1] =  0.0;    // x-axis
    world.X[2] = 0.0;    world.Y[2] =  50.0;  world.Z[2] =  0.0;    // y-axis
    world.X[3] = 0.0;    world.Y[3] =  0.0;   world.Z[3] =  50.0;   // y-axis
    
    world.X[4] = 60.0;     world.Y[4] = -50.0;    world.Z[4] = 0.0;//p4 of box
    world.X[5] = 60.0;     world.Y[5] = 50.0;    world.Z[5] = 0.0; //p5 of box
    
    world.X[6] = 60.0;     world.Y[6] = 50.0;    world.Z[6] = 100.0;//p6 of box
    world.X[7] = 60.0;     world.Y[7] = -50.0;    world.Z[7] = 100.0;//p7 of box. Pi
    
//    world.X[8] = 60.0;     world.Y[8] = 10.0-50.0;    world.Z[8] = 10.0;
//    world.X[9] = 60.0;     world.Y[9] = 90.0-50.0;    world.Z[9] = 10.0;
//    world.X[10] = 60.0;     world.Y[10] = 90.0-50.0;    world.Z[10] = 30.0;
//    world.X[11] = 60.0;     world.Y[11] = 30.0-50.0;    world.Z[11] = 30.0;
//    world.X[12] = 60.0;     world.Y[12] = 30.0-50.0;    world.Z[12] = 90.0;
//    world.X[13] = 60.0;     world.Y[13] = 10.0-50.0;    world.Z[13] = 90.0;
    
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
        perspective.X[i] = D_focal * viewer.X[i] / viewer.Z[i] ;
        perspective.Y[i] = D_focal * viewer.Y[i] / viewer.Z[i] ;
        //if (perspective.X[i] > xMax) xMax = perspective.X[i];
        //if (perspective.X[i] < xMin) xMin = perspective.X[i];
        //if (perspective.Y[i] > yMax) yMax = perspective.Y[i];
        //if (perspective.Y[i] < yMin) yMin = perspective.Y[i];
        /*
         std::cout << "xMin " << xMin << std::endl;
         std::cout << "xMax " << xMax << std::endl;
         std::cout << "yMin " << yMin << std::endl;
         std::cout << "yMax " << yMax << std::endl;
         */
    }

/*
    for(int i = 0; i <= UpperBD; i++)
    {
        if ((xMax-xMin) != 0) perspective.X[i] = perspective.X[i]/(xMax-xMin);
        if ((yMax-yMin) != 0) perspective.Y[i] = perspective.Y[i]/(yMax-yMin);
        //std::cout << i << perspective.X[i] << perspective.Y[i] << std::endl;
    }
*/   
    
    glBegin(GL_LINES);
    // cross at the display screen
    //glVertex2f(p1x,p1y);
    //glVertex2f(p2x,p2y);
    //glVertex2f(p3x, p3y);
    //glVertex2f(p4x, p4y);
    
    
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
    glEnd();
    
/*
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(perspective.X[4],perspective.Y[4]); // bottom line
    glVertex2f(perspective.X[5],perspective.Y[5]);
    
    glVertex2f(perspective.X[5],perspective.Y[5]); // right line
    glVertex2f(perspective.X[6],perspective.Y[6]);
    
    glVertex2f(perspective.X[6],perspective.Y[6]); // upper line
    glVertex2f(perspective.X[7],perspective.Y[7]);
    
    glVertex2f(perspective.X[4],perspective.Y[4]); // left line
    glVertex2f(perspective.X[7],perspective.Y[7]);
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(perspective.X[8],perspective.Y[8]); // K start
    glVertex2f(perspective.X[9],perspective.Y[9]);
    
    glVertex2f(perspective.X[9],perspective.Y[9]);
    glVertex2f(perspective.X[10],perspective.Y[10]);
    
    glVertex2f(perspective.X[10],perspective.Y[10]);
    glVertex2f(perspective.X[11],perspective.Y[11]);
    
    glVertex2f(perspective.X[11],perspective.Y[11]);
    glVertex2f(perspective.X[12],perspective.Y[12]);
    
    glVertex2f(perspective.X[12],perspective.Y[12]);
    glVertex2f(perspective.X[13],perspective.Y[13]);
    
    glVertex2f(perspective.X[13],perspective.Y[13]);
    glVertex2f(perspective.X[14],perspective.Y[14]);
    
    glVertex2f(perspective.X[14],perspective.Y[14]);
    glVertex2f(perspective.X[15],perspective.Y[15]);
    
    glVertex2f(perspective.X[15],perspective.Y[15]);
    glVertex2f(perspective.X[16],perspective.Y[16]);
    
    glVertex2f(perspective.X[16],perspective.Y[16]);
    glVertex2f(perspective.X[17],perspective.Y[17]);
    
    glVertex2f(perspective.X[17],perspective.Y[17]);
    glVertex2f(perspective.X[18],perspective.Y[18]);
    
    glVertex2f(perspective.X[18],perspective.Y[18]);
    glVertex2f(perspective.X[8],perspective.Y[8]);
    
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2f(perspective.X[19],perspective.Y[19]); // outer D
    glVertex2f(perspective.X[20],perspective.Y[20]);
    
    glVertex2f(perspective.X[20],perspective.Y[20]);
    glVertex2f(perspective.X[21],perspective.Y[21]);
    
    glVertex2f(perspective.X[21],perspective.Y[21]);
    glVertex2f(perspective.X[22],perspective.Y[22]);
    
    glVertex2f(perspective.X[22],perspective.Y[22]);
    glVertex2f(perspective.X[23],perspective.Y[23]);
    
    glVertex2f(perspective.X[23],perspective.Y[23]);
    glVertex2f(perspective.X[24],perspective.Y[24]);
    
    glVertex2f(perspective.X[24],perspective.Y[24]);
    glVertex2f(perspective.X[19],perspective.Y[19]);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2f(perspective.X[25],perspective.Y[25]); //inner D
    glVertex2f(perspective.X[26],perspective.Y[26]);
    
    glVertex2f(perspective.X[26],perspective.Y[26]);
    glVertex2f(perspective.X[27],perspective.Y[27]);
    
    glVertex2f(perspective.X[27],perspective.Y[27]);
    glVertex2f(perspective.X[28],perspective.Y[28]);
    
    glVertex2f(perspective.X[28],perspective.Y[28]);
    glVertex2f(perspective.X[29],perspective.Y[29]);
    
    glVertex2f(perspective.X[29],perspective.Y[29]);
    glVertex2f(perspective.X[30],perspective.Y[30]);
    
    glVertex2f(perspective.X[30],perspective.Y[30]);
    glVertex2f(perspective.X[25],perspective.Y[25]);
    
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(perspective.X[31],perspective.Y[31]); //arrow p0''
    glVertex2f(perspective.X[32],perspective.Y[32]);// p1''
    
    glVertex2f(perspective.X[32],perspective.Y[32]); // p1''
    glVertex2f(perspective.X[33],perspective.Y[33]);// p2''
    
    glVertex2f(perspective.X[33],perspective.Y[33]);
    glVertex2f(perspective.X[34],perspective.Y[34]);
    
    glVertex2f(perspective.X[34],perspective.Y[34]);
    glVertex2f(perspective.X[35],perspective.Y[35]);
    
    glVertex2f(perspective.X[35],perspective.Y[35]);
    glVertex2f(perspective.X[36],perspective.Y[36]);
    
    glVertex2d(perspective.X[36],perspective.Y[36]);
    glVertex2d(perspective.X[37],perspective.Y[37]);
    
    glVertex2f(perspective.X[37],perspective.Y[37]);//p6''
    glVertex2f(perspective.X[31],perspective.Y[31]);//p0''
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(perspective.X[38],perspective.Y[38]); //arrow p0''
    glVertex2f(perspective.X[39],perspective.Y[39]);// p1''
    
    glVertex2f(perspective.X[39],perspective.Y[39]); // p1''
    glVertex2f(perspective.X[40],perspective.Y[40]);// p2''
    
    glVertex2f(perspective.X[40],perspective.Y[40]);
    glVertex2f(perspective.X[41],perspective.Y[41]);
    
    glVertex2f(perspective.X[41],perspective.Y[41]);
    glVertex2f(perspective.X[42],perspective.Y[42]);
    
    glVertex2f(perspective.X[42],perspective.Y[42]);
    glVertex2f(perspective.X[43],perspective.Y[43]);
    
    glVertex2d(perspective.X[43],perspective.Y[43]);
    glVertex2d(perspective.X[44],perspective.Y[44]);
    
    glVertex2f(perspective.X[44],perspective.Y[44]);//p6''
    glVertex2f(perspective.X[38],perspective.Y[38]);//p0''
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(perspective.X[31],perspective.Y[31]); //arrow p0''
    glVertex2f(perspective.X[31+7],perspective.Y[31+7]);// p1''
    
    glVertex2f(perspective.X[32],perspective.Y[32]); // p1''
    glVertex2f(perspective.X[32+7],perspective.Y[32+7]);// p2''
    
    glVertex2f(perspective.X[33],perspective.Y[33]);
    glVertex2f(perspective.X[33+7],perspective.Y[33+7]);
    
    glVertex2f(perspective.X[34],perspective.Y[34]);
    glVertex2f(perspective.X[34+7],perspective.Y[34+7]);
    
    glVertex2f(perspective.X[35],perspective.Y[35]);
    glVertex2f(perspective.X[35+7],perspective.Y[35+7]);
    
    glVertex2d(perspective.X[36],perspective.Y[36]);
    glVertex2d(perspective.X[36+7],perspective.Y[36+7]);
    
    glVertex2f(perspective.X[37],perspective.Y[37]);//p6''
    glVertex2f(perspective.X[37+7],perspective.Y[37+7]);//p0''
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2f(perspective.X[48],perspective.Y[48]); // Pi
    glVertex2f(perspective.X[49],perspective.Y[49]); // Pi+1
    
    glVertex2f(perspective.X[48],perspective.Y[48]); // Pi to 4
    glVertex2f(perspective.X[4],perspective.Y[4]);

    glVertex2f(perspective.X[49],perspective.Y[49]); // Pi+1 to 5
    glVertex2f(perspective.X[5],perspective.Y[5]);


    glEnd();

*/    
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

