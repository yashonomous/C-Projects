/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 50
#define MAX_OUTPUT_SIZE MAX_INPUT_SIZE*20
#define MAX_VALUE_SIZE 8

#define amp "&amp"
#define lt "&lt"
#define gt "&gt"
#define quot "&quot"
#define apos "&apos"

typedef struct hash_table{
    char key;
    char* value;
}hash_table_t;

static hash_table_t hash_table[] = {
    {'&', amp},
    {'<', lt},
    {'>', gt},
    {'\"', quot},
    {'\'', apos}
};

#define SIZE_HASHTABLE sizeof(hash_table)/sizeof(hash_table_t)

void copyCharToString(char* dest, char src, int dest_size){
    if((strlen(dest)+1) > dest_size){
        printf("%s ->  %s\n", __func__, "Destination buffer full. Cannot copy");
        return;
    }
    int len = strlen(dest);
    dest[len] = src;
    dest[len+1] = '\0';
}

void copyStringToString(char* dest, char* src, int dest_size){
    if((strlen(dest)+strlen(src)) > dest_size){
        printf("%s -> %s\n", __func__, "Destination buffer full. Cannot copy");
        return;
    }
    int offset = strlen(dest);
    int src_len = strlen(src);
    int i = 0;
    for(i=0; i<src_len; i++){
        dest[offset + i] = src[i];
    }
    dest[offset + i] = '\0';
}

int inHashTable(char c, char* value){
    for(int i=0; i<SIZE_HASHTABLE; i++){
        if(hash_table[i].key == c){
            //value = hash_table[i].value;      //wont work
            copyStringToString(value, hash_table[i].value, MAX_VALUE_SIZE);
            return 1; 
        }
    }
    return 0;
}

int matchStrings(char* str1, char* str2){
    int i, j, len_str1, len_str2;
    i = j = 0;
    len_str1 = strlen(str1);
    len_str2 = strlen(str2);
    for(i,j; (i<len_str1)&&(j<len_str2); i++,j++){
        if(str1[i] != str2[j]){
            return 0;
        }
    }
    // if(i != len_str1){
    //     return str1[i]-str2[j];
    // }
    // if(j != len_str2){
    //     return str2[j];
    // }
    return 1;
}

int findXmlChar(char* str_starting_point, char* key){
    for(int i=0; i<SIZE_HASHTABLE; i++){
        if(matchStrings(str_starting_point, hash_table[i].value)){
            *key = hash_table[i].key;
            return strlen(hash_table[i].value)-1;
        }
    }
    return 0;
}

void escapeXmlCharacters(char* str, char* output_str){
    if(strlen(str) == 0){
        printf("Empty string sent\n");
        return;
    }
    for(int i=0; i<strlen(str); i++){
        char* value = malloc((MAX_VALUE_SIZE+1) * sizeof(char));
        if(inHashTable(str[i], value)){
            copyStringToString(output_str, value, MAX_OUTPUT_SIZE);
        }
        else{
            copyCharToString(output_str, str[i], MAX_OUTPUT_SIZE);
        }
        free(value);
    }
}

void unescapeXmlCharacters(char* str, char* output){
    for(int i=0; i<strlen(str); i++){
        if(str[i] == '&'){
            char xml_char;
            int len_to_skip = findXmlChar(str+i, &xml_char);
            if(len_to_skip == 0){
                printf("%s -> %s\n", __func__, "Couldn't find the value in hash_table_t");
                return;
            }
            copyCharToString(output, xml_char, MAX_INPUT_SIZE);
            i += len_to_skip;
        }
        else{
            copyCharToString(output, str[i], MAX_INPUT_SIZE);
        }
    }
}

int main()
{
    char* input = malloc((MAX_INPUT_SIZE+1) * sizeof(char));
    memset(input, 0, MAX_INPUT_SIZE+1);
    //scanf("%s", input);
    // input = "h&llo";
    copyStringToString(input, "<script>yash's</script>", MAX_INPUT_SIZE);
    char* output = malloc((MAX_OUTPUT_SIZE+1) * sizeof(char));
    memset(output, 0, MAX_OUTPUT_SIZE+1);
    escapeXmlCharacters(input, output);
    printf("%s\n", output);
    
    // char* input1 = malloc((MAX_OUTPUT_SIZE+1) * sizeof(char));
    // memset(input, 0, MAX_INPUT_SIZE+1);
    // copyStringToString(input1, "&ltscript&gthello&lt/script&gt", MAX_OUTPUT_SIZE);
    char* output1 = malloc((MAX_INPUT_SIZE+1) * sizeof(char));
    memset(output1, 0, MAX_INPUT_SIZE+1);
    unescapeXmlCharacters(output, output1);
    printf("%s\n", output1);
    
    //free malloc
    free(input);
    free(output);
    
    return 0;
}
