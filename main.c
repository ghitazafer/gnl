#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

void f(){system("leaks a.out");}

int main(void)
{
    int fd1;
    char *line;

    fd1 = open("test1.txt", O_RDONLY);
    line = get_next_line(fd1);
    printf("%s", line);
    free(line);
    // while ((line = get_next_line(fd1)) != NULL)
    // {
    //     printf("%s", line);
    //     free(line);
    // } 
    close(fd1);
    atexit(f);
    return 0;
}

