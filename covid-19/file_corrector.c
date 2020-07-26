#include "file_corrector.h"
#include<string.h>

int _no_of_words(char *string, int SIZE, char delim){
    int count_words = 0;
    char *start = string;
    while(SIZE >= 0)
    {
        if(*start == delim || *start == '\0' || *start == '.' || *start == '\n'){
            count_words++;
        }
        start++; SIZE--;    
    }
    return count_words;
}

int* _split(char *string, int SIZE, char delim){
    char *start = string, *end = string ;
    int size_of_word = 0;
    int count_words = _no_of_words(string, SIZE, delim);
    int *words = malloc(count_words * sizeof(int));
    memset(words, 0, count_words);
    if(words == NULL){
        fprintf(stderr, "Error creating array.\n");
        exit(1);
    }
    int index = 0;
    while(SIZE >= 0)
    {
        if(*start == delim || *start == '\0'  || *start == '\n'){
            //words[index] = malloc((size_of_word) * sizeof(char));
            //memset(words[index], 0, size_of_word);
            char number[MAX_NUMBER_LENGTH];
            strncpy(number, end, size_of_word);       //here null char will not be encountered 
                                                            //as size_of_word is less than *end. so the resulting string
                                                            //will not be null terminated.
            number[size_of_word] = '\0';
            //  char buff[size_of_word+1];
            // snprintf(buff, size_of_word+1, "%s", number);
            // fprintf(stdout, "%s ", buff);
            words[index++] = atoi(number);
            //fprintf(stdout, "%d ", words[index++]);
            end = start + 1; 
            size_of_word = 0;
        }
        else
        {
            size_of_word++;
        }
        start++; SIZE--;
    }
    return words;
}

int _open_files(FILE **fd1, FILE **fd2, char *filename1, char *filename2, char *mode1, char *mode2){
    if(((*fd1 = fopen(filename1, mode1)) == NULL) || ((*fd2 = fopen(filename2, mode2)) == NULL)){
        fprintf(stderr, "%s", "Error while opening the files. Couldn't open.\n");
        return 0;
    }
    fprintf(stdout, "%s", "Files opened successfully.\n");
    return 1;
    // *fd1 = fopen(filename1, "r");
    // *fd2 = fopen(filename2, "w");
    // if((*fd1 == NULL) || (*fd2 == NULL)){
    //     fprintf(stderr, "%s", "Error while opening the files. Couldn't open.\n");
    //     return 0;
    // }
    // fprintf(stdout, "%s", "Files opened successfully.\n");
    // return 1;
}

int _read_write_file(FILE **fd1, FILE **fd2){
    char data[MAX_LEN];
    fprintf(stdout, "%s", "Reading file.....\n");
    while(fgets(data, MAX_LEN, *fd1)){
        int no_of_numbers = _no_of_words(data, strlen(data), ',');
        fprintf(stdout, "Number of numbers are %d\n", no_of_numbers);
        int *numbers = _split(data, strlen(data), ',');
        for(int i=0; i<no_of_numbers; i++){
            fprintf(stdout, "%s", "Writing to new file.....\n");
            if(fprintf(*fd2, "%d\n", numbers[i]) < 0){
                fprintf(stderr, "%s", "Error writing data to new file.\n");
                return 0;
            }
            //fprintf(*fd2, "%d\n", numbers[i]);
        }
        memset(data, 0, MAX_LEN);
    }
    return 1;
}

int _close_files(FILE **fd1, FILE **fd2){
    if(fclose(*fd1) || fclose(*fd2)){
        fprintf(stderr, "%s", "Error while closing files.\n");
        return -1;
    }
    fprintf(stdout, "%s", "Files closed successfully.\n");
}

file_corrector_st table = { .open_covid_files =  _open_files, 
                          .read_write_covid_files = _read_write_file, 
                          .close_covid_files = _close_files 
                          };