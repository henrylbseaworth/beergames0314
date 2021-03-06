#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "common.h"

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

    if(read(fd, buf, st.st_size) < st.st_size) {
        close(fd);
        fprintf(stderr, "Error reading from file\n");
        return 1;
    }

    lseek(fd, 0, SEEK_SET);

    const char *ptr = buf, *end = (buf + st.st_size) - keylen;
    const char *ptr2, *kptr, *kend = key + keylen;
    int count = 0;
    int out_offset = 0;

    const size_t outbuf_size = st.st_blksize;
    char *outbuf = (char*)malloc(outbuf_size + 256);
    for(;ptr < end; ptr ++) {
        for(kptr = key, ptr2 = ptr;kptr < kend && ptr2 < end; kptr ++, ptr2++) {
            if(*kptr != *ptr2) {
                break;
            }
        }

        if(kptr == kend) {
            count ++;
            for(kptr = key;kptr < kend; kptr ++)
            {
                *(outbuf + out_offset) = *kptr;
                out_offset++;
            }
            *(outbuf + out_offset) = '(';
            out_offset++;
            WRITE_DIGITS(count, outbuf, out_offset);
            *(outbuf + out_offset) = ')';
            out_offset++;
            ptr += keylen - 1;
        } else {
            *(outbuf + out_offset) = *ptr;
            out_offset ++;
        }

        if(out_offset >= outbuf_size) {
            if(write(fd, outbuf, out_offset) != out_offset) {
                fprintf(stderr, "Write error");
                close(fd);
                return 1;
            }
            out_offset = 0;
        }
    }
    if(out_offset > 0) {
        if(write(fd, outbuf, out_offset) != out_offset) {
            fprintf(stderr, "Write error");
            close(fd);
            return 1;
        }
    }

    printf("Count: %d\n", count);

    close(fd);

    free(buf);
    free(outbuf);

    return 0;
}
