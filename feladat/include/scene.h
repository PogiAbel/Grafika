#ifndef SCENE_H
#define SCENE_H

#include "obj/model.h"
#include "obj/load.h"
#include "obj/draw.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <GL/gl.h>

typedef struct Scene
{
    Model model[7];
    Model skybox_model;
    Material material;
    GLuint texture_id[7];
    GLuint skybox_texture_id;
} Scene;

/* Initialize scene */
void init_scene(Scene* scene);

void set_lighting();

void set_material(const Material* material);

void update_scene(Scene* scene);

void render_scene(Scene* scene);

void render_skybox();

void draw_origin();

#endif // "SCENE_H"