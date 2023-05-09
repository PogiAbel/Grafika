#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "particle.h"

typedef struct App{
    SDL_Window *window;
    SDL_GLContext gl_context;
    ParticleSystem* ps;
    FireEvent event;
    float elapsedTime;
}App;

/* initialize SDL, OpenGL, SDL_image, SDL_ttf, GLU, GLEW*/
int init_app(App* app, int width, int height);

/* handle events*/
void handle_events(App* app);

/* render app */
void render(App* app);

void fire_events(FireEvent* event, ParticleSystem* ps, float value);

/*destroy app*/
void destroy_app(App* app);