#include "scene.h"
#include <math.h>
#include <GL/gl.h>

#define PI 3.14159265358979323846

void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    draw_origin();
    draw_ball(0.5, 0.5, 0.5, 0.1);
}

void draw_ball(double x, double y, double z, double radius) {
    // TODO: implement ball.h and ball object so can change coordinates
    int slices = 20;
    int stacks = 20;
    double slice_step = 2 * PI / slices;
    double stack_step = PI / stacks;

    glPushMatrix();
    glTranslatef(x, y, z);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= stacks; i++) {
        double stack_angle = i * stack_step;
        for (int j = 0; j <= slices; j++) {
            double slice_angle = j * slice_step;
            double x = cos(slice_angle) * sin(stack_angle) * radius;
            double y = sin(slice_angle) * sin(stack_angle) * radius;
            double z = cos(stack_angle) * radius;
            glVertex3d(x, y, z);
            x = cos(slice_angle) * sin(stack_angle + stack_step) * radius;
            y = sin(slice_angle) * sin(stack_angle + stack_step) * radius;
            z = cos(stack_angle + stack_step) * radius;
            glVertex3d(x, y, z);
        }
    }
    glEnd();
    glPopMatrix();
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

    // draw ball
    glBegin(GL_TRIANGLE_FAN);

    glColor3f(1, 1, 1);
    glVertex3f(0.5, 0.5, 0.5);

    glEnd();
}
