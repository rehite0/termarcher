#include "marc.h"

#define length2(a) sqrt(a[0]*a[0]+a[1]*a[1])
#define length3(a) sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2])
#define normalize(a) {a[0]/length3(a),a[1]/length3(a),a[2]/length3(a)}
#define cpy2(a,b) a[0] = b[0];a[1] = b[1];
#define cpy3(a,b) (a)[0] = b[0];(a)[1] = b[1];(a)[2] = b[2];
#define o2(a,b,op) {a[0] op b[0],a[1] op b[1]}
#define o3(a,b,op) {a[0] op b[0],a[1] op b[1],a[2] op b[2]}
#define dot(a,b) (a[0] * b[0]+a[1] * b[1]+a[2] * b[2])

void rotate_x(float rad,vec3 in,vec3* out){
    float s = sin(rad);
    float c = cos(rad);
    vec3 ret= {
	    1.0*in[0]+0.0*in[1]+0.0*in[2],
	    0.0*in[0]+c  *in[1]+-s *in[2],
	    0.0*in[0]+s  *in[1]+c  *in[2]};
    cpy3(*out,ret);
}
void rotate_y(float rad,vec3 in,vec3* out){
    float s = sin(rad); 
    float c = cos(rad);
    vec3 ret= {
	    c  *in[0]+0.0*in[1]+s  *in[2],
	    0.0*in[0]+1.0*in[1]+0.0*in[2],
	    -s *in[0]+0.0*in[1]+c  *in[2]};
    cpy3(*out,ret);
}
void rotate_z(float rad,vec3 in,vec3* out)
{
    float s = sin(rad); 
    float c = cos(rad);
    vec3 ret= {
	    c  *in[0]+-s *in[1]+0.0*in[2],
	    s  *in[0]+c  *in[1]+0.0*in[2],
	    0.0*in[0]+0.0*in[1]+1.0*in[2]};
    cpy3(*out,ret);
}

float sdtorus(vec3 p_,float R, float r){
    vec3 p;
    vec3 temp;
    cpy3(p,p_);
    rotate_x(3.14/2.0, p, &temp);
    cpy3(p,temp);
    rotate_y(timefs,p,&temp);
    cpy3(p,temp);
    rotate_z(timefs,p,&temp);
    cpy3(p,temp);
    vec2 h={p[0],p[2]};
    vec2 q = {length2(h)-R,p[1]};
    return length2(q)-r;
}
float get_dist(vec3 p){
    float r=0.2;
    float R=0.4;
    return sdtorus(p,R,r);
}
void get_normal(vec3 sp,vec3* out){
    float d = get_dist(sp);
    vec3 xyy={0.1,0.0,0.0};
    vec3 yxy={0.0,0.1,0.0};
    vec3 yyx={0.0,0.0,0.1};
    vec3 a=o3(sp,xyy,-);
    vec3 b=o3(sp,yxy,-);
    vec3 c=o3(sp,yyx,-);
    vec3 n = {
        d-get_dist(a),
        d-get_dist(b),
        d-get_dist(c)};
    vec3 nn=normalize(n);
    cpy3(*out, nn);
}
float get_light(vec3 sp){
    vec3 lightpos = {2.0,0.0, 3.0};
    vec3 ltop=o3(lightpos, sp, -);
    vec3 l = normalize(ltop);
    vec3 n;
    get_normal(sp,&n);
    
    float dif = dot(n, l);
    if (dif<0.0) dif=0.0;
    if (dif>1.0) dif=1.0;
    return dif;
}
float raymarch(float nx, float ny){
    vec3 uv={nx,ny,0.0};
    vec3 cam={0.0,0.0,-2.0};
    vec3 _d=o3(uv,cam,-);
    vec3 camd=normalize(_d);

    vec3 o={0.0,0.0,0.0};
    vec3 t;
    cpy3(t,cam);
    float d=0.0;
    for(int i=0;i<100;i++){
	vec3 t_o=o3(o,t,-);
	float dist=get_dist(t_o);
	d+=dist;
	if (dist<=0.005)
	    return get_light(t_o);
	else{ 
	    vec3 temp=o3(t,camd,+dist*);
	    cpy3(t,temp);
	}
    }
    return 0.0;
}
