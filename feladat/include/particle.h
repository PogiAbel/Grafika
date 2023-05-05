#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>

typedef struct Particle
{
    // SDL_Texture* texture;
    float x, y, z;      // Position
    float vx, vy, vz;   // Velocity
    float life;         // Lifetime
}Particle;

void init_particle(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h);

void update_particle();

#endif /* PARTICLE_H */