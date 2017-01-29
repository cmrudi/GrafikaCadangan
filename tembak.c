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
    int key = 0;
    int shootActive = 0;
    int shootIdx[2];
    for (int i = 0; i <1266; i++) {
		printBackground();
		printRectangle(75,100,i,668);
		
		key = getchar();
		if (key > 0) {
			shootIdx[0] = i;
			shootIdx[1] = 578;
			shoot(i,578);
			shootActive = 1;
			key = 0;
		}
		if (shootActive == 1) {
			shootIdx[1]--;
			shoot(shootIdx[0],shootIdx[1]);
		}
		
	}
    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}
