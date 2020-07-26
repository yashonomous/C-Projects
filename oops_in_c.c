#include <stdio.h>

// typedef struct test_vtable test_vtable_t;

// typedef struct test{
//     test_vtable_t *vtable_ptr;
// }test_t;

// struct test_vtable{
//     char *value;
//     char* (*getValue)(test_t *this);
//     void (*setValue)(test_t *this, char *value);
// };


typedef struct test_vtable{
    char *value;
    char* (*getValue)();
    void (*setValue)();
}test_vtable_t;

typedef struct test{
    test_vtable_t *vtable_ptr;
}test_t;

char* _get_value(test_t *this){
    if(this == NULL)
        return "this ptr is NULL";
    return this->vtable_ptr->value;    
}

void _set_value(test_t *this, char *value){
    if(this == NULL)
        return;
    this->vtable_ptr->value = value;    
}

static test_vtable_t obj_table= {"hello_world", _get_value, _set_value};

test_t obj_ptr = {&obj_table};

test_t *obj = &obj_ptr;



int main()
{
    printf("string is -> %s\n", obj->vtable_ptr->getValue(obj));
    
    obj->vtable_ptr->setValue(obj, "hello_world_again");
    
    printf("string is -> %s\n", obj->vtable_ptr->getValue(obj));
    return 0;
}
