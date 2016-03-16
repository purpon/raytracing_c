#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "Vector.h"
#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Sphere.h"
#include "Object.h"
#include "Plane.h"
#include "Source.h"
#include "Bool.h"




typedef struct _RGBType {
    double r;
    double g;
    double b;
} RGBType;

static Color* getColorAt(Vect *intersection_position,Vect *intersection_ray_direction,Vector* scene_objects,int index_of_winning_object,Vector* light_sources ,double accuracy,double ambientlight);
static int savebmp(const char *filename,int w,int h, int dpi,RGBType *data);
static int winningObjectIndex(Vector *object_intersections);




int main()
{
    clock_t t1,t2;
    printf("pid =  %d\n", getpid());
    printf("rendering...\n");
    //sleep(10);
    t1=clock();
    int width=640;
    int height=480;
    int dpi=72;
    int n=width*height;
    double aspectratio;
    double ambientlight;
    double accuracy;
    //double aathreshold

    accuracy=0.000001;
    RGBType *pixels;

    int aadepth=1; //how many times color in averaging

    //double aathreshold=0.1;
    ambientlight=0.2;
    aspectratio= (double)width/(double)height;

    Vect *Y,*O;
    Vect *new_sphere_location1;
    O=Vect_Constructor_Value(0,0,0);
    //X=Vect_Constructor_Value(1,0,0);
    Y=Vect_Constructor_Value(0,1,0);
    //Z=Vect_Constructor_Value(0,0,1);
    //new_sphere_location=Vect_Constructor_Value(1.75,0,0);
    new_sphere_location1=Vect_Constructor_Value(2,0,0);

    Vect *look_at;  //where camera look at
    look_at=Vect_Constructor_Value(0,0,0);

    Vect *campos;
    campos=Vect_Constructor_Value(3,1.5,-4);

    Vect* diff_btw;
    diff_btw=Vect_Constructor_Value(campos->getVectX(campos) - look_at->getVectX(look_at),\
                                    campos->getVectY(campos) - look_at->getVectY(look_at),\
                                    campos->getVectZ(campos) - look_at->getVectZ(look_at));
    look_at->destructor(look_at);
    Vect *camdir;
    camdir=diff_btw->negative(diff_btw,0);
    diff_btw->destructor(diff_btw);
    camdir->self_normalize(camdir);

    Vect *camright;
    camright=Y->crossProduct(Y,camdir,0);
    camright->self_normalize(camright);

    Vect *camdown;
    camdown=camright->crossProduct(camright,camdir,0);

    Camera *scene_cam;
    scene_cam=Camera_Constructor_Vect(campos,camdir,camright,camdown);

    Color *white_light;
    Color *pretty_green;
    //Color *gray;
    //Color *black;
    //Color *maroon;
    Color *tile_floor;
    Color *unknow;
    white_light=Color_Constructor_Value(1.0,1.0,1.0,0);
    pretty_green=Color_Constructor_Value(0.5,1.0,0.5,0.3);
    //gray=Color_Constructor_Value(0.5,0.5,0.5,0);
    //black=Color_Constructor_Value(0.0,0.0,0.0,0);
    //maroon=Color_Constructor_Value(0.5, 0.25, 0.25, 0);
    tile_floor=Color_Constructor_Value(1,1,1,2);
    unknow=Color_Constructor_Value(1.0,0.5,1.0,0.5);

    Vect *light_position;
    light_position=Vect_Constructor_Value(-7,10,-10);
    Light *scene_light;
    scene_light=Light_Constructor_Vect(light_position,white_light);

    Vector *light_sources;
    light_sources=Vector_constructor(5);
    light_sources->push_back(light_sources,scene_light);

    //scene objects
    Sphere *scene_sphere;
    scene_sphere=Sphere_Constructor_Vect(O,1,pretty_green);

    Plane *scene_plane;
    scene_plane=Plane_Constructor_Vect(Y, -1, tile_floor);

    Sphere *scene_sphere1;
    scene_sphere1=Sphere_Constructor_Vect(new_sphere_location1,0.4,unknow);

    Vector *scene_objects;
    scene_objects=Vector_constructor(5);
    scene_objects->push_back(scene_objects,scene_sphere);
    //scene_objects->push_back(scene_objects,scene_sphere1);
    scene_objects->push_back(scene_objects,scene_plane);


    double xamnt,yamnt;
    pixels=(RGBType*)malloc(sizeof(RGBType)*n);
    int thisone,aa_index;
    int x;
    int y;
    for(x=0; x<width; x++) {
        for(y=0; y<height; y++) {
            thisone=y*width+x;

            //start with a blank pixel
            double tempRed[aadepth*aadepth];
            double tempGreen[aadepth*aadepth];
            double tempBlue[aadepth*aadepth];
            int aax,aay;
            for(aax=0; aax<aadepth; aax++) {
                for(aay=0; aay<aadepth; aay++) {
                    aa_index=aay*aadepth+aax;
                    srand(time(0));
                    // create the ray from the camera to this pixel
                    if (aadepth == 1) {
                        // start with no anti-aliasing
                        if (width > height) {
                            // the image is wider than it is tall
                            xamnt = ((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
                            yamnt = ((height - y) + 0.5)/height;
                        } else if (height > width) {
                            // the imager is taller than it is wide
                            xamnt = (x + 0.5)/ width;
                            yamnt = (((height - y) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
                        } else {
                            // the image is square
                            xamnt = (x + 0.5)/width;
                            yamnt = ((height - y) + 0.5)/height;
                        }
                    } else {
                        // anti-aliasing
                        if (width > height) {
                            // the image is wider than it is tall
                            xamnt = ((x + (double)aax/((double)aadepth - 1))/width)*aspectratio - (((width-height)/(double)height)/2);
                            yamnt = ((height - y) + (double)aax/((double)aadepth - 1))/height;
                        } else if (height > width) {
                            // the imager is taller than it is wide
                            xamnt = (x + (double)aax/((double)aadepth - 1))/ width;
                            yamnt = (((height - y) + (double)aax/((double)aadepth - 1))/height)/aspectratio - (((height - width)/(double)width)/2);
                        } else {
                            // the image is square
                            xamnt = (x + (double)aax/((double)aadepth - 1))/width;
                            yamnt = ((height - y) + (double)aax/((double)aadepth - 1))/height;
                        }
                    }

                    Vect *cam_ray_origin=scene_cam->getCameraPosition(scene_cam);

                    Vect *cam_ray_direction;
                    Vect *tmp1,*tmp2;
                    tmp2=camright->VectMult(camright,xamnt-0.5,0);
                    tmp1=camdown->VectMult(camdown,yamnt-0.5,0);
                    tmp2=tmp2->VectAdd(tmp2,tmp1,1);
                    tmp1->destructor(tmp1);
                    tmp1=camdir->VectAdd(camdir,tmp2,0);
                    cam_ray_direction=tmp1->normalize(tmp1,0);
                    tmp1->destructor(tmp1);
                    tmp2->destructor(tmp2);
                    Ray *cam_ray;
                    cam_ray=Ray_Constructor_Vect(cam_ray_origin,cam_ray_direction);

                    Vector *intersections;
                    intersections=Vector_constructor(30);
                    int index;
                    for(index=0; index<scene_objects->item_index; index++) {
                        Object **x;
                        double *p;
                        x=(Object **)(scene_objects->at(scene_objects,index));
                        if((p=(double *)malloc(sizeof(double)))==NULL) return 0;
                        *p=(*x)->findIntersection(x,cam_ray);
                        intersections->push_back(intersections,p);
                    }

                    int index_of_winning_object=winningObjectIndex(intersections);
                    //printf("%d",index_of_winning_object);
                    if(index_of_winning_object==-1) {
                        //set the background black
                        tempRed[aa_index] = 0;
                        tempGreen[aa_index] = 0;
                        tempBlue[aa_index] = 0;
                    } else {
                        // index corresponds to an object in our scene
                        if((*((double *)(intersections->at(intersections,index_of_winning_object)))) >accuracy ) {
                            //determine the position and direction vectors at the point of the intersection
                            Vect *intersection_position;
                            Vect *tmp_vect;
                            double scalar;
                            scalar=(*((double *)(intersections->at(intersections,index_of_winning_object))));
                            tmp_vect=cam_ray_direction->VectMult(cam_ray_direction,scalar,0);
                            intersection_position=cam_ray_origin->VectAdd(cam_ray_origin,tmp_vect,0);
                            tmp_vect->destructor(tmp_vect);
                            Vect *intersection_ray_direction;
                            intersection_ray_direction=Vect_Constructor();
                            memcpy(intersection_ray_direction,cam_ray_direction,sizeof(*intersection_ray_direction));
                            /**
                            Object **x;
                            x=(Object **)(scene_objects->at(scene_objects,index_of_winning_object));
                            **/
                            Color *intersection_color;

                            intersection_color=getColorAt(intersection_position,intersection_ray_direction,scene_objects,\
                                                          index_of_winning_object, light_sources ,accuracy,ambientlight);

                            tempRed[aa_index]=intersection_color->getColorRed(intersection_color);
                            tempGreen[aa_index]=intersection_color->getColorGreen(intersection_color);
                            tempBlue[aa_index]=intersection_color->getColorBlue(intersection_color);

                            intersection_color->destructor(intersection_color);
                            intersection_position->destructor(intersection_position);
                            intersection_ray_direction->destructor(intersection_ray_direction);

                        }
                    }
                    cam_ray_direction->destructor(cam_ray_direction);
                    intersections->destructor(intersections);
                    cam_ray_origin->destructor(cam_ray_origin);
                    cam_ray->destructor(cam_ray);
                }
            }

            // average the pixel color
            double totalRed = 0;
            double totalGreen = 0;
            double totalBlue = 0;
            int iRed,iGreen,iBlue;
            for (iRed = 0; iRed < aadepth*aadepth; iRed++) {
                totalRed = totalRed + tempRed[iRed];
            }
            for (iGreen = 0; iGreen < aadepth*aadepth; iGreen++) {
                totalGreen = totalGreen + tempGreen[iGreen];
            }
            for (iBlue = 0; iBlue < aadepth*aadepth; iBlue++) {
                totalBlue = totalBlue + tempBlue[iBlue];
            }

            double avgRed = totalRed/(aadepth*aadepth);
            double avgGreen = totalGreen/(aadepth*aadepth);
            double avgBlue = totalBlue/(aadepth*aadepth);

            pixels[thisone].r = avgRed;
            pixels[thisone].g = avgGreen;
            pixels[thisone].b = avgBlue;
        }
    }

    scene_sphere->destructor(scene_sphere);
    free(scene_objects->item); //need to keep the content of the scene_objects->item
    free( scene_objects);
    scene_plane->destructor(scene_plane);
    free(light_sources->item); //need to keep the content of the light_source-item
	free(light_sources);
    scene_cam->destructor(scene_cam);
    scene_light->destructor(scene_light);
    savebmp("scene_anti-aliased.bmp",width,height,dpi,pixels);
    free(pixels);

    t2=clock();
    float diff= (((float)t2)-((float) t1))/1000;

    printf("%f seconds\n",diff);

    return 0;
}

/*********************************************************************** function*******************************************************/

Color* getColorAt(Vect *intersection_position,Vect *intersection_ray_direction,\
                  Vector* scene_objects,int index_of_winning_object,Vector* light_sources ,\
                  double accuracy,double ambientlight)
{

    Object **x;
    x=(Object **)(scene_objects->at(scene_objects,index_of_winning_object));
    Color *winning_object_color;
    winning_object_color=(*x)->getColor(x);
    Vect *winning_object_normal;
    winning_object_normal=(*x)->getNormalAT(x,intersection_position);

    if(winning_object_color->getColorSpecial(winning_object_color) == 2) {
        //check tile floor pattern
        int square= (int) floor(intersection_position->getVectX(intersection_position)) + \
                    (int) floor(intersection_position->getVectZ(intersection_position));
        if((square % 2 )==0) {
            //Black tile
            winning_object_color->setColorRed(winning_object_color,0);
            winning_object_color->setColorGreen(winning_object_color,0);
            winning_object_color->setColorBlue(winning_object_color,0);
        } else {
            //white tile
            winning_object_color->setColorRed(winning_object_color,1);
            winning_object_color->setColorGreen(winning_object_color,1);
            winning_object_color->setColorBlue(winning_object_color,1);

        }
    }


    Color *final_color;
    final_color=winning_object_color->colorScalar(winning_object_color,ambientlight);

    if((winning_object_color->getColorSpecial(winning_object_color)) >0 && (winning_object_color->getColorSpecial(winning_object_color) <=1)) {
        // reflection from objects with specular intensity
        Vect *tmpp=intersection_ray_direction->negative(intersection_ray_direction,0);
        double dot1=winning_object_normal->dotProduct(winning_object_normal,tmpp,0);
        Vect *scalar1=winning_object_normal->VectMult(winning_object_normal,dot1,0);
        Vect *add1=scalar1->VectAdd(scalar1,intersection_ray_direction,0);
        Vect *scalar2=add1->VectMult(add1,2,0);
        
		add1->destructor(add1);
        scalar1->destructor(scalar1);

        //tmpp=intersection_ray_direction->negative(intersection_ray_direction,0);
        tmpp=tmpp->VectAdd(tmpp,scalar2,1);
        Vect *reflection_direction=tmpp->normalize(tmpp,0);
        scalar2->destructor(scalar2);
        tmpp->destructor(tmpp);
        Ray *reflection_ray=Ray_Constructor_Vect(intersection_position,reflection_direction);
        //determine what the ray intersects with first
        Vector *reflection_intersections;
        reflection_intersections=Vector_constructor(5);
        int reflection_index;
        for(reflection_index=0; reflection_index<scene_objects->item_index; reflection_index++) {
            Object **o_tmp;
            o_tmp=(Object **)(scene_objects->at(scene_objects,reflection_index));
            double *double_pointer;
            double_pointer=(double *)malloc(sizeof(double));
            *double_pointer=(*o_tmp)->findIntersection(o_tmp,reflection_ray);
            reflection_intersections->push_back(reflection_intersections,double_pointer);
        }
        int index_of_winning_object_with_reflection;
        index_of_winning_object_with_reflection=winningObjectIndex(reflection_intersections);

        if(index_of_winning_object_with_reflection!=-1) {
            //reflection ray missed everything else
            if((*((double *)(reflection_intersections->at(reflection_intersections,index_of_winning_object_with_reflection)))) >accuracy) {
                //determine the position and direction at the point of intersection with the reflection ray
                //the ray only affects the color if it reflected off something
                Vect *Vect_tmp;
                Vect *reflection_intersection_position;
                Vect_tmp=reflection_direction->VectMult(reflection_direction,(*((double *)(reflection_intersections->at(reflection_intersections,index_of_winning_object_with_reflection)))),0);
                reflection_intersection_position=intersection_position->VectAdd(intersection_position,Vect_tmp,0);
                Vect *reflection_intersection_ray_direction;
                reflection_intersection_ray_direction=Vect_Constructor();
                memcpy(reflection_intersection_ray_direction,reflection_direction,sizeof(*reflection_intersection_ray_direction));
                Color *reflection_intersection_color;
                reflection_intersection_color=getColorAt(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, index_of_winning_object_with_reflection, light_sources, accuracy, ambientlight);
                Color *Color_tmp,*Color_tmp2;
                Color_tmp=reflection_intersection_color->colorScalar(reflection_intersection_color,winning_object_color->getColorSpecial(winning_object_color));
                Color_tmp2=final_color;
                final_color=final_color->colorAdd(final_color,Color_tmp);

                Vect_tmp->destructor(Vect_tmp);
                Color_tmp2->destructor(Color_tmp2);
                Color_tmp->destructor(Color_tmp);
                reflection_intersection_color->destructor(reflection_intersection_color);
                reflection_intersection_position->destructor(reflection_intersection_position);
                reflection_intersection_ray_direction->destructor(reflection_intersection_ray_direction);
            }
        }
        reflection_intersections->destructor(reflection_intersections);
        reflection_ray->destructor(reflection_ray);
        reflection_direction->destructor(reflection_direction);
    }


    int light_index;
    for(light_index=0; light_index<light_sources->item_index; light_index++) {
        Source **s; //Source pointer
        s=(Source**) (light_sources->at(light_sources,light_index));
        Vect *light_direction;
        light_direction=(*s)->getLightPosition(s);
        Vect *tmp;
        tmp=intersection_position->negative(intersection_position,0);
        light_direction=light_direction->VectAdd(light_direction,tmp,1);
        light_direction->self_normalize(light_direction);
        tmp->destructor(tmp);
        double cosine_angle;
        cosine_angle=winning_object_normal->dotProduct(winning_object_normal,light_direction,0);

        if (cosine_angle >0) {
            //test for shadows
            bool shadowed=false;

            Vect *distance_to_light;
            distance_to_light=(*s)->getLightPosition(s);
            tmp=intersection_position->negative(intersection_position,0);
            distance_to_light=distance_to_light->VectAdd(distance_to_light,tmp,1);
            distance_to_light->self_normalize(distance_to_light);
            tmp->destructor(tmp);
            double distance_to_light_magnitude;
            distance_to_light_magnitude=distance_to_light->magnitude(distance_to_light);

            Ray *shadow_ray;
            Vect *tmp2;
            tmp=(*s)->getLightPosition(s);
            tmp2=intersection_position->negative(intersection_position,0);
            tmp=tmp->VectAdd(tmp,tmp2,1);
            tmp->self_normalize(tmp);
            Vect *for_long;
            for_long=(Vect*)malloc(sizeof(Vect));
            memcpy(for_long,tmp,sizeof(*for_long));
            shadow_ray=Ray_Constructor_Vect(intersection_position,for_long);
            tmp->destructor(tmp);
            tmp2->destructor(tmp2);

            Vector *secondary_intersections;

            secondary_intersections=Vector_constructor(10);
            int object_index;
            for(object_index=0; (object_index < scene_objects->item_index) && shadowed==false; object_index++) {
                Object **O;
                O=(Object **)(scene_objects->at(scene_objects,object_index));
                double *p;
                p=(double *)malloc(sizeof(double));
                *p=(*O)->findIntersection(O,shadow_ray);
                secondary_intersections->push_back(secondary_intersections,p);
            }
            int c;
            for(c=0; c < secondary_intersections->item_index; c++) {
                double compare_tmp;
                compare_tmp=*((double *)(secondary_intersections->at(secondary_intersections,c)));
                if( compare_tmp > accuracy) {
                    if (compare_tmp<=distance_to_light_magnitude) {
                        shadowed=true;
                    }
                    break;
                }
            }
            if(shadowed==false) {
                Color *color_tmp,*tmp3,*tmp4;
                tmp3=(*s)->getColor(s);
                color_tmp=winning_object_color->colorMultiply(winning_object_color,tmp3);
                tmp4=color_tmp->colorScalar(color_tmp,cosine_angle);
                color_tmp->destructor(color_tmp);
                color_tmp=final_color;
                final_color=final_color->colorAdd(final_color,tmp4);

                color_tmp->destructor(color_tmp);
                tmp3->destructor(tmp3);
                tmp4->destructor(tmp4);
                if(winning_object_color->getColorSpecial(winning_object_color) >0 && winning_object_color->getColorSpecial(winning_object_color) <= 1 ) {
                    //special [0-1]
                    double dot1;
                    tmp=intersection_ray_direction->negative(intersection_ray_direction,0);
                    dot1=winning_object_normal->dotProduct(winning_object_normal,tmp,0);
                    tmp->destructor(tmp);
                    Vect *scalar1;
                    scalar1=winning_object_normal->VectMult(winning_object_normal,dot1,0);
                    Vect *add1;
                    add1=scalar1->VectAdd(scalar1,intersection_ray_direction,0);
                    scalar1->destructor(scalar1);
                    Vect *scalar2;
                    scalar2=add1->VectMult(add1,2,1);
                    Vect *add2;
                    add2=intersection_ray_direction->negative(intersection_ray_direction,0);
                    add2=add2->VectAdd(add2,scalar2,1);
                    scalar2->destructor(scalar2);
                    Vect *reflection_direction;
                    reflection_direction=add2->normalize(add2,1);

                    double specular;
                    specular=reflection_direction->dotProduct(reflection_direction,light_direction,0);
                    if(specular > 0) {
                        specular=pow(specular,10);
                        color_tmp=(*s)->getColor(s);
                        tmp3=color_tmp->colorScalar(color_tmp,(specular * winning_object_color->getColorSpecial(winning_object_color)));
                        color_tmp->destructor(color_tmp);
                        color_tmp=final_color;
                        final_color=final_color->colorAdd(final_color,tmp3);

                        color_tmp->destructor(color_tmp);
                        tmp3->destructor(tmp3);

                    }
                    reflection_direction->destructor(reflection_direction);
                }
            }
            secondary_intersections->destructor(secondary_intersections);
            distance_to_light->destructor(distance_to_light);
            for_long->destructor(for_long);
            shadow_ray->destructor(shadow_ray);
        }
        light_direction->destructor(light_direction);
        winning_object_color->destructor(winning_object_color);
        winning_object_normal->destructor(winning_object_normal);
    }


    return final_color->clip(final_color,1);
}
/******************************Savebmp***********************/

int savebmp(const char *filename,int w,int h, int dpi,RGBType *data)
{
    FILE *_file;
    int k =w*h;
    int s=4*k;
    int filesize=54+s;

    double factor =39.375;
    int m =(int) factor;

    int ppm=dpi*m;

    unsigned char bmpfileheader[14]= {'B','M',0,0,0,0, 0,0,0,0 ,54,0,0,0};
    unsigned char bmpinfoheader[40]= {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
    /***
    typedef struct tagBITMAPINFOHEADER{
        DWORD biSize;
        LONG biWidth;
        LONG biHeight;
        WORD biPlanes;
        WORD biBitCount
        DWORD biCompression;
        DWORD biSizeImage;
        LONG biXPelsPerMeter;
        LONG biYPelsPerMeter;
        DWORD biClrUsed;
        DWORD biClrImportant;
    }BITMAPINFOHEADER;
    ***/
    bmpfileheader[2]=(unsigned char)(filesize);
    bmpfileheader[3]=(unsigned char)(filesize>>8);
    bmpfileheader[4]=(unsigned char)(filesize>>16);
    bmpfileheader[5]=(unsigned char)(filesize>>24);

    bmpinfoheader[4]=(unsigned char)(w);
    bmpinfoheader[5]=(unsigned char)(w>>8);
    bmpinfoheader[6]=(unsigned char)(w>>16);
    bmpinfoheader[7]=(unsigned char)(w>>24);

    bmpinfoheader[8]=(unsigned char)(h);
    bmpinfoheader[9]=(unsigned char)(h>>8);
    bmpinfoheader[10]=(unsigned char)(h>>16);
    bmpinfoheader[11]=(unsigned char)(h>>24);

    bmpinfoheader[21]=(unsigned char)(s);
    bmpinfoheader[22]=(unsigned char)(s>>8);
    bmpinfoheader[23]=(unsigned char)(s>>16);
    bmpinfoheader[24]=(unsigned char)(s>>24);

    bmpinfoheader[25]=(unsigned char)(ppm);
    bmpinfoheader[26]=(unsigned char)(ppm>>8);
    bmpinfoheader[27]=(unsigned char)(ppm>>16);
    bmpinfoheader[28]=(unsigned char)(ppm>>24);

    bmpinfoheader[29]=(unsigned char)(ppm);
    bmpinfoheader[30]=(unsigned char)(ppm>>8);
    bmpinfoheader[31]=(unsigned char)(ppm>>16);
    bmpinfoheader[32]=(unsigned char)(ppm>>24);

    _file=fopen(filename,"wb");

    fwrite(bmpfileheader,1,14,_file);
    fwrite(bmpinfoheader,1,40,_file);
    int i;
    unsigned char color[3]= {0,0,0};
    for(i=0; i<k; i++) {

        double red=(data[i].r)*255;
        double green=(data[i].g)*255;
        double blue=(data[i].b)*255;

        color[0]=(int)blue;
        color[1]=(int)green;
        color[2]=(int)red;
        fwrite(&color,1,3,_file);
    }
    fclose(_file);
    return 0;
}
/******************************* winningObjectIndex************************************/

int winningObjectIndex(Vector *object_intersections)
{
    //return the index of the winning intersection
    int index_of_minimum_value;

    //prevent unnecessary calculations
    if (object_intersections->item_index==0) {
        //if there ate no intersections
        return -1;
    } else if (object_intersections->item_index==1) {
        if((*((double *)(object_intersections->at(object_intersections,0))))>0) {
            //if that intersections is greater than zero then its our index of minimum value
            return 0;
        } else {
            // otherwise the only intersection value is negative
            return -1;
        }
    } else {
        //otherwise there is more than one intersection
        //first find the maximum value
        double max=0;
        int i;
        for(i=0; i < (object_intersections->item_index) ; i++) {
            if(max<(*((double *)(object_intersections->at(object_intersections,i))))) {
                max=*((double *)(object_intersections->at(object_intersections,i)));
            }
        }
        //then starting from the maximum value find the minimum position
        if(max >0) {
            //we only want positive intersections
            int index;
            for(index =0 ; index < object_intersections->item_index; index++) {
                if (((*((double *)(object_intersections->at(object_intersections,index))))>0) && (*((double *)(object_intersections->at(object_intersections,index)))) <=max ) {
                    max=*((double *)(object_intersections->at(object_intersections,index)));
                    index_of_minimum_value=index;
                }
            }
            return index_of_minimum_value;

        } else {
            //all the intersections were negative
            return -1;
        }
    }

}
