#include "raytrace.h"

t_hit_info		ray_cylinder_intersect(const t_ray *r, const t_cylndr *c)
{
	t_point_vector	n;
	t_point_vector	p0_cnt;
	float			dist;
	float			tmp;
	t_hit_info		inf;

	inf.hit_or_not = 0;
	inf.t = 0;
	n = cros_multiplication(&r->direction, &c->vec);
	p0_cnt = get_vec_a_to_b(r->origin, &c->cnt);
	tmp = vec_mag(&n);
	if (tmp == 0)
	{
		inf.hit_or_not = 1;
		inf.t = 30;
		return (inf);
	}
	dist = (dot_multiplication(&p0_cnt, &n) / fabs(tmp));
	if (fabs(dist) > c->rad)
		return (inf);
	
	inf.t = 30;
	inf.hit_or_not = 1;
	return (inf);
}
