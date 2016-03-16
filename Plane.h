#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include "Vect.h"
#include "Color.h"
#include "Object.h"
#include "Bool.h"
typedef struct _Plane Plane;

typedef double (*fp_get_Distance)(Plane *self);
typedef void (*fp_PlaneInit)(Plane *self);
typedef double (*fp_findIntersection)(void *_self,Ray *ray);
typedef void (*fp_destructor_Plane) (Plane *self);

Plane* Plane_Constructor();
Plane* Plane_Constructor_Vect(Vect *v,double distance,Color *c);

struct _Plane {
    Object *object; //inheritance Object
    Vect *normal;
    Color *color;
    double distance;
    fp_PlaneInit Plane_init;
    fp_get_Distance getPlaneDistance;
    fp_findIntersection findIntersection;
	fp_destructor_Plane destructor;
};


#endif // PLANE_H_INCLUDED
