#include "obj/draw.h"
#include "texture.h"

#include <GL/gl.h>

void draw_model(const Model* model)
{
    draw_triangles(model);
}

void draw_model_texture(const Model* model, GLuint texture_id)
{
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

void draw_skybox()
{
    GLuint texture_id;

    texture_id = load_texture("./assets/textures/night.png");
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    float scale = 15.0f;


    glBegin(GL_QUADS);

    // Right face
    glTexCoord2f(0.5f, 0.666f);
    glVertex3f(scale, -scale, -scale);
    glTexCoord2f(0.75f, 0.666f);
    glVertex3f(scale, -scale, scale);
    glTexCoord2f(0.75f, 0.333f);
    glVertex3f(scale, scale, scale);
    glTexCoord2f(0.5f, 0.333f);
    glVertex3f(scale, scale, -scale);
    
    // Front face
    glTexCoord2f(0.25f, 1.0f);
    glVertex3f(-scale, -scale, scale);
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(scale, -scale, scale);
    glTexCoord2f(0.5f, 0.666f);
    glVertex3f(scale, scale, scale);
    glTexCoord2f(0.25f, 0.666f);
    glVertex3f(-scale, scale, scale);
    
    // Back face
    glTexCoord2f(0.25f, 0.333f);
    glVertex3f(scale, -scale, -scale);
    glTexCoord2f(0.5f, 0.333f);
    glVertex3f(-scale, -scale, -scale);
    glTexCoord2f(0.5f, 0.0);
    glVertex3f(-scale, scale, -scale);
    glTexCoord2f(0.25f, 0.0);
    glVertex3f(scale, scale, -scale);
    
    // Left face
    glTexCoord2f(0.0f, 0.666f);
    glVertex3f(-scale, -scale, -scale);
    glTexCoord2f(0.25f, 0.666f);
    glVertex3f(-scale, -scale, scale);
    glTexCoord2f(0.25f, 0.333f);
    glVertex3f(-scale, scale, scale);
    glTexCoord2f(0.0f, 0.333f);
    glVertex3f(-scale, scale, -scale);
    
    // Bottom face
    glTexCoord2f(0.75f, 0.666f);
    glVertex3f(-scale, -scale, scale);
    glTexCoord2f(1.0f, 0.666f);
    glVertex3f(scale, -scale, scale);
    glTexCoord2f(1.0f, 0.333f);
    glVertex3f(scale, -scale, -scale);
    glTexCoord2f(0.75f, 0.333f);
    glVertex3f(-scale, -scale, -scale);
    
    // Top face
    glTexCoord2f(0.25f, 0.666f);
    glVertex3f(-scale, scale, -scale);
    glTexCoord2f(0.5f, 0.666f);
    glVertex3f(scale, scale, -scale);
    glTexCoord2f(0.5f, 0.333f);
    glVertex3f(scale, scale, scale);
    glTexCoord2f(0.25f, 0.333f);
    glVertex3f(-scale, scale, scale);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}
