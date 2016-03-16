#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "Vect.h"
#include <math.h>
#include "Bool.h"
typedef struct _Ray Ray;
typedef void(*fp_destructor_Ray)(Ray *self);
typedef void (*fp_RayInit)(Ray *self);
void Ray_init(Ray *self);

Ray* Ray_Constructor();
Ray* Ray_Constructor_Vect(Vect  *origin,Vect  *direction);


struct _Ray {
    Vect *origin;
    Vect *direction;
    fp_RayInit Ray_Init;
	fp_destructor_Ray destructor;
};


#endif // RAY_H_INCLUDED
