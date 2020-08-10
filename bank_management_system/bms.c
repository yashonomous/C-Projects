#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_EMAIL_LEN 50+1
#define MAX_PASSWORD_LEN 15+1
#define MAX_ACCOUNT_NO_LEN 17+1
#define MAX_ACCOUNT_TYPE_LEN 11+1
#define MAX_FNAME_LEN 15+1
#define MAX_LNAME_LEN 15+1
#define MAX_DATE_LEN 11+1
#define MAX_AADHAR_LEN 13+1
#define MAX_COUNTRY_CODE_LEN 4+1
#define MAX_PH_NO_LEN 10+1
#define MAX_APARTMENT_NO_LEN 5+1
#define MAX_BUILDING_LEN 30+1
#define MAX_COLONY_LEN 40+1
#define MAX_CITY_LEN 20+1
#define MAX_STATE_LEN 15+1
#define MAX_COUNTRY_LEN 15+1
#define MAX_PINCODE_LEN 7+1

int is_admin=0;
char logged_in_user_email[MAX_EMAIL_LEN], logged_in_user_fname[MAX_FNAME_LEN], logged_in_user_lname[MAX_LNAME_LEN];
typedef int (*int_fun_ptr)();

typedef enum menu_exit{
    exit_program = 0,
    main_menu = 1
}menu_exit_e;

typedef struct user_credentials{
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
}user_credentials_t;

typedef struct phone_number{
    char country_code[MAX_COUNTRY_CODE_LEN];
    char ph_no[MAX_PH_NO_LEN];
}phone_number_t;

typedef struct address_details{
    char apartment_no[MAX_APARTMENT_NO_LEN];
    char building[MAX_BUILDING_LEN];
    char colony[MAX_COLONY_LEN];
    char city[MAX_CITY_LEN];
    char state[MAX_STATE_LEN];
    char country[MAX_COUNTRY_LEN];
    char pin_code[MAX_PINCODE_LEN];
}address_details_t;

typedef struct customer_details{
    char account_number[MAX_ACCOUNT_NO_LEN];
    char account_type[MAX_ACCOUNT_TYPE_LEN];
    char first_name[MAX_FNAME_LEN];   //can be changed to char array
    char last_name[MAX_LNAME_LEN]; 
    char dob[MAX_DATE_LEN];
    char aadhar_no[MAX_AADHAR_LEN];
    char email_id[MAX_EMAIL_LEN];
    address_details_t* address;
    phone_number_t* phone_no;
    double amount;
    char deposit_date[MAX_DATE_LEN];
    char withdraw_date[MAX_DATE_LEN];
    struct customer_details* next_customer_details;
}customer_details_t;

typedef struct menu
{
    int_fun_ptr createNewAccount;
    int_fun_ptr viewCustomerDetails;
    int_fun_ptr edit;
    int_fun_ptr transact;
    int_fun_ptr erase;
    int_fun_ptr see;
}menu_t;

void login_register(void);
int login(void);
int register_user(void);
void menu(void);
void close_program();

int dateNotCorrectFormat(char* date_str){
    int invalid = 0;
    int len = strlen(date_str);
    if((len!=10) || (date_str[2]!='/') || (date_str[5]!='/')){
        return 1;
    }
    for(int i=0; i<len; i++){
        if((i!=2) && (i!=5)){
            if((date_str[i]<'0') || (date_str[i]>'9'))
                return 1;
        }
    }
    return 0;
}

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
} 

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

customer_details_t* prepareCustomerDetailsStruct(){
    customer_details_t* temp_customer_ptr = malloc(sizeof(customer_details_t));
    if(temp_customer_ptr == NULL){
        fprintf(stderr, "%s -> %s\n", __func__, "Failed to allocate memory to customer_details_ptr");
        exit(0);
    }
    memset(temp_customer_ptr, 0, sizeof(customer_details_t));
    temp_customer_ptr->address = malloc(sizeof(address_details_t));
    temp_customer_ptr->phone_no = malloc(sizeof(phone_number_t));
    memset(temp_customer_ptr->address, 0, sizeof(address_details_t));
    memset(temp_customer_ptr->phone_no, 0, sizeof(phone_number_t));
    temp_customer_ptr->next_customer_details = NULL;
    return temp_customer_ptr;
}

