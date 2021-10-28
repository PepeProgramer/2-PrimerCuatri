#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd, fd2, cont = 1;
    char * pathname = argv[1], filePointer = 0;
    char buf[80] = {}, bloque[8] = "bloque ";
    if(fd = open("salida.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR) < 0){
        printf("\nError %d en open", errno);
        perror("\nError en open");
        exit(-1);
    }

    if(fd2 = open(pathname, S_IRUSR) < 0){
        printf("\nError %d en segundo open", errno);
        perror("\nError en segundo open");
        exit(-1);
    }
    printf("buena tarde");
    while(read(fd2, buf, 80) < 0){
        bloque[7] = cont;
        printf("piuuuu");
        if (write(fd, bloque, 8) != 8)
    {
        perror("\nError en primer write");
        exit(-1);
    }

    if (lseek(fd, 40, SEEK_CUR) < 0)
    {
        perror("\nError en lseek");
        exit(-1);
    }

      if (write(fd, buf, 80) != 80)
    {
        perror("\nError en primer write gordo");
        exit(-1);
    }

    if (lseek(fd, 40, SEEK_CUR) < 0)
    {
        perror("\nError en lseek");
        exit(-1);
    }



    

    close(fd);
    close(fd2);
    return 0;
    }
    






}