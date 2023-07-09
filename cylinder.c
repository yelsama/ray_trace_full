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
    if (inf.t < 0.0)
        return (inf);
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
        // if (inf.t < 0.0)
        //     return (inf);
        inf.hit_or_not = 1;
        return (inf);
    }
    return (inf);
}
