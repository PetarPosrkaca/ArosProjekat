#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <sys/stat.h>

#define PIPE "/tmp/my_named_pipe"
#define SEM_READER "/my_semaphore"

int main() {
    int deskriptor;
    sem_t *sem;
    char message[100];

    deskriptor = open(PIPE, O_RDONLY);
    if (deskriptor == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    sem = sem_open(SEM_READER, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    sem_wait(sem);

    ssize_t bytes_read = read(deskriptor, message, sizeof(message) - 1);
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    message[bytes_read] = '\0';
    printf("Poruka: %s\n", message);
    sem_post(sem);

    close(deskriptor);
    sem_close(sem);

    return 0;
}