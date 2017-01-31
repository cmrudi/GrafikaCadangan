#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define SWAP(x, y, T) do { T temp##x##y = x; x = y; y = temp##x##y; } while (0)

void plot (int widthofA, char* A, int x, int y, char flipAboutX, int y0, char flipAboutY, int x0, char swapXY) {
   if (flipAboutY) {
      x = 2*x0 - x;
   }
   if (flipAboutX) {
      y = 2*y0 - y;
   }
   if (swapXY) {
      SWAP(x, y, int);
   }
   A[y*widthofA+x] = 1;
}
   
void plotLine(int widthofA, char* A, int x0, int y0, int x1, int y1) {
   int dx=x1-x0;
   int dy=y1-y0;

   char flipAboutX = 0;
   char flipAboutY = 0;
   char swapXY = 0;

   if (abs(dy) > abs(dx)) {
      swapXY = 1;
      SWAP(dx, dy, int);
      SWAP(x1, y1, int);
      SWAP(x0, y0, int);
   }

   if (dy < 0) {
      flipAboutX = 1;
      y1 = 2*y0 - y1;
      dy = -dy;
   }

   if (dx < 0) {
      flipAboutY = 1;
      x1 = 2*x0 - x1;
      dx = -dx;
   }


   int D = 2*dy - dx;
   plot(widthofA, A, x0, y0, flipAboutX, y0, flipAboutY, x0, swapXY);
   int y=y0;

   int x;

   for (x = x0+1; x < x1+1; x++) {
      if (D > 0) {
         y = y+1;
         plot(widthofA, A, x, y, flipAboutX, y0, flipAboutY, x0, swapXY);
         D = D + (2*dy-2*dx);
      }
      else {
         plot(widthofA, A, x, y, flipAboutX, y0, flipAboutY, x0, swapXY);
         D = D + (2*dy);
      }
   }
}/*
int main(int argc, char** argv) {

   int width = 200;
   int height = 200;

   char* A;
   A = (char*)malloc(sizeof(char)*width*height);
   
   int i = 0;
   for (i = 0; i < width*height; i++) {
      A[i] = 0;
   }

   int ax = 11;
   int bx = 5;
   int cx = 30;

   int ay = 27;
   int by = 2;
   int cy = 23;

   plotLine(width, A, ax, ay, bx, by);
   plotLine(width, A, ax, ay, cx, cy);
   plotLine(width, A, bx, by, cx, cy);

   int y;
   int x;
   for (y = height-1; y >= 0; y--) {
      for (x = width-1; x >= 0; x--) {
         if (A[y*width+x] == 0) {
            printf("  ");
         }
         else {
            printf("X ");
         }
      }
      printf("\n");
   }
}

*/
