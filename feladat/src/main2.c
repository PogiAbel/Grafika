#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glu.h>
#include <GL/gl.h>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PARTICLE_LIFETIME 3.0f
#define PARTICLE_VELOCITY_RANGE 0.5f
#define PARTICLE_SIZE 0.35f


typedef struct Particle {
    float x, y, z;      // Position
    float vx, vy, vz;   // Velocity
    float life;         // Lifetime
} Particle;

static GLuint fireTexture;
static Particle* particles;
static int numParticles;

// Load a texture from a file using SDL2 and OpenGL
GLuint loadTexture(const char* filename) {
    // SDL_Surface* surface = SDL_LoadBMP(filename);
    SDL_Surface* surface = IMG_Load(filename);

    if (!surface) {
        fprintf(stderr, "Failed to load texture: %s\n", SDL_GetError());
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);

    return texture;
}

// Initialize the particle system
void initParticles(int numParticles) {
    particles = malloc(numParticles * sizeof(Particle));

    for (int i = 0; i < numParticles; i++) {
        particles[i].x = 0.0f;
        particles[i].y = 0.0f;
        particles[i].z = 0.0f;

        particles[i].vx = ((float)rand() / RAND_MAX) * PARTICLE_VELOCITY_RANGE - (PARTICLE_VELOCITY_RANGE / 2);
        particles[i].vy = ((float)rand() / RAND_MAX) * PARTICLE_VELOCITY_RANGE + 0.1f;
        particles[i].vz = ((float)rand() / RAND_MAX) * PARTICLE_VELOCITY_RANGE - (PARTICLE_VELOCITY_RANGE / 2);

        particles[i].life = ((float)rand() / RAND_MAX) * PARTICLE_LIFETIME + PARTICLE_LIFETIME / 2;
    }
}

// Update the particle system
void updateParticles(float dt) {
    for (int i = 0; i < numParticles; i++) {
        particles[i].x += particles[i].vx * dt;
        particles[i].y += particles[i].vy * dt;
        particles[i].z += particles[i].vz * dt;

        particles[i].life -= dt;

        if (particles[i].life <= 0.0f) {
            particles[i].x = 0.0f;
            particles[i].y = 0.0f;
            particles[i].z = 0.0f;

            particles[i].vx = ((float)rand() / RAND_MAX) * PARTICLE_VELOCITY_RANGE - (PARTICLE_VELOCITY_RANGE / 2);
            particles[i].vy = ((float)rand() / RAND_MAX) * PARTICLE_VELOCITY_RANGE + 0.1f;
            particles[i].vz = ((float)rand() / RAND_MAX) * PARTICLE_VELOCITY_RANGE - (PARTICLE_VELOCITY_RANGE / 2);

            particles[i].life = ((float)rand() / RAND_MAX) * PARTICLE_LIFETIME + PARTICLE_LIFETIME / 2;
        }
    }
}

// Render the particle system
void renderParticles() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, fireTexture);

    glBegin(GL_QUADS);

    for (int i = 0; i < numParticles; i++) {
        float alpha = particles[i].life / PARTICLE_LIFETIME;

        glColor4f(1.0f, 1.0f, 1.0f, alpha);

        float size = PARTICLE_SIZE * alpha;

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(particles[i].x - size, particles[i].y - size, particles[i].z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(particles[i].x + size, particles[i].y - size, particles[i].z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(particles[i].x + size, particles[i].y + size, particles[i].z);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(particles[i].x - size, particles[i].y + size, particles[i].z);
    }

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

// Clean up the particle system
void cleanupParticles() {
    free(particles);
}

// Main function
int main(int argc, char* argv[]) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Failed to initialize SDL2: %s\n", SDL_GetError());
    return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Fire Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create an OpenGL context
    SDL_GLContext context = SDL_GL_CreateContext(window);

    if (!context) {
        fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize GLEW
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(glewError));
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load the fire texture
    fireTexture = loadTexture("./assets/textures/fire_particle.png");

    if (!fireTexture) {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize the particle system
    numParticles = 1000;
    initParticles(numParticles);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 0.1, 100.0);

    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Set up the viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Set up the event loop
    SDL_Event event;
    bool quit = false;
    Uint32 lastFrameTime = SDL_GetTicks();

    while (!quit) {
         Uint32 currentFrameTime = SDL_GetTicks();
        float elapsedTime = (currentFrameTime - lastFrameTime) / 1000.0f; // Convert to seconds
        lastFrameTime = currentFrameTime;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update and render the particle system
        updateParticles(elapsedTime);
        renderParticles();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
    }

    // Clean up the particle system
    cleanupParticles();

    // Clean up SDL2
    SDL_GL_DeleteContext(context);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
