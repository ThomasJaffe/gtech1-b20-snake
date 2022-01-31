
#include "playgroundrenderer.hpp"

PlaygroundRenderer::PlaygroundRenderer(){
    renderer = NULL;
    tile_size = 0;
}

PlaygroundRenderer::~PlaygroundRenderer(){

}

void PlaygroundRenderer::draw(){
    int x = 0;
    int y = 0;

    SDL_RenderSetViewport(renderer, &drawZone);
    SDL_SetRenderDrawColor(renderer, 21, 71, 52, 255);
    
    while(y < drawZone.h){
        if(x >= drawZone.w){
            y += tile_size;
            x = 0;
        }

        SDL_Rect actual_tile = {x, y, tile_size, tile_size};
        SDL_RenderDrawRect(renderer, &actual_tile);

        x += tile_size;
    }
}

int PlaygroundRenderer::Init(SDL_Renderer* renderer, SDL_Rect drawZone, int tile_size){
    this->renderer = renderer;
    this->drawZone = drawZone;
    this->tile_size = tile_size;

    return EXIT_SUCCESS;
}