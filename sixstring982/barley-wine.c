#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  MATCH,
  NO_MATCH,
  NO_MATCH_EOF
}StartResult;

int fpeek(FILE* strm)
{
  int c;
  c = fgetc(strm);
  ungetc(c, strm);

  return c;
}

StartResult strmstart(const char* key, FILE* stream, FILE* out)
{
  int c;
  while(*key)
  {
    fputc(c = fgetc(stream), out);
    if(*(key++) != c)
    {
      return c == EOF ? NO_MATCH_EOF : NO_MATCH;
    }
  }
  return MATCH;
}

void strmrep(const char* filename, const char* key)
{
  FILE* input = fopen(filename, "r");

  /* Let's write out immediately, then rename when we're done. */
  FILE* output = fopen("output.txt", "w");

  StartResult result;
  unsigned int matches = 0;

  while((result = strmstart(key, input, output)) == MATCH || result == NO_MATCH)
  {
    if(result == MATCH)
    {
      fprintf(output, "(%d)", ++matches);
    }

    if(fpeek(input) == EOF)
    {
      break;
    }
  }

  fclose(input);
  fclose(output);

  rename("output.txt", filename);
}

int main(int argc, const char** argv)
{
  strmrep(argv[1], argv[2]);
  return 0;
}
