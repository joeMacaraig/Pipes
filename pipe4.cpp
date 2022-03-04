//pipe4.cpp  (data producer)

/*
g++ -o pipe4 pipe4.cpp
g++ -o pipe5 pipe5.cpp
./pipe4 write anything youd like
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])//like pipe1a
{
    int data_processed;
    int file_pipes[2];
    char user[BUFSIZ + 1]; //./pipe4 type anything you want
    char buffer[BUFSIZ + 1];
    pid_t fork_result;

    strcpy(user, argv[1]);

    memset(buffer, '\0', sizeof(buffer));

    for(int i = 2; i < argc; i++){
      strcat(user, " ");
      strcat(user, argv[i]);
    }

    if (pipe(file_pipes) == 0) {   //creates pipe
        fork_result = fork();
        if (fork_result == (pid_t)-1) {  //fork fails
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (fork_result == 0) {    //child
            sprintf(buffer, "%d", file_pipes[0]);
            (void)execl("pipe5", "pipe5", buffer, (char *)0);
            exit(EXIT_FAILURE);
        }
        else {                     //parent
            data_processed = write(file_pipes[1], user,
                                   strlen(user));
            printf("%d - wrote %d bytes\n", getpid(), data_processed);
        }
    }
    exit(EXIT_SUCCESS);
}
