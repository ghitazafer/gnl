#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

void f(){system("leaks a.out");}

// int main(void)
// {
//     int fd1;
//     char *line;

//     fd1 = open("test1.txt", O_RDONLY);
//     line = get_next_line(fd1);
//     printf("%s", line);
//     free(line);
//     while ((line = get_next_line(fd1)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     } 
//     close(fd1);
//     atexit(f);
//     return 0;
// }

#include "get_next_line_bonus.h"

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    int fd3 = open("file3.txt", O_RDONLY);
    char *line;

    line = get_next_line(fd1);
    printf("File1: %s", line);
    free(line);

    line = get_next_line(fd2);
    printf("File2: %s", line);
    free(line);

    line = get_next_line(fd3);
    printf("File3: %s", line);
    free(line);

    line = get_next_line(fd1);
    printf("File1: %s", line);
    free(line);

    line = get_next_line(fd2);
    printf("File2: %s", line);
    free(line);

    line = get_next_line(fd3);
    printf("File3: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    close(fd3);

    atexit(f);
    return 0;
}