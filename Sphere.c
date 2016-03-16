#include <stdlib.h>
#include <math.h>
#include<string.h>

#include "Sphere.h"
static void Sphere_init(Sphere *self);
static double _getSphereRadius(Sphere *self);
static Vect* ___getNormalAt(void *self,Vect *point);
static double findIntersection(void *_self, Ray *ray);
static Color *getColor(void *self);
static void _destructor(Sphere *self);

void _destructor(Sphere *self)
{
	free(self->object);
	self->center->destructor(self->center);
	self->color->destructor(self->color);
	free(self);
}

static void Sphere_init(Sphere *self)
{
	
    self->getSphereRadius=_getSphereRadius;
    self->getNormalAt=___getNormalAt;
    self->findIntersection=findIntersection;
    self->object->findIntersection=self->findIntersection;
    self->object->getColor=getColor;
    self->object->getNormalAT=___getNormalAt;
	self->destructor=_destructor;
}

Sphere* Sphere_Constructor_Vect(Vect  *center,double radius,Color  *color)
{
    Sphere *p;
    if((p=(Sphere*)malloc(sizeof(Sphere)))==NULL) return NULL;
    if ((center==NULL) || (color==NULL) ) return NULL;
    p->object=Object_Constructor();
    p->center=center;
    p->color=color;
    p->Sphere_init=Sphere_init;
    p->Sphere_init(p);
    p->radius=radius;
    return p;
}

Sphere* Sphere_Constructor()
{
    Sphere *p;
    if((p=(Sphere*)malloc(sizeof(Sphere)))==NULL) return NULL;
    p->object=Object_Constructor();
    p->center=Vect_Constructor();
    p->color=Color_Constructor();
    p->Sphere_init=Sphere_init;
    p->Sphere_init(p);
    p->color->setValue_color(p->color,0.5, 0.5, 0.5, 0);
    p->radius=1.0;
    return p;
}

double _getSphereRadius(Sphere *self)
{
    return self->radius;
}

Vect* ___getNormalAt(void *self,Vect *point)
{
    //normal always points away from the center of a sphere
    Vect *p,*tmp;
    Sphere *v;
    v=(Sphere*)self;
    tmp=v->center->negative(v->center,0);
    p=point->VectAdd(point,tmp,0);
    p->self_normalize(p);
    free(tmp);
    return p;
}

double findIntersection(void *_self, Ray *ray)
{
    Sphere *self=(Sphere *) _self;
    double ray_origin_x=ray->origin->getVectX(ray->origin);
    double ray_origin_y=ray->origin->getVectY(ray->origin);
    double ray_origin_z=ray->origin->getVectZ(ray->origin);

    double ray_direction_x=ray->direction->getVectX(ray->direction);
    double ray_direction_y=ray->direction->getVectY(ray->direction);
    double ray_direction_z=ray->direction->getVectZ(ray->direction);

    double sphere_center_x=self->center->getVectX(self->center);
    double sphere_center_y=self->center->getVectY(self->center);
    double sphere_center_z=self->center->getVectZ(self->center);

    double a=1; //normalized
    double b=((2*(ray_origin_x - sphere_center_x)*ray_direction_x) + \
              (2*(ray_origin_y - sphere_center_y)*ray_direction_y)+ \
              (2*(ray_origin_z - sphere_center_z)*ray_direction_z));
    double c=pow(ray_origin_x-sphere_center_x,2)+pow(ray_origin_y-sphere_center_y,2)+pow(ray_origin_z-sphere_center_z,2) - (self->radius * self->radius);
    double discriminant=b*b - 4*c;

    if (discriminant > 0) {
        //the ray intersects the sphere

        //the first root
        double root_1 =((-1 * b - sqrt(discriminant)) / 2) - 0.0000001;

        if(root_1 >0) {
            //the first root is the smallest positive root
            return root_1;
        } else {
            //the second root is the smallest positive root
            double root_2=((sqrt(discriminant)-b)/2) -0.0000001;
            return root_2;
            //return 0;
        }

    } else {
        // the rat missed the sphere;
        return -1;
        //return 0;

    }
}

Color *getColor(void *self)
{
    Sphere *p;
    p=(Sphere *) self;
    Color *Color_tmp;
    Color_tmp=Color_Constructor();
    memcpy(Color_tmp,p->color,sizeof(*Color_tmp));
    return Color_tmp;
}
