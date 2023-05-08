#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdbool.h>

#include "app.h"
#include "particle.h"

int init_app(App* app, int width, int height){

     // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Failed to initialize SDL2: %s\n", SDL_GetError());
    }

    // Create a window
    app->window = SDL_CreateWindow("Fire Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!app->window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create an OpenGL context
    app->gl_context = SDL_GL_CreateContext(app->window);

    if (!app->gl_context) {
        fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(app->window);
        SDL_Quit();
        return 1;
    }

    // Initialize GLEW
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(glewError));
        SDL_GL_DeleteContext(app->gl_context);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
        return 1;
    }

    init_particle(app->ps,10, 3.0f, 0.35f, 0.5f);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);

    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Set up the viewport
    glViewport(0, 0, width, height);

    return 0;
}

void render(App* app){
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update and render the particle system
    update_particle(app->ps,app->elapsedTime);
    render_particle(app->ps);

    // Swap the buffers
    SDL_GL_SwapWindow(app->window);
}

void handle_events(App* app){
    SDL_Event event;
    bool quit = false;
    Uint32 lastFrameTime = SDL_GetTicks();

    while(!quit){
        Uint32 currentFrameTime = SDL_GetTicks();
        app->elapsedTime = (currentFrameTime - (Uint32)lastFrameTime) / 1000.0f; // Convert to seconds
        lastFrameTime = currentFrameTime;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    quit = true;
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
        render(app);
    }
    
}

void destroy_app(App* app){
    // Destroy the particle system
    destroy_particle(app->ps);

    // Destroy the OpenGL context
    SDL_GL_DeleteContext(app->gl_context);

    // Clean up SDL2 and exit
    SDL_DestroyWindow(app->window);
    free(app);
    SDL_Quit();
}