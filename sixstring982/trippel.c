#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;

typedef struct
{
  char* array;
  u32 length;
}CharArray;

/**
 * Gets the size of a file from its FILE descriptor.
 *
 * @param fp The FILE* describing the file to check.
 *
 * @returns The size of the file pointed to by \c fp .
 */
u32 fileSize(FILE* fp)
{
  u32 size = 0;

  fseek(fp, 0L, SEEK_END);
  size = ftell(fp);

  fseek(fp, 0L, SEEK_SET);

  return size;
}

CharArray* readToEnd(const char* filename)
{
  FILE* fp = fopen(filename, "r");
  u32 filesize = fileSize(fp);
  CharArray* array = malloc(sizeof(CharArray));

  array->array = malloc(filesize);

  fread((void*)array->array, filesize, 1, fp);

  array->length = filesize;

  fclose(fp);

  return array;
}

void freeCharArray(CharArray* arr)
{
  free(arr->array);
  free(arr);
}

void writeCharArray(CharArray* arr, const char* filename)
{
  FILE* fp = fopen(filename, "w");

  fwrite((void*)arr->array, arr->length, 1, fp);

  fclose(fp);
}

void doSubstitution(const char* filename, const char* key)
{
  CharArray* arr = readToEnd(filename);

  writeCharArray(arr, filename);

  freeCharArray(arr);
}

int main(int argc, const char** argv)
{
  doSubstitution(argv[1], argv[2]);
  return 0;
}
