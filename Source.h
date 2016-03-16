#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED

#include "Vect.h"
#include "Color.h"
#include "Bool.h"
typedef struct _Source Source;
typedef Vect* (*fp_getLightPosition)(void *self);
typedef Color* (*fp_getColor)(void *self);

Source* Source_Constructor();

struct _Source {
    fp_getLightPosition getLightPosition;
    fp_getColor getColor;
};

#endif // SOURCE_H_INCLUDED
