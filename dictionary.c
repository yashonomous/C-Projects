#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE_LEN 15
typedef unsigned int uint32;

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

#define MEMSET(array, value, length) ({ \
    int tmp = length;                   \
    while (tmp--)                       \
    {                                   \
        array[tmp] = value;             \
    }                                   \
})

typedef struct
{
    int key;
    char *value;
} dictionary_node;

typedef enum
{
    DICT_UNSORTED = 0,
    DICT_SORTED_ON_KEY,
    DICT_SORTED_ON_VALUE
} sort_type;

void getValueFromKey(sort_type type, dictionary_node *dictionary, int dictionary_size, int *key, char *value);
void getValueFromKeyUnsorted(dictionary_node *dictionary, int dictionary_size, int *key, char *value);
void getValueFromKeySorted(dictionary_node *dictionary, int dictionary_size, int *key, char *value);
void getKeyFromValue(sort_type type, dictionary_node *dictionary, int dictionary_size, char *value, int *key);
void getKeyFromValueUnsorted(dictionary_node *dictionary, int dictionary_size, char *value, int *key);
void getKeyFromValueSorted(dictionary_node *dictionary, int dictionary_size, char *value, int *key);

int copyString(char *dest, char *src, int destLen)
{
    int lenSrc = STRLEN(src);
    if (lenSrc >= destLen)
    {
        printf("%s\n", "src len is more than dest len\n");
        return -1;
    }
    char *tmp = dest;
    while (lenSrc-- && (*dest++ = *src++))
        ;
    *dest = '\0';
    dest = tmp;
    return 0;
}

int areEqual(char *str1, char *str2)
{
    return (str1[0] == '\0' && str2[0] == '\0') ? (0) : (str1[0] != str2[0]) ? (str1[0] - str2[0]) : areEqual(str1 + 1, str2 + 1);
}

void getValueFromKeyUnsorted(dictionary_node *dictionary, int dictionary_size, int *key, char *value)
{
    int found = 0, left = 0, right = dictionary_size - 1;
    while (left <= right)
    {
        if (dictionary[left].key == *key)
        {
            copyString(value, dictionary[left].value, MAX_VALUE_LEN);
            found = 1;
            break;
        }
        else if (dictionary[right].key == *key)
        {
            copyString(value, dictionary[right].value, MAX_VALUE_LEN);
            found = 1;
            break;
        }
        left++;
        right--;
    }
    if (!found)
        printf("Given key not found in the dictionary\n");
}

void getValueFromKeySorted(dictionary_node *dictionary, int dictionary_size, int *key, char *value)
{
    int found = 0, left = 0, middle = 0, right = dictionary_size - 1;

    //using binary search
    while (left <= right)
    {
        middle = (left + right) / 2;
        if (dictionary[middle].key == *key)
        {
            copyString(value, dictionary[middle].value, MAX_VALUE_LEN);
            found = 1;
            break;
        }
        else if (*key < dictionary[middle].key)
            right = middle - 1;
        else
            left = middle + 1;
    }
    if (!found)
        printf("Given key not found in the dictionary\n");
}

void getKeyFromValueUnsorted(dictionary_node *dictionary, int dictionary_size, char *value, int *key)
{
    int found = 0, left = 0, right = dictionary_size - 1;
    while (left <= right)
    {
        if (areEqual(dictionary[left].value, value) == 0)
        {
            *key = dictionary[left].key;
            found = 1;
            break;
        }
        else if (areEqual(dictionary[right].value, value) == 0)
        {
            *key = dictionary[right].key;
            found = 1;
            break;
        }
        left++;
        right--;
    }
    if (!found)
        printf("Given value not found in the dictionary\n");
}

void getKeyFromValueSorted(dictionary_node *dictionary, int dictionary_size, char *value, int *key)
{
    int found = 0, left = 0, middle = 0, right = dictionary_size - 1;

    //using binary search
    while (left <= right)
    {
        middle = (left + right) / 2;
        if (areEqual(dictionary[middle].value, value) == 0)
        {
            *key = dictionary[middle].key;
            found = 1;
            break;
        }
        else if (areEqual(dictionary[middle].value, value) > 0)
            right = middle - 1;
        else
            left = middle + 1;
    }
    if (!found)
        printf("Given key not found in the dictionary\n");
}

void getValueFromKey(sort_type type, dictionary_node *dictionary, int dictionary_size, int *key, char *value)
{
    if (dictionary == NULL)
    {
        printf("Dictionary supplied is null\n");
        return;
    }

    switch (type)
    {
    case DICT_UNSORTED:
        getValueFromKeyUnsorted(dictionary, dictionary_size, key, value);
        break;
    case DICT_SORTED_ON_KEY:
        getValueFromKeySorted(dictionary, dictionary_size, key, value);
        break;
    default:
        printf("Unsupported sort_type on dictionary\n");
        break;
    }
}

void getKeyFromValue(sort_type type, dictionary_node *dictionary, int dictionary_size, char *value, int *key)
{
    if (dictionary == NULL)
    {
        printf("Dictionary supplied is null\n");
        return;
    }

    switch (type)
    {
    case DICT_UNSORTED:
        getKeyFromValueUnsorted(dictionary, dictionary_size, value, key);
        break;
    case DICT_SORTED_ON_VALUE:
        getKeyFromValueSorted(dictionary, dictionary_size, value, key);
        break;
    default:
        printf("Unsupported sort_type on dictionary\n");
        break;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    dictionary_node dictionary[5] = {{1, "one"},
                                     {2, "two"},
                                     {3, "three"},
                                     {4, "four"},
                                     {5, "five"}};

    char *value = malloc(MAX_VALUE_LEN * sizeof(char));
    MEMSET(value, '\0', MAX_VALUE_LEN);
    int key = 3;

    getValueFromKey(DICT_SORTED_ON_KEY, dictionary, 5, &key, value);
    value = (STRLEN(value) == 0) ? "NULL" : value;
    printf("value is %s\n", value);

    int key_out = -1;
    getKeyFromValue(DICT_UNSORTED, dictionary, 5, value, &key_out);
    printf("key is %d\n", key_out);

    return 0;
}
