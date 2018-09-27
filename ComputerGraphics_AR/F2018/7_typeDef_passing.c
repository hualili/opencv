/*-------------------------------------------------------*
 * Program: typeDef_passing.c                            * 
 * Coded by: HL;                                         *
 * Date: June 28, 2014;                                  *
 * Status: tested.                                       *
 * Note: this program just to test passing typedef-struct*  
 *       array by reference.                             *  
 * Compilation and build:                                *
 * gcc -Wall typeDef_passing.c -o main.o                 * 
 *-------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

#define ARRAY_LEN 20  //define array length  

typedef struct
{
int x[ARRAY_LEN];
int y[ARRAY_LEN];
int i_accumulator;  
} MY_STRUCT;  

void getArrayPts( MY_STRUCT * );  
 
int main()
{
MY_STRUCT my_struct; 
int index; 

   printf("Please Enter i_accumulator :\n");
   scanf("%d", &my_struct.i_accumulator);
   printf("i_accumulator = %4d \n", my_struct.i_accumulator);

   for(index = 0; index <= my_struct.i_accumulator; index++) {
      my_struct.x[index] = my_struct.y[index] = index; 
      printf( "Main x = %4d y = %4d \n", my_struct.x[index], 
               my_struct.y[index]);
   }

   getArrayPts( &my_struct ); 
   
   for(index = 0; index <= my_struct.i_accumulator; index++) {
      printf( "Main After x = %4d y = %4d \n", my_struct.x[index], 
               my_struct.y[index]);
   }     
}// main  

void getArrayPts( MY_STRUCT *xx )   
{
int i; 

printf( "sub: i_accumulator = %4d \n", xx->i_accumulator);
int tmp; 
for (i=0; i <= xx->i_accumulator; i++) {  
   printf( "sub: x = %4d y = %4d \n", xx->x[i], xx->y[i]);
   tmp = xx->x[i]; 
   xx->x[i] = xx->x[i] + xx->y[i]; 
   xx->y[i] = tmp * xx->y[i]; 
   }   
}  
