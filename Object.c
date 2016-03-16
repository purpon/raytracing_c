#include <stdlib.h>
#include "Object.h"

static void Object_init(Object *self)
{

}


Object* Object_Constructor()
{
    Object *p;
    if((p=(Object*)malloc(sizeof(Object)))==NULL) return NULL;
    // p->Object_init=Object_init;
    return p;
}

Color* _getObjectColor()
{
    Color *p;
    p=Color_Constructor_Value(0.0, 0.0, 0.0, 0);
    return p;
}
