#ifndef SCENE_H
#define SCENE_H

#include "obj/model.h"
#include "obj/load.h"
#include "obj/draw.h"
#include "utils.h"
#include "texture.h"
#include "camera.h"
#include "particle.h"
#include <SDL2/SDL.h>
#include <GL/gl.h>

typedef struct Scene
{
    Model model[7];
    GLuint texture_id[7];
    Model skybox_model;
    Material material;
    GLuint skybox_texture_id;
    float light_x;
    float light_y;
    float light_z;
    float cutoff;
} Scene;

/* Initialize scene */
void init_scene(Scene* scene);

void set_lighting(Scene* scene, ParticleSystem* ps);

void set_material(const Material* material);

void update_scene(Scene* scene, float eladpsed_time);

void render_scene(Scene* scene);

void render_skybox();

void draw_origin();

void render_help_menu(Scene* scene);

#endif // "SCENE_H"