#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int c, start = 0, len = 0;
    while ((c = getopt(argc, argv, "s:l:")) != -1) {
        switch (c) {
        case 's':
            start = atoi(optarg);
            break;
        case 'l':
            len = atoi(optarg);
            break;
        }
    }
 
    if (optind != argc - 1) {
        printf("usage:%s [-s <start>] [-l <len>] <pathname>\n", argv[0]);
        return 1;
    }
    printf("start = %d, len = %d, file_name = %s\n", start, len, argv[optind]);
    return 0;
}
