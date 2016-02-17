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

    // Open COM3 for read/write
    fd = open("/dev/ttyS2", O_RDWR | O_NOCTTY | O_NDELAY);
    //Error handling
    if (fd == 1) {
        perror("open_port: Unable to open /dev/ttyS2 - ");
    }
    else
        fcntl(fd, F_SETFL, 0);

    struct termios options;

    tcgetattr(fd, &options);
    
    // Set baudrate and serial options
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag |= (CLOCAL | CREAD);

    tcsetattr(fd, TCSANOW, &options);
    
    // Buffer for holding received data
    char buf[32];
    char b = 0;

    int i = 0;
    do {
        // Read the serial input
        int n = read(fd, &b, 1);
        buf[i] = b; i++;
        // Output to the serial device
        write(fd, "Hello World!\n", 13);
    } while(i < (sizeof(buf) - 1));
    // Make sure the buffer is NULL terminated
    buf[i] = '\0';
    
    // Print the stored buffer
    printf("Buffer: ");
    int k;
    for (k = 0; k < strlen(buf); k++) {
        printf("%c", buf[k]);
    }

    return(fd);
}
