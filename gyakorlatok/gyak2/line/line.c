#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window and a renderer
    SDL_Window *window = SDL_CreateWindow("SDL2 Line Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // Set the drawing color to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Initialize line coordinates
    int x1 = 0, y1 = 240, x2 = 100, y2 = 240;
    int dx = 5, dy = 5;
    int delay = 10;

    // Loop until user quits
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        y1 -= dy;
                        y2 -= dy;
                        break;
                    case SDLK_s:
                        y1 += dy;
                        y2 += dy;
                        break;
                    case SDLK_a:
                        if (delay > 1)
                            {
                                delay -= 1;
                            }
                        break;
                    case SDLK_d:
                        delay += 1;
                        break;
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                }
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Update line coordinates
        x1 += dx;
        x2 += dx;
        if (x2 > 640 || x1 < 0) {
            dx = -dx;
        }

        // Draw the line
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

        // Render the result
        SDL_RenderPresent(renderer);

        // Wait for a short time
        SDL_Delay(delay);
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
