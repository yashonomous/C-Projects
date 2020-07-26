/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char charAfterEncryption(char c, int num){
    char transformed_char = '\0';
    // if(((int)c+num) <= (int)'z'){
    //     transformed_char = (char)((int)c+num);
    // }
    // else{
    //     transformed_char = (char)((((int)c+num)%(int)'z') + (int)'a' - 1);
    // }
    transformed_char = (char)(((int)c+num-(int)'a')%26 + (int)'a');
    return transformed_char;
}

char charAfterDecryption(char c, int num){
    char transformed_char = '\0';
    // if(((int)c+num) <= (int)'z'){
    //     transformed_char = (char)((int)c+num);
    // }
    // else{
    //     transformed_char = (char)((((int)c+num)%(int)'z') + (int)'a' - 1);
    // }
    transformed_char = (char)(((int)c+26-num-(int)'a')%26 + (int)'a');
    return transformed_char;
}

char* encrypt(){
    printf("Enter the string to be encrypted :- ");
    char *str = malloc(20 * sizeof(char));
    scanf("%[^\n]%*c", str);
    int tranformation_num;
    printf("Enter encryption key :- ");
    scanf("%d", &tranformation_num);
    getchar();
    for(int i=0; i<strlen(str); i++){
        str[i] = charAfterEncryption(str[i], tranformation_num);
    }
    printf("Encrypted string for is -> %s\n\n", str);
}

char* decrypt(){
    printf("Enter the string to be decrypted :- ");
    char *str = malloc(20 * sizeof(char));
    scanf("%[^\n]%*c", str);
    int tranformation_num;
    printf("Enter decryption key :- ");
    scanf("%d", &tranformation_num);
    getchar();
    for(int i=0; i<strlen(str); i++){
        str[i] = charAfterDecryption(str[i], tranformation_num);
    }
    printf("Decrypted string for is -> %s\n\n", str);
}

int main()
{
    printf("Caesar's Cipher Generator\n");
    encrypt();
    decrypt();
    
    
    return 0;
}
