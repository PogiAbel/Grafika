#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdbool.h>

#include "particle.h"
#include "scene.h"
#include "camera.h"
#include "text.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

typedef struct App{
    SDL_Window *window;
    SDL_GLContext gl_context;
    SDL_Renderer* renderer;
    ParticleSystem ps;
    FireEvent event;
    Scene scene;
    double uptime;
    bool is_running;
    Camera camera;
    bool help_menu;
}App;

/* initialize SDL, OpenGL, SDL_image, SDL_ttf, GLU, GLEW, GLUT*/
int init_app(App* app, int width, int height, int argc, char** argv);

/* initialize OpenGL */
void init_opengl();

void reshape(int width, int height);

/* handle events*/
void handle_events(App* app);

/* render app */
void render(App* app);

/* update app */
void update_app(App* app);

/* handle fire events */
void fire_events(FireEvent* event, ParticleSystem* ps, float value);

/*destroy app*/
void destroy_app(App* app);

#endif /* APP_H */