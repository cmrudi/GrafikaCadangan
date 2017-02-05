#include "Base.c"
#include <termios.h>
#include <stdio.h>
#include <curses.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct termios stdin_orig;  // Structure to save parameters
int startXBomb = 0;
int endXBomb = 0;
int meetBomb = 0;

void term_reset() {
        tcsetattr(STDIN_FILENO,TCSANOW,&stdin_orig);
        tcsetattr(STDIN_FILENO,TCSAFLUSH,&stdin_orig);
}

void term_nonblocking() {
        struct termios newt;
        tcgetattr(STDIN_FILENO, &stdin_orig);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // non-blocking
        newt = stdin_orig;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        atexit(term_reset);
}

void *plane(void *vargp) {
	
	int initX = (int)vargp;
	int initY = 0;
	initX = 0;
	startXBomb = initX;
	endXBomb = initX + 148;
	int location = 0;
	int width = 1366;
	int height = 150;

	char* A;
	A = (char*)malloc(sizeof(char)*width*height);
	while (initX < 1301) {
		if (initX == 1300) {
			initX = 0;
		}
		if (meetBomb == 1) {
			initX = 0;
			pthread_exit(NULL);
		}
		initX++;
		startXBomb = initX;
		endXBomb = initX + 148;
		int i = 0;
		for (i = 0; i < width*height; i++) {
		  A[i] = 0;
		}
		
		//Pesawat
		int x1 = 2 +initX;
		int y1 = 83;
		int x2 = 148 +initX;
		int y2 = 83;
		int x3 = 117 +initX;
		int y3 = 57;
		int x4 = 37 +initX;
		int y4 = 57;
		int x5 = 8 +initX;
		int y5 = 28;
		int x9 = 2 + initX;
		int y9 = 28;
		
		//Sayap
		int x6 = 77 +initX;
		int y6 = 76;
		int x7 = 105 +initX;
		int y7 = 76;
		int x8 = 93 +initX;
		int y8 = 116;
		
		plotLine(width, A, x1, y1, x2, y2);
		plotLine(width, A, x2, y2, x3, y3);
		plotLine(width, A, x3, y3, x4, y4);
		plotLine(width, A, x4, y4, x5, y5);
		plotLine(width, A, x5, y5, x9, y9);
		plotLine(width, A, x9, y9, x1, y1);
		
		plotLine(width, A, x6, y6, x7, y7);
		plotLine(width, A, x7, y7, x8, y8);
		plotLine(width, A, x8, y8, x6, y6);
		
		
			for (int y = height-1; y >= 0; y--) {
			  for (int x = width-1; x >= 0; x--) {
				  
				 if (A[y*width+x] != 0) {
					location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
							   (y+vinfo.yoffset) * finfo.line_length;
					
					if (vinfo.bits_per_pixel == 32) {
						*(fbp + location) = 100;        // Some blue
						*(fbp + location + 1) = 15+(x-100)/2;     // A little green
						*(fbp + location + 2) = 200-(y-100)/5;    // A lot of red
						*(fbp + location + 3) = 0;      // No transparency
				//location += 4;
					} else  { //assume 16bpp
						int b = 10;
						int g = (x-100)/6;     // A little green
						int r = 31-(y-100)/16;    // A lot of red
						unsigned short int t = r<<11 | g << 5 | b;
						*((unsigned short int*)(fbp + location)) = t;
					}
				 }
				 else {
					 location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
							   (y+vinfo.yoffset) * finfo.line_length;
					  if (vinfo.bits_per_pixel == 32) {
						*(fbp + location) = 0;        // Some blue
						*(fbp + location + 1) = 0;     // A little green
						*(fbp + location + 2) = 0;    // A lot of red
						*(fbp + location + 3) = 0;      // No transparency
				//location += 4;
					} else  { //assume 16bpp
						int b = 10;
						int g = (x-100)/6;     // A little green
						int r = 31-(y-100)/16;    // A lot of red
						unsigned short int t = r<<11 | g << 5 | b;
						*((unsigned short int*)(fbp + location)) = t;
					}
				 }
			  }
			}
		}
	
}

