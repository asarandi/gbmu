#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <errno.h>

sem_t *sem;
static const char *sem_name = "sfml_sync";

int sync_open() {
    sem = sem_open(sem_name, O_CREAT, 0777, 0);
    if (sem == SEM_FAILED)
        perror(__func__);
    return sem != SEM_FAILED;
}

int sync_close() {
    int res = sem_unlink(sem_name);
    if (res != 0)
        perror(__func__);
    return res == 0;
}

int sync_signal() {
    int res = sem_post(sem);
    if (sem == SEM_FAILED)
        perror(__func__);
    return res == 0;
}

int sync_wait() {
    int res = sem_wait(sem);
    if (sem == SEM_FAILED)
        perror(__func__);
    return res == 0;
}
