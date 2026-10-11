#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
int i;
for( i=0; i<10000; i++){

int fd=open("/dev/binder", O_RDWR);
if(fd>=0)
close(fd);

}
printf("Completed 10000 Binder Opens\n");
return 0;

}


