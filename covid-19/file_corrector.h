#include<stdio.h>
#include<stdlib.h>

#ifndef COVID_EXTRACTOR_H_INCLUDED
#define COVID_EXTRACTOR_H_INCLUDED

#define MAX_FILENAME_LENGTH 30
#define MAX_LEN 1024
#define MAX_NUMBER_LENGTH 8

typedef int (*open_files)();
typedef int (*read_write_file)();
typedef int (*close_files)();

typedef struct
{
    open_files open_covid_files;
    read_write_file read_write_covid_files;
    close_files close_covid_files;
} file_corrector_st;

int _open_files(FILE **fd1, FILE **fd2, char *filename1, char *filename2, char *mode1, char *mode2);
int _read_write_file(FILE **fd1, FILE **fd2);
int _close_files(FILE **fd1, FILE **fd2);
int* _split(char *string, int SIZE, char delim);
int _no_of_words(char *string, int SIZE, char delim);

file_corrector_st table;

#endif