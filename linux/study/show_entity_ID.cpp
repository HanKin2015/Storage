#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>
#include <assert.h>
#include <linux/videodev2.h>
#include <linux/fb.h>
#include <sys/ioctl.h> 
#include <linux/media.h>
#include <unistd.h>

int enum_media_device_entities(int iFd)
{
    int iRet;
    struct media_entity_desc desc;

    desc.id = 0 | MEDIA_ENT_ID_FLAG_NEXT;
    while (1) {
        iRet = ioctl(iFd, MEDIA_IOC_ENUM_ENTITIES, &desc);
        if (iRet < 0) {
            printf("enum media entities end\n");
            break;
        }
        printf("entity name[%s]\n", desc.name);
        desc.id |= MEDIA_ENT_ID_FLAG_NEXT;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int iErr = 0, ivFd;

    ivFd = open("/dev/media0", O_RDWR);
    iErr = enum_media_device_entities(ivFd);

    close(ivFd);
open_err:
    return iErr;
}