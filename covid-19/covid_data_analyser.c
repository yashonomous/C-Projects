#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_LEN 1024
static int number_of_entries = 0;


FILE* _open_file(char *filename, char *mode){
    FILE *fd_temp;
    if((fd_temp = fopen(filename, mode)) == NULL){
        fprintf(stdout, "%s", "Error opening file.\n");
        return NULL;
    }
    fprintf(stdout, "%s", "File opened successfully.\n");
    return fd_temp;
}

int _number_of_entries(FILE *fd){
    int count = 0;
    char data[MAX_LEN];
    while (fgets(data, MAX_LEN, fd))
    {
        /* code */
        int data_int = atoi(data);
        //if(data_int != 0){
            count++; number_of_entries++;
        //}

    }
    return count;
}

int* _create_integer_array(char *filename, char *mode, FILE* (_open_file_cb)()){
    FILE *fd = _open_file_cb(filename, mode);
    char data[MAX_LEN];
    int i = 0;
    int number_of_entries = _number_of_entries(fd);

    fseek(fd, 0, SEEK_SET);

    fprintf(stdout, "number of entries -> %d.\n", number_of_entries);
    int *numbers =  malloc(number_of_entries * sizeof(int));
    while (fgets(data, MAX_LEN, fd))
    {
        /* code */
        numbers[i++] = atoi(data);
    }
    if(fclose(fd)){
        fprintf(stderr, "File cannot be closed.\n");
        return NULL;
    }
    fprintf(stdout, "File closed successfully.\n");
    return numbers;
}

double _return_exponent(int *numbers, int number_of_entries){
    double sum = 0;
    int zeros = 0;
    for(int i=0; i<number_of_entries; i++){
        if(numbers[i] != 0)
            sum += log((double)numbers[i]);
        else
            zeros++;    
        //fprintf(stdout, "%lf ", log((double)numbers[i]));
    }
    fprintf(stdout, "sum of entries -> %lf.\n", sum);
    fprintf(stdout, "num of entries are -> %d\n", number_of_entries-zeros);
    return sum/(double)(number_of_entries - zeros);
}

int main(int argc, char const *argv[])
{
    /* code */
    char *filename = "covid_19_corrected.txt";
    char *mode = "r";
    int *numbers = _create_integer_array(filename, mode, _open_file);
    //int number_of_entries = _number_of_entries(_open_file(filename, mode));

    double avg_exponent = _return_exponent(numbers, number_of_entries);
    fprintf(stdout ,"Corona cases are increasing at a rate of exp(%lf).\n", avg_exponent);
    return 0;
}
