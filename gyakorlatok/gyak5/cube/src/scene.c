#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <obj/transform.h>
#include <math.h>

#define PI 3.14159265358979323846

void rotate_model_y(Model* model, float angle)
{
    float radian = angle * (PI / 180.0f);
    float cosine = cosf(radian);
    float sine = sinf(radian);

    for (int i = 0; i < model->n_vertices; i++) {
        float x = model->vertices[i].x;
        float y = model->vertices[i].y;
        float z = model->vertices[i].z;

        model->vertices[i].x = x * cosine + z * sine;
        model->vertices[i].y = y;
        model->vertices[i].z = z * cosine - x * sine;
    }
}

void rotate_model_x(Model* model, float angle)
{
    float radian = angle * (PI / 180.0f);
    float cosine = cosf(radian);
    float sine = sinf(radian);

    for (int i = 0; i < model->n_vertices; i++) {
        float x = model->vertices[i].x;
        float y = model->vertices[i].y;
        float z = model->vertices[i].z;

        model->vertices[i].x = x;
        model->vertices[i].y = y * cosine - z * sine;
        model->vertices[i].z = y * sine + z * cosine;
    }
}

void move_model(Model* model, float dx, float dy, float dz) {
    for (int i = 1; i <= model->n_vertices; i++) {
        model->vertices[i].x += dx;
        model->vertices[i].y += dy;
        model->vertices[i].z += dz;
    }
}


void init_scene(Scene* scene)
{
    load_model(&(scene->model1), "assets/models/cube.obj");
    //load_model(&(scene->model2), "assets/models/cube.obj");
    scene->texture_id[0] = load_texture("assets/textures/chess.jpg");
    scene->texture_id[1] = load_texture("assets/textures/fox_texture.png");

    //scale_model(&(scene->model[0]), 2.0, 2.0, 2.0);

    glBindTexture(GL_TEXTURE_2D, scene->texture_id[0]);

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
    // rotate
    // rotate_model_x(&(scene->model1), 5.0f);
    // rotate_model_y(&(scene->model1), 2.0f);

}

void render_scene(Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    draw_model(&(scene->model1));
    //draw_model(&(scene->model2));
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
