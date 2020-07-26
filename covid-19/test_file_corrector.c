// build the program using gcc -o file_corrector test_file_corrector.c file_corrector.c

#include "file_corrector.h"

int main(int argc, char const *argv[])
{
    /* code */
    FILE *fd1;
    FILE *fd2;
    char *filename1 = "covid_19.txt";
    char *filename2 = "covid_19_corrected.txt";

    table.open_covid_files(&fd1, &fd2, filename1, filename2, "r", "w");
    table.read_write_covid_files(&fd1, &fd2);
    table.close_covid_files(&fd1, &fd2);

    return 0;
}
