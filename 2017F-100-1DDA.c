/*****************************************************
 * Program: 1DDA.c   Coded by: Harry Li              *
 * Version: x1.0;    status: tested;                 *
 * Compile and build:                                *
 * gcc -lGL -lGLU -lglut line.c -o main.o            *
 * Date: Jun 16, 2014                                * 
 * Purpose: Compute DDA line & graphics visulization *
 *          of DDA line.                             *  
 ****************************************************＊　

location: 
/home/harry/Desktop/SJSU/EE264/EE264Ubuntu/OpenGL/CT/lec1DDA/


*/ 
#include<GL/glut.h>
#include<stdio.h>

#define ARRAY_LEN 1024 //define array length 
#define GRIDARRAY_LEN 512 //define grid square 512X512  

typedef struct 
{
int x_start;
int y_start;
int x_end;
int y_end;
int i_accumulator;  
int x[ARRAY_LEN];
int y[ARRAY_LEN];
} MY_STRUCT;  

void getDDAline( MY_STRUCT * ); //define subroutine prototype 

// 
void mydisplay()
{

MY_STRUCT  my_struct;  
my_struct.i_accumulator = 0; //initializtion
 
//------------------------------------------------// 
//---Draw outter grid squre for visualization-----//  
//   where the DDA line can be drawn              //
//   note the grid square will be drawn on this   //
//   coordinate system with this size.            //  
//                                                //  
/*-------------------------------------------------
   define virtex for the outter big square
   (p4x,p4y) ---------- (p1x,p1y)
  (0.0f,1.0f)          (1.0f,1.0f) 
       |                    | 
       |                    |  
       |                    |  
   (p3x,p3y) ----------  (p2x,p2y)
  (0.0f,0.0f)           (1.0f,0.0f)  
-------------------------------------------------- 
*/
   
float p1x=1.0f,p1y=1.0f;  // naming convention: point-number-x-or-y  
float p2x=1.0f,p2y=0.0f;
float p3x=0.0f,p3y=0.0f; 
float p4x=0.0f,p4y=1.0f;  

float grid, float_r;      
int i; 
int r;
int ix_max, iy_max;  

/*define the x-y axis 

             (px4x,px4y)     
             (0.5f,1.0f)  
                  |
                  |
                  | 
   (px1x,px1y) -------- (px2x,px2y)
   (0.0f,0.5f)    |     (1.0f,0.5f)
                  |
                  |   
             (px3x,px3y) 
             (0.5f,0.0f)   
*/
 
float px1x=0.0f,px1y=0.5f, px2x=1.0f, px2y=0.5f; //naming convention:
                                                 // point+x+number+x-or-y   
float px3x=0.5f,px3y=0.0f, px4x=0.5f, px4y=1.0f;   

//--------- in main(module) to get DDA Line -----------------//

   printf("Please Enter x_start:\n");
   scanf("%d", &my_struct.x_start);
   printf("Please Enter y_start :\n");
   scanf("%d", &my_struct.y_start);
   printf(" \n");  
   printf("x_start = %4d y_start =%4d \n",
               my_struct.x_start,
               my_struct.y_start);
   printf(" \n");  
   printf("-------------------------------------- \n");  

   printf("Please Enter x_end :\n");
   scanf("%d", &my_struct.x_end);
   printf("Please Enter y_end :\n");
   scanf("%d", &my_struct.y_end);
   printf(" \n");  
   printf("x_end = %4d y_end = %4d \n",
               my_struct.x_end,
               my_struct.y_end);
   printf("-------------------------------------- \n");  
   printf(" \n");  

   my_struct.x[my_struct.i_accumulator] = my_struct.x_start ; //initializtion
   my_struct.y[my_struct.i_accumulator] = my_struct.y_start ; //initializtion

/*
   printf("main 110: i_accumulator = %4d \n",my_struct.i_accumulator );  
   printf("main 110: x[i_accumulator] = %4d \n",my_struct.x[my_struct.i_accumulator] );  
   printf("main 110: y[i_accumulator] = %4d \n",my_struct.y[my_struct.i_accumulator] );  
*/ 


   getDDAline( &my_struct );

   printf("main 114: i_accumulator = %4d \n",my_struct.i_accumulator );  



//------------ graphics --------------------------- 
glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity();
glTranslatef(-0.5f,-0.5f,0.0f);
glFlush();
sleep(1);

//-------draw outter big square----------------------// 
/* define virtex for the outter big square
   (p4x,p4y) ---------- (p1x,p1y)
       |                    |
       |                    |
       |                    |
   printf(" \n");  
   (p3x,p3y) ----------  (p2x,p2y)
*/

glBegin(GL_LINES);
glVertex2f(p1x,p1y);  
glVertex2f(p2x,p2y);
glVertex2f(p2x,p2y);
glVertex2f(p3x,p3y);
glVertex2f(p3x,p3y);
glVertex2f(p4x,p4y);
glVertex2f(p4x,p4y);
glVertex2f(p1x,p1y);
glEnd();

//-------draw x-y axis----------------------//  
glBegin(GL_LINES);
glVertex2f(px1x,px1y); 
glVertex2f(px2x,px2y);
glVertex2f(px3x,px3y);
glVertex2f(px4x,px4y);
glEnd();

//-----------------------grids size--------------------------//  
/*   
   Note: 
   (1) both x and y can be positive or 
       negative; 
   (2) the size of the grid square is 
       512X512, therefore it stretches from 
       -255 to +255; 
   (3) to find grid squre size, we will have 
       to define the proper size of the number 
       grid per row and per column, e.g., 
       find max[abs(x_start), abs(x_end),  
                abs(y_start), abs(y_end0] ... (eqn 1) 
       x_max = y_max = (eqn 1) 
   (4) the grid size then is 
       (0,0) = x_max = y_max   
   (5) hence the grid square is 
       (-x_max,y_max)-------------|----------------(x_max,y_max)
              |                   |                      | 
              |                   |                      | 
              |-----------------(0,0)--------------------|
              |                   |                      |
              |                   |                      |
       (-x_mx,-y_max)-------------|----------------(x_max,-y_mx)  
 
*/ 

if (abs(my_struct.x_end) - abs(my_struct.x_start) >= 0) {
       ix_max = my_struct.x_end; 
} 
else if (abs(my_struct.x_end) - abs(my_struct.x_start) < 0) {
       ix_max = my_struct.x_start; 
} 
 
if (abs(my_struct.y_end) - abs(my_struct.y_start) >= 0) {
       iy_max = my_struct.y_end; 
} 
else if (abs(my_struct.y_end) - abs(my_struct.y_start) < 0) {
       iy_max = my_struct.y_start; 
} 

if (abs(ix_max) - abs(iy_max) >= 0) {
       grid = 2*abs(ix_max)+1;  
       grid = 1/grid;  
//       r = abs(ix_max) + 1;      //define r, so the previous program for
       r = abs(ix_max) ;      //define r, so the previous program for
//   printf("main 206: r = %4d \n", r );  
//   printf("main 206: grid = %4f \n", grid );  
} 
else if (abs(ix_max) - abs(iy_max) < 0) {
       //grid = 1/(2*abs(iy_max)+1); this will result in 0.0 due to integer
       //                            conversion first, before assigning to 
       //                            the float.  
       grid = 2*abs(iy_max)+1;  
       grid = 1/grid;  
       //r = abs(iy_max) + 1;      //define r, so the previous program for
       r = abs(iy_max) ;      //define r, so the previous program for
                                       //Bresenham circle can be reused.  
   printf("main 213: r = %4d \n", r );  
   printf("main 213: grid = %4f \n", grid );  
} //end else if  


   printf("main 221: r = %4d \n", r );  
   printf("main 221: grid = %4f \n", grid );  


//-------compute grid pts--------------------// 
/* This figure defines the big square where all 
   the grids are drawn, Fig 1.   

             (px4x,px4y)     
             (0.5f,1.0f)  
                  |
                  |
                  | 
   (px1x,px1y) -------- (px2x,px2y)
   (0.0f,0.5f)    |     (1.0f,0.5f)
                  |
                  |   
             (px3x,px3y) 
             (0.5f,0.0f)   

    So the following coordinate defines 
    where each individual dot can be 
    drawn on this coordinate, Fig 2.  

    (0.0f,1.0f)-----------(1.0f,1.0f)
         |          |          |
         |          |          |
         |-----(0.5f,0.5f)-----|
         |          |          |
         |          |          |
    (0.0f,0.0f)-----------(1.0f,0.0f)
         
*/
//--------------------------------------------

glBegin(GL_LINES);

/*
-----------------grids-------------------  
 draw parallel lines along x and y axis
-----------------------------------------
*/
 
for (i=0; i <= r; i++) {
glVertex2f(px1x,px1y+i*grid);  //x direction, upper half   
glVertex2f(px2x,px2y+i*grid);

glVertex2f(px1x,px1y-i*grid);  //x direction, lower half   
glVertex2f(px2x,px2y-i*grid);

glVertex2f(px3x+i*grid,px3y);  //y direction, right half   
glVertex2f(px4x+i*grid,px4y);

glVertex2f(px3x-i*grid,px3y);  //y direction, left half   
glVertex2f(px4x-i*grid,px4y);

//getchar(); 
} //end for  

glEnd();

//-------draw dots----------------//
/* 
    From Fig 1 and 2 (see below) 

Fig 1.

             (px4x,px4y)    
             (0.5f,1.0f) 
                  |
                  |
                  |
   (px1x,px1y) -------- (px2x,px2y)
   (0.0f,0.5f)    |     (1.0f,0.5f)
                  |
                  |  
             (px3x,px3y)
             (0.5f,0.0f)  

Fig 2. 

    (0.0f,1.0f)-----------(1.0f,1.0f)
         |          |          |
         |          |          |
         |-----(0.5f,0.5f)-----|
         |          |          |
         |          |          |
    (0.0f,0.0f)-----------(1.0f,0.0f)

    we have Fig 3 as follows 

    (0.0f,1.0f)-----------(1.0f,1.0f)
      (-r,r)        |        (r,r)
    (px1x,px4y)     |     (px2x,px4y) 
         |          |          |
         |-----(0.5f,0.5f)-----|
      ((px1x+px2x)/2,(px3y+px4y)/2))            
         |          |          |
    (0.0f,0.0f)     |     (1.0f,0.0f)
      (-r,-r)-------|--------(r,-r)
    (px1x,px3y)           (px2x,px3y)   

*/ 

for(i = 0; i <= my_struct.i_accumulator; i++) {
glBegin(GL_POLYGON);
glVertex2f((px1x+px2x)/2+my_struct.x[i]*grid, 
           (px3y+px4y)/2+my_struct.y[i]*grid); // the grid lower left corner 
glVertex2f((px1x+px2x)/2+my_struct.x[i]*grid, 
           (px3y+px4y)/2+my_struct.y[i]*grid+grid); // up 1 grid
glVertex2f((px1x+px2x)/2+my_struct.x[i]*grid+grid, 
           (px3y+px4y)/2+my_struct.y[i]*grid+grid); // right 1 grid    
glVertex2f((px1x+px2x)/2+my_struct.x[i]*grid+grid, 
           (px3y+px4y)/2+my_struct.y[i]*grid); // down 1 grid
//printf("(1): grid i = %4d | x = %4d y = %4d\n",i, my_struct.x[i], my_struct.y[i]);
printf("main 314: x = %4d y = %4d\n",i, my_struct.x[i], my_struct.y[i]);
glEnd();
} //end for  

glFlush();
//usleep(50);

} //end module  

