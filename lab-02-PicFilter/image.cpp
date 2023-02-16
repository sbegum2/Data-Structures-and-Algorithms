
/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "image.h"
#include "ppmio.h"

#include <iostream>
using namespace std;

int pixelToIndex(int width, int x, int y) {
   int index = (3 * y * width) + (3 * x);  
   return index;

}



void noRed(int width, int height, int* ppm) {
  for (int i=0; i<height; i++) {
      for (int j=0; j<width; j++) {
          ppm[pixelToIndex(width,j,i)] = 0;
      }
  }
}



void noGreen(int width, int height, int* ppm) {
  for (int i=0; i<height; i++) {
      for (int j=0; j<width; j++) {
          ppm[pixelToIndex(width,j,i)+1] = 0;
      }
    }
}



void noBlue(int width, int height, int* ppm) {
  for (int i=0; i<height; i++) {
      for (int j=0; j<width; j++) {
          ppm[pixelToIndex(width,j,i)+2] = 0;
      }
    }
}

 
void invert(int width, int height, int* ppm) {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
          int x = pixelToIndex(width,j,i);
          ppm[x] = (255 - ppm[x]); 

          int y = pixelToIndex(width,j,i)+1;
          ppm[y] = (255 - ppm[y]);

          int z = pixelToIndex(width,j,i)+2;
          ppm[z] = (255 - ppm[z]);
      }
    }
}



void grayscale(int width, int height, int* ppm) {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
          int x = pixelToIndex(width,j,i);

          int y = pixelToIndex(width,j,i)+1;

          int z = pixelToIndex(width,j,i)+2;

          int avg = (ppm[x] + ppm[y] + ppm[z]) / 3;
          ppm[x] = avg;
          ppm[y] = avg;
          ppm[z] = avg;
      }
    }
}



void flipHorizontally(int width, int height, int* ppm) {
    for (int i=0; i< height; i++) {
        for (int j=0; j<(width/2); j++) {
          // D
          int temp = pixelToIndex(width,width-j-1,i);
          
          int temp_1 = pixelToIndex(width,width-j-1,i)+1;
          
          int temp_2 = pixelToIndex(width,width-j-1,i)+2;

          // A
          int temp_3 = pixelToIndex(width,j,i);
          
          int temp_4 = pixelToIndex(width,j,i)+1;
          
          int temp_5 = pixelToIndex(width,j,i)+2;

          int temp_a = ppm[temp_3];

          int temp_b = ppm[temp_4];

          int temp_c = ppm[temp_5];

          ppm[temp_3] = ppm[temp];
          ppm[temp_4] = ppm[temp_1];
          ppm[temp_5] = ppm[temp_2];
          
          ppm[temp] = temp_a;
          ppm[temp_1] = temp_b;
          ppm[temp_2] = temp_c;

          }    
        }
    }


void flipVertically(int width, int height, int* ppm) {
    for (int i=0; i< width; i++) {
        for (int j=0; j<(height/2); j++) {
          // D
          int temp = pixelToIndex(width,i,height-j-1);
          
          int temp_1 = pixelToIndex(width,i,height-j-1)+1;
          
          int temp_2 = pixelToIndex(width,i,height-j-1)+2;

          // A
          int temp_3 = pixelToIndex(width,i,j);
          
          int temp_4 = pixelToIndex(width,i,j)+1;
          
          int temp_5 = pixelToIndex(width,i,j)+2;

          int temp_a = ppm[temp_3];

          int temp_b = ppm[temp_4];

          int temp_c = ppm[temp_5];

          ppm[temp_3] = ppm[temp];
          ppm[temp_4] = ppm[temp_1];
          ppm[temp_5] = ppm[temp_2];
          
          ppm[temp] = temp_a;
          ppm[temp_1] = temp_b;
          ppm[temp_2] = temp_c;

          }    
      }
    }