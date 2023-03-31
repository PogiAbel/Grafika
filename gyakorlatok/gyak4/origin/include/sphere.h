#ifndef SPHERE_H
#define SPHERE_H

typedef struct Sphere{
    double x;
    double y;
    double z;
    double radius;
} Sphere;

void init_sphere(Sphere *sphere);

void draw_sphere(Sphere *sphere);

void move_sphere(Sphere *sphere, int x, int y, int z);

#endif /* SPHERE_H */