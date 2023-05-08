#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "particle.h"

typedef struct App{
    SDL_Window *window;
    SDL_GLContext gl_context;
    ParticleSystem* ps;
    float elapsedTime;
}App;

/* initialize SDL, OpenGL, SDL_image, SDL_ttf, GLU, GLEW*/
int init_app(App* app, int width, int height);

/* handle events*/
void handle_events(App* app);

/* render app */
void render(App* app);

/*destroy app*/
void destroy_app(App* app);