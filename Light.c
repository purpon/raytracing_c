#include "Light.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
static void Light_init(Light *self);
static Vect* _getLightPosition(void *self);
static Color* _getColor(void *self);
static void _destructor(Light *self);

void _destructor(Light *self)
{
	free(self->source);
	self->position->destructor(self->position);
	self->color->destructor(self->color);
	free(self);
}

void Light_init(Light *self)
{
    /**
    (self)->position->init(self->position);
    (self)->color->init(self->color);

    (self)->position->setValue_vect(self->position,0,0,0);
    (self)->color->setValue_color(self->color,0,0,0,0);
    **/
    self->getLightPosition=_getLightPosition;
    self->getColor=_getColor;
    self->source->getLightPosition=_getLightPosition; // virtual function
    self->source->getColor=_getColor;
	self->destructor=_destructor;
}

Light* Light_Constructor_Vect(Vect  *position,Color  *color)
{
    Light *p;
    if((p=(Light*)malloc(sizeof(Light)))==NULL) return NULL;
    if ((position==NULL) || (color==NULL) ) return NULL;
    p->position=position;
    p->color=color;
    p->source=Source_Constructor();
    p->Light_init=Light_init;
    p->Light_init(p);
    return p;
}

Light* Light_Constructor()
{
    Light *p;
    if((p=(Light*)malloc(sizeof(Light)))==NULL) return NULL;
    p->position=Vect_Constructor();
    p->color=Color_Constructor();
    p->source=Source_Constructor();
    p->Light_init=Light_init;
    p->Light_init(p);
    p->color->setValue_color(p->color,1,1,1, 0);
    return p;
}

Vect* _getLightPosition(void *self)
{
    Light *p;
    p=(Light*)self;
    Vect *tmp;
    tmp=Vect_Constructor();
    memcpy(tmp,p->position,sizeof(*tmp));
    return tmp;

}


Color* _getColor(void *self)
{
    Light *p;
    p=(Light*)self;
    Color *tmp;
    tmp=Color_Constructor();
    memcpy(tmp,p->color,sizeof(*tmp));
    return tmp;

}
