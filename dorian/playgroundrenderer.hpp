#ifndef PLAYGROUNDRENDERER_HPP
#define PLAYGROUNDRENDERER_HPP

#include <SDL2/SDL.h>

class PlaygroundRenderer{
    public:
        PlaygroundRenderer();
        ~PlaygroundRenderer();

        void draw();
        int Init(SDL_Renderer* renderer, SDL_Rect drawZone, int tile_size);

    private:
        SDL_Rect drawZone;
        SDL_Renderer* renderer;
        int tile_size;
};


#endif