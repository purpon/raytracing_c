#include "Ray.h"
#include <stdlib.h>

static void _destructor(Ray *self);

void _destructor(Ray *self)
{
	free(self);
}

Ray* Ray_Constructor()
{
    Ray *p;
    if((p=(Ray*)malloc(sizeof(Ray)))==NULL) return NULL;
    p->direction=Vect_Constructor();
    p->origin=Vect_Constructor();
    p->Ray_Init=Ray_init;
    p->Ray_Init(p);
    return p;
}

void Ray_init(Ray *self)
{
	self->destructor=_destructor;
}

Ray* Ray_Constructor_Vect(Vect  *origin,Vect  *direction)
{
    Ray *p;
    if((p=(Ray*)malloc(sizeof(Ray)))==NULL) return NULL;
    if ((origin==NULL) || (direction==NULL) ) return NULL;
    p->origin=origin;
    p->direction=direction;
    p->Ray_Init=Ray_init;
  	p->Ray_Init(p);
    return p;
}