int _createNewAccount(){
    customer_details_t* customer_details_ptr = prepareCustomerDetailsStruct();
    if(customer_details_ptr == NULL){
        fprintf(stderr, "%s -> %s\n", __func__, "Failed to allocate memory to customer_details_ptr");
        // exit(0);
        return -1;
    }
    FILE *fd, *fd1;
    fd = fopen("customers.txt", "a+");
    fd1 = fopen("customers.txt", "r");
    if((fd == NULL) || (fd1 == NULL)){
        fprintf(stderr, "%s -> %s\n", __func__, "Couldn't open file");
        //exit(0);
        return -1;
    }
    else
    {
        customer_details_t check_customer_details_ptr;
        check_customer_details_ptr.address = malloc(sizeof(address_details_t));
        memset(check_customer_details_ptr.address, 0, sizeof(address_details_t));
        check_customer_details_ptr.phone_no = malloc(sizeof(phone_number_t));
        memset(check_customer_details_ptr.phone_no, 0, sizeof(phone_number_t));
        if((check_customer_details_ptr.address==NULL) || (check_customer_details_ptr.phone_no==NULL)){
            fprintf(stderr, "%s -> %s\n", __func__, "Failed to allocate memory to address struct or ph_no struct");
            return -1;
        }
        system("cls");
        acc_no:
        fprintf(stdout, "%s", "Enter account number -> ");
        fgets(customer_details_ptr->account_number, MAX_ACCOUNT_NO_LEN, stdin);
        if(sscanf(customer_details_ptr->account_number, "%s", customer_details_ptr->account_number) != 1){
            fprintf(stderr, "%s\n", "Wrong account number format");
            // exit(0);
            //return -1;
            goto acc_no;
        }
        while(fscanf(fd1, "%s %s %s %s %s %s %s %s,%s,%s,%s,%s,%s.%s %s-%s %s %s", check_customer_details_ptr.account_number,
            check_customer_details_ptr.account_type, check_customer_details_ptr.first_name, check_customer_details_ptr.last_name,
            check_customer_details_ptr.dob, check_customer_details_ptr.aadhar_no, check_customer_details_ptr.email_id, 
            check_customer_details_ptr.address->apartment_no, check_customer_details_ptr.address->building,
            check_customer_details_ptr.address->colony, check_customer_details_ptr.address->city,
            check_customer_details_ptr.address->state, check_customer_details_ptr.address->country,
            check_customer_details_ptr.address->pin_code, check_customer_details_ptr.phone_no->country_code,
            check_customer_details_ptr.phone_no->ph_no, check_customer_details_ptr.deposit_date, check_customer_details_ptr.withdraw_date) 
            != EOF){
                if(strncmp(customer_details_ptr->account_number, check_customer_details_ptr.account_number, 
                    strlen(customer_details_ptr->account_number)) == 0){
                        fprintf(stderr, "%s\n", "Account already exists. Try different account number");
                        goto acc_no;
                }
        }
        acc_type:
        fprintf(stdout, "%s", "Enter account type -> ");
        fgets(customer_details_ptr->account_type, MAX_ACCOUNT_TYPE_LEN, stdin);
        if(sscanf(customer_details_ptr->account_type, "%s", customer_details_ptr->account_type) != 1){
            fprintf(stderr, "%s\n", "Wrong account type format");
            // exit(0);
            // return -1;
            goto acc_type;
        }
        f_name:
        fprintf(stdout, "%s", "Enter first name -> ");
        fgets(customer_details_ptr->first_name, MAX_FNAME_LEN, stdin);
        if(sscanf(customer_details_ptr->first_name, "%s", customer_details_ptr->first_name) != 1){
            fprintf(stderr, "%s\n", "Wrong fname format");
            // exit(0);
            // return -1;
            goto f_name;
        }
        l_name:
        fprintf(stdout, "%s", "Enter last name -> ");
        fgets(customer_details_ptr->last_name, MAX_LNAME_LEN, stdin);
        if(sscanf(customer_details_ptr->last_name, "%s", customer_details_ptr->last_name) != 1){
            fprintf(stderr, "%s\n", "Wrong lname format");
            // exit(0);
            // return -1;
            goto l_name;
        }
        dob:
        fprintf(stdout, "%s", "Enter date of birth(DD/MM/YYYY) -> ");
        scanf("%s", customer_details_ptr->dob);
        getchar();
        if(dateNotCorrectFormat(customer_details_ptr->dob)){
            fprintf(stderr, "%s\n", "Wrong date format");
            goto dob;
        }
        // fgets(customer_details_ptr->dob, MAX_DATE_LEN, stdin);
        // if(sscanf(customer_details_ptr->dob, "%[/]s", customer_details_ptr->dob) != 1){
        //     fprintf(stdout, "%s\n", "Wrong dob format");
        //     // exit(0);
        //     return -1;
        // }

        email_id:
        fprintf(stdout, "%s", "Enter email id -> ");
        fgets(customer_details_ptr->email_id, MAX_EMAIL_LEN, stdin);
        if(sscanf(customer_details_ptr->email_id, "%s", customer_details_ptr->email_id) != 1){
            fprintf(stderr, "%s\n", "Wrong email id format");
            // exit(0);
            // return -1;
            goto email_id;
        }

        aadhar_no:
        fprintf(stdout, "%s", "Enter aadhar card number -> ");
        fgets(customer_details_ptr->aadhar_no, MAX_AADHAR_LEN, stdin);
        if(sscanf(customer_details_ptr->aadhar_no, "%s", customer_details_ptr->aadhar_no) != 1){
            fprintf(stderr, "%s\n", "Wrong aadhar_number format");
            // exit(0);
            // return -1;
            goto aadhar_no;
        }
        
        fprintf(stdout, "%s", "Enter address details : \n");
        apt_no:
        fprintf(stdout, "%s", "Enter apartment number -> ");
        fgets(customer_details_ptr->address->apartment_no, MAX_APARTMENT_NO_LEN, stdin);
        if(sscanf(customer_details_ptr->address->apartment_no, "%s", customer_details_ptr->address->apartment_no) != 1){
            fprintf(stderr, "%s\n", "Wrong apartment number format");
            // exit(0);
            // return -1;
            goto apt_no;
        }
        building_name:
        fprintf(stdout, "%s", "Enter building name -> ");
        fgets(customer_details_ptr->address->building, MAX_BUILDING_LEN, stdin);
        if(sscanf(customer_details_ptr->address->building, "%[^\n]s", customer_details_ptr->address->building) != 1){
            fprintf(stderr, "%s\n", "Wrong building name format");
            // exit(0);
            // return -1;
            goto building_name;
        }
        colony_name:
        fprintf(stdout, "%s", "Enter colony name -> ");
        fgets(customer_details_ptr->address->colony, MAX_COLONY_LEN, stdin);
        if(sscanf(customer_details_ptr->address->colony, "%[^\n]s", customer_details_ptr->address->colony) != 1){
            fprintf(stderr, "%s\n", "Wrong colony name format");
            // exit(0);
            // return -1;
            goto colony_name;
        }
        city_name:
        fprintf(stdout, "%s", "Enter city name -> ");
        fgets(customer_details_ptr->address->city, MAX_CITY_LEN, stdin);
        if(sscanf(customer_details_ptr->address->city, "%[^\n]s", customer_details_ptr->address->city) != 1){
            fprintf(stderr, "%s\n", "Wrong city name format");
            // exit(0);
            // return -1;
            goto city_name;
        }
        state_name:
        fprintf(stdout, "%s", "Enter state name -> ");
        fgets(customer_details_ptr->address->state, MAX_STATE_LEN, stdin);
        if(sscanf(customer_details_ptr->address->state, "%[^\n]s", customer_details_ptr->address->state) != 1){
            fprintf(stderr, "%s\n", "Wrong state name format");
            // exit(0);
            // return -1;
            goto state_name;
        }
        country_name:
        fprintf(stdout, "%s", "Enter country name -> ");
        fgets(customer_details_ptr->address->country, MAX_COUNTRY_LEN, stdin);
        if(sscanf(customer_details_ptr->address->country, "%[^\n]s", customer_details_ptr->address->country) != 1){
            fprintf(stderr, "%s\n", "Wrong country name format");
            // exit(0);
            // return -1;
            goto country_name;
        }
        pincode:
        fprintf(stdout, "%s", "Enter pincode -> ");
        fgets(customer_details_ptr->address->pin_code, MAX_PINCODE_LEN, stdin);
        if(sscanf(customer_details_ptr->address->pin_code, "%s", customer_details_ptr->address->pin_code) != 1){
            fprintf(stderr, "%s\n", "Wrong pincode format");
            // exit(0);
            // return -1;
            goto pincode;
        }

        fprintf(stdout, "%s", "Enter phone number details : \n");
        country_code:
        fprintf(stdout, "%s", "Enter country code -> ");
        fgets(customer_details_ptr->phone_no->country_code, MAX_COUNTRY_CODE_LEN, stdin);
        if(sscanf(customer_details_ptr->phone_no->country_code, "%s", customer_details_ptr->phone_no->country_code) != 1){
            fprintf(stderr, "%s\n", "Wrong country code format");
            // exit(0);
            // return -1;
            goto country_code;
        }
        phone_no:
        fprintf(stdout, "%s", "Enter phone number -> ");
        fgets(customer_details_ptr->phone_no->ph_no, MAX_PH_NO_LEN, stdin);
        if(sscanf(customer_details_ptr->phone_no->ph_no, "%s", customer_details_ptr->phone_no->ph_no) != 1){
            fprintf(stderr, "%s\n", "Wrong phone number format");
            // exit(0);
            // return -1;
            goto phone_no;
        }

        fprintf(stdout, "%s", "Enter amount -> Rs.");
        scanf("%lf", &customer_details_ptr->amount);
        getchar();

        deposit_date:
        fprintf(stdout, "%s", "Enter deposit date(DD/MM/YYYY) -> ");
        scanf("%s", customer_details_ptr->deposit_date);
        getchar();
        if(dateNotCorrectFormat(customer_details_ptr->deposit_date)){
            fprintf(stderr, "%s\n", "Wrong date format");
            goto deposit_date;
        }
        withdraw_date:
        fprintf(stdout, "%s", "Enter withdraw date(DD/MM/YYYY) -> ");
        scanf("%s", customer_details_ptr->withdraw_date);
        getchar();
        if(dateNotCorrectFormat(customer_details_ptr->withdraw_date)){
            fprintf(stderr, "%s\n", "Wrong date format");
            goto withdraw_date;
        }

        char record[1024];
        sprintf(record, "%s %s %s %s ", customer_details_ptr->account_number, customer_details_ptr->account_type, 
                customer_details_ptr->first_name, customer_details_ptr->last_name);
        sprintf(record+strlen(record), "%s %s %s ", customer_details_ptr->dob, customer_details_ptr->aadhar_no, customer_details_ptr->email_id);
        sprintf(record+strlen(record), "%s,%s,%s,%s,%s,%s.%s ", customer_details_ptr->address->apartment_no,
                customer_details_ptr->address->building, customer_details_ptr->address->colony,
                customer_details_ptr->address->city, customer_details_ptr->address->state,
                customer_details_ptr->address->country, customer_details_ptr->address->pin_code);
        sprintf(record+strlen(record), "%s-%s ", customer_details_ptr->phone_no->country_code, customer_details_ptr->phone_no->ph_no);
        sprintf(record+strlen(record), "%lf %s %s\n", customer_details_ptr->amount, 
                customer_details_ptr->deposit_date, customer_details_ptr->withdraw_date);
        fprintf(stdout, "%s\n", record);
        // fprintf(fd, "%s\t%s\t%s\t\t%s\t\t\t\t\t\t\t%s\t\t\t\t\t\t\t\t\t\t\t%s\n", "fname",
        //         "lname", "dob", "aadhar_no", "address", "ph_no");
        fprintf(fd, "%s", record);
        fclose(fd);
        fclose(fd1);
        if(temp_customer_details_ptr.address)
            free(temp_customer_details_ptr.address);
        if(temp_customer_details_ptr.phone_no)
            free(temp_customer_details_ptr.phone_no);
        check_customer_details_ptr.address = NULL;      //good practice to make them null to avoid unwanted access
        check_customer_details_ptr.phone_no = NULL;
        fprintf(stdout, "%s\n", "Account created successfully.");

        int choice;
        menu_exit_choice:
        fprintf(stdout, "%s\n", "Enter 1 to go to main menu or 0 to exit");
        scanf("%d", &choice);
        if(choice == exit_program){
            close_program();
        }
        else if(choice == main_menu){
            system("cls");
            menu();
        }
        else{
            fprintf(stderr, "%s -> %s\n", __func__, "Please enter a correct choice");
            goto menu_exit_choice;
        }
        return 1;
    }
}

