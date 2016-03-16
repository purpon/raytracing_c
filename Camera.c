#include"Camera.h"
#include <stdlib.h>
#include <string.h>

static void Camera_init(Camera *self);
static Vect* _getCameraPosition(Camera *self);
static Vect* _getCameraDirection(Camera *self);
static Vect* _getCameraRight(Camera *self);
static Vect* _getCameraDown(Camera *self);
static void _destructor(Camera *self);

void _destructor(Camera *self)
{
	self->campos->destructor(self->campos);
	self->camdir->destructor(self->camdir);
	self->camright->destructor(self->camright);
	self->camdown->destructor(self->camdown);
	free(self);
}

Camera* Camera_Constructor()
{
    Camera *p;
    if((p=(Camera*)malloc(sizeof(Camera)))==NULL) return NULL;
    p->campos=Vect_Constructor();
    p->camdir=Vect_Constructor();
    p->camright=Vect_Constructor();
    p->camdown=Vect_Constructor();
    p->Camera_Init=Camera_init;
    p->Camera_Init(p);
    return p;
}

void Camera_init(Camera *self)
{
    /**
        self->campos->init(self->campos);
        self->camdir->init(self->camdir);
        self->camright->init(self->camright);
        self->camdown->init(self->camdown);

        self->campos->setValue_vect(self->campos,0,0,0);
        self->camdir->setValue_vect(self->camdir,0,0,0);
        self->camright->setValue_vect(self->camright,0,0,0);
        self->camdown->setValue_vect(self->camdown,0,0,0);
    **/

    self->getCameraPosition=_getCameraPosition;
    self->getCameraDirection=_getCameraDirection;
    self->getCameraRight=_getCameraRight;
    self->getCameraDown=_getCameraDown;
	self->destructor=_destructor;
}

Camera* Camera_Constructor_Vect(Vect *campos,Vect *camdir,Vect *camright,Vect *camdown)
{
    Camera *p;
    if((p=(Camera*)malloc(sizeof(Camera)))==NULL) return NULL;
    if ((campos==NULL) || (camdir==NULL) || (camright==NULL) || (camdown==NULL)) return NULL;
    p->campos=campos;
    p->camdir=camdir;
    p->camright=camright;
    p->camdown=camdown;

    p->Camera_Init=Camera_init;
    p->Camera_Init(p);
    return p;
}

Vect* _getCameraPosition(Camera *self)
{
    Vect *p;
    p=(Vect *)malloc(sizeof(Vect));
    memcpy(p,self->campos,sizeof(*p));
    return p;
}

Vect* _getCameraDirection(Camera *self)
{
    Vect *p;
    p=(Vect *)malloc(sizeof(Vect));
    memcpy(p,self->camdir,sizeof(*p));
    return p;
}

Vect* _getCameraRight(Camera *self)
{
    Vect *p;
    p=(Vect *)malloc(sizeof(Vect));
    memcpy(p,self->camright,sizeof(*p));
    return p;
}

Vect* _getCameraDown(Camera *self)
{
    Vect *p;
    p=(Vect *)malloc(sizeof(Vect));
    memcpy(p,self->camdown,sizeof(*p));
    return p;
}
