#include "scene.h"
#include <math.h>
#include <GL/gl.h>
#include "sphere.h"
#include <stdio.h>

void init_scene(Scene* scene)
{
    init_sphere(&scene->sphere);
}

void update_scene(Scene* scene)
{
}

void render_scene(Scene* scene)
{
    static double t = 0;
    draw_origin();
    draw_sphere(&scene->sphere);
    rotate_sphere_x(&scene->sphere,60);
    // rotate_sphere_y(&scene->sphere,30);
    t += 0.01;
}

void draw_origin()
{
    // draw origin
    glBegin(GL_LINES);

    // X axis
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    // Y axis
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    // Z axis
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();

    // draw triangle
    glBegin(GL_TRIANGLES);

    glColor3f(1, 1, 0);
    glVertex3f(1.5, 1.5, 1.5);
    glColor3f(0, 1, 1);
    glVertex3f(2, 2, 2);
    glColor3f(1, 0, 1);
    glVertex3f(2, 0, 2);

    glEnd();
}