int _edit(){
    FILE *fd, *update_fd;
    int found = 0, count = 1, menu_exit_choice;
    char record[1024];
    fd = fopen("customers.txt", "r");
    update_fd = fopen("temporary_file.txt", "w");
    if((fd==NULL || (update_fd==NULL))){
        fprintf(stderr, "%s %s\n", __func__, "Cannot open file");
        return -1;
    }
    customer_details_t temp_customer_details_ptr;
    temp_customer_details_ptr.address = malloc(sizeof(address_details_t));
    temp_customer_details_ptr.address = malloc(sizeof(address_details_t));
    memset(temp_customer_details_ptr.address, 0, sizeof(address_details_t));
    temp_customer_details_ptr.phone_no = malloc(sizeof(phone_number_t));
    memset(temp_customer_details_ptr.phone_no, 0, sizeof(phone_number_t));
    if((temp_customer_details_ptr.address==NULL) || (temp_customer_details_ptr.phone_no==NULL)){
        fprintf(stderr, "%s\n", "Failed to allocate memory to address struct or ph_no struct");
        return -1;
    }
    while(fscanf(fd, "%s %s %s %s %s %s %s %[^,],%[^,],%[^,],%[^,],%[^,],%[^.].%s %[^-]-%s %lf %s %s", temp_customer_details_ptr.account_number,
            temp_customer_details_ptr.account_type, temp_customer_details_ptr.first_name, temp_customer_details_ptr.last_name,
            temp_customer_details_ptr.dob, temp_customer_details_ptr.aadhar_no, temp_customer_details_ptr.email_id, 
            temp_customer_details_ptr.address->apartment_no, temp_customer_details_ptr.address->building,
            temp_customer_details_ptr.address->colony, temp_customer_details_ptr.address->city,
            temp_customer_details_ptr.address->state, temp_customer_details_ptr.address->country,
            temp_customer_details_ptr.address->pin_code, temp_customer_details_ptr.phone_no->country_code,
            temp_customer_details_ptr.phone_no->ph_no, &temp_customer_details_ptr.amount,
            temp_customer_details_ptr.deposit_date, temp_customer_details_ptr.withdraw_date) 
            != EOF)
            {
                if(strncmp(temp_customer_details_ptr.email_id, logged_in_user_email, strlen(logged_in_user_email)) == 0)
                {
                    found = 1;
                    fprintf(stdout, "%s\n\n", "Your previous details are :");
                    fprintf(stdout, "%s -> %s\n", "Account Number", temp_customer_details_ptr.account_number);
                    fprintf(stdout, "%s -> %s\n", "Account Type", temp_customer_details_ptr.account_type);
                    fprintf(stdout, "%s -> %s %s\n", "Name", temp_customer_details_ptr.first_name, temp_customer_details_ptr.last_name);
                    fprintf(stdout, "%s -> %s\n", "Date of Birth", temp_customer_details_ptr.dob);
                    fprintf(stdout, "%s -> %s\n", "Aadhar number", temp_customer_details_ptr.aadhar_no);
                    fprintf(stdout, "%s -> %s\n", "Email id", temp_customer_details_ptr.email_id);
                    fprintf(stdout, "%s -> %s, %s, %s, %s, %s, %s. %s\n", "Address",
                            temp_customer_details_ptr.address->apartment_no,
                            temp_customer_details_ptr.address->building, temp_customer_details_ptr.address->colony,
                            temp_customer_details_ptr.address->city, temp_customer_details_ptr.address->state,
                            temp_customer_details_ptr.address->country, temp_customer_details_ptr.address->pin_code);
                    fprintf(stdout, "%s -> +%s-%s\n", "Phone number", temp_customer_details_ptr.phone_no->country_code,
                            temp_customer_details_ptr.phone_no->ph_no);
                    fprintf(stdout, "%s -> %lf\n", "Amount", temp_customer_details_ptr.amount);
                    fprintf(stdout, "%s -> %s\n", "Deposit date", temp_customer_details_ptr.deposit_date);
                    fprintf(stdout, "%s -> %s\n\n", "Withdrawl date", temp_customer_details_ptr.withdraw_date);

                    fprintf(stdout, "%s\n\n", "Choose what you wish to edit :");
                    fprintf(stdout, "%s\n\n", "1. Address\n2. Phone number");
                    fprintf(stdout, "%s", "Please enter your choice -> ");
                    int choice;
                    choose:
                    scanf("%d", &choice);
                    getchar();
                    address_details_t address;
                    phone_number_t phone_no;
                    switch(choice){
                        case 1:
                            fprintf(stdout, "%s", "Enter new address details : \n");
                            apt_no:
                            fprintf(stdout, "%s", "Enter apartment number . ");
                            fgets(address.apartment_no, MAX_APARTMENT_NO_LEN, stdin);
                            if(sscanf(address.apartment_no, "%s", address.apartment_no) != 1){
                                fprintf(stderr, "%s\n", "Wrong apartment number format");
                                // exit(0);
                                // return -1;
                                goto apt_no;
                            }
                            building_name:
                            fprintf(stdout, "%s", "Enter building name . ");
                            fgets(address.building, MAX_BUILDING_LEN, stdin);
                            if(sscanf(address.building, "%[^\n]s", address.building) != 1){
                                fprintf(stderr, "%s\n", "Wrong building name format");
                                // exit(0);
                                // return -1;
                                goto building_name;
                            }
                            colony_name:
                            fprintf(stdout, "%s", "Enter colony name . ");
                            fgets(address.colony, MAX_COLONY_LEN, stdin);
                            if(sscanf(address.colony, "%[^\n]s", address.colony) != 1){
                                fprintf(stderr, "%s\n", "Wrong colony name format");
                                // exit(0);
                                // return -1;
                                goto colony_name;
                            }
                            city_name:
                            fprintf(stdout, "%s", "Enter city name . ");
                            fgets(address.city, MAX_CITY_LEN, stdin);
                            if(sscanf(address.city, "%[^\n]s", address.city) != 1){
                                fprintf(stderr, "%s\n", "Wrong city name format");
                                // exit(0);
                                // return -1;
                                goto city_name;
                            }
                            state_name:
                            fprintf(stdout, "%s", "Enter state name . ");
                            fgets(address.state, MAX_STATE_LEN, stdin);
                            if(sscanf(address.state, "%[^\n]s", address.state) != 1){
                                fprintf(stderr, "%s\n", "Wrong state name format");
                                // exit(0);
                                // return -1;
                                goto state_name;
                            }
                            country_name:
                            fprintf(stdout, "%s", "Enter country name . ");
                            fgets(address.country, MAX_COUNTRY_LEN, stdin);
                            if(sscanf(address.country, "%[^\n]s", address.country) != 1){
                                fprintf(stderr, "%s\n", "Wrong country name format");
                                // exit(0);
                                // return -1;
                                goto country_name;
                            }
                            pincode:
                            fprintf(stdout, "%s", "Enter pincode . ");
                            fgets(address.pin_code, MAX_PINCODE_LEN, stdin);
                            if(sscanf(address.pin_code, "%s", address.pin_code) != 1){
                                fprintf(stderr, "%s\n", "Wrong pincode format");
                                // exit(0);
                                // return -1;
                                goto pincode;
                            }
                            break;
                        case 2:
                            fprintf(stdout, "%s", "Enter new phone number details : \n");
                            country_code:
                            fprintf(stdout, "%s", "Enter country code -> ");
                            fgets(phone_no.country_code, MAX_COUNTRY_CODE_LEN, stdin);
                            if(sscanf(phone_no.country_code, "%s", phone_no.country_code) != 1){
                                fprintf(stderr, "%s\n", "Wrong country code format");
                                // exit(0);
                                // return -1;
                                goto country_code;
                            }
                            phone_no:
                            fprintf(stdout, "%s", "Enter phone number -> ");
                            fgets(phone_no.ph_no, MAX_PH_NO_LEN, stdin);
                            if(sscanf(phone_no.ph_no, "%s", phone_no.ph_no) != 1){
                                fprintf(stderr, "%s\n", "Wrong phone number format");
                                // exit(0);
                                // return -1;
                                goto phone_no;
                            }
                            break;
                        default:
                            fprintf(stdout, "%s\n", "Please enter a valid choice");
                            goto choose;
                            break; 
                    }
                    // char record[1024];
                    memset(record, 0, sizeof(record));
                    if(choice == 1){
                        sprintf(record, "%s %s %s %s ", temp_customer_details_ptr.account_number, temp_customer_details_ptr.account_type, 
                            temp_customer_details_ptr.first_name, temp_customer_details_ptr.last_name);
                        sprintf(record+strlen(record), "%s %s %s ", temp_customer_details_ptr.dob, temp_customer_details_ptr.aadhar_no, temp_customer_details_ptr.email_id);
                        sprintf(record+strlen(record), "%s,%s,%s,%s,%s,%s.%s ", address.apartment_no, address.building, address.colony,
                                address.city, address.state, address.country, address.pin_code);
                        sprintf(record+strlen(record), "%s-%s ", temp_customer_details_ptr.phone_no->country_code, temp_customer_details_ptr.phone_no->ph_no);
                        sprintf(record+strlen(record), "%lf %s %s\n", temp_customer_details_ptr.amount, 
                                temp_customer_details_ptr.deposit_date, temp_customer_details_ptr.withdraw_date);
                        fprintf(stdout, "%s\n", record);
                        // fprintf(fd, "%s\t%s\t%s\t\t%s\t\t\t\t\t\t\t%s\t\t\t\t\t\t\t\t\t\t\t%s\n", "fname",
                        //         "lname", "dob", "aadhar_no", "address", "ph_no");
                        fprintf(update_fd, "%s", record);
                    }
                    else if(choice == 2){
                        sprintf(record, "%s %s %s %s ", temp_customer_details_ptr.account_number, temp_customer_details_ptr.account_type, 
                                temp_customer_details_ptr.first_name, temp_customer_details_ptr.last_name);
                        sprintf(record+strlen(record), "%s %s %s ", temp_customer_details_ptr.dob, temp_customer_details_ptr.aadhar_no, temp_customer_details_ptr.email_id);
                        sprintf(record+strlen(record), "%s,%s,%s,%s,%s,%s.%s ", temp_customer_details_ptr.address->apartment_no,
                                temp_customer_details_ptr.address->building, temp_customer_details_ptr.address->colony,
                                temp_customer_details_ptr.address->city, temp_customer_details_ptr.address->state,
                                temp_customer_details_ptr.address->country, temp_customer_details_ptr.address->pin_code);
                        sprintf(record+strlen(record), "%s-%s ", phone_no.country_code, phone_no.ph_no);
                        sprintf(record+strlen(record), "%lf %s %s\n", temp_customer_details_ptr.amount, 
                                temp_customer_details_ptr.deposit_date, temp_customer_details_ptr.withdraw_date);
                        fprintf(stdout, "%s\n", record);
                        // fprintf(fd, "%s\t%s\t%s\t\t%s\t\t\t\t\t\t\t%s\t\t\t\t\t\t\t\t\t\t\t%s\n", "fname",
                        //         "lname", "dob", "aadhar_no", "address", "ph_no");
                        fprintf(update_fd, "%s", record);
                    } 
                }
                else{
                    memset(record, 0, sizeof(record));
                    sprintf(record, "%s %s %s %s ", temp_customer_details_ptr.account_number, temp_customer_details_ptr.account_type, 
                            temp_customer_details_ptr.first_name, temp_customer_details_ptr.last_name);
                    sprintf(record+strlen(record), "%s %s %s ", temp_customer_details_ptr.dob, temp_customer_details_ptr.aadhar_no, temp_customer_details_ptr.email_id);
                    sprintf(record+strlen(record), "%s,%s,%s,%s,%s,%s.%s ", temp_customer_details_ptr.address->apartment_no,
                            temp_customer_details_ptr.address->building, temp_customer_details_ptr.address->colony,
                            temp_customer_details_ptr.address->city, temp_customer_details_ptr.address->state,
                            temp_customer_details_ptr.address->country, temp_customer_details_ptr.address->pin_code);
                    sprintf(record+strlen(record), "%s-%s ", temp_customer_details_ptr.phone_no->country_code, temp_customer_details_ptr.phone_no->ph_no);
                    sprintf(record+strlen(record), "%lf %s %s\n", temp_customer_details_ptr.amount, 
                            temp_customer_details_ptr.deposit_date, temp_customer_details_ptr.withdraw_date);
                    fprintf(stdout, "%s\n", record);
                    // fprintf(fd, "%s\t%s\t%s\t\t%s\t\t\t\t\t\t\t%s\t\t\t\t\t\t\t\t\t\t\t%s\n", "fname",
                    //         "lname", "dob", "aadhar_no", "address", "ph_no");
                    fprintf(update_fd, "%s", record);
                }
            }
            if(found == 0){
                fprintf(stderr, "\n%s -> %s\n\n", __func__, "no record found."\
                        "Please add account details");
                int menu_exit_choice;
                menu_exit_choice:
                fprintf(stdout, "%s\n", "Enter 1 to go to main menu or 0 to exit");
                scanf("%d", &menu_exit_choice);
                if(menu_exit_choice == exit_program){
                    close_program();
                }
                else if(menu_exit_choice == main_menu){
                    system("cls");
                    menu();
                }
                else{
                    fprintf(stderr, "%s -> %s\n", __func__, "Please enter a correct choice");
                    goto menu_exit_choice;
                }
            }
            //system("cls");
            fprintf(stdout, "\n%s\n", "Record updated!!!");
            fclose(fd);
            fclose(update_fd);
            if(temp_customer_details_ptr.address)
                free(temp_customer_details_ptr.address);
            if(temp_customer_details_ptr.phone_no)
                free(temp_customer_details_ptr.phone_no);
            temp_customer_details_ptr.address = NULL;
            temp_customer_details_ptr.phone_no = NULL;

            remove("customers.txt");
            rename("temporary_file.txt", "customers.txt");
            
            fprintf(stdout, "%s\n", "Enter 1 to go to main menu or 0 to logout");
            scanf("%d", &menu_exit_choice);
            getchar();
            if(menu_exit_choice == exit_program){
                close_program();
            }
            else if(menu_exit_choice == main_menu){
                system("cls");
                menu();
            }
            else{
                fprintf(stderr, "%s -> %s\n", __func__, "Please enter a correct choice");
                goto menu_exit_choice;
            }
            return 1;
}

