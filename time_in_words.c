/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define toUpperCase(c) (((c)>='a' && (c)<='z') ? (c - 32) : (c))  

#define HEX_DIGIT(c) ((toUpperCase(c) < 'A') ? ((c) - '0') : (toUpperCase(c) - 'A' + 10))

#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

#define STRLEN(string) ({ \
						int count=0; \
                        char *tmp = string; \
                    	while(*tmp != '\0') \
						{ \
                        	count++; \
							tmp++; \
						} \
                        count; \
						})

#define MEMSET(string, char, length)  ({ \
										int tmp = length; \
										while (tmp--) \
										{ \
											string[tmp] = '\0'; \
										} \
										})						
#define MAX_IN_WORDS_LEN 30

static char* ones[20] = {
                            "", "one", "two", "three", "four", "five", "six",
                            "seven", "eight", "nine", "ten", "eleven", 
                            "twelve", "thirteen", "fourteen", "fifteen",
                            "sixteen", "seventeen", "eighteen", "nineteen"
                        };

static char* tens[6] = {
                            "", "", "twenty", "thirty", "fourty", "fifty"
                        };

void append(char *dest, char *src){
    int len_dest = STRLEN(dest);
    int len_src = STRLEN(src);
    if(len_src > MAX_IN_WORDS_LEN)
        dest = realloc(dest, MAX_IN_WORDS_LEN*2);   
    
    for(int i=0; i<len_src; i++)
        dest[len_dest + i] = src[i];

    dest[len_dest + len_src] = '\0';
}

void processDigit(int digit, char *result){
    if(digit < 20)
        append(result, ones[digit]);
    else{
        int ones_digit = digit % 10;
        int tens_digit = digit /10;
        append(result, tens[tens_digit]);
        append(result, " ");
        append(result, ones[ones_digit]);
    }    
}

void convertTime(struct tm *now_ptr, char *result){
    append(result, "It's ");
    processDigit(now_ptr->tm_hour, result);
	append(result, " ");
    processDigit(now_ptr->tm_min, result);
}

int main()
{
    time_t now = time(&now);
    struct tm *now_ptr = localtime(&now);
    char *result = malloc(MAX_IN_WORDS_LEN * sizeof(char));
	MEMSET(result, '\0', MAX_IN_WORDS_LEN);
    convertTime(now_ptr, result);
    printf("%s\n", result);
    // printf("time is -> %s\n", ctime(&now));
    // printf("%d : %d : %d\n", now_ptr->tm_hour, now_ptr->tm_min, now_ptr->tm_sec);
    
    return 0;
}
