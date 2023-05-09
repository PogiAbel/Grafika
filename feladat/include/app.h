#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "particle.h"
#include "camera.h"

typedef struct App{
    SDL_Window *window;
    SDL_GLContext gl_context;
    ParticleSystem ps;
    FireEvent event;
    double uptime;
    bool is_running;
    Camera camera;
}App;

/* initialize SDL, OpenGL, SDL_image, SDL_ttf, GLU, GLEW*/
int init_app(App* app, int width, int height);

/* initialize OpenGL */
void init_opengl();

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