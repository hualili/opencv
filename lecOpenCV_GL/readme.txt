readme 
HL
March 2016

Line command 
gcc -ggdb `pkg-config --cflags opencv` -o `basename test.c .c` test.c `pkg-config --libs opencv` -lGL -lGLU -lglut -lm 

1. Compile and build 
   sudo cmake . 
   or 
   sudo cmake -DWITH_OPENGL=ON ..  

   then 
   sudo make 

 
