#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LEN 256
typedef struct
{
    int id;
    char *fname;
    char *lname;
}testStruct;

int no_of_words(char *string, int SIZE){
    int count_words = 0;
    char *start = string;
    while(SIZE >= 0)
    {
        if(*start == ' ' || *start == '\0' || *start == '.' || *start == '\n'){
            count_words++;
        }
        start++; SIZE--;    
    }
    return count_words;
}

char *strtok1(char *string, char delim){
    char *string_copy = string;
    while(*string_copy != '\0'){
        if(*string_copy == delim){
            fprintf(stdout, "delim detected");
            *string_copy = '\0';
            fprintf(stdout, "string is %s\n", string);
            break;
        }
        string_copy++;
    }
    fprintf(stdout, "hola" );
    return string;
}

char** split(char *string, int SIZE){
    char *start = string, *end = string ;
    int size_of_word = 0;
    int count_words = no_of_words(string, SIZE);
    char **words = malloc(count_words * sizeof(char*));
    if(words == NULL){
        fprintf(stdout, "Error creating words array.n");
        exit(1);
    }
    int index = 0;
    while(SIZE >= 0)
    {
        if(*start == ' ' || *start == '\0' || *start == '.' || *start == '\n'){
            words[index] = malloc((size_of_word) * sizeof(char));
            memset(words[index], 0, size_of_word);
            strncpy(words[index], end, size_of_word);       //here null char will not be encountered 
                                                            //as size_of_word is less than *end. so the resulting string
                                                            //will not be null terminated.

            words[index++][size_of_word] = '\0';      //null termination is required.
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

int fread_struct_from_file(FILE *fd){
    int count=0;
    char data[MAX_LEN];
    while(fgets(data, MAX_LEN, fd) != NULL){
        //fprintf(stdout, "data is %s with length %d", data,strlen(data));
        char **items = split(data, strlen(data));
        fprintf(stdout, "id = %s, first_name = %s, last_name = %s\n", items[0], items[1], items[2]);
        count++;
    }
    return count;
}

int main(int argc, char const *argv[])
{
    /* code */
    FILE *fd = fopen("structure1.dat", "r");
    testStruct output; 

    if(fd == NULL){
        fprintf(stderr, "\nError opening file.\n");
        exit(1);
    }
    
    #if 0
    only used when struct is written to file.
    while (fread(&output, sizeof(testStruct), 1, fd))
    {
        printf("id = %d, fname = %s, lname = %s\n", output.id, output.fname, output.lname);
    }
    #endif

    fprintf(stdout, "no of structs are %d.\n", fread_struct_from_file(fd));
    char *line = "he is a boy";
    fprintf(stdout, "%s", strtok1(line, ' '));
    fclose(fd);

    return 0;
}
