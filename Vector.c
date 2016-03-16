#include <stdlib.h>
#include <string.h>
#include "Vector.h"

static void _destructor(Vector *self);
static int _push_back(Vector *self,void *item);
static void* _pop_back(Vector *self);
static void* _at(Vector *self,unsigned int index);

void _destructor(Vector *self)
{
	int i;
	for(i=0;i < self->item_index; i++) {
		free(self->item[i]);
	}
	free(self->item);
	free(self);
}

Vector* Vector_constructor(unsigned int max_Buffer_size)
{
    Vector *p;
    p=(Vector*)malloc(sizeof(Vector));
    p->capacity=0;
    p->item_index=0;
    p->maxsize=max_Buffer_size;
    p->item=(void**)malloc(sizeof(void*)*max_Buffer_size);
    p->push_back=_push_back;
    p->pop_back=_pop_back;
    p->at=_at;
	p->destructor=_destructor;
    return p;
}



int _push_back(Vector *self,void *item)
{
    if ((self->capacity+1)>self->maxsize) {
        self->maxsize+=15;
        void **p;
        if((p=(void**)malloc(sizeof(void*)*self->maxsize))==NULL) return -1;
        memcpy(p,self->item,sizeof(self->item));
        free(self->item);
        self->item=p;
    }
    self->item[self->item_index]=item;
    self->item_index+=1;
    return 0;
}

void *_pop_back(Vector *self)
{
    void *tmp;
    tmp=self->item[self->item_index];
    self->item_index-=1;
    return tmp;
}

void* _at(Vector *self,unsigned int index)
{
    return self->item[index];
}