//------------------main--------------------------// 
int main(int argc, char** argv)
{
glutInit(&argc,argv);
glutCreateWindow("testing pattern: square");
glutDisplayFunc(mydisplay);
glutMainLoop();
} //main  
 
//---------------------------------------------------//
//             DDA subroutine                        //
//---------------------------------------------------//
// Find DDA line in x[] and y[]                      //  
//---------------------------------------------------//
//      starting pt (x_start, y_start) as integer    //
//      ending pt   (x_end, y_end)  as integer       //
//      i_accumulator as integer, gives the total    //
//                 number of points of the DDA line. // 
//---------------------------------------------------//  

void getDDAline( MY_STRUCT *xx )   
{
#include <math.h>
#include <stdio.h>

int   i; 
float fslop1; 
float fx_buf[ARRAY_LEN];    // intermediate data 
float fy_buf[ARRAY_LEN];    // intermediate data 

/*
printf("Sub 0, 348: i_accumulator = %4d \n",xx->i_accumulator );  
printf("Sub 0, 348: x_start = %4d y_start = %4d\n",xx->x_start, xx->y_start);  
printf("Sub 0, 348: x_end = %4d y_end = %4d\n",xx->x_end, xx->y_end);  
printf("Sub 0, 348: x = %4d y = %4d\n",xx->x[xx->i_accumulator], xx->y[xx->i_accumulator]);  
*/

//-------compute slop----------------------//

if ((xx->x_end - xx->x_start) == 0) {
  printf( "same starting and ending x, try different x value \n");
  exit; 
}

//--------------------------------------------
// for DDA line, if slop1 <= 1; 
// y_(k+1) = y_k + slop1;                   
// x_(k+1) = x_k; 
//-------------------------------------------- 

fslop1 = (xx->y_end - xx->y_start);  
fslop1 = fslop1 / (xx->x_end - xx->x_start);  

fx_buf[xx->i_accumulator] = xx->x_start;  // convert to floating point  
fy_buf[xx->i_accumulator] = xx->y_start;  // convert to floating point  

while ( (xx->x[xx->i_accumulator] != xx->x_end) &&   
        (xx->y[xx->i_accumulator] != xx->y_end) ) {  

printf("Sub 0, 374: x = %4d y = %4d\n",xx->x[xx->i_accumulator], xx->y[xx->i_accumulator]);  

if (abs(fslop1) <= 1) {  //absolute value of the slop1 is less than 1 
xx->x[xx->i_accumulator+1] = xx->x[xx->i_accumulator] + 1; 
fy_buf[xx->i_accumulator+1] = fy_buf[xx->i_accumulator] + fslop1; 
xx->y[xx->i_accumulator+1] = fy_buf[xx->i_accumulator+1];  // convert back to integer   
printf("Sub 1: x = %4d y = %4d\n",xx->x[xx->i_accumulator+1], xx->y[xx->i_accumulator+1]);  
} //end if 

//---------------------------------------
// for slop1 > 1  
// from y = slop1 * x + b 
// we have 
// x = 1/slop1 * y - b/slop1 
// so rewrite x as y
// y = slop2 * x - slop2 * b 
// where
// slop2 = 1/slop1   
//--------------------------------------- 

else if ((fslop1 * fslop1) > 1) {
fslop1 = 1/fslop1;  
xx->y[xx->i_accumulator+1] = xx->y[xx->i_accumulator] + 1; 
fx_buf[xx->i_accumulator+1] = fx_buf[xx->i_accumulator] + fslop1; 
xx->x[xx->i_accumulator+1] = fx_buf[xx->i_accumulator+1];  
printf("Sub 2: x = %4d y = %4d\n",xx->x[xx->i_accumulator+1], xx->y[xx->i_accumulator+1]);  
} //end else if  

xx->i_accumulator++;
} //end while loop 

} //end getDDAline(.)  

