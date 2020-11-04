#include <stdio.h>
#include <stdlib.h>

#define CHAR_TO_INT(c) (c- 97)

#define STRLEN(string) ({ \
    int count = 0;        \
    char *tmp = string;   \
    while (*tmp != '\0')  \
    {                     \
        count++;          \
        tmp++;            \
    }                     \
    count;                \
})

static int count[26] = {0};

void printFrequency(){
    for (int i = 0; i < 26; i++)
    {
        if(count[i] > 0)
            printf("%c:%d, ", (char)(i+97), count[i]);
    }
    
}

void countNumbers(char *number_string, int len){
    for(int i=0; i<len; i++){
        count[CHAR_TO_INT(number_string[i])]++;
    }
    printFrequency();
}

int main(int argc, char const *argv[])
{
    /* code */
    char *str = "ahjgdtrtah";
    
    printf("%d\n", CHAR_TO_INT('z'));

    countNumbers(str, STRLEN(str));

    return 0;
}
