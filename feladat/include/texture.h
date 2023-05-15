#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glu.h>
#include <GL/gl.h>

GLuint load_texture(const char *filename);

#endif /* TEXTURE_H */