int _transact(void){
    FILE *fd, *update_fd;
    int found = 0, count = 1, menu_exit_choice;
    double amount;
    char record[1024];
    fd = fopen("customers.txt", "r");
    update_fd = fopen("temporary_file.txt", "w");
    if((fd==NULL || (update_fd==NULL))){
        fprintf(stderr, "%s %s\n", __func__, "Cannot open file");
        return -1;
    }
    customer_details_t temp_customer_details_ptr;
    temp_customer_details_ptr.address = malloc(sizeof(address_details_t));
    temp_customer_details_ptr.address = malloc(sizeof(address_details_t));
    memset(temp_customer_details_ptr.address, 0, sizeof(address_details_t));
    temp_customer_details_ptr.phone_no = malloc(sizeof(phone_number_t));
    memset(temp_customer_details_ptr.phone_no, 0, sizeof(phone_number_t));
    if((temp_customer_details_ptr.address==NULL) || (temp_customer_details_ptr.phone_no==NULL)){
        fprintf(stderr, "%s\n", "Failed to allocate memory to address struct or ph_no struct");
        return -1;
    }
    while(fscanf(fd, "%s %s %s %s %s %s %s %[^,],%[^,],%[^,],%[^,],%[^,],%[^.].%s %[^-]-%s %lf %s %s", temp_customer_details_ptr.account_number,
            temp_customer_details_ptr.account_type, temp_customer_details_ptr.first_name, temp_customer_details_ptr.last_name,
            temp_customer_details_ptr.dob, temp_customer_details_ptr.aadhar_no, temp_customer_details_ptr.email_id, 
            temp_customer_details_ptr.address->apartment_no, temp_customer_details_ptr.address->building,
            temp_customer_details_ptr.address->colony, temp_customer_details_ptr.address->city,
            temp_customer_details_ptr.address->state, temp_customer_details_ptr.address->country,
            temp_customer_details_ptr.address->pin_code, temp_customer_details_ptr.phone_no->country_code,
            temp_customer_details_ptr.phone_no->ph_no, &temp_customer_details_ptr.amount,
            temp_customer_details_ptr.deposit_date, temp_customer_details_ptr.withdraw_date) 
            != EOF)
            {
                if(strncmp(temp_customer_details_ptr.email_id, logged_in_user_email, strlen(logged_in_user_email)) == 0){
                    // if(strncmp(temp_customer_details_ptr.account_type, "fixed1", strlen("fixed1"))==0 ||
                    // strncmp(temp_customer_details_ptr.account_type, "fixed2", strlen("fixed2"))==0 ||
                    // strncmp(temp_customer_details_ptr.account_type, "fixed3", strlen("fixed3"))==0)
                    // {
                    //     printf("\a\a\a\n\nYOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!");
                    //     system("cls");
                    //     menu();
                    // }
                    found = 1;
                    int choice;
                    system("cls");
                    fprintf(stdout, "%s\n", "\nDo you want to\n1.Deposit\n2.Withdraw"\
                                            "\n\nEnter your choice :");
                    scanf("%d",&choice);
                    if (choice==1)
                    {
                        printf("Enter the amount you want to deposit: ");
                        scanf("%lf",&amount);
                        getchar();
                        temp_customer_details_ptr.amount += amount;
                        fprintf(stdout, "%s\n""\n\nDeposited successfully!");
                    }
                    else
                    {
                        printf("Enter the amount you want to withdraw: ");
                        scanf("%lf",&amount);
                        getchar();
                        temp_customer_details_ptr.amount -= amount;
                        fprintf(stdout, "%s\n""\n\nWithdrawn successfully!");
                    }
                }
                memset(record, 0, sizeof(record));
                sprintf(record, "%s %s %s %s ", temp_customer_details_ptr.account_number, temp_customer_details_ptr.account_type, 
                            temp_customer_details_ptr.first_name, temp_customer_details_ptr.last_name);
                sprintf(record+strlen(record), "%s %s %s ", temp_customer_details_ptr.dob, temp_customer_details_ptr.aadhar_no, temp_customer_details_ptr.email_id);
                sprintf(record+strlen(record), "%s,%s,%s,%s,%s,%s.%s ", temp_customer_details_ptr.address->apartment_no,
                            temp_customer_details_ptr.address->building, temp_customer_details_ptr.address->colony,
                            temp_customer_details_ptr.address->city, temp_customer_details_ptr.address->state,
                            temp_customer_details_ptr.address->country, temp_customer_details_ptr.address->pin_code);
                sprintf(record+strlen(record), "%s-%s ", temp_customer_details_ptr.phone_no->country_code, temp_customer_details_ptr.phone_no->ph_no);
                sprintf(record+strlen(record), "%lf %s %s\n", temp_customer_details_ptr.amount, 
                            temp_customer_details_ptr.deposit_date, temp_customer_details_ptr.withdraw_date);
                fprintf(stdout, "%s\n", record);
                // fprintf(fd, "%s\t%s\t%s\t\t%s\t\t\t\t\t\t\t%s\t\t\t\t\t\t\t\t\t\t\t%s\n", "fname",
                //         "lname", "dob", "aadhar_no", "address", "ph_no");
                fprintf(update_fd, "%s", record);
            }

            if(found == 0){
                fprintf(stderr, "\n%s -> %s\n\n", __func__, "no record found."\
                        "Please add account details");
                int menu_exit_choice;
                menu_exit_choice:
                fprintf(stdout, "%s\n", "Enter 1 to go to main menu or 0 to exit");
                scanf("%d", &menu_exit_choice);
                if(menu_exit_choice == exit_program){
                    close_program();
                }
                else if(menu_exit_choice == main_menu){
                    system("cls");
                    menu();
                }
                else{
                    fprintf(stderr, "%s -> %s\n", __func__, "Please enter a correct choice");
                    goto menu_exit_choice;
                }
            }

            fclose(fd);
            fclose(update_fd);
            if(temp_customer_details_ptr.address)
                free(temp_customer_details_ptr.address);
            if(temp_customer_details_ptr.phone_no)
                free(temp_customer_details_ptr.phone_no);
            temp_customer_details_ptr.address = NULL;
            temp_customer_details_ptr.phone_no = NULL;

            remove("customers.txt");
            rename("temporary_file.txt", "customers.txt");
            
            menu_exit_choice:
            fprintf(stdout, "%s\n", "Enter 1 to go to main menu or 0 to logout");
            scanf("%d", &menu_exit_choice);
            if(menu_exit_choice == exit_program){
                close_program();
            }
            else if(menu_exit_choice == main_menu){
                system("cls");
                menu();
            }
            else{
                fprintf(stderr, "%s -> %s\n", __func__, "Please enter a correct choice");
                goto menu_exit_choice;
            }
            return 1;
}

