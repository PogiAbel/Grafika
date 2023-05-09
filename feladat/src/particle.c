#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "particle.h"
#include "texture.h"

void init_particle(ParticleSystem* ps,int particle_count, float particle_lifetime, float particle_size, float particle_velocity_range){
    ps->texture = loadTexture("./assets/textures/fire_particle.png");
    ps->particles = malloc(particle_count * sizeof(Particle));
    ps->particle_lifetime = particle_lifetime;
    ps->particle_size = particle_size;
    ps->particle_velocity_range = particle_velocity_range;
    ps->particle_count = particle_count;

    for (int i = 0; i < particle_count; i++) {
        ps->particles[i].x = 0.0f;
        ps->particles[i].y = 0.0f;
        ps->particles[i].z = 0.0f;

        ps->particles[i].vx = ((float)rand() / RAND_MAX) * particle_velocity_range - (particle_velocity_range / 2);
        ps->particles[i].vy = ((float)rand() / RAND_MAX) * particle_velocity_range + 0.1f;
        ps->particles[i].vz = ((float)rand() / RAND_MAX) * particle_velocity_range - (particle_velocity_range / 2);

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
        ps->particles[i].y += ps->particles[i].vz * dt;
        ps->particles[i].z += ps->particles[i].vy * dt;

        ps->particles[i].life -= dt;

        if (ps->particles[i].life <= 0.0f) {
            ps->particles[i].x = 0.0f;
            ps->particles[i].y = 0.0f;
            ps->particles[i].z = 0.0f;
        ps->particles[i].vx = ((float)rand() / RAND_MAX) * ps->particle_velocity_range - (ps->particle_velocity_range / 2);
        ps->particles[i].vy = ((float)rand() / RAND_MAX) * ps->particle_velocity_range + 0.1f;
        ps->particles[i].vz = ((float)rand() / RAND_MAX) * ps->particle_velocity_range - (ps->particle_velocity_range / 2);

        ps->particles[i].life = ((float)rand() / RAND_MAX) * ps->particle_lifetime + ps->particle_lifetime / 2;
        }
    }
}

void render_particle(ParticleSystem* ps){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ps->texture);

    // setup matrix to face camera
    glMatrixMode(GL_MODELVIEW);
    float modelview[16];
    int i,j;
    glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
    for( i=0; i<3; i++ ) {
        for( j=0; j<3; j++ ) {
            if ( i==j )
                modelview[i*4+j] = 1.0;
            else
                modelview[i*4+j] = 0.0;
        }
    }
    glLoadMatrixf(modelview);

    glBegin(GL_QUADS);

    for (int i = 0; i < ps->particle_count; i++) {
        float alpha = ps->particles[i].life / ps->particle_lifetime;

        glColor4f(1.0f, 1.0f, 1.0f, alpha);

        float size = ps->particle_size * alpha;

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(ps->particles[i].x - size, ps->particles[i].y - size, ps->particles[i].z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(ps->particles[i].x + size, ps->particles[i].y - size, ps->particles[i].z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(ps->particles[i].x + size, ps->particles[i].y + size, ps->particles[i].z);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(ps->particles[i].x - size, ps->particles[i].y + size, ps->particles[i].z);
    }

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void destroy_particle(ParticleSystem* ps){
    free(ps->particles);
    free(ps);
}