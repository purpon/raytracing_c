#include "Color.h"
#include <stdlib.h>
static double _getColorRed(Color *self);
static double _getColorGreen(Color *self);
static double _getColorBlue(Color *self);
static double _getColorSpecial(Color *self);

static void _SetColorRed(Color *self,double color_value);
static void _SetColorGreen(Color *self,double color_value);
static void _SetColorBlue(Color *self,double color_value);
static void _SetColorSpecial(Color *self,double color_value);
static void _Color_init(Color *self);
static void setValue(Color *self,double r,double g,double b,double s);
static Color* _colorScalar(Color *self, double scalar);
static double _brightness(Color *self);
static Color* _colorAdd(Color *self , Color *c);
static Color* _colorMultiply(Color *self , Color *c);
static Color* _colorAverage(Color *self , Color *c);
static Color* _clip(Color *self,bool destory);
static void _destructor(Color *self);

void _destructor(Color *self)
{
	free(self);
}

void _Color_init(Color *self)
{
    self->red=0.5;
    self->blue=0.5;
    self->green=0.5;
    self->special=0;
    self->getColorRed=_getColorRed;
    self->getColorGreen=_getColorGreen;
    self->getColorBlue=_getColorBlue;
    self->getColorSpecial=_getColorSpecial;

    self->setColorRed=_SetColorRed;
    self->setColorGreen=_SetColorGreen;
    self->setColorBlue=_SetColorBlue;
    self->setColorSpecial=_SetColorSpecial;

    self->setValue_color=setValue;
    self->brightness=_brightness;
    self->colorScalar=_colorScalar;
    self->colorAdd=_colorAdd;
    self->colorMultiply=_colorMultiply;
    self->colorAverage=_colorAverage;
    self->clip=_clip;
	self->destructor=_destructor;
}

Color* _clip(Color *self,bool destory)
{
    double allLight;
    double excessLight;
    double r,g,b,s;
    r=self->red;
    g=self->green;
    b=self->blue;
    s=self->special;
    allLight=r+g+b;
    excessLight=allLight-3;
    if (excessLight >0) {
        r=r+excessLight*(r/allLight);
        g=g+excessLight*(g/allLight);
        b=b+excessLight*(b/allLight);
    }
    if(r>1) r=1;
    if(g>1) g=1;
    if(b>1) b=1;

    if(r<0) r=0;
    if(g<0) g=0;
    if(b<0) b=0;
    Color *p;
    p=Color_Constructor_Value(r,g,b,s);
    if (destory) free(self);

    return p;
}


Color* _colorAdd(Color *self , Color *c)
{
    Color *tmp;
    double r;
    double g;
    double b;
    double s;
    r=self->red + c->red;
    g=self->green +c->green;
    b=self->blue + c->blue;
    s=self->special;
    tmp=Color_Constructor_Value(r,g,b,s);
    return tmp;
}

Color* _colorAverage(Color *self , Color *c)
{
    Color *tmp;
    double r;
    double g;
    double b;
    double s;
    r=(self->red + c->red)/2;
    g=(self->green +c->green)/2;
    b=(self->blue + c->blue)/2;
    s=self->special;
    tmp=Color_Constructor_Value(r,g,b,s);
    return tmp;
}

Color* _colorMultiply(Color *self , Color *c)
{
    Color *tmp;
    double r;
    double g;
    double b;
    double s;
    r=self->red * c->red;
    g=self->green *c->green;
    b=self->blue * c->blue;
    s=self->special;
    tmp=Color_Constructor_Value(r,g,b,s);
    return tmp;
}


Color* _colorScalar(Color *self, double scalar)
{
    Color *tmp;
    double r;
    double g;
    double b;
    double s;
    r=self->red*scalar;
    g=self->green*scalar;
    b=self->blue*scalar;
    s=self->special;
    tmp=Color_Constructor_Value(r,g,b,s);
    return tmp;
}


double _brightness(Color *self)
{
    return (self->red+self->green+self->blue)/3;
}


double _getColorRed(Color *self)
{
    return self->red;
}

double _getColorGreen(Color *self)
{
    return self->green;
}

double _getColorBlue(Color *self)
{
    return self->blue;
}

double _getColorSpecial(Color *self)
{
    return self->special;
}

void _SetColorRed(Color *self,double color_value)
{
    self->red=color_value;
}
void _SetColorGreen(Color *self,double color_value)
{
    self->green=color_value;
}
void _SetColorBlue(Color *self,double color_value)
{
    self->blue=color_value;
}
void _SetColorSpecial(Color *self,double color_value)
{
    self->special=color_value;
}

void setValue(Color *self,double r,double g,double b,double s)
{
    self->red=r;
    self->green=g;
    self->blue=b;
    self->special=s;
}

Color* Color_Constructor()
{
    Color *p;
    if((p=(Color*)malloc(sizeof(Color)))==NULL) return NULL;
    p->init=_Color_init;
    p->init(p);
    return p;
}

Color* Color_Constructor_Value(double r ,double g, double b ,double s)
{
    Color *p;
    if((p=(Color*)malloc(sizeof(Color)))==NULL) return NULL;
    p->init=_Color_init;
    p->init(p);
    p->setValue_color(p,r,g,b,s);

    return p;

}
