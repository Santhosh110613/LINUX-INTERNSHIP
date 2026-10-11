#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/android/binder.h>

int main()
{
    int fd = open("/dev/binder", O_RDWR);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct binder_version ver;

    if (ioctl(fd, BINDER_VERSION, &ver) == -1) {
        perror("ioctl");
        close(fd);
        return 1;
    }

    printf("Binder Protocol Version = %d\n",
           ver.protocol_version);

    close(fd);
    return 0;
}
