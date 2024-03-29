#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <assimp/types.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

void assimp_load(){
    aiLogStream stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT, NULL);
    aiAttachLogStream(&stream);
    aiSetLogLevel(AI_LOG_INFO);

    // Load a model
    const char* filename = "./assets/models/land.obj";
    const aiScene* scene = aiImportFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene) {
        printf("Failed to load model: %s\n", aiGetErrorString());
    }
    printf("Loaded model: %s\n", filename);
    // Cleanup
    aiReleaseImport(scene);
    aiDetachAllLogStreams();
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Text Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("./crunchy.ttf", 24);
    SDL_Color color = { 255, 255, 255 ,0};
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, World! Today ijm going to announc my return", color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = { 0, 0, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);

    assimp_load();

    SDL_Delay(1000);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}