#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM "/my_semaphore"

int main() {
    sem_t *sem;
    sem = sem_open(SEM, O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    printf("Semafor je uspesno kreiran");

    getchar();

    sem_close(sem);

    return 0;
}