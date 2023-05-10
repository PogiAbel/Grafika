#include "scene.h"
#define PI 3.14159265358979323846

void rotate_model_x(Model* model, float angle)
{
    float radian = angle * (PI / 180.0f);
    float cosine = cosf(radian);
    float sine = sinf(radian);

    for (int i = 1; i <= model->n_vertices; i++) {
        float x = model->vertices[i].x;
        float y = model->vertices[i].y;
        float z = model->vertices[i].z;

        model->vertices[i].x = x;
        model->vertices[i].y = y * cosine - z * sine;
        model->vertices[i].z = y * sine + z * cosine;
    }
}

void init_scene(Scene* scene){
    load_model(&scene->model,"./assets/models/scene.obj");
    rotate_model_x(&scene->model, 90.0f);

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 0.0;
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 5.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { -5.0f, 0.0f, 5.0f, 1.0f };

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
    set_lighting();
    draw_model(&(scene->model));
}