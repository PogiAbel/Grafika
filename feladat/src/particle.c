#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "particle.h"
#include "texture.h"
#include "camera.h"

static float START_X = 0.6f;
static float START_Y = -3.2f;
static float  START_Z = -2.0f;

void init_particle(ParticleSystem* ps,int particle_count, float particle_lifetime, float particle_size, float particle_velocity_range){
    ps->texture = load_texture("./assets/textures/fire_particle.png");
    ps->particles = malloc(particle_count * sizeof(Particle));
    ps->particle_lifetime = particle_lifetime;
    ps->particle_size = particle_size;
    ps->particle_velocity_range = particle_velocity_range;
    ps->particle_count = particle_count;
    ps->start[0] = START_X;
    ps->start[1] = START_Y;
    ps->start[2] = START_Z;
    ps->fire_color = FIRE_COLOR_RED;

    for (int i = 0; i < particle_count; i++) {
        ps->particles[i].x = ps->start[0];
        ps->particles[i].y = ps->start[1];
        ps->particles[i].z = ps->start[2];

        ps->particles[i].vx = ((float)rand() / RAND_MAX) * particle_velocity_range - (particle_velocity_range / 2);
        ps->particles[i].vy = ((float)rand() / RAND_MAX) * particle_velocity_range - (particle_velocity_range / 2);
        ps->particles[i].vz = ((float)rand() / RAND_MAX) * particle_velocity_range + 0.1f;

        ps->particles[i].life = ((float)rand() / RAND_MAX) * particle_lifetime + particle_lifetime / 2;
    }
}

void recount_particles(ParticleSystem* ps, int particle_count){
    free(ps->particles);
    ps->particles = malloc(particle_count * sizeof(Particle));
    ps->particle_count = particle_count;

}

void update_particle(ParticleSystem* ps, float dt){
    for (int i = 0; i < ps->particle_count; i++) {
        ps->particles[i].x += ps->particles[i].vx * dt;
        ps->particles[i].y += ps->particles[i].vy * dt;
        ps->particles[i].z += ps->particles[i].vz * dt;

        ps->particles[i].life -= dt;

        if (ps->particles[i].life <= 0.0f) {
            ps->particles[i].x = ps->start[0];
            ps->particles[i].y = ps->start[1];
            ps->particles[i].z = ps->start[2];

            ps->particles[i].vx = ((float)rand() / RAND_MAX) * ps->particle_velocity_range - (ps->particle_velocity_range / 1.5);
            ps->particles[i].vy = ((float)rand() / RAND_MAX) * ps->particle_velocity_range - (ps->particle_velocity_range / 1.5);
            ps->particles[i].vz = ((float)rand() / RAND_MAX) * ps->particle_velocity_range + 0.1f;


            ps->particles[i].life = ((float)rand() / RAND_MAX) * ps->particle_lifetime + ps->particle_lifetime / 2;
        }
    }
}

void render_particle(ParticleSystem* ps, Camera* camera){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.2f);

    set_fire_material(ps->fire_color);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, ps->texture);
    
    // calculate rotation angel
    float dx = camera->position.x - ps->start[0];
    float dy = camera->position.y - ps->start[1];
    GLfloat angle = atan2(dy, dx) * 180 / M_PI;

    glPushMatrix();
    glTranslatef(ps->start[0], ps->start[1], ps->start[2]);
    glRotatef( angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-ps->start[0], -ps->start[1], -ps->start[2]);
    // glNormal3f(-dx, -dy, 0.0f);
    glBegin(GL_QUADS);
    for (int i = 0; i < ps->particle_count; i++) {

        float alpha = ps->particles[i].life / ps->particle_lifetime;
        glColor4f(1.0f, 1.0f, 1.0f, alpha);

        float size = ps->particle_size * alpha;

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(ps->particles[i].x, ps->particles[i].y - size, ps->particles[i].z - size);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(ps->particles[i].x, ps->particles[i].y - size, ps->particles[i].z + size);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(ps->particles[i].x, ps->particles[i].y + size, ps->particles[i].z + size);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(ps->particles[i].x, ps->particles[i].y + size, ps->particles[i].z - size);

    }
    glEnd();
    glPopMatrix();

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void set_fire_material(FireColor fire_color)
{
    GLfloat brightness = 20.0f;
    float ambient_material_color[] = { 0.0f,0.0f,0.0,1.0f };
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    switch (fire_color)
    {
    case FIRE_COLOR_RED:
        r = 5.0f;
        break;
    case FIRE_COLOR_GREEN:
        g = 5.0f;
        break;
    case FIRE_COLOR_BLUE:
        b = 5.0f;
        break;
    default:
        r = 5.0f;
        break;
    }
    float diffuse_material_color[] = { r*0.2f,g*0.2f,b*0.2f,1.0f };
    float specular_material_color[] = { 0.0f,0.0f,0.0f,0.0f };
    GLfloat emissive_color[] = { r*0.2f, g*0.2f, b*0.2f, 1.0f };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &brightness);
}

void get_rgb(float* rgb,FireColor color){
    rgb[0] = 0.2 ;
    rgb[1] = 0.2 ;
    rgb[2] = 0.2 ;
    switch (color)
    {
    case FIRE_COLOR_RED:
        rgb[0] = 5.0f;
        break;
    case FIRE_COLOR_GREEN:
        rgb[1] = 5.0f;
        break;
    case FIRE_COLOR_BLUE:
        rgb[2] = 5.0f;
        break;
    default:
        rgb[0] = 5.0f;
        break;
    }
}

void destroy_particle(ParticleSystem* ps){
    free(ps->particles);
    free(ps);
}