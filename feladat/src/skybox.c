#include "skybox.h"

void setup_cube_map(GLuint *texture){
    // glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void setup_cube_map_texture(GLuint *texture, SDL_Surface *xpos, SDL_Surface *xneg, SDL_Surface *ypos, SDL_Surface *yneg, SDL_Surface *zpos, SDL_Surface *zneg)
{
    setup_cube_map(texture);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, xpos->w, xpos->h, 0, GL_RGB , GL_UNSIGNED_BYTE, xpos->pixels);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, xneg->w, xneg->h, 0, GL_RGB , GL_UNSIGNED_BYTE, xneg->pixels);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, ypos->w, ypos->h, 0, GL_RGB , GL_UNSIGNED_BYTE, ypos->pixels);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, yneg->w, yneg->h, 0, GL_RGB , GL_UNSIGNED_BYTE, yneg->pixels);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, zpos->w, zpos->h, 0, GL_RGB , GL_UNSIGNED_BYTE, zpos->pixels);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, zneg->w, zneg->h, 0, GL_RGB , GL_UNSIGNED_BYTE, zneg->pixels);
}

void delete_cube_map(GLuint *texture){
    glDeleteTextures(1, texture);
}

void init_cubemap_texture(GLuint *cubemap_texture){
    SDL_Surface *xpos = IMG_Load("./assets/textures/skybox/xpos.jpg"); SDL_Surface *xneg = IMG_Load("./assets/textures/skybox/xneg.jpg");
    SDL_Surface *ypos = IMG_Load("./assets/textures/skybox/ypos.jpg"); SDL_Surface *yneg = IMG_Load("./assets/textures/skybox/yneg.jpg");
    SDL_Surface *zpos = IMG_Load("./assets/textures/skybox/zpos.jpg"); SDL_Surface *zneg = IMG_Load("./assets/textures/skybox/zneg.jpg");
    setup_cube_map_texture(cubemap_texture, xpos, xneg, ypos, yneg, zpos, zneg);
    SDL_FreeSurface(xneg);  SDL_FreeSurface(xpos);
    SDL_FreeSurface(yneg);  SDL_FreeSurface(ypos);
    SDL_FreeSurface(zneg);  SDL_FreeSurface(zpos);
}

void render_skybox(GLuint* cubemap_texture, GLuint shader_program){
    // cube vertices for vertex buffer object
    GLfloat cube_vertices[] = {
        -1.0,  1.0,  1.0,
        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0,  1.0, -1.0,
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0,  1.0, -1.0,
    };
    GLuint vbo_cube_vertices;
    glGenBuffers(1, &vbo_cube_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    // cube indices for index buffer object
    GLushort cube_indices[] = {
        0, 1, 2, 3,
        3, 2, 6, 7,
        7, 6, 5, 4,
        4, 5, 1, 0,
        0, 3, 7, 4,
        1, 2, 6, 5,
    };
    GLuint ibo_cube_indices;
    glGenBuffers(1, &ibo_cube_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // setup cube map texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *cubemap_texture);

    // use shader program
    glUseProgram(shader_program);
    GLint loc = glGetUniformLocation(shader_program, "skybox");
    glUniform1i(loc, 0);

    // render skybox
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_indices);
    glDrawElements(GL_QUADS, sizeof(cube_indices)/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    glDepthMask(GL_TRUE);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glEnable(GL_CULL_FACE);
}