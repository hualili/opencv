/*****************************************************
 * Program: 1DDA.c   Coded by: Harry Li              *
 * Version: x1.0;    status: tested;                 *
 * Compile and build:                                *
 * gcc -Wall 1DDA.c -o main.o                        *
 * //gcc -lGL -lGLU -lglut line.c -o main.o          *
 * Date: Jun 16, 2014                                * 
 * Purpose: Compute DDA line & graphics visulization *
 *          of DDA line.                             *  
 *****************************************************/ 
//#include<GL/glut.h>
#include<stdio.h>
#include <stdlib.h>

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
float slop; 
} MY_STRUCT;  

void getDDAline( MY_STRUCT * ); //define subroutine prototype 
  FILE *wr;
// 
void mydisplay()
{
MY_STRUCT  my_struct;  
my_struct.i_accumulator = 0; //initializtion
     
int i; 
//int r;
//int ix_max, iy_max;  

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
   getDDAline( &my_struct );  
int l;
char x='x', y='y';
fprintf(wr, "%c, %c\n", x, y);
for (l = 0; l <= my_struct.i_accumulator; l++)
{
  if (abs(my_struct.slop) > 1) {
  fprintf(wr, "%d, %d\n", my_struct.y[l], my_struct.x[l]);
  } 
  else 
  fprintf(wr, "%d, %d\n", my_struct.x[l], my_struct.y[l]);
}
//fclose(wr);
} //end module  

//------------------main--------------------------// 
int main(int argc, char** argv)
{
     wr = fopen("write_dda.csv", "w");
  if (wr < 0)
    {
        perror("unable to write to file");
        return 1;
    } 
mydisplay();
fclose(wr);
} //main  
 
//------------- DDA subroutine --------------//
void getDDAline( MY_STRUCT *xx )   
{
#include <math.h>
#include <stdio.h>

int   i; 
float fslop1, fslop2; 
float fx_buf[ARRAY_LEN];    // intermediate data 
float fy_buf[ARRAY_LEN];    // intermediate data 
//-------compute slop----------------------//
if ((xx->x_end - xx->x_start) == 0) {
  printf( "same starting and ending x, try different x value \n");
  exit; 
}

//--------------------------------------------
// for slop1 <= 1;  
//-------------------------------------------- 
fslop1 = (xx->y_end - xx->y_start);  
fslop1 = fslop1 / (xx->x_end - xx->x_start);   
xx->slop = fslop1; 

// for swapping the (x,y) coordinates if x_start>x_end
if((abs(fslop1) <= 1 && (xx->x_start > xx->x_end)) || 
   (abs(fslop1) > 1 && (xx->y_start > xx->y_end)))
  {
  int temp, temp1;
  temp = xx->x_start;
  xx->x_start = xx->x_end;
  xx->x_end = temp;
  temp1 = xx->y_start;
  xx->y_start = xx->y_end;
  xx->y_end = temp1;
  }

xx->x[xx->i_accumulator] = xx->x_start;
xx->y[xx->i_accumulator] = xx->y_start; 
fx_buf[xx->i_accumulator] = xx->x_start;  // convert to floating point  
fy_buf[xx->i_accumulator] = xx->y_start;  // convert to floating point   

if (abs(fslop1) > 1) fslop2 = 1/fslop1;

while ( (xx->x[xx->i_accumulator] != xx->x_end) &&   
        (xx->y[xx->i_accumulator] != xx->y_end) ) 
    {    
    if (abs(fslop1) <= 1) 
      {  //absolute value of the slop1 is less than 1 
      xx->x[xx->i_accumulator+1] = xx->x[xx->i_accumulator] + 1; 
      fy_buf[xx->i_accumulator+1] = fy_buf[xx->i_accumulator] + fslop1; 
      xx->y[xx->i_accumulator+1] = fy_buf[xx->i_accumulator+1];  // convert back to integer    
      } //end if 
      // for slop1 > 1   
      else if ((fslop1 * fslop1) > 1) 
      {
      xx->y[xx->i_accumulator+1] = xx->y[xx->i_accumulator] + 1; 
      fx_buf[xx->i_accumulator+1] = fx_buf[xx->i_accumulator] + fslop2; 
       xx->x[xx->i_accumulator+1] = fx_buf[xx->i_accumulator+1];   
      } //end else if  
    xx->i_accumulator++;
} //end while loop 
} //end getDDAline(.)  

