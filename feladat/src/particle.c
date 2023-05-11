#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "particle.h"
#include "texture.h"
#include "camera.h"

static float START_X = 0.6f;
static float START_Y = -2.5f;
static float  START_Z = -2.0f;

void init_particle(ParticleSystem* ps,int particle_count, float particle_lifetime, float particle_size, float particle_velocity_range){
    ps->texture = loadTexture("./assets/textures/fire_particle.png");
    ps->particles = malloc(particle_count * sizeof(Particle));
    ps->particle_lifetime = particle_lifetime;
    ps->particle_size = particle_size;
    ps->particle_velocity_range = particle_velocity_range;
    ps->particle_count = particle_count;

    for (int i = 0; i < particle_count; i++) {
        ps->particles[i].x = START_X;
        ps->particles[i].y = START_Y;
        ps->particles[i].z = START_Z;

        ps->particles[i].vx = ((float)rand() / RAND_MAX) * particle_velocity_range - (particle_velocity_range / 2);
        ps->particles[i].vy = ((float)rand() / RAND_MAX) * particle_velocity_range - (particle_velocity_range / 2);
        ps->particles[i].vz = ((float)rand() / RAND_MAX) * particle_velocity_range + 0.1f;

        ps->particles[i].life = ((float)rand() / RAND_MAX) * particle_lifetime + particle_lifetime / 2;
    }
}

void recount_particles(ParticleSystem* ps, int particle_count){
    ps->particles = realloc(ps->particles, particle_count * sizeof(Particle));
    ps->particle_count = particle_count;
}

void update_particle(ParticleSystem* ps, float dt){
    for (int i = 0; i < ps->particle_count; i++) {
        ps->particles[i].x += ps->particles[i].vx * dt;
        ps->particles[i].y += ps->particles[i].vy * dt;
        ps->particles[i].z += ps->particles[i].vz * dt;

        ps->particles[i].life -= dt;

        if (ps->particles[i].life <= 0.0f) {
            ps->particles[i].x = START_X;
            ps->particles[i].y = START_Y;
            ps->particles[i].z = START_Z;
        ps->particles[i].vx = ((float)rand() / RAND_MAX) * ps->particle_velocity_range - (ps->particle_velocity_range / 2);
        ps->particles[i].vy = ((float)rand() / RAND_MAX) * ps->particle_velocity_range - (ps->particle_velocity_range / 2);
        ps->particles[i].vz = ((float)rand() / RAND_MAX) * ps->particle_velocity_range + 0.1f;

        ps->particles[i].life = ((float)rand() / RAND_MAX) * ps->particle_lifetime + ps->particle_lifetime / 2;
        }
    }
}

void render_particle(ParticleSystem* ps, Camera* camera){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ps->texture);
    
    // calculate rotation angel
    float dx = camera->position.x - ps->particles[0].x;
    float dy = camera->position.y - ps->particles[0].y;
    float angle = atan2(dy, dx) * 180 / M_PI;


    glPushMatrix();
    glTranslatef(START_X, START_Y, START_Z);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-START_X, -START_Y, -START_Z);
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

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void destroy_particle(ParticleSystem* ps){
    free(ps->particles);
    free(ps);
}