int _viewCustomerDetails(){
    int count=1, menu_exit_choice;
    FILE *fd;
    fd = fopen("customers.txt", "r");
    if(fd == NULL){
        fprintf(stderr, "%s %s\n", __func__, "Cannot open file");
        return -1;
    }
    customer_details_t temp_customer_details_ptr;
    temp_customer_details_ptr.address = malloc(sizeof(address_details_t));
    memset(temp_customer_details_ptr.address, 0, sizeof(address_details_t));
    temp_customer_details_ptr.phone_no = malloc(sizeof(phone_number_t));
    memset(temp_customer_details_ptr.phone_no, 0, sizeof(phone_number_t));
    if((temp_customer_details_ptr.address==NULL) || (temp_customer_details_ptr.phone_no==NULL)){
        fprintf(stderr, "%s\n", "Failed to allocate memory to address struct or ph_no struct");
        return -1;
    }
    fprintf(stdout, "%s\n", "\nCustomer Details are :");
    while(fscanf(fd, "%s %s %s %s %s %s %s %[^,],%[^,],%[^,],%[^,],%[^,],%[^.].%s %[^-]-%s %lf %s %s", temp_customer_details_ptr.account_number,
            temp_customer_details_ptr.account_type, temp_customer_details_ptr.first_name, temp_customer_details_ptr.last_name,
            temp_customer_details_ptr.dob, temp_customer_details_ptr.aadhar_no, temp_customer_details_ptr.email_id, 
            temp_customer_details_ptr.address->apartment_no, temp_customer_details_ptr.address->building,
            temp_customer_details_ptr.address->colony, temp_customer_details_ptr.address->city,
            temp_customer_details_ptr.address->state, temp_customer_details_ptr.address->country,
            temp_customer_details_ptr.address->pin_code, temp_customer_details_ptr.phone_no->country_code,
            temp_customer_details_ptr.phone_no->ph_no, &temp_customer_details_ptr.amount,
            temp_customer_details_ptr.deposit_date, temp_customer_details_ptr.withdraw_date) 
            != EOF){
            if(strncmp(logged_in_user_email, "admin", strlen(logged_in_user_email)) == 0){
                fprintf(stdout, "%d) %s -> %s\n", count++, "Account Number", temp_customer_details_ptr.account_number);
                fprintf(stdout, "%s -> %s\n", "Account Type", temp_customer_details_ptr.account_type);
                fprintf(stdout, "%s -> %s %s\n", "Name", temp_customer_details_ptr.first_name, temp_customer_details_ptr.last_name);
                fprintf(stdout, "%s -> %s\n", "Date of Birth", temp_customer_details_ptr.dob);
                fprintf(stdout, "%s -> %s\n", "Aadhar number", temp_customer_details_ptr.aadhar_no);
                fprintf(stdout, "%s -> %s\n", "Email id", temp_customer_details_ptr.email_id);
                fprintf(stdout, "%s -> %s, %s, %s, %s, %s, %s. %s\n", "Address",
                        temp_customer_details_ptr.address->apartment_no,
                        temp_customer_details_ptr.address->building, temp_customer_details_ptr.address->colony,
                        temp_customer_details_ptr.address->city, temp_customer_details_ptr.address->state,
                        temp_customer_details_ptr.address->country, temp_customer_details_ptr.address->pin_code);
                fprintf(stdout, "%s -> +%s-%s\n", "Phone number", temp_customer_details_ptr.phone_no->country_code,
                        temp_customer_details_ptr.phone_no->ph_no);
                fprintf(stdout, "%s -> %lf\n", "Amount", temp_customer_details_ptr.amount);
                fprintf(stdout, "%s -> %s\n", "Deposit date", temp_customer_details_ptr.deposit_date);
                fprintf(stdout, "%s -> %s\n\n", "Withdrawl date", temp_customer_details_ptr.withdraw_date);
            }    
            else{
                if(strncmp(temp_customer_details_ptr.email_id, logged_in_user_email,
                    strlen(logged_in_user_email)) == 0){
                        fprintf(stdout, "%d) %s -> %s\n", count++, "Account Number", temp_customer_details_ptr.account_number);
                        fprintf(stdout, "%s -> %s\n", "Account Type", temp_customer_details_ptr.account_type);
                        fprintf(stdout, "%s -> %s %s\n", "Name", temp_customer_details_ptr.first_name, temp_customer_details_ptr.last_name);
                        fprintf(stdout, "%s -> %s\n", "Date of Birth", temp_customer_details_ptr.dob);
                        fprintf(stdout, "%s -> %s\n", "Aadhar number", temp_customer_details_ptr.aadhar_no);
                        fprintf(stdout, "%s -> %s\n", "Email id", temp_customer_details_ptr.email_id);
                        fprintf(stdout, "%s -> %s, %s, %s, %s, %s, %s. %s\n", "Address", temp_customer_details_ptr.address->apartment_no,
                                temp_customer_details_ptr.address->building, temp_customer_details_ptr.address->colony,
                                temp_customer_details_ptr.address->city, temp_customer_details_ptr.address->state,
                                temp_customer_details_ptr.address->country, temp_customer_details_ptr.address->pin_code);
                        fprintf(stdout, "%s -> +%s-%s\n", "Phone number", temp_customer_details_ptr.phone_no->country_code,
                                temp_customer_details_ptr.phone_no->ph_no);
                        fprintf(stdout, "%s -> %lf\n", "Amount", temp_customer_details_ptr.amount);
                        fprintf(stdout, "%s -> %s\n", "Deposit date", temp_customer_details_ptr.deposit_date);
                        fprintf(stdout, "%s -> %s\n\n", "Withdrawl date", temp_customer_details_ptr.withdraw_date);
                        break;
                    }
            }               
    }
    if(count-1 == 0){
        system("cls");
        fprintf(stderr, "%s -> %s\n", __func__, "No records found");
    }
    else{
        fprintf(stdout, "%s -> %d %s\n\n", __func__, count-1, "records found");
    }
    menu_exit_choice:
    fprintf(stdout, "%s\n", "Enter 1 to go to main menu or 0 to logout");
    scanf("%d", &menu_exit_choice);
    if(menu_exit_choice == exit_program){
        close_program();
    }
    else if(menu_exit_choice == main_menu){
        system("cls");
        menu();
    }
    else{
        fprintf(stderr, "%s -> %s\n", __func__, "Please enter a correct choice");
        goto menu_exit_choice;
    }
    if(temp_customer_details_ptr.address)
        free(temp_customer_details_ptr.address);
    if(temp_customer_details_ptr.phone_no)
        free(temp_customer_details_ptr.phone_no);
    temp_customer_details_ptr.address = NULL;
    temp_customer_details_ptr.phone_no = NULL;
    return 1;
}

