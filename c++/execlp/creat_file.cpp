#include <stdio.h>
#include "log.h"

bool ProcessCmdLine(int argc, char *argv[])
{
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (!ProcessCmdLine(argc, argv)) {
        printf("[main] parse cmd line failed");
        return -1;
    }

    FILE *fp = fopen("./log.txt", "a");
    fprintf(fp, "%s %s [%s: %d: %s]\n", __DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__);
    fclose(fp);
    LOG_INFO();
    return 0;
}
