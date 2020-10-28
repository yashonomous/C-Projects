#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

#define MEMSET(array, value, length)  ({ \
										int tmp = length; \
										while (tmp--) \
										{ \
										array[tmp] = value; \
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
	//process hours
    processDigit(now_ptr->tm_hour, result);
	append(result, " ");
	//process minutes
    processDigit(now_ptr->tm_min, result);
}

int main()
{
    //get current time
	time_t now = time(&now);
    struct tm *now_ptr = localtime(&now);
	
    char *result = malloc(MAX_IN_WORDS_LEN * sizeof(char));
	MEMSET(result, '\0', MAX_IN_WORDS_LEN);
    
	convertTime(now_ptr, result);
    printf("%s\n", result);
    
    return 0;
}