void login_register(void){
    //system("cls");
    int choice=0, error=0;
    fprintf(stdout, "%s\n", "Welcome to the login/signup menu");
    login_signup:
    fprintf(stdout, "%s\n", "1. Login\n2. Register\n-1. Exit");
    fprintf(stdout, "%s -> ", "Enter you choice");
    scanf("%d", &choice);
    getchar();
    switch(choice){
        case 1:
            if(login() == -1){
                error = 1;
                fprintf(stderr, "%s -> %s\n", __func__, "Failed to login");
                break;
            }
            break;
        case 2:
            if(register_user() == -1){
                error = 1;
                fprintf(stderr, "%s -> %s\n", __func__, "Failed to register");
                break;
            }    
            break;
        case -1:
            close_program();
            break;    
        default:
            fprintf(stderr, "%s -> %s\n", __func__, "Choice not supported");
            goto login_signup;
            break;
    }               
}

int login(void){
    FILE *fd, *fd1;
    fd = fopen("login_data.txt", "r+");
    //fd1 = fopen("login_data.txt", "r");
    if((fd==NULL) || (fd1==NULL)){
        fprintf(stderr, "%s %s\n", __func__, "Cannot open file");
        return -1;
    }
    user_credentials_t temp_user, check_user;
    char first_name[MAX_FNAME_LEN], last_name[MAX_LNAME_LEN], ascii_password[MAX_PASSWORD_LEN], hex_password[2*MAX_PASSWORD_LEN];
    int count, found=0;
    system("cls");
    fprintf(stdout, "%s\n\n", "User Login");
    //system("color 02");
    login:
        memset(temp_user.email, 0, MAX_EMAIL_LEN);
        memset(temp_user.password, 0, MAX_PASSWORD_LEN);
        memset(check_user.email, 0, MAX_EMAIL_LEN);
        memset(check_user.password, 0, MAX_PASSWORD_LEN);
        count=0; 
        email:
        fprintf(stdout, "%s\n", "Enter your email -> ");
        fgets(temp_user.email, MAX_EMAIL_LEN, stdin);
        if((sscanf(temp_user.email, "%s", temp_user.email)!=1) ){  //|| isNotValidEmailType()
            fprintf(stderr, "%s -> %s\n", __func__, "Please enter the email in correct format");
            goto email;
        }
        password:
        fprintf(stdout, "%s\n", "Enter your password -> ");
        fgets(temp_user.password, MAX_PASSWORD_LEN, stdin);
        if(sscanf(temp_user.password, "%s", temp_user.password)!=1){
            fprintf(stderr, "%s -> %s\n", __func__, "Do not use spaces in password");
            goto password;
        }
        while(fscanf(fd, "%s %s %s %s", first_name, last_name, check_user.email, hex_password) != EOF){
            count++;
            char* temp_ascii_password = hexToAscii(hex_password, strlen(hex_password));
            // fprintf(stdout, "\n%s   fname -> %s,  lname -> %s,  email -> %s, password -> %s\n\n", __func__, first_name, last_name,
            //         check_user.email, temp_ascii_password);
            if((strncmp(temp_user.email, check_user.email, strlen(check_user.email))==0) && 
                (strncmp(temp_user.password, temp_ascii_password, strlen(temp_ascii_password))==0)){
                    found = 1;
                    strncpy(logged_in_user_email, temp_user.email, strlen(temp_user.email));
                    strncpy(logged_in_user_fname, first_name, strlen(first_name));
                    strncpy(logged_in_user_lname, last_name, strlen(last_name));
                    logged_in_user_email[strlen(logged_in_user_email)] = '\0';
                    logged_in_user_fname[strlen(logged_in_user_fname)] = '\0';
                    logged_in_user_lname[strlen(logged_in_user_lname)] = '\0';
                    fprintf(stdout, "%s", "Logging in.");
                    for(int i=0; i<3; i++){
                        printf(".");
                        delay(1);
                    }
                    system("cls");
                    fseek(fd, 0, SEEK_SET);
                    menu();
                    //return 1;
                }
            else if((strncmp(temp_user.email, check_user.email, strlen(check_user.email))==0)){
                if(strncmp(temp_user.password, temp_ascii_password, strlen(temp_ascii_password))!=0){          //check for invalid password
                    found = 1;
                    system("cls");
                    fprintf(stderr, "%s\n", "Password is invalid");
                    fseek(fd, 0, SEEK_SET);         //to enable multiple login attempts
                    goto login;
                    //break;
                }
            }      
        }
        if(!found){
            system("cls");
            fprintf(stderr, "%s\n", "Email doesn't exist. Please register");
            fseek(fd, 0, SEEK_SET);
            login_register();
        } 
        if(count == 0){
            system("cls");
            fprintf(stderr, "%s\n", "Email doesn't exist. Please register");
            login_register();
        }
    fclose(fd);
    //fclose(fd1);    
    return 1;
}

