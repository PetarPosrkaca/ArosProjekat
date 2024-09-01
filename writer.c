#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <sys/stat.h>

#define PIPE "/tmp/my_named_pipe"
#define SEM_WRITER "/my_semaphore"

int main() {
    int deskriptor;
    sem_t *sem;
    //char message[100];
    deskriptor = open(PIPE, O_WRONLY);
    if (deskriptor == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    } 

    sem = sem_open(SEM_WRITER, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    //printf("Unesi poruku: ");
    //fgets(message, 100, stdin);

    sem_wait(sem);
    const char *message = "Pozdrav";
    ssize_t bytes_written = write(deskriptor, message, strlen(message)+1);
    if ( bytes_written == -1)  {
        perror("write");
        exit(EXIT_FAILURE);
    }

    printf("Poruka napisana:%s\n",message);

    sem_post(sem);

    close(deskriptor);
    sem_close(sem);

    return 0;
}