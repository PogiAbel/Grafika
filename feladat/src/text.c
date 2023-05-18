#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>

void render_text(const char* text){
    TTF_Font* font = TTF_OpenFont("./assets/fonts/crunchy.ttf", 24);
    SDL_Color color = {104, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) {
        fprintf(stderr, "Error creating surface: %s\n", SDL_GetError());
        return;
    }
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    // Render text
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    int X = 0;
    int Y = 0;
    int Width = 100;
    int Height = 100;
    
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(X, Y, 0);
        glTexCoord2f(1, 0); glVertex3f(X + Width, Y, 0);
        glTexCoord2f(1, 1); glVertex3f(X + Width, Y + Height, 0);
        glTexCoord2f(0, 1); glVertex3f(X, Y + Height, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}