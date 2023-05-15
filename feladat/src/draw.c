#include "obj/draw.h"
#include "texture.h"

#include <GL/gl.h>

void draw_model(const Model* model)
{
    draw_triangles(model);
}

void draw_model_texture(const Model* model, const char* texture_filename)
{
    GLuint texture_id;

    texture_id = load_texture(texture_filename);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    GLfloat tex_coords[] = {
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0,
    };

    // Enable vertex array and texture coordinate array
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Specify the vertex and texture coordinate data for the object's geometry
    glVertexPointer(3, GL_FLOAT, 0, model->vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);

    draw_triangles(model);

    // Disable vertex array and texture coordinate array
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
}

void draw_triangles(const Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    float x, y, z, u, v;

    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i) {
        for (k = 0; k < 3; ++k) {

            normal_index = model->triangles[i].points[k].normal_index;
            x = model->normals[normal_index].x;
            y = model->normals[normal_index].y;
            z = model->normals[normal_index].z;
            glNormal3f(x, y, z);

            texture_index = model->triangles[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            glTexCoord2f(u, 1.0 - v);

            vertex_index = model->triangles[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3f(x, y, z);
        }
    }

    glEnd();
}