void menu(void){
    // system("cls");
    //system("color 09");
    int choice=0, error=0;
    fprintf(stdout, "%s\n", "Customer Account Bank Management System");
    if(strncmp(logged_in_user_email, "admin", strlen("admin")) == 0){
        fprintf(stdout, "\n%s %s\n\n", "Welcome", logged_in_user_email);
    }
    else{
        fprintf(stdout, "\n%s %s %s\n\n", "Welcome", logged_in_user_fname, logged_in_user_lname);
    }
    menu:
    fprintf(stdout, "%s\n", "1. Create new account\n2. Update account information\n3. Deposit/Withdraw\n4. Account details\n"\
                            "5. Remove account\n6. View customers list\n-1. Logout");
    fprintf(stdout, "%s -> ", "Enter your choice");
    scanf("%d", &choice);
    getchar();
    switch(choice){
        case 1:
            if(_createNewAccount() == -1){
                error = 1;
                fprintf(stderr, "%s -> %s\n", __func__, "Failed to create new account");
                break;
            }
            break;
        case 2:
            if(_edit() == -1){
                error = 1;
                fprintf(stderr, "%s -> %s\n", __func__, "Failed to edit account");
                break;
            }
            break; 
        case 3:
            if(_transact() == -1){
                error = 1;
                fprintf(stderr, "%s -> %s\n", __func__, "Failed to edit account");
                break;
            }
            break;      
        case 6:
            if(_viewCustomerDetails() == -1){
                error = 1;
                fprintf(stderr, "%s -> %s\n", __func__, "Failed to view account details");
                break;
            }    
            break;
        case -1:
            fprintf(stdout, "%s", "Logging out.");
            for(int i=0; i<3; i++){
                printf(".");
                delay(1);
            }
            system("cls");
            login_register();
            break;
        default:
            fprintf(stderr, "%s -> %s\n", __func__, "Choice not supported"); 
            goto menu;
            break;   
    }                            
}

