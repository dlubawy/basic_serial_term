//////////////////////////////////////////////////////////
// Serial Communication for Arduino
// Reference - https://www.cmrr.umn.edu/~strupp/serial.html
//////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */

int main(void) {
    int fd;

    fd = open("/dev/ttyS2", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == 1) {
        perror("open_port: Unable to open /dev/ttyS2 - ");
    }
    else
        fcntl(fd, F_SETFL, 0);

    struct termios options;

    tcgetattr(fd, &options);

    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag |= (CLOCAL | CREAD);

    tcsetattr(fd, TCSANOW, &options);
    
    char buf[256];
    char b = 0;

    int i = 0;
    do {
        int n = read(fd, &b, 1);
        buf[i] = b; i++;
    } while(b != '\n');
    
    printf("Buffer: ");
    int k;
    for (k = 0; k < strlen(buf); k++) {
       printf("%c", buf[k]);
    }

    return(fd);
}
