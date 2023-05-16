#ifndef SCENE_H
#define SCENE_H

#include "obj/model.h"
#include "obj/load.h"
#include "obj/draw.h"
#include "utils.h"
#include "skybox.h"
#include <SDL2/SDL.h>
#include <GL/gl.h>

typedef struct Scene
{
    Model model[7];
    Material material;
    GLuint texture_id;
    GLuint skybox_texture_id;
    GLuint shader_program;
} Scene;

/* Initialize scene */
void init_scene(Scene* scene);

GLuint create_shader_program();

void set_lighting();

void set_material(const Material* material);

void update_scene(Scene* scene);

void render_scene(Scene* scene);

void render_skybox();

#endif // "SCENE_H"