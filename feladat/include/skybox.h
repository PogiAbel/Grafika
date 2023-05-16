#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

void setup_cube_map(GLuint *texture);

void setup_cube_map_texture(GLuint *texture, SDL_Surface *xpos, SDL_Surface *xneg, SDL_Surface *ypos, SDL_Surface *yneg, SDL_Surface *zpos, SDL_Surface *zneg);

void delete_cube_map(GLuint *texture);

void init_cubemap_texture(GLuint *cubemap_texture);

void render_skybox(GLuint *cubemap_texture,GLuint shader_program);
#endif // SKYBOX_H