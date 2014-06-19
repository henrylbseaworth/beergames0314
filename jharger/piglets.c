#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "common.h"

#define NUM_THREADS 4

typedef struct {
    char *buf;
    const char *buf_end;
    const char *key;
    const char *key_end;
    int keylen;
} find_key_params_t;

void *find_key(void* data)
{
    find_key_params_t *params = (find_key_params_t*)data;

    const char *end = params->buf_end;
    const char *kptr, *ptr2, *kend = params->key_end;
    int keylen = params->keylen;
    
    for(char *ptr=params->buf;ptr < end; ptr ++) {
        for(kptr = params->key, ptr2 = ptr;kptr < kend && ptr2 < end; kptr ++, ptr2++) {
            if(*kptr != *ptr2) {
                break;
            }
        }
        if(kptr == kend) {
            *ptr = '\0';
            ptr += keylen - 1;
        }
    }

    return NULL;
}

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

    char *ptr;
    const char *end = (buf + st.st_size) - keylen;
    const char *ptr2, *kptr, *kend = key + keylen;
    int count = 0;
    int out_offset = 0;

    pthread_t threads[NUM_THREADS];
    find_key_params_t params[NUM_THREADS];

    int inc = st.st_size / NUM_THREADS;
    for(int i = 0; i < NUM_THREADS; i ++) {
        char *start = buf + (i * inc);
        params[i].buf = start;
        params[i].buf_end = i == (NUM_THREADS-1) ? end : start + inc;
        params[i].key = key;
        params[i].key_end = kend;
        params[i].keylen = keylen;
        if(i > 0) {
            pthread_create(&threads[i], NULL, find_key, &params[i]);
        }
    }

    find_key(&params[0]);

    for(int i = 1; i < NUM_THREADS; i ++) {
        pthread_join(threads[i], NULL);
    }

    const size_t outbuf_size = st.st_blksize;
    char *outbuf = (char*)malloc(outbuf_size + 256);

    for(ptr = buf;ptr < end; ptr ++) {
        if(*ptr == '\0') {
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
