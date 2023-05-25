#include "app.h"


int init_app(App* app, int width, int height, int argc, char** argv){

    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Failed to initialize SDL2: %s\n", SDL_GetError());
    }

    // Create a window
    // app->window = SDL_CreateWindow("Fire Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    app->window = SDL_CreateWindow("Fire Simulator",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      0, 0,
                                      SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!app->window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
    // dm.w = width;
    // dm.h = height;

    // Create an OpenGL context
    app->gl_context = SDL_GL_CreateContext(app->window);

    if (!app->gl_context) {
        fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(app->window);
        SDL_Quit();
        return 1;
    }

    // Initialize GLEW
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(glewError));
        SDL_GL_DeleteContext(app->gl_context);
        SDL_DestroyWindow(app->window);
        SDL_Quit();
        return 1;
    }

    // Initialize GLUT
    glutInit(&argc, argv);

    // Create a renderer
    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Set up particle system
    init_particle(&app->ps,200, 3.0f, 0.15f, 0.6f);

    init_opengl();
    // reshape(width, height);
    init_scene(&app->scene);

    // Set up parameters
    app->event = FIRE_EVENT_NONE;
    app->is_running = true;
    app->help_menu = false;


    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)dm.w / (double)dm.h, 0.1, 100.0);

    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set up the viewport
    glViewport(0, 0, dm.w, dm.h);
    // Set up camera
    init_camera(&app->camera);

    return 0;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10
    );
}

void render(App* app){

    if(app->help_menu){
        render_help_menu(&app->scene);
    }else{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    set_lighting(&app->scene,&app->ps);
    render_particle(&app->ps,&app->camera);
    render_scene(&app->scene);
    glPopMatrix();
    }

    // Swap the buffers
    SDL_GL_SwapWindow(app->window);
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_particle(&app->ps,elapsed_time);
    update_scene(&app->scene, current_time);
}

void fire_event(FireEvent* event, ParticleSystem* ps, float value){
    switch (*event) {
    case FIRE_EVENT_NONE:
        break;
    case FIRE_EVENT_PARTICLE_COUNT:
        if(ps->particle_count+value <= 0){
            break;
        }
        recount_particles(ps,ps->particle_count + (int)(value*1000));
        printf("Particle count: %d\n", ps->particle_count);
        break;
    case FIRE_EVENT_LIFETIME:
        if( ps->particle_lifetime+value <= 0){
            break;
        }
        ps->particle_lifetime += value;
        printf("Particle lifetime: %f\n", ps->particle_lifetime);
        break;
    case FIRE_EVENT_SIZE:
        if(ps->particle_size+value <= 0){
            break;
        }
        ps->particle_size += value;
        printf("Particle size: %f\n", ps->particle_size);
        break;
    case FIRE_EVENT_VELOCITY_RANGE:
        if(ps->particle_velocity_range+value <= 0){
            break;
        }
        ps->particle_velocity_range += value;
        printf("Particle velocity range: %f\n", ps->particle_velocity_range);
        break;
    default:
        break;
    }
}

void handle_events(App* app){
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            app->is_running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;;
                break;
            // Camera controls
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 4);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -4);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 4);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -4);
                break;
            case SDL_SCANCODE_Q:
                app->camera.position.z -= 1.0f;
                break;
            case SDL_SCANCODE_E:
                app->camera.position.z += 1.0f;
                break;
            // Particle controls
            case SDL_SCANCODE_H:
                app->event = FIRE_EVENT_PARTICLE_COUNT;
                break;
            case SDL_SCANCODE_J:
                app->event = FIRE_EVENT_LIFETIME;
                break;
            case SDL_SCANCODE_K:
                app->event = FIRE_EVENT_SIZE;
                break;
            case SDL_SCANCODE_L:
                app->event = FIRE_EVENT_VELOCITY_RANGE;
                break;
            case SDL_SCANCODE_DOWN:
                fire_event(&app->event, &app->ps, -0.1f);
                break;
            case SDL_SCANCODE_UP:
                fire_event(&app->event, &app->ps, 0.1f);
                break;
            // Light controls
            case SDL_SCANCODE_F:
                app->scene.light_y += 0.5f;
                printf("Light pos: %f %f %f\n", app->scene.light_x, app->scene.light_y, app->scene.light_z);
                break;
            case SDL_SCANCODE_C:
                app->scene.light_x -= 0.5f;
                printf("Light pos: %f %f %f\n", app->scene.light_x, app->scene.light_y, app->scene.light_z);
                break;
            case SDL_SCANCODE_V:
                app->scene.light_y -= 0.5f;
                printf("Light pos: %f %f %f\n", app->scene.light_x, app->scene.light_y, app->scene.light_z);
                break;
            case SDL_SCANCODE_N:
                app->scene.light_x += 0.5f;
                printf("Light pos: %f %f %f\n", app->scene.light_x, app->scene.light_y, app->scene.light_z);
                break;
            case SDL_SCANCODE_X:
                app->scene.light_z -= 0.5f;
                break;
            case SDL_SCANCODE_M:
                app->scene.light_z += 0.5f;
                break;
            // Fire color controls
            case SDL_SCANCODE_R:
                app->ps.fire_color = FIRE_COLOR_RED;
                break;
            case SDL_SCANCODE_G:
                app->ps.fire_color = FIRE_COLOR_GREEN;
                break;
            case SDL_SCANCODE_B:
                app->ps.fire_color = FIRE_COLOR_BLUE;
                break;
            // Help menu
            case SDL_SCANCODE_F1:
            app->help_menu = !app->help_menu;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                // printf("Camera posittion: x: %f, y: %f, z: %f\n", app->camera.position.x, app->camera.position.y, app->camera.position.z);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                // printf("Camera posittion: x: %f, y: %f, z: %f\n", app->camera.position.x, app->camera.position.y, app->camera.position.z);
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        default:
            break;
        }
    }
}
    


void destroy_app(App* app){

    // glDeleteProgram(app->scene.shader_program);
    // Destroy the OpenGL context
    SDL_GL_DeleteContext(app->gl_context);

    // Clean up SDL2 and exit
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);

    SDL_Quit();
    free(app);
}