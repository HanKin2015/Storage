#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

// 给指定文件添加读锁
int file_read_lock(const char* file_path)
{
    assert(file_path);
    
    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        perror("open error");
        return -1;
    }
    
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    
    if (fcntl(fd, F_SETLK, &lock) == -1){
        perror("fcntl error");
        return -1;
    }
    sleep(5);
    close(fd);
    printf("%s done\n", __FUNCTION__);
    return 0;
}

int fd_w;
void handler(int sig)
{
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; 
    if(fcntl(fd_w, F_SETLKW, &lock) == -1){
        perror("fcntl error");
        exit(-1);
    }
    exit(0);
}

int file_write_lock(const char* file_path)
{
    assert(file_path);
    
    signal(SIGUSR1, handler);
 
    fd_w = open(file_path, O_WRONLY);
    if (fd_w == -1){
        perror("open error");
        return 1;
    }
    
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; 
    if (fcntl(fd_w, F_SETLKW, &lock) == -1) {
        perror("fcntl error");
        return 1;
    }
    
    close(fd_w);
    printf("%s done\n", __FUNCTION__);
    return 0;
}

// 查看文件当前锁的状态
int file_lock_status(const char* file_path)
{
    assert(file_path);
    
    int fd = open(file_path, O_RDWR);
    if (fd == -1) {
        perror("open error");
        return -1;
    }
    
    struct flock lock;
    bzero(&lock, sizeof(lock));
    if (fcntl(fd, F_GETLK, &lock) == -1) {
        perror("fcntl error");
        return -1;
    }
    
    const char* lock_type = NULL;
    switch (lock.l_type) {
        case F_RDLCK:
            lock_type = "F_RDLCK";
            break;
        case F_WRLCK:
            lock_type = "F_WRLCK";
            break;
        case F_UNLCK:
            lock_type = "F_UNLCK";
            break;
        default:
            break;
    }
    printf("file:%s, lock type:%s, start:%d, len:%d, by %d\n", file_path, lock_type, lock.l_start, lock.l_len, lock.l_pid);
    printf("%s done\n", __FUNCTION__);
    return 0;
}

int write_file()
{
    char content[] = "This test file lock programer11!";
    int fd = open("./tmp.txt", O_WRONLY|O_CREAT);
    printf("write sizeof = %d, strlen = %d\n", sizeof(content), strlen(content));
    write(fd, content, strlen(content));
    close(fd);
    printf("%s done\n", __FUNCTION__);
    return 0;
}
int read_file()
{
    char buffer[256];
    int fd = open("./tmp.txt", O_RDONLY);
    printf("befor read sizeof = %d, strlen = %d\n", sizeof(buffer), strlen(buffer));
    read(fd, buffer, sizeof(buffer));
    printf("after read sizeof = %d, strlen = %d\n", sizeof(buffer), strlen(buffer));
    close(fd);
    buffer[strlen(buffer)] = '\n';
    printf("%s", buffer);
    printf("%s done\n", __FUNCTION__);
    return 0;
}

void test()
{
    char  str1[] = "1234567890 123";
    const char* str2   = "1234567890 123";    // 这个必须加const(warning: deprecated conversion from string constant to ‘char*’)
    char str3[256];
    //char* str4 = NULL;    // Segmentation fault
    
    printf("str1 sizeof = %d, strlen = %d\n", sizeof(str1), strlen(str1));
    printf("str2 sizeof = %d, strlen = %d\n", sizeof(str2), strlen(str2));
    printf("str3 sizeof = %d, strlen = %d\n", sizeof(str3), strlen(str3));
    printf("str3 sizeof = %d, strlen = %d\n", sizeof str3, strlen(str3));
    //printf("str4 sizeof = %d, strlen = %d\n", sizeof(str4), strlen(str4));
    printf("%s done\n", __FUNCTION__);
    return;
}

int main(int argc, char* argv[])
{
    write_file();
    //read_file();
    //test();
    
    const char* file_path = "/home/vdi/hejian/lock/tmp.txt";
    
    pid_t pid = fork();
    assert(pid >= 0);
    
    if (pid > 0) {
        file_read_lock(file_path);
    } else {
        sleep(2);
        file_lock_status(file_path);
    }
    printf("pid = %d done\n", getpid());
    file_write_lock(file_path);
    file_lock_status(file_path);
    return 0;
}
