#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED
#include "Vect.h"
#include "Color.h"
#include "Source.h"
#include "Bool.h"
typedef struct _Light Light;

typedef void (*fp_LightInit)(Light *self);
typedef Vect* (*fp_getLightPosition)(void *self);
typedef Color* (*fp_getColor_)(void *self);
typedef void (*fp_destructor_Light)(Light* self);

Light* Light_Constructor();
Light* Light_Constructor_Vect(Vect  *v,Color *c);


struct _Light {
    Source *source;
    Vect *position;
    Color *color;
    fp_LightInit Light_init;
    fp_getLightPosition getLightPosition ;
    fp_getColor_ getColor;
	fp_destructor_Light destructor;
};


#endif // LIGHT_H_INCLUDED
