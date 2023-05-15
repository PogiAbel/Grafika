#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>

GLuint load_texture(const char* filename) {
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