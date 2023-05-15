#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "camera.h"

typedef struct Particle
{
    float x, y, z;      // Position
    float vx, vy, vz;   // Velocity
    float life;         // Lifetime
}Particle;

typedef struct ParticleSystem
{
    Particle* particles;
    float particle_lifetime;
    float particle_size;
    float particle_velocity_range;
    int particle_count;
    float start[3];
    GLuint texture;
}ParticleSystem;


typedef enum FireEvent {
    FIRE_EVENT_NONE,
    FIRE_EVENT_PARTICLE_COUNT,
    FIRE_EVENT_LIFETIME,
    FIRE_EVENT_VELOCITY_RANGE,
    FIRE_EVENT_SIZE
}FireEvent;

/* initalize particle system */
void init_particle(ParticleSystem* ps,int particle_count, float particle_lifetime, float particle_size, float particle_velocity_range);

void recount_particles(ParticleSystem* ps, int particle_count);

/* update particle system */
void update_particle(ParticleSystem* ps, float dt);

/* render particle system */
void render_particle(ParticleSystem* ps,Camera* camera);

void set_fire_material();

/* destroy particle system */
void destroy_particle(ParticleSystem* ps);

#endif /* PARTICLE_H */