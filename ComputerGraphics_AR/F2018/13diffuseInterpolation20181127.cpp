//-----------------------------------------------------------*
//  13diffuseInterpolation.cpp                                            *
//  cmpe163_092718_labsample                                 *
//  purpose : demo of diffuse reflection                     *
//  date    : nov 2018                                       *
//  status  : debug                                          *
//  note    ：this code is modified from DK for CMPE 163     *
//            class for diffuse reflection demo.             *
//  compilation and build:                                   *
//  g++ -Wall 11diffuse.cpp -o main.o -lGL -lGLU -lglut -lm  *
//-----------------------------------------------------------*

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

float Xe = 200.0f, Ye = 200.0f, Ze = 250.0f;  //virtual camera location 
float Rho = sqrt(pow(Xe,2) + pow(Ye,2) + pow(Ze,2));
float D_focal = 100.0f; 
//------point light source defined in line 160 

typedef struct {
    float X[UpperBD], Y[UpperBD], Z[UpperBD];
} pworld;

typedef struct {
    float X[UpperBD], Y[UpperBD], Z[UpperBD];
} pviewer;

typedef struct{
    float X[UpperBD], Y[UpperBD];
} pperspective;

typedef struct{
    float X[30], Y[30];
} letter;

typedef struct {
    float r[UpperBD], g[UpperBD], b[UpperBD];
} pt_diffuse;

