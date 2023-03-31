#include "sphere.h"
#include <GL/gl.h>
#include <math.h>

#define PI 3.14159265358979323846

void init_sphere(Sphere *sphere)
{
    sphere->x = 0.5;
    sphere->y = 0.5;
    sphere->z = 0.5;
    sphere->radius = 0.2;
}

void draw_sphere(Sphere* sphere) {
    int slices = 20;
    int stacks = 20;
    double slice_step = 2 * PI / slices;
    double stack_step = PI / stacks;

    glPushMatrix();
    glTranslatef(sphere->x, sphere->y, sphere->z);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= stacks; i++) {
        double stack_angle = i * stack_step;
        for (int j = 0; j <= slices; j++) {
            double slice_angle = j * slice_step;
            double x = cos(slice_angle) * sin(stack_angle) * sphere->radius;
            double y = sin(slice_angle) * sin(stack_angle) * sphere->radius;
            double z = cos(stack_angle) * sphere->radius;
            glVertex3d(x, y, z);
            x = cos(slice_angle) * sin(stack_angle + stack_step) * sphere->radius;
            y = sin(slice_angle) * sin(stack_angle + stack_step) * sphere->radius;
            z = cos(stack_angle + stack_step) * sphere->radius;
            glVertex3d(x, y, z);
        }
    }
    glEnd();
    glPopMatrix();
}


void move_sphere(Sphere *sphere, int x, int y, int z)
{
    sphere->x += x;
    sphere->y += y;
    sphere->z += z;
}

void rotate_sphere(Sphere *sphere, double t){
    sphere->x = cos(t) * sphere->x - sin(t) * sphere->y;
    sphere->y = sin(t) * sphere->x + cos(t) * sphere->y;
}

void rotate_sphere_x(Sphere *sphere, double angle) {
    double radians = angle * PI / 180.0;
    double cos_angle = cos(radians);
    double sin_angle = sin(radians);
    double new_y = sphere->y * cos_angle - sphere->z * sin_angle;
    double new_z = sphere->y * sin_angle + sphere->z * cos_angle;
    sphere->y = new_y;
    sphere->z = new_z;
}

void rotate_sphere_y(Sphere *sphere, double angle) {
    glPushMatrix();
    glTranslatef(sphere->x, sphere->y, sphere->z);
    glRotatef(angle, 0.0, 1.0, 0.0); // rotate around y-axis
    glTranslatef(-sphere->x, -sphere->y, -sphere->z);
    sphere->x += 0.1;
    glPopMatrix();
}