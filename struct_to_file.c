#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    int id;
    char *fname;           //either use a fixed size so that we can directly write struct to a file using fwrite.
    char *lname;
}testStruct;

int fwrite_struct_to_file(testStruct *persons, FILE *fd, size_t size_arr){
    int i=0;
    while(size_arr--){
        // fwrite(&(persons[i].id), sizeof(int), 1, fd);
        // fwrite(persons[i].fname, sizeof(char), strlen(persons[i].fname), fd);
        // fwrite(persons[i].lname, sizeof(char), strlen(persons[i].lname), fd);

        fprintf(fd, "%d", persons[i].id); fputs(" ", fd); fputs(persons[i].fname, fd); 
        fputs(" ", fd); fputs(persons[i].lname, fd); fputs("\n", fd);

        i++;
    }
    if (fwrite != 0)
        return 1;
    return 0;    
}

int main(int argc, char const *argv[])
{
    /* code */
    FILE *fd;
    fd = fopen("structure1.dat", "w");
    if(fd == NULL){
        fprintf(stderr, "\nError in opening file.\n");
        exit(1);
    }

    testStruct struct_array[] = {{1, "fname1", "lname1"}, \
                                  {2, "fname2", "lname2"}, \
                                  {3, "fname3", "lname3"}, \
                                  {4, "fname4", "lname4"}, \
                                  {5, "fname5", "lname5"}};
    
    // testStruct *input1 = (testStruct*)malloc(sizeof(testStruct));
    // testStruct *input2 = (testStruct*)malloc(sizeof(testStruct));

    // input1 -> id = 1;
    // input1 -> fname = "yashaswi";
    // input1 -> lname = "soni";

    // input2 -> id = 2;
    // input2 -> fname = "shreyansh";
    // input2 -> lname = "soni";

    //fwrite(&temp2, sizeof(testStruct), 1, fd);
    size_t SIZE =  sizeof(struct_array)/sizeof(testStruct);
    if(fwrite_struct_to_file(struct_array, fd, SIZE))
        fprintf(stderr, "\nContent written successfully.\n");
    else
        fprintf(stderr, "\nError writing file.\n");

    fclose(fd);
    return 0;
}
