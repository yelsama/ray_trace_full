/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_intersect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:29:13 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/15 21:15:19 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static void	calculate_intersecion(const t_ray *r, const t_sphere *s, float *inf)
{
	float			a;
	float			b;
	float			c;
	float			det;
	t_point_vector	tmp;

	tmp = get_vec_a_to_b(&s->cent, r->origin);
	b = 2.0 * dot_multiplication(&tmp, &r->direction);
	a = dot_multiplication(&r->direction, &r->direction);
	c = dot_multiplication(&tmp, &tmp) - (s->rad * s->rad);
	det = (b * b) - (4 * a * c);
	if (det < 0.0)
		return ;
	a = 2.0 * a;
	det = sqrtf(det) / a;
	c = (-1.0 * b) / a;
	inf[1] = c + det;
	inf[2] = c - det;
	if (inf[2] > 0 || inf[1] > 0)
		inf[0] = 1;
	else
		inf[0] = 0;
}

t_hit_info	ray_sphare_intrsection(const t_ray *r, const t_sphere *s)
{
	float		tmp;
	t_hit_info	new;
	float		inf[3];
	// t_point_vector t1;
	// t_color			clr;

	// clr = (t_color)s->color;
	// t1 = (t_point_vector)s->cent;
	// printf("got to sphere rad: %f, with color red: %f, green: %f, blue: %f\n", s->rad, clr.red, clr.green, clr.blue);
	// print_an_elemnt(&t1);
	// exit(0);
	if (!r || !s)
	{
		write(2, "Error getting intersctions with sphere\n", 39);
		return (new.hit_or_not = 0, new.t = 0, new);
	}
	inf[0] = 0;
	inf[1] = 0.0;
	inf[2] = 0.0;
	calculate_intersecion(r, s, inf);
	if (inf[1] > inf[2] && inf[2] > 0)
	{
		tmp = inf[1];
		inf[1] = inf[2];
		inf[2] = tmp;
	}
	new.hit_or_not = inf[0];
	new.t = inf[1];
	return (new);
}

t_hit_info	ray_plane_intersection(const t_ray *r, const t_plane *p)
{
	t_point_vector	oc_v;
	float			vdotn;
	float			oc_vdotn;
	t_hit_info		new;

	new.hit_or_not = 0;
	new.t = 0;
	if (!r || !p)
	{
		write(2, "Error getting intersctions with plane\n", 39);
		return (new);
	}
	oc_v = get_vec_a_to_b(r->origin, &p->c_point);
	// oc_v = vec_norm(&oc_v);
	vdotn = dot_multiplication(&r->direction, &p->normal_v);
	if (vdotn == 0.0)
		return (new);
	oc_vdotn = dot_multiplication(&oc_v, &p->normal_v);
	new.t = oc_vdotn / vdotn;
	if (new.t < 0.00001)
		return (new);
	new.hit_or_not = 1;
	return (new);
}


// t_hit_info		ray_cylinder_intersect(const t_ray *r, const t_cylndr *c)
// {
// 	t_hit_info		new;
// 	float	xyz_min[3];
// 	float	xyz_max[3];

// 	if (c->start.x < c->end.x)
// 	{
// 		xyz_min[0] = c->start.x - c->rad;
// 		xyz_max[0] = c->end.x + c->rad;
// 	}
// 	else
// 	{
// 		xyz_min[0] = c->end.x - c->rad;
// 		xyz_max[0] = c->start.x + c->rad;
// 	}
// 	if (c->start.y < c->end.y)
// 	{
// 		xyz_min[1] = c->start.y - c->rad;
// 		xyz_max[1] = c->end.y + c->rad;
// 	}
// 	else
// 	{
// 		xyz_min[1] = c->end.y - c->rad;
// 		xyz_max[1] = c->start.y + c->rad;
// 	}

		
// }

 /// Line segment VS <cylinder>
 // - cylinder (A, B, r) (start point, end point, radius)
 // - line has starting point (x0, y0, z0) and ending point (x0+ux, y0+uy, z0+uz) ((ux, uy, uz) is "direction")
 // => start = (x0, y0, z0)
 //   dir = (ux, uy, uz)
 //   A
 //   B
 //   r
 //   optimize? (= don't care for t > 1)
 // <= t  = "time" of intersection
 //   norm = surface normal of intersection point
// void CollisionExecuter::cylinderVSline(const Ogre::Vector3& start, const Ogre::Vector3& dir, const Ogre::Vector3& A, const Ogre::Vector3& B, const double r,
//              const bool optimize, double& t, Ogre::Vector3& normal) {
//   t = NaN;

//   // Solution : http://www.gamedev.net/community/forums/topic.asp?topic_id=467789
//   double cxmin, cymin, czmin, cxmax, cymax, czmax;
//   if (A.z < B.z) { czmin = A.z - r; czmax = B.z + r; } else { czmin = B.z - r; czmax = A.z + r; }
//   if (A.y < B.y) { cymin = A.y - r; cymax = B.y + r; } else { cymin = B.y - r; cymax = A.y + r; }
//   if (A.x < B.x) { cxmin = A.x - r; cxmax = B.x + r; } else { cxmin = B.x - r; cxmax = A.x + r; }
//   if (optimize) {
//    if (start.z >= czmax && (start.z + dir.z) > czmax) return;
//    if (start.z <= czmin && (start.z + dir.z) < czmin) return;
//    if (start.y >= cymax && (start.y + dir.y) > cymax) return;
//    if (start.y <= cymin && (start.y + dir.y) < cymin) return;
//    if (start.x >= cxmax && (start.x + dir.x) > cxmax) return;
//    if (start.x <= cxmin && (start.x + dir.x) < cxmin) return;
//   }

//   Ogre::Vector3 AB = B - A;
//   Ogre::Vector3 AO = start - A;
//   Ogre::Vector3 AOxAB = AO.crossProduct(AB);
//   Ogre::Vector3 VxAB  = dir.crossProduct(AB);
//   double ab2 = AB.dotProduct(AB);
//   double a = VxAB.dotProduct(VxAB);
//   double b = 2 * VxAB.dotProduct(AOxAB);
//   double c = AOxAB.dotProduct(AOxAB) - (r*r * ab2);
//   double d = b * b - 4 * a * c;
//   if (d < 0) return;
//   double time = (-b - sqrt(d)) / (2 * a);
//   if (time < 0) return;

//   Ogre::Vector3 intersection = start + dir * time;        /// intersection point
//   Ogre::Vector3 projection = A + (AB.dotProduct(intersection - A) / ab2) * AB; /// intersection projected onto cylinder axis
//   if ((projection - A).length() + (B - projection).length() > AB.length()) return; /// THIS IS THE SLOW SAFE WAY
//   //if (projection.z > czmax - r || projection.z < czmin + r ||
//   // projection.y > cymax - r || projection.y < cymin + r ||
//   // projection.x > cxmax - r || projection.x < cxmin + r ) return; /// THIS IS THE FASTER BUGGY WAY

//   normal = (intersection - projection);
//   normal.normalise();
//   t = time; /// at last
//  }
