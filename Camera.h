#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include "Vect.h"
#include "Bool.h"
typedef struct _Camera Camera;

typedef void (*fp_CameraInit)(Camera *self);
typedef void(*fp_destructor_Camera)(Camera *self);

typedef Vect* (*fp_getCameramember)(Camera *self);

Camera* Camera_Constructor();
Camera* Camera_Constructor_Vect(Vect  *campos,Vect  *camdir,Vect  *camright,Vect  *camdown);


struct _Camera {
    Vect *campos;
    Vect *camdir;
    Vect *camright;
    Vect *camdown;
    fp_CameraInit Camera_Init;

    fp_getCameramember getCameraPosition;
    fp_getCameramember getCameraDirection;
    fp_getCameramember getCameraRight;
    fp_getCameramember getCameraDown;
    fp_destructor_Camera destructor;

};


#endif // CAMERA_H_INCLUDED
