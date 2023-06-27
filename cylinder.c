#include "raytrace.h"


t_hit_info		ray_cylinder_intersect(const t_ray *r, const t_cylndr *c)
{
    t_point_vector  oc_v;
    float           bard;
    float           baoc;
    float           k2;
    float           k1;
    float           k0;
    float           h;
    float           y;
    t_hit_info      inf;

    inf.hit_or_not = 0;
    oc_v = get_vec_a_to_b(&c->a, r->origin);
    bard = dot_multiplication(&c->ba_v, &r->direction);
    baoc = dot_multiplication(&c->ba_v, &oc_v);
    k2 = c->baba - (bard * bard);
    k1 = (c->baba * dot_multiplication(&oc_v, &r->direction)) - (baoc * bard);
    k0 = (c->baba * dot_multiplication(&oc_v, &oc_v)) - (baoc * baoc) - (c->rad * c->rad * c->baba);
    h = k1 * k1 - k2 * k0;
    if (h < 0.0)
        return (inf);
    h = sqrtf(h);
    inf.t = (-1.0 * k1 - h)/k2;
    y = baoc + inf.t * bard;
    if( y > 0.0 && y < c->baba )
    {
        inf.hit_or_not = 1;
        return (inf);
    }
    if (y < 0.0)
        inf.t = (0.0 - baoc) / bard;
    else
        inf.t = (c->baba - baoc) / bard;
    if (fabs(k1 + k2 * inf.t) < h)
    {
        inf.hit_or_not = 1;
        return (inf);
    }
    return (inf);
}

int	light_effect_on_cylndr_pxl_color(t_ranger *alive, t_point_vector hit_p,
int obj_id)
{
	t_cylndr	*c;
	t_color			amb_clr;
	t_color			full_clr;
	t_point_vector	pxl_to_light_v;
	t_point_vector	normal_v;
	t_point_vector	ch_v;
	t_point_vector	n_cnt;
	t_point_vector	tmp;
	float			d;
	float			sa, sb;

	c = (t_cylndr *)alive->objcs[obj_id].the_obj;
	tmp = get_vec_a_to_b(&c->a, &hit_p);
	sa = fabs(vec_mag(&tmp));
	tmp = get_vec_a_to_b(&c->b, &hit_p);
	sb = fabs(vec_mag(&tmp));
	pxl_to_light_v = get_vec_a_to_b(&hit_p, &alive->main_light.position);
	pxl_to_light_v = vec_norm(&pxl_to_light_v);
	ch_v = get_vec_a_to_b(&c->cnt, &hit_p);
	d = dot_multiplication(&ch_v, &c->vec);
	p0_plus_t_mul_v(&n_cnt, &c->cnt, &c->vec, d);
	normal_v = get_vec_a_to_b(&n_cnt, &hit_p);
	normal_v = vec_norm(&normal_v);
	if (sa < c->rad || sb < c->rad)
		normal_v = c->vec;
	amb_clr = blend_two_colors(&alive->amb_appear_clr, &c->color);
	if (under_shadow(alive, hit_p, pxl_to_light_v, obj_id))
		return (rgb_to_int(&amb_clr));
	full_clr = color_multi_scalar(&alive->light_appear_clr,
		dot_multiplication(&normal_v, &pxl_to_light_v));
	full_clr = blend_two_colors(&full_clr, &c->color);
	full_clr = add_colors(&full_clr, &amb_clr);
	return (rgb_to_int(&full_clr));
}
