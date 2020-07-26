#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum{
    INT = 1,
    FLOAT,
    DOUBLE,
    CHAR_PTR
}vartype;

typedef struct hash{
    //char *key;
    void *key;
    int value;
}hash_t;

typedef enum{
    a = 1,
    b,
    c,
    d,
    e
}values;

typedef struct dictionary
{
    /* data */
    hash_t *dict;
    int (*get_value_for_int)(struct dictionary*, int, int);
    int (*get_value_for_double)(struct dictionary*, double, int);
    int (*get_value_for_char_ptr)(struct dictionary*, char*, int);
}DICTIONARY;

int _get_value_for_int(DICTIONARY *this , int key, int SIZE){
    int found = 0, value;
    for(int i=0; i<SIZE; i++){
        if(*(int*)this->dict[i].key == key){
            found = 1;
            value = this->dict[i].value;
            printf("Found!!!\n");
            printf("key -> %d, value = %d\n", key, this->dict[i].value);
            break;
        }
    }
    if(found == 1){
        return value;
    }
    else
    {
        printf("Key not Found!!!\n");
        return -1;
    }
    
}

int _get_value_for_double(DICTIONARY *this , double key, int SIZE){
    int found = 0, value;
    for(int i=0; i<SIZE; i++){
        if(*(double*)this->dict[i].key == key){
            found = 1;
            value = this->dict[i].value;
            printf("Found!!!\n");
            printf("key -> %f, value = %d\n", key, this->dict[i].value);
            break;
        }
    }
    if(found == 1){
        return value;
    }
    else
    {
        printf("Key not Found!!!\n\n");
        return -1;
    }
    
}

int _get_value_for_char_ptr(DICTIONARY *this , char *key, int SIZE){
    int found = 0, value;
    for(int i=0; i<SIZE; i++){
        if(this->dict[i].key == key){
            found = 1;
            value = this->dict[i].value;
            printf("Found!!!\n");
            printf("key -> %s, value = %d\n", key, this->dict[i].value);
            break;
        }
    }
    if(found == 1){
        return value;
    }
    else
    {
        printf("Key not Found!!!\n\n");
        return -1;
    }
    
}

int get_value(DICTIONARY *this , void *key, vartype type, int SIZE){
    int val;
    switch (type)
    {
    case INT:
        printf("Encountered INT data\n");
        val = this->get_value_for_int(this, *(int*)key, SIZE);
        break;
    case DOUBLE:
        printf("Encountered DOUBLE data\n");
        val = this->get_value_for_double(this, *(double*)key, SIZE);
        break;
    case CHAR_PTR:
        printf("Encountered CHAR* data\n");
        val = this->get_value_for_char_ptr(this, (char*)key, SIZE);
        break;
    default:
        printf("Unknown data type provided.\n");
        break;
    }
    return val;
}

hash_t dict[] = {
    {"a", a},
    {"b", b},
    {"c", c},
    {"d", d},
    {"e", e}
};

int x1 = 11, x2 = 12, x3 = 13, x4 = 14, x5 = 15;

hash_t dict1[] = {
    {(void *)&x1, a},
    {(void *)&x2, b},
    {(void *)&x3, c},
    {(void *)&x4, d},
    {(void *)&x5, e}
};

DICTIONARY v_table = {dict, _get_value_for_int, _get_value_for_double, _get_value_for_char_ptr};
DICTIONARY v_table1 = {dict1, _get_value_for_int, _get_value_for_double, _get_value_for_char_ptr};

int main()
{
    for(int i=0; i<5; i++){
        printf("key is -> %s, value is -> %d\n", (char*)dict[i].key, dict[i].value);
    }
    //printf("size of table is %d", sizeof(dict)/sizeof(hash_t));
    int SIZE = sizeof(dict) / sizeof(hash_t);
    int SIZE1 = sizeof(dict1) / sizeof(hash_t);
    //int val = v_table.get_value_for_char_ptr(&v_table, "f", SIZE);
    int val = get_value(&v_table, "c", CHAR_PTR, SIZE);
    int key = 16;                       //key to be searched
    int val1 = get_value(&v_table1, (void*)&key, INT, SIZE1);
    return 0;
}
/* using dynamic memory

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct hash{
    char key;
    int value;
}hash_t;

typedef enum{
    a = 1,
    b,
    c,
    d,
    e
}values;
int main()
{
    hash_t **hash_arr = (hash_t**)malloc(5 * sizeof(hash_t*));
    char *str = "abcde";
    for(int i=0,val=a; i<5,val<=e; i++,val++){
        hash_t *hash_ptr = (hash_t*)malloc(sizeof(hash_t));
        hash_ptr->key = str[i];
        hash_ptr->value = val;
        hash_arr[i] = hash_ptr;
    }

    for(int i=0; i<5; i++){
        printf("key is -> %c, value is -> %d\n", hash_arr[i]->key, hash_arr[i]->value);
    }

    return 0;
}


*/