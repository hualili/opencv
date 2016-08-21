readme on DisplayImage

1. Create DisplayImage.cpp 

2. Create CMakeLists.txt 

    1 cmake_minimum_required(VERSION 2.8)
    2 project( DisplayImage )
    3 find_package( OpenCV REQUIRED )
    4 include_directories( ${OpenCV_INCLUDE_DIRS} )
    5 add_executable( DisplayImage DisplayImage.cpp )
    6 target_link_libraries( DisplayImage ${OpenCV_LIBS} ) 

3. Generate executable by two steps process 
    sudo cmake . 
    sudo make 

   Note: "." period follows cmake 

   then execute program by 
   ./DisplayImage lena.jpg 

4. With OpenGL 
  cmake -DWITH_OPENGL=ON .  

5. AR OpenCV and OpenGL 
  A tutorial on using OpenCV's camera position estimation functions to create Augmented 
  Reality effects. http://www.morethantechnical.com/2010/11/10/20-lines-ar-in-opencv-wcode/ 
  
  code download 
  http://morethantechnical.googlecode.com/svn/trunk/OpenCVAR/ 
 
