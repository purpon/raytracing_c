#ifndef VECT_H_INCLUDED
#define VECT_H_INCLUDED

#include <math.h>
#include "Bool.h"

typedef struct _Vect Vect;
typedef void (*fp_VectInit)(Vect *self);
typedef void (*fp_setValue)(Vect *self,double,double,double);
typedef double (*fp_return)(Vect *self);
typedef double (*_magnitude)(Vect *self);
typedef Vect* (*_normalize)(Vect *self,bool destory);
typedef Vect* (*_negative)(Vect *self,bool destory);
typedef double (*_dotProduct)(Vect *self,Vect *other,bool destory);
typedef void (*_self_normalize)(Vect *self);
typedef Vect* (*fp_cross_add)(Vect *self,Vect *v,bool destory);
typedef Vect* (*_VectMult)(Vect *self,double scalar,bool destory);
typedef void (*fp_destructor_Vect) (Vect *self);

struct _Vect {
    double x,y,z;
    fp_VectInit init;
    fp_setValue setValue_vect;
    fp_return getVectX;
    fp_return getVectY;
    fp_return getVectZ;
    _magnitude magnitude;
    _normalize normalize;
    _negative negative;
    _dotProduct dotProduct;
    _self_normalize self_normalize;
    fp_cross_add crossProduct;
    fp_cross_add VectAdd;
    _VectMult VectMult;
	fp_destructor_Vect destructor;
};


void init_vect(Vect *self);
void setValue(Vect *self,double x,double y,double z);


Vect* Vect_Constructor();
Vect* Vect_Constructor_Value(double x ,double y, double z);

#endif // VECT_H_INCLUDED