void mydisplay()
{ 
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
    
    //define projection plane
    world.X[4] = 60.0;     world.Y[4] = -50.0;    world.Z[4] = 0.0;//p4 of box
    world.X[5] = 60.0;     world.Y[5] = 50.0;    world.Z[5] = 0.0; //p5 of box
    
    world.X[6] = 60.0;     world.Y[6] = 50.0;    world.Z[6] = 100.0;//p6 of box
    world.X[7] = 60.0;     world.Y[7] = -50.0;    world.Z[7] = 100.0;//p7 of box. Pi
    
    //----------letter---------------------*
    letterL.X[0] = 10.0; letterL.Y[0] = 10.0; letterL.X[1] = 20.0; letterL.Y[1] = 10.0;
    letterL.X[2] = 20.0; letterL.Y[2] = 40.0; letterL.X[3] = 40.0; letterL.Y[3] = 10.0;
    letterL.X[4] = 50.0; letterL.Y[4] = 10.0; letterL.X[5] = 30.0; letterL.Y[5] = 50.0;
    letterL.X[6] = 50.0; letterL.Y[6] = 90.0; letterL.X[7] = 40.0; letterL.Y[7] = 90.0;
    letterL.X[8] = 20.0; letterL.Y[8] = 60.0; letterL.X[9] = 20.0; letterL.Y[9] = 90.0;
    letterL.X[10] = 10.0; letterL.Y[10] = 90.0; letterL.X[11] = 50.0; letterL.Y[11] = 10.0;
    letterL.X[12] = 80.0; letterL.Y[12] = 10.0; letterL.X[13] = 90.0; letterL.Y[13] = 20.0;
    letterL.X[14] = 90.0; letterL.Y[14] = 80.0; letterL.X[15] = 80.0; letterL.Y[15] = 90.0;
    letterL.X[16] = 50.0; letterL.Y[16] = 90.0; letterL.X[17] = 60.0; letterL.Y[17] = 20.0;
    letterL.X[18] = 70.0; letterL.Y[18] = 20.0; letterL.X[19] = 80.0; letterL.Y[19] = 30.0;
    letterL.X[20] = 80.0; letterL.Y[20] = 70.0; letterL.X[21] = 70.0; letterL.Y[21] = 80.0;
    letterL.X[22] = 60.0; letterL.Y[22] = 80.0;

    //-------decoration-----------*
    for(int i = 8; i<31; i++){
        world.X[i] = 60;
        world.Y[i] = letterL.X[i-8] - 50.0;
        world.Z[i] = letterL.Y[i-8];
    }
    
    //--------arrow in 2D-------------- * 
    arrow.X[0] = 0.0; arrow.Y[0] = 25.0;    arrow.X[1] = 0.0; arrow.Y[1] = 75.0;
    arrow.X[2] = 60.0; arrow.Y[2] = 75.0;   arrow.X[3] = 60.0; arrow.Y[3] = 85.0;
    arrow.X[4] = 90.0; arrow.Y[4] = 50.0;   arrow.X[5] = 60.0; arrow.Y[5] = 15.0;
    arrow.X[6] = 60.0; arrow.Y[6] = 25.0;   //point 6
    arrow.X[7] = 0.0; arrow.Y[7] = 25.0;    //point 7 
    arrow.X[8] = 0.0; arrow.Y[8] = 75.0;    arrow.X[9] = 60.0; arrow.Y[9] = 75.0;
    arrow.X[10] = 60.0; arrow.Y[10] = 85.0; arrow.X[11] = 90.0; arrow.Y[11] = 50.0;
    arrow.X[12] = 60.0; arrow.Y[12] = 15.0; arrow.X[13] = 60.0; arrow.Y[13] = 25.0;
    
    //-------arrow top surface--------* 
    for(int j = 0; j<7; j++){
        world.X[31 + j] = arrow.X[j];
        world.Y[31 + j] = arrow.Y[j];
        world.Z[31 + j] = 150.0;
    }
    //-------arrow base---------------* 
    for(int k = 0; k<7; k++){
        world.X[38 + k] = arrow.X[k];
        world.Y[38 + k] = arrow.Y[k];
        world.Z[38 + k] = 140.0;
    }
    
    //sin and cosine computation for world-to-viewer 
    float sPheta = Ye / sqrt(pow(Xe,2) + pow(Ye,2));
    float cPheta = Xe / sqrt(pow(Xe,2) + pow(Ye,2));
    float sPhi = sqrt(pow(Xe,2) + pow(Ye,2)) / Rho;
    float cPhi = Ze / Rho;
    
    
    //47 = normal vector, 46 = A, 45 = Ps, 7 = top left box vertex
    world.X[45] = -200.0; world.Y[45] = 50.0; world.Z[45] = 200.0; // Ps (point source)
    world.X[46] = 0; world.Y[46] = 0; world.Z[46] = 0; // arbitrary vector A on x-y plane
    world.X[47] = 0; world.Y[47] = 0; world.Z[47] = 1; // normal vector for x-y plane 
    
    //----------lambda for Intersection pt on xw-yw plane----------* 
    float temp = (world.X[47]*(world.X[46]-world.X[45]))
                +(world.Y[47]*(world.Y[46]-world.Y[45]))
                +(world.Z[47]*(world.Z[46]-world.Z[45]));
    float lambda = temp / ((world.X[47]*(world.X[45]-world.X[7]))
                           +(world.Y[47]*(world.Y[45]-world.Y[7]))
                           +(world.Z[47]*(world.Z[45]-world.Z[7])));
    float lambda_2 = temp / ((world.X[47]*(world.X[45]-world.X[6]))
                           +(world.Y[47]*(world.Y[45]-world.Y[6]))
                           +(world.Z[47]*(world.Z[45]-world.Z[6])));
    
    //-----------ray equation to find intersection pts------------* 
    world.X[48] = world.X[45] + lambda*(world.X[45] - world.X[7]); // Intersection pt p7
    world.Y[48] = world.Y[45] + lambda*(world.Y[45] - world.Y[7]); // Intersection pt p7
    world.Z[48] = 0.0;
    
    world.X[49] = world.X[45] + lambda_2*(world.X[45] - world.X[6]);  //intersection pt p6
    world.Y[49] = world.Y[45] + lambda_2*(world.Y[45] - world.Y[6]);  //intersection pt p6
    world.Z[49] = 0.0;
    
    //-------------diffuse reflection-----------* 
    pt_diffuse  diffuse;   //diffuse.r[3] 

    //-------reflectivity coefficient-----------*  
    #define 	Kdr 	0.8
    #define 	Kdg 	0.0
    #define 	Kdb 	0.0
 
    // define additional pts to find diffuse reflection 
    //world.X[49] = world.X[45] + lambda_2*(world.X[45] - world.X[6]); 

    //--------compute distance------------------*
    float distance[UpperBD]; 
    for (int i=48; i<=49; i++) {
    distance[i] = sqrt(pow((world.X[i]-world.X[45]),2)+         //intersect pt p7 
                        pow((world.Y[i]-world.Y[45]),2)+
                        pow((world.X[i]-world.X[45]),2) );
    //std::cout << "distance[i]  " << distance[i] << std::endl;
    }  
  
    for (int i=4; i<=5; i++){
    distance[i] = sqrt(pow((world.X[i]-world.X[45]),2)+         //pt p4 of projection plane 
                        pow((world.Y[i]-world.Y[45]),2)+
                        pow((world.X[i]-world.X[45]),2) ); 
    //std::cout << "distance[i]  " << distance[i] << std::endl;
    }
 

    //--------compute angle---------------------*
    float angle[UpperBD], tmp_dotProd[UpperBD], tmp_mag_dotProd[UpperBD];  

    for (int i=48; i<=49; i++){ 
/*
    tmp_dotProd[i] =  (world.X[i]-world.X[45])*world.X[47]+   //...[47] for normal vector 
                 (world.Y[i]-world.Y[45])*world.Y[47]+        //...[45] for pt light source 
                 (world.Z[i]-world.Z[45])*world.Z[47]; 

*/ 
    tmp_dotProd[i] = world.Z[i]-world.Z[45];  
    std::cout << " tmp_dotProd[i]  " <<  tmp_dotProd[i] << std::endl;

    tmp_mag_dotProd[i] = sqrt(pow((world.X[i]-world.X[45]),2)+         //[45] pt light source  
                        pow((world.Y[i]-world.Y[45]),2)+
                        pow((world.Z[i]-world.Z[45]),2) );
    std::cout << " tmp_mag_dotProd[i]  1 " <<  tmp_mag_dotProd[i] << std::endl;

    angle[i] = tmp_dotProd[i]/ tmp_mag_dotProd[i];  
    std::cout << "angle[i]  " << angle[i] << std::endl;

    //compute color intensity 
    diffuse.r[i] = Kdr *  angle[i] /  pow(distance[i],2) ;
    diffuse.g[i] = Kdg *  angle[i] /  pow(distance[i],2) ;
    diffuse.b[i] = Kdb *  angle[i] /  pow(distance[i],2) ;
    } 

   for (int i=4; i<=5; i++){ 
 
    tmp_dotProd[i] = world.Z[i]-world.X[45];  
    std::cout << " tmp_dotProd[i]  " <<  tmp_dotProd[i] << std::endl;

    tmp_mag_dotProd[i] = sqrt(pow((world.X[i]-world.X[45]),2)+         //[45] pt light source  
                        pow((world.Y[i]-world.Y[45]),2)+
                        pow((world.Z[i]-world.Z[45]),2) );
    std::cout << " tmp_mag_dotProd[i]  1 " <<  tmp_mag_dotProd[i] << std::endl;

    angle[i] = tmp_dotProd[i]/ tmp_mag_dotProd[i];  
    std::cout << "angle[i]  " << angle[i] << std::endl;

    //compute color intensity 
    diffuse.r[i] = Kdr *  angle[i] /  pow(distance[i],2) ;
    diffuse.g[i] = Kdg *  angle[i] /  pow(distance[i],2) ;
    diffuse.b[i] = Kdb *  angle[i] /  pow(distance[i],2) ;
 
    //std::cout << "diffuse.r[i]  " << diffuse.r[i] << std::endl;
    //std::cout << "diffuse.g[i]  " << diffuse.g[i] << std::endl;
    } 

    //-----set initialization, e.g., scaling perspective projection to display it------* 
    float xMin = 1000.0, xMax = -1000.0;
    float yMin = 1000.0, yMax = -1000.0;

    //*-------------Transformation pipeline-----------------* 
    for(int i = 0; i <= UpperBD; i++)
    {   
        //*-------world to viewer----------------* 
        viewer.X[i] = -sPheta * world.X[i] + cPheta * world.Y[i];
        viewer.Y[i] = -cPheta * cPhi * world.X[i]
        - cPhi * sPheta * world.Y[i]
        + sPhi * world.Z[i];
        viewer.Z[i] = -sPhi * cPheta * world.X[i]
        - sPhi * cPheta * world.Y[i]
        -cPheta * world.Z[i] + Rho;

        //*-------perspective projection--------------------* 
        perspective.X[i] = D_focal * viewer.X[i] / viewer.Z[i] ;
        perspective.Y[i] = D_focal * viewer.Y[i] / viewer.Z[i] ;
        if (perspective.X[i] > xMax) xMax = perspective.X[i];
        if (perspective.X[i] < xMin) xMin = perspective.X[i];
        if (perspective.Y[i] > yMax) yMax = perspective.Y[i];
        if (perspective.Y[i] < yMin) yMin = perspective.Y[i];
        /*
         std::cout << "xMin " << xMin << std::endl;
         std::cout << "xMax " << xMax << std::endl;
         std::cout << "yMin " << yMin << std::endl;
         std::cout << "yMax " << yMax << std::endl;
         */
    }

    for(int i = 0; i <= UpperBD; i++)
    {
        if ((xMax-xMin) != 0) perspective.X[i] = perspective.X[i]/(xMax-xMin);
        if ((yMax-yMin) != 0) perspective.Y[i] = perspective.Y[i]/(yMax-yMin);
        //std::cout << i << perspective.X[i] << perspective.Y[i] << std::endl;
    }
    

    //----------Now start ploting---------*
    glBegin(GL_LINES); 
    
    //----------world coordinate----------*
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
    
    //---------projection plane-----------* 
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
    
    //-----letter projection on the screen-------* 
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

    //--------arrow-top-----------------* 

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
  
  
    //---------arrow base------------------* 
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
  
    //-----------------shade------------------* 

    glBegin(GL_LINES);
    glVertex2f(perspective.X[48],perspective.Y[48]); // Pi
    glVertex2f(perspective.X[49],perspective.Y[49]); // Pi+1
    
    glVertex2f(perspective.X[48],perspective.Y[48]); // Pi to 4
    glVertex2f(perspective.X[4],perspective.Y[4]);

    glVertex2f(perspective.X[49],perspective.Y[49]); // Pi+1 to 5
    glVertex2f(perspective.X[5],perspective.Y[5]);
    glEnd();


    //---------plot diffuse reflection-----------* 

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 

    #define 	display_scaling		150000.0
    #define 	display_shifting	0.45

    float r, g, b; 
    for (int i=48; i<=49; i++) {
    r = display_scaling*diffuse.r[i]+display_shifting; 
    //r = display_scaling*diffuse.r[i];
    g = diffuse.g[i]; b = diffuse.b[i] ; 
    glColor3f(r, g, b); 
    std::cout << "display_scaling*diffuse.r[i]  " << r << std::endl;
    glBegin(GL_POLYGON);
    glVertex2f(perspective.X[i],perspective.Y[i]);
    glVertex2f(perspective.X[i]+0.1,perspective.Y[i]);
    glVertex2f(perspective.X[i]+0.1,perspective.Y[i]+0.1);
    glVertex2f(perspective.X[i],perspective.Y[i]+0.1);
    glEnd();
    }

    for (int i=4; i<=5; i++) {
    r = display_scaling*diffuse.r[i]+display_shifting; 
    g = diffuse.g[i]; b = diffuse.b[i] ; 
    glColor3f(r, g, b); 
    std::cout << "display_scaling*diffuse.r[i]  " << r << std::endl;
    glBegin(GL_POLYGON);
    glVertex2f(perspective.X[i],perspective.Y[i]);
    glVertex2f(perspective.X[i]+0.1,perspective.Y[i]);
    glVertex2f(perspective.X[i]+0.1,perspective.Y[i]+0.1);
    glVertex2f(perspective.X[i],perspective.Y[i]+0.1);
    glEnd();
    }

    //--------interpolation demo--------------* 
    // find a middle point on the line between pt indexed 4 and 5 
    // which are the points of the projection plane on x-y plane
    float mid_x = (perspective.X[4] + perspective.X[5])/2.0; 
    float mid_y = (perspective.Y[4] + perspective.Y[5])/2.0; 

    float rDiff_Point[10], gDiff_Point[10], bDiff_Point[10];
    float left_rDiff_Pt[10], left_gDiff_Pt[10], left_bDiff_Pt[10];
    float right_rDiff_Pt[10], right_gDiff_Pt[10], right_bDiff_Pt[10];

    for (int i=4; i<=5; i++) {
    rDiff_Point[i] = display_scaling*diffuse.r[i]+display_shifting; 
    gDiff_Point[i] = diffuse.g[i]; bDiff_Point[i] = diffuse.b[i] ; 
    } 

    left_rDiff_Pt[5] = rDiff_Point[5]; 
    //left_gDiff_Pt[5] = gDiff_Point[5]; 
    //left_bDiff_Pt[5] = gDiff_Point[5];
 
    right_rDiff_Pt[4] = rDiff_Point[4]; 
    //right_gDiff_Pt[4] = gDiff_Point[4]; 
    //right_bDiff_Pt[4] = gDiff_Point[4];

    float newx_rDiff_Pt, newx_gDiff_Pt, newx_bDiff_Pt; //for interpolation
    float newy_rDiff_Pt, newy_gDiff_Pt, newy_bDiff_Pt; //for interpolation
    float new_rDiff_Pt,  new_gDiff_Pt,  new_bDiff_Pt;  //for interpolation

    // y - y1 = (y2-y1)/(x2-x1) (x-x1)
    // for x direction 
    // independent variable is .X and function y is diffuse reflection intensity 
    newx_rDiff_Pt = rDiff_Point[4] + 
                    (rDiff_Point[5] - rDiff_Point[4])/(perspective.X[5]-perspective.X[4])*
                    (mid_x - perspective.X[4]);  
    newx_gDiff_Pt = 0.0; newx_bDiff_Pt = 0.0;   

    // for y direction 
    // independent variable is .Y and function y is diffuse reflection intensity 
    newy_rDiff_Pt = rDiff_Point[4] + 
                    (rDiff_Point[5] - rDiff_Point[4])/(perspective.Y[5]-perspective.Y[4])*
                    (mid_y - perspective.Y[4]);  
    newy_gDiff_Pt = 0.0; newy_bDiff_Pt = 0.0;  

    // combination of both 
    new_rDiff_Pt = (newx_rDiff_Pt +  newy_rDiff_Pt)/2.0; 
    new_gDiff_Pt = 0.0; new_bDiff_Pt = 0.0; 

    glColor3f(new_rDiff_Pt, new_gDiff_Pt, new_bDiff_Pt); 
    std::cout << "interpolation diffuse reflection  " << new_rDiff_Pt << std::endl;
    glBegin(GL_POLYGON);
    glVertex2f(mid_x,mid_y);
    glVertex2f(mid_x+0.1,mid_y);
    glVertex2f(mid_x+0.1,mid_y+0.1);
    glVertex2f(mid_x,mid_y+0.1);
    glEnd();

    glFlush(); 
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutCreateWindow("diffuse reflection demo");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
}

