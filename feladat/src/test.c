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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);

    return texture;
}

SDL_Surface* loadSurface( const char* filename )
{

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( filename );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError() );
    }
    

    return loadedSurface;
}

int main(int argc, char* argv[]){
    // Initialize SDL2
    printf("Initializing SDL2...\n");
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
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        printf( "Error: %s\n", glewGetErrorString(err));
    }
    printf( "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    } else {
        printf("SDL_image initialized!\n");
    }

    // Load the fire texture
    // GLuint fireTexture = loadTexture("./assets/textures/fire_particle.png");
    // if (!fireTexture) {
    //     SDL_DestroyRenderer(renderer);
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return 1;}
    // printf("fireTexture: %d\n", fireTexture);

    // GLuint textureId; // Assume this contains the ID of your OpenGL texture
    SDL_Surface* surface = IMG_Load("./assets/textures/fire_particle.png"); // Load the texture image

    // // Create an SDL_Texture from the OpenGL texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture* texture2 = IMG_LoadTexture(renderer, "./assets/textures/fire_particle.png");

    // // Free the SDL_Surface since it is no longer needed
    SDL_FreeSurface(surface);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture2, NULL, NULL);

    //  // Clear screen
    // SDL_SetRenderDrawColor(renderer, 120, 0, 0, 255);
    // SDL_RenderClear(renderer);

    // Draw cube with texture
    SDL_Rect rect;
    rect.x = 50;
    rect.y = 50;
    rect.w = 50;
    rect.h = 50;
    // SDL_RenderCopy(renderer, texture, NULL, &rect);
    // printf("success: %d\n", success);

    // // Update screen
    SDL_RenderPresent(renderer);


    // Wait for user exit
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
           switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                }
                break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    return 0;
}