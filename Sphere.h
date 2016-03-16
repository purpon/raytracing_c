#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED
#include "Vect.h"
#include "Color.h"
#include "Object.h"
#include "Bool.h"
typedef struct _Sphere Sphere;

typedef double (*fp_get_Radius)(Sphere *self);
typedef void (*fp_SphereInit)(Sphere *self);
typedef Vect* (*_getNormalAT) (void *self,Vect *point);
typedef double(*__findIntersection) (void *_self, Ray *ray);
typedef void (*fp_destructor_Sphere) (Sphere *self);

Sphere* Sphere_Constructor();
Sphere* Sphere_Constructor_Vect(Vect *v,double radius,Color *c);

struct _Sphere {
    Object *object; //inheritance Object
    Vect *center;
    Color *color;
    double radius;
    fp_SphereInit Sphere_init;
    fp_get_Radius getSphereRadius;
    _getNormalAT getNormalAt;
    __findIntersection findIntersection;
	fp_destructor_Sphere destructor;
};


#endif // SPHERE_H_INCLUDED
