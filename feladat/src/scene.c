#include "scene.h"

void init_scene(Scene* scene){

    // load objects
    load_model(&scene->model[0],"./assets/models/land.obj");
    load_model(&scene->model[1],"./assets/models/pit.obj");
    load_model(&scene->model[2],"./assets/models/top.obj");
    load_model(&scene->model[3],"./assets/models/trunk.obj");
    load_model(&scene->model[4],"./assets/models/top.obj");
    load_model(&scene->model[5],"./assets/models/trunk.obj");
    load_model(&scene->skybox_model,"./assets/models/sky.obj");

    // load textures
    scene->texture_id[0] = load_texture("./assets/textures/land.png");
    scene->texture_id[1] = load_texture("./assets/textures/pit.png");
    scene->texture_id[2] = load_texture("./assets/textures/top.png");
    scene->texture_id[3] = load_texture("./assets/textures/trunk.png");
    scene->texture_id[4] = load_texture("./assets/textures/top.png");
    scene->texture_id[5] = load_texture("./assets/textures/trunk.png");
    scene->skybox_texture_id = load_texture_jpg("./assets/textures/sky2.jpg");

    rotate_model(&scene->skybox_model, 90.0f);
    scale_model(&scene->skybox_model, 3.0f,3.0f,3.0f);

    rotate_model(&scene->model[0], 90.0f);
    scale_model(&scene->model[0], 10.0f,10.0f,10.0f);
    translate_model(&scene->model[0], 0.0f, 0.0f, -3.0f);

    rotate_model(&scene->model[1], 90.0f);
    scale_model(&scene->model[1], 2.0f,2.0f,2.0f);
    translate_model(&scene->model[1], 0.6f, -2.5f, -2.0f);

    rotate_model(&scene->model[2], 90.0f);
    scale_model(&scene->model[2], 10.0f,10.0f,10.0f);
    translate_model(&scene->model[2], 1.5f, -4.5f, -1.5f);

    rotate_model(&scene->model[3], 90.0f);
    scale_model(&scene->model[3], 10.0f,10.0f,10.0f);
    translate_model(&scene->model[3], 1.5f, -4.5f, -1.5f);

    rotate_model(&scene->model[4], 90.0f);
    rotate_model_z(&scene->model[4], 90.0f);
    scale_model(&scene->model[4], 10.0f,10.0f,10.0f);
    translate_model(&scene->model[4], -5.0f, -5.0f, -1.5f);

    rotate_model(&scene->model[5], 90.0f);
    rotate_model_z(&scene->model[5], 90.0f);
    scale_model(&scene->model[5], 10.0f,10.0f,10.0f);
    translate_model(&scene->model[5], -5.0f, -5.0f, -1.5f);

    // scale_model(&scene->skybox, 10.0f,10.0f,10.0f);

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 0.7;
    scene->material.diffuse.green = 0.5;
    scene->material.diffuse.blue = 0.4;

    scene->material.specular.red = 0.7;
    scene->material.specular.green = 0.2;
    scene->material.specular.blue = 0.2;

    scene->material.shininess = 0.5;
}

void set_lighting()
{
    float ambient_light[] = { 0.3f, 0.3f, 0.3f, 0.3f };
    float diffuse_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    float diffuse_light1[] = { 0.2f, 0.2f, 0.2f, 0.2f };
    float ambient_light1[] = { 1.0f, 0.4f, 0.4f, 1.0f };
    float specular_light1[] = { 1.0f, 0.4f, 0.4f, 1.0f };
    float position1[] = { 0.6f, -3.2f, -1.0f, 0.0f };
    float spot_direction[] = { 0.6f, -3.2f, -1.0f };

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light1);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);

    // Enable distance-based attenuation
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01f); // Adjust the attenuation factor as needed
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.001f);

    // Set spotlight properties for light 1
    // glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0f); // Set spot cutoff angle
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f);
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

    // draw origin
    draw_origin();

    set_material(&(scene->material));

    draw_model_texture(&scene->skybox_model, scene->skybox_texture_id);
    draw_model_texture(&scene->model[0], scene->texture_id[0]);
    draw_model_texture(&scene->model[1], scene->texture_id[1]);
    draw_model_texture(&scene->model[2], scene->texture_id[2]);
    draw_model_texture(&scene->model[3], scene->texture_id[3]);
    draw_model_texture(&scene->model[4], scene->texture_id[4]);
    draw_model_texture(&scene->model[5], scene->texture_id[5]);
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 3);

    glEnd();
}