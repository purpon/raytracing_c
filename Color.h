#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED
#include "Bool.h"
typedef struct  _Color Color;

typedef void (*fp_ColortInit)(Color *self);
typedef double (*fp_get_Color)(Color *self);
typedef double (*fp_get_Brightness)(Color *self);
typedef void (*fp_set_Color)(Color *self,double color_value);
typedef void (*fp_setValue_Color)(Color *self,double,double,double,double);
typedef Color* (*fp_colorScalar)(Color *self, double scalar);
typedef Color* (*fp_colorAdd)(Color *self,Color *c);
typedef Color* (*fp_Multiply)(Color *self,Color *c);
typedef Color* (*fp_Average)(Color *self,Color *c);
typedef Color* (*fp_clip)(Color *self,bool destory);
typedef void (*fp_destructor_Color)(Color *self);

struct _Color {
    double red;
    double green;
    double blue;
    double special;

    fp_ColortInit init;
    fp_get_Color getColorRed;
    fp_get_Color getColorGreen;
    fp_get_Color getColorBlue;
    fp_get_Color getColorSpecial;

    fp_set_Color setColorRed;
    fp_set_Color setColorGreen;
    fp_set_Color setColorBlue;
    fp_set_Color setColorSpecial;
    fp_get_Brightness brightness;
    fp_colorScalar colorScalar;
    fp_setValue_Color setValue_color;
    fp_colorAdd colorAdd;
    fp_Multiply colorMultiply;
    fp_Average colorAverage;
    fp_clip clip;
	fp_destructor_Color destructor;
};

Color* Color_Constructor();


Color* Color_Constructor_Value(double r ,double g, double b ,double s);

#endif // COLOR_H_INCLUDED
