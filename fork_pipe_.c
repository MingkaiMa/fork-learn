#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){

    int n;
    int fd[2];
    pid_t pid;

    char line[80];

    if(pipe(fd) < 0){

        perror("pipe");
        exit(1);

    }

    if((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }

    if(pid > 0){

    //parent

        printf("pid is %d\n", pid);
        printf("I am parent %d, I am reading\n", getpid());
        close(fd[1]);
        n = read(fd[0], line, 80);
        printf("*****************\n");
        write(STDOUT_FILENO, line, n);
        printf("*****************\n");

    }

    else{

    //child

        printf("pid is %d\n", pid);
        printf("I am child %d, I am writing\n", getpid());
        close(fd[0]);
        write(fd[1], "helloworld\n", 12);

        for(;;);
        //wait(NULL);
    }


    printf("$$$$$$$$ending %d\n", getpid());

    return 0;

}