#pragma once
#include <math.h>
typedef float vec3 [3] ;
typedef float vec2 [2] ;

extern double timefs;

extern void rotate_x(float rad,vec3 in,vec3* out);
extern void rotate_y(float rad,vec3 in,vec3* out);
extern void rotate_z(float rad,vec3 in,vec3* out);
extern float sdtorus(vec3 p,float R, float r);
extern void get_normal(vec3 sp,vec3* out);
extern float get_dist(vec3 p);
extern float get_light(vec3 sp);
extern float raymarch(float nx, float ny);
