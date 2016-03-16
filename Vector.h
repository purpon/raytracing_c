#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include "Bool.h"
typedef struct _Vector Vector ;
typedef void* (*fp_at)(Vector *self,unsigned int index);
typedef int (*fp_push_back)(Vector *self,void *item);
typedef void* (*fp_pop_back)(Vector *self);
typedef void (*fp_destructor_Vector) (Vector *self);

Vector* Vector_constructor(unsigned int max_Buffer_size);

struct _Vector {
    unsigned int capacity;
    unsigned int item_index;
    unsigned int maxsize;
    fp_push_back push_back;
    fp_pop_back pop_back;
    fp_at at;
    void **item;
	fp_destructor_Vector destructor;
};



#endif // VECTOR_H_INCLUDED