int register_user(void){
    FILE *fd;
    fd = fopen("login_data.txt", "a+");
    if(fd == NULL){
        fprintf(stderr, "%s %s\n", __func__, "Cannot open file");
        return -1;
    }
    user_credentials_t temp_user;
    char first_name[MAX_FNAME_LEN], last_name[MAX_LNAME_LEN], record[128], hex_password[2*MAX_PASSWORD_LEN];
    system("cls");
    fprintf(stdout, "%s\n\n", "User Registration");
    fname:
    fprintf(stdout, "%s\n", "Enter your first name -> ");
    fgets(first_name, MAX_FNAME_LEN, stdin);
    if(sscanf(first_name, "%s", first_name)!=1){
        fprintf(stderr, "%s -> %s\n", __func__, "Wrong first name format");
        goto fname;
    }
    lname:
    fprintf(stdout, "%s\n", "Enter your last name -> ");
    fgets(last_name, MAX_LNAME_LEN, stdin);
    if(sscanf(last_name, "%s", last_name)!=1){
        fprintf(stderr, "%s -> %s\n", __func__, "Wrong last name format");
        goto lname;
    }
    email:
    fprintf(stdout, "%s\n", "Enter your email -> ");
    fgets(temp_user.email, MAX_EMAIL_LEN, stdin);
    if((sscanf(temp_user.email, "%s", temp_user.email)!=1)){  // || isNotValidEmailType()
        fprintf(stderr, "%s -> %s\n", __func__, "Please enter the email in correct format");
        goto email;
    }
    password:
    fprintf(stdout, "%s\n", "Enter your password -> ");
    fgets(temp_user.password, MAX_PASSWORD_LEN, stdin);
    if(sscanf(temp_user.password, "%s", temp_user.password)!=1){
        fprintf(stderr, "%s -> %s\n", __func__, "Do not use spaces in password");
        goto password;
    }
    char* temp_hex_str = asciiToHex(temp_user.password, strlen(temp_user.password));
    int len_temp_hex_str = strlen(temp_hex_str);
    strncpy(hex_password, temp_hex_str, len_temp_hex_str);
    hex_password[len_temp_hex_str] = '\0';      //either directly use temp_hex_str;=
    sprintf(record, "%s %s %s %s\n", first_name, last_name, temp_user.email, hex_password);
    fprintf(stdout, "%s\n", record);
    fprintf(fd, "%s", record);
    fclose(fd);
    system("cls");
    fprintf(stdout, "%s\n", "User registered successfully");
    system("cls");
    login_register();
    return 1;
}

void close_program(void){
    system("cls");
    fprintf(stdout, "%s\n", "-/-/-/-/-/-Thank you for using the Bank Management System-/-/-/-/-/-");
}

int main(int argc, char const *argv[])
{
    //_createNewAccount();
    // _viewCustomerDetails();
    system("cls");
    login_register();
    //register_user();
    // login();
    return 0;
}
