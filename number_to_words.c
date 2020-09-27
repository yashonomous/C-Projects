#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HANDLE(digits) (digits##DigitsCase)

#define INT_TO_CHAR(num) ((char)(48 + num))

#define STRLEN(string) ({int count=0; \
                        char *tmp = string; \
                    while(*tmp != '\0'){ \
                        count++; tmp++; } \
                        count;})

#define NUMLEN(num) ({ int tmp = num; \
                              int count = 0; \
                              while(tmp > 0){ \
                                count++; \
                                tmp /= 10;} \
                              count;})

#define TOSTRING(num) ({ int len = NUMLEN(num); \
                        int tmp = num; \
                        char* tmpStr = malloc(len * sizeof(char)); \
                        while(tmp && len--){ \
                            tmpStr[len] = INT_TO_CHAR(tmp % 10); \
                            tmp /= 10;} \
                            tmpStr; })

#define MAX_IN_ALPHABET_LEN 100
#define MAX_SINGLE_NUM_TO_ALPHABET_LEN 7

int copyString(char *dest, char* src, int destLen){
    int lenSrc = STRLEN(src);
    if(lenSrc >= destLen){
        printf("%s\n", "src len is more than dest len");
        return -1;
    }
    char *tmp = dest;
    while(lenSrc-- && (*dest++ = *src++));
    *dest = '\0';
    dest = tmp;
    return 0;
}

int appendString(char *dest, char* src, int destLen){
    int lenSrc = STRLEN(src);
    int lenDest = STRLEN(dest);
    if((lenSrc+lenDest) >= destLen){
        printf("%s\n", "src len is more than dest len");
        return -1;
    }
    char *tmp = dest;
    dest += lenDest;
    while(lenSrc-- && (*dest++ = *src++));
    *dest = '\0';
    dest = tmp;
    return 0;
}

int areEqual(char *str1, char *str2){
    return (str1[0]=='\0' && str2[0]=='\0') ? 1:
            (str1[0] != str2[0]) ? 0:areEqual(str1+1, str2+1);
}

static char *ones[] = { "", "one", "two", "three", "four", "five", "six",
                            "seven", "eight", "nine", "ten", "eleven", "twelve",
                            "thirteen", "fourteen", "fifteen", "sixteen",
                            "seventeen", "eighteen", "nineteen"};

static char *tens[] = { "", "", "twenty", "thirty", "forty", "fifty", "sixty",
                "seventy", "eighty", "ninety" };

void numericalToAlphabetUtil(int number, char *suffix, char *inAlphabet){
    //check if num > 19
    if(number > 19){
        appendString(inAlphabet, tens[number/10], MAX_IN_ALPHABET_LEN);
        appendString(inAlphabet, " ", MAX_IN_ALPHABET_LEN);
        appendString(inAlphabet, ones[number%10], MAX_IN_ALPHABET_LEN);
    }
    else{
        appendString(inAlphabet, ones[number], MAX_IN_ALPHABET_LEN);
    }
    if(number && (STRLEN(suffix)>0)){
        appendString(inAlphabet, " ", MAX_IN_ALPHABET_LEN);
        if(number == 1){
            appendString(inAlphabet, suffix, MAX_IN_ALPHABET_LEN);
            appendString(inAlphabet, " ", MAX_IN_ALPHABET_LEN);
        }
        else if(areEqual(suffix, "crore") || areEqual(suffix, "lakh")){
            appendString(inAlphabet, suffix, MAX_IN_ALPHABET_LEN);
            appendString(inAlphabet, "s ", MAX_IN_ALPHABET_LEN);
        }
        else{
            appendString(inAlphabet, suffix, MAX_IN_ALPHABET_LEN);
            appendString(inAlphabet, " ", MAX_IN_ALPHABET_LEN);
        }    
    }
}

void numericalToAlphabet(int number, char *inAlphabet){
    // int lenOfNumber = NUMLEN(number);
    numericalToAlphabetUtil((number/10000000), "crore", inAlphabet);
    numericalToAlphabetUtil(((number/100000)%100), "lakh", inAlphabet);
    numericalToAlphabetUtil(((number/1000)%100), "thousand", inAlphabet);
    numericalToAlphabetUtil((number%1000)/100, "hundred", inAlphabet);
    numericalToAlphabetUtil(number%100, "", inAlphabet);
    if(number == 1)
        appendString(inAlphabet, " rupee", MAX_IN_ALPHABET_LEN);
    else
        appendString(inAlphabet, " rupees", MAX_IN_ALPHABET_LEN);
}

int main()
{
    int number = 0;
    printf("Enter a number -> ");
    scanf("%d", &number);
    getchar(); 
    char *inAlphabet = malloc(MAX_IN_ALPHABET_LEN * sizeof(char));
    memset(inAlphabet, 0, MAX_IN_ALPHABET_LEN);
    numericalToAlphabet(number, inAlphabet);
    printf("amount is -> %s\n", inAlphabet);
    free(inAlphabet);
    return 0;
}
