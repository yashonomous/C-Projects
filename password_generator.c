#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* capitalAlphabetGenerator(){
    char* capital_alphabets = malloc(27 * sizeof(char));
    int i = 0;
    capital_alphabets[i] = 'A';
    for(i=1; i<26; i++){
        capital_alphabets[i] = (char)((int)capital_alphabets[i-1] + 1);
    }
    capital_alphabets[i] = '\0';
    return capital_alphabets;
}

char* smallAlphabetGenerator(){
    char* small_alphabets = malloc(27 * sizeof(char));
    int i = 0;
    small_alphabets[i] = 'a';
    for(i=1; i<26; i++){
        small_alphabets[i] = (char)((int)small_alphabets[i-1] + 1);
    }
    small_alphabets[i] = '\0';
    return small_alphabets;
}

char* integerGenerator(){
    char* integers = malloc(11 * sizeof(char));
    int i = 0;
    integers[i] = '0';
    for(i=1; i<10; i++){
        integers[i] = (char)((int)integers[i-1] + 1);
    }
    integers[i] = '\0';
    return integers;
}

char* concat_string(char* dest, char* src, int offset, int src_len){
    for(int i=0; i<src_len; i++){
        dest[offset + i] = src[i];
    }
    dest[offset + src_len] = '\0';      //always null terminate string in C
    return dest;
}

int main(int argc, char const *argv[])
{
    /* code */
    char* capital_alphabets = capitalAlphabetGenerator();
    //printf("%s\n", capital_alphabets);
    char* small_alphabets = smallAlphabetGenerator();
    //printf("%s\n", small_alphabets);
    char* integers = integerGenerator();
    //printf("%s\n", integers);
    char* special_chars = "!@#$%^&*_=+-/.?<>\\|";

    char* alphabets = concat_string(capital_alphabets, small_alphabets, (int)strlen(capital_alphabets), (int)strlen(small_alphabets));
    // printf("%s\n", alphabets);
    // printf("length is -> %ld\n", strlen(alphabets));
    char* nums_special_chars = concat_string(integers, special_chars, strlen(integers), strlen(special_chars));
    // printf("%s\n", nums_special_chars);
    // printf("length is -> %ld\n", strlen(nums_special_chars));
    
    char* password_chars_inventory = concat_string(alphabets, nums_special_chars, strlen(alphabets), strlen(nums_special_chars));
    // printf("%s\n", password_chars_inventory);
    // printf("%ld\n", strlen(password_chars_inventory));
    
    int length;
    printf("Enter the length of password -> ");
    scanf("%d", &length);
    char* password = malloc((length+1) * sizeof(char));
    memset(password, 0, length+1);
    char char_to_str[2];
    
    for(int i=0; i<length; i++){
        int rand_idx = rand() % (strlen(password_chars_inventory));
        char_to_str[0] = password_chars_inventory[rand_idx];
        char_to_str[1] = '\0';
        concat_string(password, char_to_str, strlen(password), strlen(char_to_str));
        // printf("%d ", rand_idx);
    }
    printf("Password is %s\n\n", password);
    
    printf("Password length is %Iu\n", strlen(password));
    
    //flush all the allocated buffer memory
    //free(capital_alphabets);
    // free(small_alphabets);
    // free(integers);
    //free(special_chars);
    //free(alphabets);
    //free(nums_special_chars);
    //free(password_chars_inventory);
    // free(password);
    return 0;
}
