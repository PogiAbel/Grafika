#ifndef OBJ_DRAW_H
#define OBJ_DRAW_H

#include "model.h"

/**
 * Draw the model.
 */
void draw_model(const Model* model);

/**
 * Draw the model with texture
 */
void draw_model_texture(const Model* model, const char* file_name);

/**
 * Draw the triangles of the model.
 */
void draw_triangles(const Model* model);

#endif /* OBJ_DRAW_H */
