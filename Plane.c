#include <stdlib.h>
#include <string.h>
#include <string.h>

#include "Plane.h"
static void Plane_init(Plane *self);
static double _getPlaneDistance(Plane *self);
static double _findIntersection(void *_self,Ray *ray);
static Color *getColor(void *self);
static Vect* ___getNormalAt(void *self,Vect *point);
static void _destructor(Plane *self);

void _destructor(Plane *self)
{
	free(self->object);
	self->normal->destructor(self->normal);
	self->color->destructor(self->color);
	free(self);
}

static void Plane_init(Plane *self)
{

    self->getPlaneDistance=_getPlaneDistance;
    self->findIntersection=_findIntersection;
    self->object->findIntersection=self->findIntersection;
    self->object->getColor=getColor;
    self->object->getNormalAT=___getNormalAt;
	self->destructor=_destructor;
}

Vect* ___getNormalAt(void *self,Vect *point)
{
    //normal always points away from the center of a sphere
    Vect *p;
    Plane *v;
    v=(Plane*)self;
    if((p=(Vect*)malloc(sizeof(Vect)))==NULL) return NULL;
    memcpy(p,v->normal,sizeof(*p));
    return p;
}

Plane* Plane_Constructor_Vect(Vect *normal, double distance, Color *color)
{
    Plane *p;
    if((p=(Plane*)malloc(sizeof(Plane)))==NULL) return NULL;
    if ((normal==NULL) || (color==NULL) ) return NULL;
    p->object=Object_Constructor();
    p->normal=normal;
    p->color=color;
    p->Plane_init=Plane_init;
    p->Plane_init(p);
    p->distance=distance;
    return p;
}

Plane* Plane_Constructor()
{
    Plane *p;
    if((p=(Plane*)malloc(sizeof(Plane)))==NULL) return NULL;
    p->object=Object_Constructor();
    p->normal=Vect_Constructor();
    p->color=Color_Constructor();
    p->Plane_init=Plane_init;
    p->Plane_init(p);
    p->normal->setValue_vect(p->normal, 1, 0, 0);
    p->color->setValue_color(p->color,0.5, 0.5, 0.5, 0);
    p->distance=0.0;
    return p;
}

double _getPlaneDistance(Plane *self)
{
    return self->distance;
}

double _findIntersection(void *_self,Ray *ray)
{
    double a;
    Plane *self=(Plane *) _self ;
    a=ray->direction->dotProduct(ray->direction,self->normal,0);
    if(a==0) {
        //ray is parallel to the plane
        return -1;
        //return 0;
    } else {
        double b;
        Vect *tmp1,*tmp2;
        tmp1=self->normal->VectMult(self->normal,self->distance,0);
        tmp1=tmp1->negative(tmp1,1);
        tmp2=ray->origin->VectAdd(ray->origin,tmp1,0);

        b=self->normal->dotProduct(self->normal,tmp2,0);
        free(tmp2);
        free(tmp1);
        return -1*b/a;
        //return 0;
    }
}

Color *getColor(void *self)
{
    Plane *p;
    p=(Plane *) self;
    Color *Color_tmp;
    Color_tmp=Color_Constructor();
    memcpy(Color_tmp,p->color,sizeof(*Color_tmp));
    return Color_tmp;
}
