#include <stdio.h>
#include <stdlib.h>

#define MEMSET(array, value, length) ({ \
    int tmp = length;                   \
    while (tmp--)                       \
    {                                   \
        array[tmp] = value;             \
    }                                   \
})

typedef enum{
    FALSE = 0,
    TRUE
}BOOL;

#define PRINT_ANY(x, y) _Generic(x, int:print_int, char:print_char, \
                                float:print_float, double:print_double, \
                                char*:print_string, int*:_Generic(y, int:print_int_arr))(x,y)

#define GENERATE_PRINT(type, specifier_str) \
int print_##type(type x, type y) \
{ \
    return printf(specifier_str"\n", x); \
} 

GENERATE_PRINT(int, "%d");
GENERATE_PRINT(char, "%c");
GENERATE_PRINT(float, "%f");
GENERATE_PRINT(double, "%lf");

int print_string(char *string){
    return printf("%s\n", string);
}

int print_int_arr(int *int_arr, int len){
    int *tmp = int_arr;
    while(len--){
        PRINT_ANY(*tmp++, 0);
    }
}

void filter(int *array, BOOL (*filterFunction)(int item), int *resArray){
    while(*array){
        if(filterFunction(*array))
            *resArray++ = *array;
        array++;
    }
}

BOOL _filterFunction(int item){
    return (item > 10)? TRUE:FALSE;
}

void map(int *array, int (*mapFunction)(int item), int *resArray){
    while(*array){
        *resArray++ = mapFunction(*array++);
    }
}

int _mapFunction(int item){
    return item * item;
}

int main(int argc, char const *argv[])
{
    int *arr = malloc(10 * sizeof(int));
    MEMSET(arr, 0, 10);
    int i=0;
    while(i <= 5){
        // scanf("%d", &arr[i++]);
        // getchar();
        int ran = rand()%20;
        while(ran == 0)
            ran = rand()%5;
        arr[i++] = ran;
    }
    
    int *tmp = arr;
    while(*tmp){
        printf("%d, ", *tmp++);
    }
    printf("\n");
    
    int *res = malloc(10 * sizeof(int));
    MEMSET(res, 0, 10);
    
    filter(arr, _filterFunction, res);
    
    int *tmp1 = res;
    while(*tmp1){
        printf("%d ", *tmp1++);
    }
    printf("\n");
    
    map(arr, _mapFunction, res);
    
    int *tmp2 = res;
    while(*tmp2){
        printf("%d ", *tmp2++);
    }

    return 0;
}
