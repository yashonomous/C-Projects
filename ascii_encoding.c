#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// char* decimalToHex(int c){
//     char* res = "";
//     switch(c){
//         case 0:
//             res = "0";
//             break;
//         case 1:
//             res = "1";
//             break;
//         case 2:
//             res = "2";
//             break;
//         case 3:
//             res = "3";
//             break;
//         case 4:
//             res = "4";
//             break;
//         case 5:
//             res = "5";
//             break;
//         case 6:
//             res = "6";
//             break;
//         case 7:
//             res = "7";
//             break;    
//         case 8:
//             res = "8";
//             break;
//         case 9:
//             res = "9";
//             break;
//         case 10:
//             res = "A";
//             break;    
//         case 11:
//             res = "B";
//             break;
//         case 12:
//             res = "C";
//             break;
//         case 13:
//             res = "D";
//             break;
//         case 14:
//             res = "E";
//             break;
//         case 15:
//             res = "F";
//             break;    
//         default:
//             res = "-1";
//             break;
//     }
//     if(res != "-1"){
//         return res;
//     }
//     return "Invalid input";
// }

char decimalToHex(int c){
    char res = '\0';
    switch(c){
        case 0:
            res = '0';
            break;
        case 1:
            res = '1';
            break;
        case 2:
            res = '2';
            break;
        case 3:
            res = '3';
            break;
        case 4:
            res = '4';
            break;
        case 5:
            res = '5';
            break;
        case 6:
            res = '6';
            break;
        case 7:
            res = '7';
            break;    
        case 8:
            res = '8';
            break;
        case 9:
            res = '9';
            break;
        case 10:
            res = 'A';
            break;    
        case 11:
            res = 'B';
            break;
        case 12:
            res = 'C';
            break;
        case 13:
            res = 'D';
            break;
        case 14:
            res = 'E';
            break;
        case 15:
            res = 'F';
            break;    
        default:
            res = 'N';
            break;
    }
    return res;
}

int hexToDecimal(char c){
    int res = 0;
    switch(c){
        case '0':
            res = 0;
            break;
        case '1':
            res = 1;
            break;
        case '2':
            res = 2;
            break;
        case '3':
            res = 3;
            break;
        case '4':
            res = 4;
            break;
        case '5':
            res = 5;
            break;
        case '6':
            res = 6;
            break;
        case '7':
            res = 7;
            break;    
        case '8':
            res = 8;
            break;
        case '9':
            res = 9;
            break;
        case 'A':
            res = 10;
            break;    
        case 'B':
            res = 11;
            break;
        case 'C':
            res = 12;
            break;
        case 'D':
            res = 13;
            break;
        case 'E':
            res = 14;
            break;
        case 'F':
            res = 15;
            break;    
        default:
            res = -1;
            break;
    }
    return res;
}

char* asciiToHex(char* ascii_str, int size){
    int hex_size = (2 * size) + 1;
    char* hex = (char*)malloc(hex_size * sizeof(char));
    int idx = 0;
    memset(hex, 0, hex_size);
    for(int i=0; i<size; i++){
        //printf("decimal for %c is %d\n", ascii_str[i], (int)ascii_str[i]);
        int dec = (int)ascii_str[i];
        // strncat(hex, decimalToHex(dec >> 4), strlen(decimalToHex(dec >> 4)));
        // strncat(hex, decimalToHex(dec % 16), strlen(decimalToHex(dec % 16)));
        hex[idx++] = decimalToHex(dec >> 4);
        hex[idx++] = decimalToHex(dec % 16);
    }
    hex[idx] = '\0';
    return hex;
}

char* hexToAscii(char* hex_str, int size){
    int ascii_size = (size/2) + 1;
    char* ascii = (char*)malloc(ascii_size * sizeof(char));
    int idx = 0;
    memset(ascii, 0, ascii_size);
    for(int i=0,j=1; i<(size-1)&&j<size; i+=2,j+=2){
        int decimal = 1;
        if((hex_str[i]>='0' && hex_str[i]<='9') || (hex_str[i]>='A' && hex_str[i]<='F')){
            decimal = hexToDecimal(hex_str[i]) << 4;
        }
        else{
            printf("Invalid hex char encountered.\n");
            return "Invalid hex char encountered.";
        } 
        if((hex_str[j]>='0' && hex_str[j]<='9') || (hex_str[j]>='A' && hex_str[j]<='F')){
            decimal += hexToDecimal(hex_str[j]);
        }
        else{
            printf("Invalid hex char encountered.\n");
            return "Invalid hex char encountered.";
        }
        ascii[idx++] = (char)decimal;
    }
    ascii[idx] = '\0';
    return ascii;
}

int main()
{
    // char* str = "this is a ascii sentence";
    // printf("str is -> %s\n", str);
    // char* hex_str = asciiToHex(str, strlen(str));
    // printf("hex value is -> %s\n", hex_str);
    // char* ascii_str = hexToAscii(hex_str, strlen(hex_str));
    // printf("ascii value is -> %s\n", ascii_str);
    
    int input, exit=0;
    char *res, *str;
    while(1){
        printf("HexToAscii and AsciiToHex Convertor\n"\
            "1. ASCII to HEX Convertor\n"\
            "2. HEX to ASCII Convertor\n"\
            "Input -1 to exit\n"\
            "Choose your tool :- ");
        scanf("%d", &input);        //scanf after scanf causes a problem
        getchar();          //use getchar to flush newline char saved in input buffer.
        switch (input)
        {
        case 1:
            printf("Enter your ASCII string -> ");
            scanf("%[^\n]%*c", str);
            // fgets(str, 20, stdin);
            printf("ASCII string is -> %s\n", str);
            res = asciiToHex(str, strlen(str));
            printf("HEX string is -> %s\n\n", res);
            break;
        case 2:
            printf("Enter your HEX string -> ");
            scanf("%[^\n]%*c", str);
            // fgets(str, 20, stdin);
            printf("HEX string is -> %s\n", str);
            res = hexToAscii(str, strlen(str));
            printf("ASCII string is -> %s\n\n", res);
            break;
        case -1:
            printf("Terminating program");
            Sleep(1); printf("."); Sleep(1); printf("."); Sleep(1); printf("."); Sleep(1); printf("."); Sleep(1); printf(".");
            exit = 1;
            break;    
        default:
            printf("Invalid input. Please try again\n");
            break;
        }
        if(exit)
            break;
    }
    return 0;
}
