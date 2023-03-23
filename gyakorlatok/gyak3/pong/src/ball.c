#include "ball.h"

#include <GL/gl.h>

#include <math.h>

#define BALL_SPEED 200

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = BALL_SPEED;
    ball->speed_y = BALL_SPEED;
    ball->rotation = 1;
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
}

void stop_ball(Ball* ball)
{
    ball->rotation = 0;
    ball->speed_x = 0;
    ball->speed_y = 0;
}

void render_ball(Ball* ball)
{
    double angle;
    double x;
    double y;

    static double rotation_angle = 0;
    rotation_angle += ball->rotation;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);

    glRotatef(rotation_angle, 0.0, 0.0, 1.0);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1) {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.8;
    }
    glEnd();
    glPopMatrix();
}
