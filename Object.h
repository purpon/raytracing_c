#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include "Vect.h"
#include "Color.h"
#include "Ray.h"
#include "Bool.h"
typedef struct _Object Object;

typedef Color* (*fp_getObjectColor)();
typedef void (*fp_ObjectInit)(Object *self);
typedef double (*___findIntersection)(void *self,Ray *ray);
typedef Color* (*_getColor)(void *self);
typedef Vect* (*__getNormalAT) (void *self,Vect *point);

Object* Object_Constructor();


struct _Object {
    ___findIntersection findIntersection;
    _getColor getColor;
    __getNormalAT getNormalAT ;
    //fp_ObjectInit Object_init;
    //fp_getObjectColor getObjectColor;
};


#endif // OBJECT_H_INCLUDED
