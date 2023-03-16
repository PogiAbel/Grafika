#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// Constants
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define CELL_SIZE 32
#define PALETTE_SIZE 6

// Colors
const SDL_Color palette[PALETTE_SIZE] = {
    { 255, 0, 0, 255 },    // Red
    { 255, 165, 0, 255 },  // Orange
    { 255, 255, 0, 255 },  // Yellow
    { 0, 255, 0, 255 },    // Green
    { 0, 0, 255, 255 },    // Blue
    { 255, 0, 255, 255 }   // Purple
};

// Function prototypes
void drawPalette(SDL_Renderer *renderer);
void drawCell(SDL_Renderer *renderer, int x, int y, SDL_Color color);
int getPaletteIndex(int x, int y);

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow("Color Palette", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize the grid to the first color in the palette
    SDL_Color currentColor = palette[0];
    SDL_Color grid[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE];
    for (int y = 0; y < WINDOW_HEIGHT / CELL_SIZE; y++) {
        for (int x = 0; x < WINDOW_WIDTH / CELL_SIZE; x++) {
            grid[y][x] = currentColor;
        }
    }

    // Event loop
    SDL_Event event;
    bool quit = false;
    int x,y;
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // Quit event, close the window
                    quit = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    // Mouse click event, check if it's on the palette or the grid
                     x = event.button.x / CELL_SIZE;
                     y = event.button.y / CELL_SIZE;
                    if (y == 0) {
                        // Palette
                        int paletteIndex = getPaletteIndex(x, y);
                        if (paletteIndex >= 0 && paletteIndex < PALETTE_SIZE) {
                            currentColor = palette[paletteIndex];
                        }
                    } else {
                        // Grid
                        if (x >= 0 && x < WINDOW_WIDTH / CELL_SIZE && y >= 1 && y < WINDOW_HEIGHT / CELL_SIZE) {
                            grid[y - 1][x] = currentColor;
                        }
                    }
                    break;
            }
        }
    }

   // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}