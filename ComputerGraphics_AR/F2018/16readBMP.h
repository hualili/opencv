/* readBMP.h
*/
/* Image type - contains height, width, and data */
struct Image {
unsigned long sizeX;
unsigned long sizeY;
char *data;
};
typedef struct Image Image;
/* Function that reads in the image; first param is 
filename, second is image struct */
/* As side effect, sets w and h */
int ImageLoad(char* filename, Image* image);
