#include <math.h>

#include "particle.h"

void particle_init(Particle *p, double x, double y, double vx, double vy, double m, double r, double k, double g)
{
    p->x = x;
    p->y = y;
    p->vx = vx;
    p->vy = vy;
    p->m = m;
    p->r = r;
    p->k = k;
    p->g = g;
}

void particle_update(Particle *p, double dt)
{
    p->x += p->vx * dt;
    p->y += p->vy * dt;
    p->vy += p->g * dt;
}