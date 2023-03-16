#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

double x = 1.0, y = 1.0;

void drawCircle(SDL_Renderer* renderer, double x, double y, double radius) {
    // Set the drawing color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    double x2,y2;

    // Calculate the step size for the angle
    double angle_step = 2.0 * M_PI / 360.0;

    // Draw the circle using homogenous coordinates
    for (double angle = 0.0; angle < 2.0 * M_PI; angle += angle_step) {
        x2 = x + radius * cos(angle);
        y2 = y + radius * sin(angle);
        // SDL_RenderDrawPoint(renderer, hx / w * WINDOW_WIDTH, hy / w * WINDOW_HEIGHT);
        SDL_RenderDrawLine(renderer, x, y, x2*100,y2*100);
    }
    printf("Coordinates: %f, %f End: %f, %f", x, y, x2, y2);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Circle in Homogenous Coordinates", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Draw the circle
    drawCircle(renderer, x, y, 1);

    // Update the renderer
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int quit = 0;
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }


    // Wait for 5 seconds
    SDL_Delay(50);

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
