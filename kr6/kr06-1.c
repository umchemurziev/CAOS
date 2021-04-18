// #define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <endian.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR);
    uint16_t cur;
    int32_t mx_vl = -1;

    // off_t size = lseek(fd, 0, SEEK_END);
    // int flag = 0;
    // if (size == 0) { 
    // 	close(fd);
    // 	exit(0);

    // }
    // lseek(fd, 0, SEEK_END);
    while (read(fd, &cur, 2) >= 1) {
    	// read(fd, &cur, 2);
    	cur = be16toh(cur);
    	// if (cur % 2 == 1) {
    		// flag = 1;
    	// }
        if (cur % 3 == 0 && cur > mx_vl) {
        	mx_vl = cur;
        }
    }
    if (mx_vl != -1) {
    	printf("%d\n", mx_vl);
    }
    close(fd);
    return 0;
}
