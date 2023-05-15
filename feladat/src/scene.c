#include "scene.h"
#include "utils.h"

void init_scene(Scene* scene){
    load_model(&scene->model[0],"./assets/models/land.obj");
    load_model(&scene->model[1],"./assets/models/pit.obj");
    rotate_model(&scene->model[0], 90.0f);
    scale_model(&scene->model[0], 10.0f,10.0f,10.0f);
    translate_model(&scene->model[0], 0.0f, 0.0f, -3.0f);
    rotate_model(&scene->model[1], 90.0f);
    scale_model(&scene->model[1], 2.0f,2.0f,2.0f);
    translate_model(&scene->model[1], 0.6f, -2.5f, -2.0f);

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 0.7;
    scene->material.diffuse.green = 0.7;
    scene->material.diffuse.blue = 0.7;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.4;
}

void set_lighting()
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse_light[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{

}

void render_scene(Scene* scene)
{
    set_material(&(scene->material));
    // draw_model(&(scene->model[1]));
    draw_model_texture(&scene->model[0],"./assets/textures/land.png");
    draw_model_texture(&scene->model[1],"./assets/textures/pit.png");
}