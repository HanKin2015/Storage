#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/file.h>
#include <time.h>
#define FILE_LOCK_NAME "/home/single_instance.lock"
#define MAX_PID_LEN 20

enum {
    FLOCK_PROG_SUCCESS = 0,
    FLOCK_PROG_RUNING,
    FLOCK_ERROR
};

static int single_instance()
{
    int ret = FLOCK_PROG_SUCCESS;
    int flock_fd = -1;
    int flag = 0;
    char cur_pid[MAX_PID_LEN];
    int cur_pid_len = 0;

    flock_fd = open(FILE_LOCK_NAME, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (flock_fd == -1) {
         printf("Create flock file failed, flock file name : %s.\n", FILE_LOCK_NAME);
         ret = FLOCK_ERROR;
         goto END;
    }
    printf("flock_fd: %d\n", flock_fd);

    flag =  fcntl(flock_fd, F_GETFD);
    flag |= FD_CLOEXEC;
    (void)fcntl(flock_fd, F_SETFD, flag);
    printf("flock_fd: %d\n", flock_fd);

    if (flock(flock_fd, LOCK_EX | LOCK_NB) == -1) {
        if (errno == EACCES || errno == EAGAIN) {
            printf("usbipd is runing.\n");
            close(flock_fd);
            ret = FLOCK_PROG_RUNING;
            goto END;
        } else {
            ret = FLOCK_ERROR;
            close(flock_fd);
            printf("lock file : %s failed.\n", FILE_LOCK_NAME);
            goto END;
        }
    }

    (void)snprintf(cur_pid, sizeof(cur_pid), "%d", (int)getpid());
    printf("cur_pid: %s\n", cur_pid);
    cur_pid_len = strlen(cur_pid);
    ftruncate(flock_fd, 0);
    lseek(flock_fd, 0, SEEK_SET);

    if (cur_pid_len != write(flock_fd, cur_pid, cur_pid_len)) {
        printf("write usbipd pid(%s) to lockfile(%s) failed.\n", cur_pid, FILE_LOCK_NAME);
        close(flock_fd);
        ret = FLOCK_ERROR;
        goto END;
    }

    printf("success\n");
    fsync(flock_fd);
    close(flock_fd);

END:
    return ret;
}

int main()
{
    single_instance();
    sleep(1000);
    return 0;
}