void *explodeThread (void *vargp) {
	int initX = (int)vargp;
	int initY = 0;
	pthread_t tid;
	int location = 0;
	int width = 1366;
	int height = 400;

	char* A;
	A = (char*)malloc(sizeof(char)*width*height);

	int i = 0;
	for (i = 0; i < width*height; i++) {
	  A[i] = 0;
	}

	int x1 = 289 + initX;
	int x2 = 368 + initX;
	int x3 = 321 + initX;
	int x4 = 491 + initX;
	int x5 = 327 + initX;
	int x6 = 502 + initX;
	int x7 = 323 + initX;
	int x8 = 269 + initX;
	int x9 = 212 + initX;
	int x10 = 189 + initX;
	int x11 = 28 + initX;
	int x12 = 157 + initX;
	int x13 = 166 + initX;

	int y1 = 179;
	int y2 = 341;
	int y3 = 128;
	int y4 = 276;
	int y5 = 79;
	int y6 = 103;
	int y7 = 6;
	int y8 = 93;
	int y9 = 4;
	int y10 = 108;
	int y11 = 51;
	int y12 = 158;
	int y13 = 322;

	plotLine(width, A, x1, y1, x2, y2);
	plotLine(width, A, x2, y2, x3, y3);
	plotLine(width, A, x3, y3, x4, y4);
	plotLine(width, A, x4, y4, x5, y5);
	plotLine(width, A, x5, y5, x6, y6);
	plotLine(width, A, x6, y6, x7, y7);
	plotLine(width, A, x7, y7, x8, y8);
	plotLine(width, A, x8, y8, x9, y9);
	plotLine(width, A, x9, y9, x10, y10);
	plotLine(width, A, x10, y10, x11, y11);
	plotLine(width, A, x11, y11, x12, y12);
	plotLine(width, A, x12, y12, x13, y13);
	plotLine(width, A, x13, y13, x1, y1);

	for (int y = height-1; y >= 0; y--) {
	  for (int x = width-1; x >= 0; x--) {
		  
		 if (A[y*width+x] != 0) {
			location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;
            
            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = 100;        // Some blue
                *(fbp + location + 1) = 15+(x-100)/2;     // A little green
                *(fbp + location + 2) = 200-(y-100)/5;    // A lot of red
                *(fbp + location + 3) = 0;      // No transparency
        //location += 4;
            } else  { //assume 16bpp
                int b = 10;
                int g = (x-100)/6;     // A little green
                int r = 31-(y-100)/16;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }
		 }
	  }
	}
	sleep(1);
	printBackground();
	pthread_create(&tid, NULL, plane, (void *)0);
	
	pthread_exit(NULL);
	
}



void *shootThread(void *vargp)
{
	pthread_t tid;
    int initX = (int)vargp;
    int initY = 678;
    while (initY > 0) {
		usleep(1000);
		shoot(initX,initY);
		initY--;
		
		if ((initY == 83)&&(initX > startXBomb)&&(initX < endXBomb)) {
			meetBomb = 1;
			usleep(500);
			pthread_create(&tid, NULL, explodeThread, (void *)initX);
			usleep(500);
			printBackground();
		}
	}
	pthread_exit(NULL);
}




int main(int argc, char **argv) {
	
	term_nonblocking();
	
    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    displayWidth = vinfo.xres;
    displayHeight = vinfo.yres;

    // Figure out the SIZE of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                        fbfd, 0);
    if (atoi(fbp) == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");
    
    
    //Tembak akan dijadikan thread yang berbada
	int key;
	int i = 0;
	int increase = 1;
	pthread_t tid;
	printBackground();
	
	pthread_create(&tid, NULL, plane, (void *)i);
	
    while (key != 10) {
		key = 0;
		printRectangle(75,100,i,668);
		usleep(2000);
		
		key = getchar();
		if ((key > 0)&&(key !=10)) {
			pthread_create(&tid, NULL, shootThread, (void *)i);
		}
		if (increase == 1) {
			i++;
			if (i == vinfo.xres) {
				increase = 0;
			}
		}
		else {
			i--;
			if (i == 0) {
				increase = 1;
			}
		}
	}
    munmap(fbp, screensize);
    pthread_join(tid, NULL);
    close(fbfd);
    return 0;
}
