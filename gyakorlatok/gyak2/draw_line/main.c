#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include "geometry.h"
#define MAX_LINE_COUNT 10
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

// Palette coordinates
const SDL_Rect palette_rects[PALETTE_SIZE] = {
    { 0, 0, 32, 32 },
    { 0, 32, 32, 32 },
    { 0, 64, 32, 32 },
    { 0, 96, 32, 32 },
    { 0, 128, 32, 32 },
    { 0, 160, 32, 32 }
};

void drawPalette(SDL_Renderer *renderer){
    for (int i = 0; i < PALETTE_SIZE; ++i) {
        SDL_SetRenderDrawColor(renderer, palette[i].r, palette[i].g, palette[i].b, palette[i].a);
        SDL_Rect rect = { 0, i * 32, 32, 32 };
        SDL_RenderFillRect(renderer, &rect);
    }
}

int main(int argc, char *argv[]) {
    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window and a renderer
    SDL_Window *window = SDL_CreateWindow("SDL2 Line Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    struct colored_line
    {
        struct Line line;
        SDL_Color color;
    };
    struct colored_line colored_lines[MAX_LINE_COUNT];
    
    int index = 0;
    int point = 0;
    int paletteIndex = 0;

    // Loop until user quits
    SDL_Event event;
    int quit = 0;
    while (1) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // Quit event, close the window
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;

                case SDL_MOUSEBUTTONDOWN:
                    // Mouse click event, print the mouse position
                    // printf("Mouse clicked at (%d,%d)\n", event.button.x, event.button.y);
                    if(index == MAX_LINE_COUNT){
                        printf("Maximum number of lines reached!\n");
                        break;
                    }
                    if(event.button.x<32 && event.button.y<32*PALETTE_SIZE){
                        // printf("Palette clicked!\n");
                        int y;
                        y = event.button.y;
                        if (y<32)
                        {
                            paletteIndex = 0;
                        }
                        else if (y<64)
                        {
                            paletteIndex = 1;
                        }
                        else if (y<96)
                        {
                            paletteIndex = 2;                        }
                        else if (y<128)
                        {
                            paletteIndex = 3;                        }
                        else if (y<160)
                        {
                            paletteIndex = 4;                        }
                        else if (y<192)
                        {
                            paletteIndex = 5;                        }
                        break;
                    }
                    if(point == 0){
                        colored_lines[index].line.p1.x = event.button.x;
                        colored_lines[index].line.p1.y = event.button.y;
                        colored_lines[index].color = palette[paletteIndex];
                        point = 1;}
                    else{
                        colored_lines[index].line.p2.x = event.button.x;
                        colored_lines[index].line.p2.y = event.button.y;
                        colored_lines[index].color = palette[paletteIndex];
                        point = 0;
                        index++;
                    }
                    break;
            }
        }


        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the line
        for (int i = 0; i < index; ++i) {
            SDL_SetRenderDrawColor(renderer,colored_lines[i].color.r, colored_lines[i].color.g, colored_lines[i].color.b, colored_lines[i].color.a );
            SDL_RenderDrawLine(renderer, colored_lines[i].line.p1.x, colored_lines[i].line.p1.y, colored_lines[i].line.p2.x, colored_lines[i].line.p2.y);
        }

        drawPalette(renderer);


        // Render the result
        SDL_RenderPresent(renderer);

        // Wait for a short time
        SDL_Delay(100);
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
