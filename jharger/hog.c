#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <key>\n", argv[0]);
        return 1;
    }
    int fd = open(argv[1], O_RDWR);
    if(fd < 0) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        return 1;
    }
    const char *key = argv[2];
    size_t keylen = strlen(key);

    struct stat st;
    fstat(fd, &st);

    char *buf = (char*)malloc(st.st_size + 1);

    read(fd, buf, st.st_size);

    lseek(fd, 0, SEEK_SET);

    char *ptr = buf, *end = (buf + st.st_size) - keylen;
    for(;ptr < end; ptr ++) {
        if(!bcmp(ptr, key, keylen)) {
            *ptr = '\0';
            ptr += keylen - 1;
        }
    }

    const size_t outbuf_size = 131072;
    char *outbuf = (char*)malloc(outbuf_size + 256);

    ptr = buf;
    int count = 0;
    int out_offset = 0;
    for(;ptr < end; ptr ++) {
        if(*ptr == '\0') {
            count ++;
            out_offset += snprintf(outbuf + out_offset, 256, "%s(%d)", key, count);
            ptr += keylen - 1;
        } else {
            *(outbuf + out_offset) = *ptr;
            out_offset ++;
        }

        if(out_offset >= outbuf_size) {
            write(fd, outbuf, out_offset);
            out_offset = 0;
        }
    }
    if(out_offset > 0) {
        write(fd, outbuf, out_offset);
    }

    printf("Count: %d\n", count);

    close(fd);

    free(buf);
    free(outbuf);

    return 0;
}
