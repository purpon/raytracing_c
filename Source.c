#include "Source.h"
#include <stdlib.h>


Source* Source_Constructor()
{
    Source *p;
    if((p=(Source*)malloc(sizeof(Source)))==NULL) return NULL;
    // p->Object_init=Object_init;
    return p;
}
