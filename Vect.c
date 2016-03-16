#include "Vect.h"
#include <stdlib.h>
static double _getVectX(Vect *self);
static double _getVectY(Vect *self);
static double _getVectZ(Vect *self);
static double magnitude(Vect *self);
static Vect* normalize(Vect *self,bool destory);
static Vect* negative(Vect *self,bool destory);
static double dotProduct(Vect *self,Vect *other,bool destory);
static Vect *VectMult(Vect *self,double scalar,bool destory);
static Vect* VectAdd(Vect *self,Vect *v,bool destory);
static Vect* crossProduct(Vect *self,Vect *v,bool destory);
static void Vect_self_normalize(Vect *self);
static void _destructor(Vect *self);

void _destructor(Vect *self)
{
	free(self);
}
void init_vect(Vect *self)
{

    self->x=0;
    self->y=0;
    self->z=0;
    self->setValue_vect=setValue;
    self->getVectX=_getVectX;
    self->getVectY=_getVectY;
    self->getVectZ=_getVectZ;
    self->magnitude=magnitude;
    self->normalize=normalize;
    self->negative=negative;
    self->dotProduct=dotProduct;
    self->self_normalize=Vect_self_normalize;
    self->crossProduct=crossProduct;
    self->VectAdd=VectAdd;
    self->VectMult=VectMult;
	self->destructor=_destructor;
}

void setValue(Vect *self,double x,double y,double z)
{
    self->x=x;
    self->y=y;
    self->z=z;
}

double _getVectX(Vect *self)
{
    return self->x;
}

double _getVectY(Vect *self)
{
    return self->y;
}

double _getVectZ(Vect *self)
{
    return self->z;
}

Vect* Vect_Constructor()
{
    Vect *p;
    if((p=(Vect*)malloc(sizeof(Vect)))==NULL) return NULL;
    p->init=init_vect;
    p->init(p); //initialize self
    return p;
}

Vect* Vect_Constructor_Value(double x ,double y, double z)
{
    Vect *p;
    if((p=(Vect*)malloc(sizeof(Vect)))==NULL) return NULL;
    p->init=init_vect;
    p->init(p);//initialize self
    p->setValue_vect(p,x,y,z);
    return p;

}

double magnitude(Vect *self)
{
    return sqrt((self->x*self->x)+(self->y*self->y)+(self->z*self->z));
}

Vect* normalize(Vect *self,bool destory)
{
    Vect *p;
    double magnitudeValue=0;
    magnitudeValue=self->magnitude(self);
    p=Vect_Constructor_Value((self->x)/magnitudeValue,self->y/magnitudeValue,self->z/magnitudeValue);
    if (destory) free(self);
    return p;
}

Vect* negative(Vect *self,bool destory)
{
    Vect *p;
    p=Vect_Constructor_Value(-(self->x),-(self->y),-(self->z));
    if (destory) free(self);
    return p;
}

Vect* crossProduct(Vect *self,Vect *v,bool destory)
{
    Vect *p;
    double result_x=0;
    double result_y=0;
    double result_z=0;
    result_x=((self->y * v->getVectZ(v)) - (self->z *v->getVectY(v)));
    result_y=((self->z * v->getVectX(v)) - (self->x*v->getVectZ(v)));
    result_z=((self->x * v->getVectY(v)) - (self->y*v->getVectX(v)));
    p=Vect_Constructor_Value(result_x,result_y,result_z);
    if (destory) free(self);
    return p;
}

double dotProduct(Vect *self,Vect *other,bool destory)
{
    double result_x=0;
    double result_y=0;
    double result_z=0;
    result_x=(self->x * (other->getVectX(other)));
    result_y=(self->y * (other->getVectY(other)));
    result_z=(self->z * (other->getVectZ(other)));
    if (destory) free(self);
    return result_x+result_y+result_z;
}

Vect* VectAdd(Vect *self,Vect *v,bool destory)
{
    Vect *p;
    double result_x=0;
    double result_y=0;
    double result_z=0;
    result_x=(self->x +v->getVectX(v) );
    result_y=(self->y +v->getVectY(v) );
    result_z=(self->z +v->getVectZ(v) );
    p=Vect_Constructor_Value(result_x,result_y,result_z);
    if (destory) free(self);
    return p;
}
Vect *VectMult(Vect *self,double scalar,bool destory)
{
    Vect *p;
    double result_x=0;
    double result_y=0;
    double result_z=0;
    result_x=(self->x * scalar );
    result_y=(self->y * scalar );
    result_z=(self->z * scalar );
    p=Vect_Constructor_Value(result_x,result_y,result_z);
    if (destory) free(self);
    return p;
}

void Vect_self_normalize(Vect *self)
{
    double magnitudeValue=0;
    magnitudeValue=self->magnitude(self);
    setValue(self,(self->x)/magnitudeValue,self->y/magnitudeValue,self->z/magnitudeValue);
}
