#include "obj/model.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void init_model(Model* model)
{
    model->n_vertices = 0;
    model->n_texture_vertices = 0;
    model->n_normals = 0;
    model->n_triangles = 0;
    model->vertices = NULL;
    model->texture_vertices = NULL;
    model->normals = NULL;
    model->triangles = NULL;
}

void allocate_model(Model* model)
{
    model->vertices =
        (Vertex*)malloc((model->n_vertices + 1) * sizeof(Vertex));
    model->texture_vertices =
        (TextureVertex*)malloc((model->n_texture_vertices + 1) * sizeof(TextureVertex));
    model->normals =
        (Vertex*)malloc((model->n_normals + 1) * sizeof(Vertex));
    model->triangles =
        (Triangle*)malloc(model->n_triangles * sizeof(Triangle));
}

void rotate_model(Model* model, double angle){
    float radian = angle * (M_PI / 180.0f);
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

rotate_model_z(Model* model,double angle){
    float radian = angle * (M_PI / 180.0f);
    float cosine = cosf(radian);
    float sine = sinf(radian);

    for (int i = 1; i <= model->n_vertices; i++) {
        float x = model->vertices[i].x;
        float y = model->vertices[i].y;
        float z = model->vertices[i].z;

        model->vertices[i].x = x * cosine - y * sine;
        model->vertices[i].y = x * sine + y * cosine;
        model->vertices[i].z = z;
    }
}

void translate_model(Model* model, double x, double y, double z){
    for (int i = 1; i <= model->n_vertices; i++) {
        model->vertices[i].x += x;
        model->vertices[i].y += y;
        model->vertices[i].z += z;
    }
}

void free_model(Model* model)
{
    if (model->vertices != NULL) {
        free(model->vertices);
    }
    if (model->texture_vertices != NULL) {
        free(model->texture_vertices);
    }
    if (model->normals != NULL) {
        free(model->normals);
    }
    if (model->triangles != NULL) {
        free(model->triangles);
    }
    init_model(model);
}

void scale_model(Model* model, double sx, double sy, double sz)
{
    int i;

    for (i = 1; i <= model->n_vertices; ++i) {
        model->vertices[i].x *= sx;
        model->vertices[i].y *= sy;
        model->vertices[i].z *= sz;
    }
}
