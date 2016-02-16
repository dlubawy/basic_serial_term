#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{ 
    FILE *file;
    char buff[255];

    file = fopen("/dev/ttyS2", "r+w");
    fwrite(argv, sizeof(argv[0]), sizeof(argv)/sizeof(argv[0]), file);
    sleep(1);
    fread(buff, sizeof(buff[0]), sizeof(buff)/sizeof(buff[0]), file);
    printf("%c", buff);
    return 0;
}
