#include "raytrace.h"


// cylinder defined by extremes a and b, and radious ra
vec4 cylIntersect( in vec3 ro, in vec3 rd, in vec3 a, in vec3 b, float ra )
{
    vec3  ba = b  - a;
    vec3  oc = ro - a;
    float baba = dot(ba,ba);
    float bard = dot(ba,rd);
    float baoc = dot(ba,oc);
    float k2 = baba            - bard*bard;
    float k1 = baba*dot(oc,rd) - baoc*bard;
    float k0 = baba*dot(oc,oc) - baoc*baoc - ra*ra*baba;
    float h = k1*k1 - k2*k0;
    if( h<0.0 ) return vec4(-1.0);//no intersection
    h = sqrt(h);
    float t = (-k1-h)/k2;
    // body
    float y = baoc + t*bard;
    if( y>0.0 && y<baba ) return vec4( t, (oc+t*rd - ba*y/baba)/ra );
    // caps
    t = ( ((y<0.0) ? 0.0 : baba) - baoc)/bard;
    if( abs(k1+k2*t)<h )
    {
        return vec4( t, ba*sign(y)/sqrt(baba) );
    }
    return vec4(-1.0);//no intersection
}

// t_hit_info		ray_cylinder_intersect(const t_ray *r, const t_cylndr *c)
// {
// 	t_point_vector	z;
// 	t_point_vector	x;
// 	t_point_vector	oc_or;
// 	t_point_vector	d;
// 	t_point_vector	sec1;
// 	t_point_vector	sec2;
// 	float			a;
// 	float			b;
// 	float			c_p;
// 	float			det;
// 	float			t1;
// 	float			t2;
// 	// float			y1;
// 	// float			y2;
// 	t_hit_info		inf;

// 	inf.hit_or_not = 0;
// 	inf.t = 0;
// 	z = vec_norm(&c->vec);
// 	oc_or = get_vec_a_to_b(&c->cnt, r->origin);
// 	print_an_elemnt(&oc_or);
// 	// oc_or = vec_norm(&oc_or);
// 	x = cros_multiplication(&z, &r->direction);
// 	x = vec_norm(&x);
// 	d = rescale_vecotr(&x, dot_multiplication(&oc_or, &x));
// 	if (vec_mag(&d) > c->rad)
// 		return (inf);
// 	a = powf(z.x, 2) + powf(z.z, 2);
// 	b = 2 * (oc_or.x * z.x + oc_or.z * z.z);
// 	c_p = powf(oc_or.x, 2) + powf(oc_or.z, 2) - powf(c->rad, 2);
// 	det = powf(b, 2) - (4 * a * c_p);
// 	if (det < 0)
// 		return (inf);
// 	t1 = ((-1.0 * b) - sqrtf(det)) / (2 * a);
// 	t2 = ((-1.0 * b) + sqrtf(det)) / (2 * a);
// 	if (t1 < 0 && t2 < 0)
// 		return (inf);
// 	// y1 = oc_or.y + (t1 * z.y);
// 	// y2 = oc_or.y + (t2 * z.y);
// 	// if ((y1 < 0 || y1 > c->height) && (y2 < 0 || y2 > c->height))
// 	// 	return (inf);
// 	p0_plus_t_mul_v(&sec1, r->origin, &z, t1);
// 	p0_plus_t_mul_v(&sec2, r->origin, &z, t2);
// 	// print_an_elemnt(&sec1);
// 	// print_an_elemnt(&sec2);
// 	// inf.t = t2;
// 	// if (t1 < t2 && t1 >= 0)
// 	// 	inf.t = t1;
// 	inf.t = 30;
// 	inf.hit_or_not = 1;
// 	return (inf);
// }

// t_hit_info		ray_cylinder_intersect(const t_ray *r, const t_cylndr *c)
// {
// 	t_point_vector	z;
// 	t_point_vector	x;
// 	t_point_vector	y;
// 	t_point_vector	d;
// 	t_point_vector	oc_or;
// 	float			dF, beta, gama,tF;
// 	t_hit_info		inf;

// 	inf.hit_or_not = 0;
// 	inf.t = 0;
// 	z = vec_norm(&c->vec);
// 	x = cros_multiplication(&c->vec, &r->direction);
// 	y = cros_multiplication(&z, &x);
// 	x = vec_norm(&x);
// 	y = vec_norm(&y);
// 	oc_or = get_vec_a_to_b(&c->cnt, r->origin);
// 	d = rescale_vecotr(&x, dot_multiplication(&oc_or, &x));
// 	dF = vec_mag(&d);
// 	if (dF > c->rad)
// 		return (inf);
// 	beta = dot_multiplication(&r->direction, &y);
// 	if (beta == 0.0)
// 		return (inf);
// 	tF = (powf(c->rad, 2) - powf(dF, 2)) / powf(beta, 2);
// 	if (tF < 0.0)
// 		return (inf);
// 	gama = dot_multiplication(&r->direction, &z);
// 	inf.t = sqrtf(tF);
// 	inf.hit_or_not = 1;
// 	return (inf);
// }

// t_hit_info		ray_cylinder_intersect(const t_ray *r, const t_cylndr *c)
// {
// 	t_point_vector	n;
// 	t_point_vector	p0_cnt;
// 	float			dist;
// 	float			tmp;
// 	t_hit_info		inf;

// 	inf.hit_or_not = 0;
// 	inf.t = 0;
// 	n = cros_multiplication(&r->direction, &c->vec);
// 	p0_cnt = get_vec_a_to_b(r->origin, &c->cnt);
// 	tmp = vec_mag(&n);
// 	if (tmp == 0)
// 	{
// 		inf.hit_or_not = 1;
// 		inf.t = 30;
// 		return (inf);
// 	}
// 	dist = (dot_multiplication(&p0_cnt, &n) / fabs(tmp));
// 	if (fabs(dist) > c->rad)
// 		return (inf);
	
// 	inf.t = 30;
// 	inf.hit_or_not = 1;
// 	return (inf);
// }
