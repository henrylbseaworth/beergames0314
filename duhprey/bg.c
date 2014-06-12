#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/time.h>

#define BS_MUL 1

#ifdef CAPTURE_TIMING
  struct timeval start, end;

  #define START_TIMER \
  { \
    gettimeofday (&start, 0); \
  } 

  #define END_TIMER(str) \
  { \
      gettimeofday (&end, 0); \
      end.tv_sec -= start.tv_sec; \
      end.tv_usec -= start.tv_usec; \
      if (end.tv_usec < 0) { \
        end.tv_sec --; \
        end.tv_usec += 1000000; \
      } \
      printf ("%s %u.%06lu\n", str, (unsigned)end.tv_sec, (unsigned long)end.tv_usec); \
  }

  struct timeval w_start, w_end;
  unsigned total_sec = 0;
  unsigned long total_usec = 0;

  #define CHECK_WRITE \
  { \
    if (out_p >= out_end) { \
      gettimeofday (&w_start, 0); \
      if (occur_str[1] != '1' || occur_str[2] != ')') \
        write (fd, out_buffer, st.st_blksize * BS_MUL); \
      gettimeofday (&w_end, 0); \
      w_end.tv_sec -= w_start.tv_sec; \
      w_end.tv_usec -= w_start.tv_usec; \
      if (w_end.tv_usec < 0) { \
        w_end.tv_sec --; \
        w_end.tv_usec += 1000000; \
      } \
      total_sec += w_end.tv_sec; \
      total_usec += w_end.tv_usec; \
      if (total_usec > 1000000) {  \
        total_sec ++; \
        total_usec -= 1000000; \
      } \
      out_p = out_buffer; \
    } \
  } 

  #define PRINT_W_TIMES printf ("Total write time %u.%06lu\n", total_sec, total_usec);
#else
  #define START_TIMER {}
  #define END_TIMER(str) {}

  #define CHECK_WRITE \
  { \
    if (out_p >= out_end) { \
      if (occur_str[1] != '1' || occur_str[2] != ')') \
        write (fd, out_buffer, st.st_blksize * BS_MUL); \
      out_p = out_buffer; \
    } \
  } 

  #define PRINT_W_TIMES {}
#endif

#define UPDATE_OCCUR \
{ \
  occur_p = occur_end - 2; \
  while (*occur_p == '9') { \
    *occur_p = '0'; \
    occur_p --; \
  } \
  if (*occur_p == '(') { \
    occur_p = occur_end; \
    *occur_p -- = ')'; \
    *occur_p -- = '0'; \
    occur_end ++; \
    occur_p = occur_str + 1; \
  } \
  *occur_p = *occur_p + 1; \
  occur_p = occur_str; \
}



int main (int argc, char **argv) {
  struct stat st;
  char *in_buffer, *in_end;
  char *out_buffer, *out_end;
  char *key_p, *in_p, *out_p;
  int fd;
  char occur_str[128];
  char *occur_p, *occur_end;
  char *occur_diff;

  if (argc != 3) {
    fprintf (stderr, "Format: %s textfile key\n", argv[0]);
    return 1;
  }

  key_p = argv[2];
  if (*key_p == '\0') {
    return 0;
  }

  if (stat (argv[1], &st) != 0) {
    fprintf (stderr, "Unable to stat file %s\n", argv[1]);
    return 1;
  }

  memset (occur_str, 0, 128);

  in_buffer = (char *) malloc (st.st_size);
  out_buffer = (char *) malloc (st.st_blksize * BS_MUL);

  in_end = in_buffer + st.st_size;
  out_end = out_buffer + st.st_blksize * BS_MUL;

  START_TIMER;

  if ((fd = open (argv[1], O_RDWR)) < 0) {
    fprintf (stderr, "Unable to open file %s for reading\n", argv[1]);
    return 1;
  }

  if (read (fd, in_buffer, st.st_size) != st.st_size) {
    fprintf (stderr, "Unable to read file %s\n", argv[1]);
    return 1;
  }

  END_TIMER ("Time to read in file");

  lseek(fd, 0, SEEK_SET); 

  in_p = in_buffer;
  out_p = out_buffer;

  occur_str[0] = '('; occur_str[1] = '1'; occur_str[2] = ')'; occur_str[3] = '\0';
  occur_p = occur_str;
  occur_end = occur_str + 3;

  START_TIMER;
  while (in_p < in_end) {
    *out_p ++ = *in_p;
    if (*in_p == *key_p) {
      key_p ++;
      if (*key_p == '\0') {
        occur_diff = occur_p + (out_end - out_p);
        if (occur_diff < occur_end) {
            while (occur_p < occur_diff) {
              *out_p ++ = *occur_p ++;
            }
            CHECK_WRITE;
        }
        while (*occur_p != '\0') {
          *out_p ++ = *occur_p ++;
        }
        UPDATE_OCCUR;
        key_p = argv[2];
      }
    } else {
      key_p = argv[2];
      if (*in_p == *key_p) {
        key_p ++;
      }
    }
    CHECK_WRITE;
    in_p ++;
  }

  if (out_p > out_buffer) {
    write (fd, out_buffer, out_p - out_buffer);
  }

  close (fd);
  END_TIMER ("Time to write in file"); 

  PRINT_W_TIMES

  free (in_buffer);
  free (out_buffer);

  return 0;
}

