#include "scorerenderer.hpp"
#include "score.hpp"

#include <string>

ScoreRenderer::ScoreRenderer(){
    renderer = NULL;
}

int ScoreRenderer::Init(SDL_Renderer* renderer, SDL_Rect drawZone){
    this->renderer = renderer;
    this->drawZone = drawZone;

    police = TTF_OpenFont("../fonts/Courgette/Courgette-Regular.ttf", 30);
    if(!police){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

ScoreRenderer::~ScoreRenderer(){

}

void ScoreRenderer::draw(Score* score){
    SDL_RenderSetViewport(renderer, &drawZone);
    SDL_SetRenderDrawColor(renderer, 65, 105, 225, 255);
    SDL_RenderFillRect(renderer, &drawZone);

    std::string numberEatenString = std::to_string(score->getNumberEaten());
    const char* numberEaten = numberEatenString.c_str();
    SDL_Surface* numbEatenSurface = TTF_RenderText_Blended(police, numberEaten, {255, 255, 255, 255});
    SDL_Texture* numbEatenTexture = SDL_CreateTextureFromSurface(renderer, numbEatenSurface);
    SDL_FreeSurface(numbEatenSurface);
    SDL_Rect numbEatenPlacement = {drawZone.w/15, drawZone.h/3, 0, 0};
    SDL_QueryTexture(numbEatenTexture, NULL, NULL, &(numbEatenPlacement.w), &(numbEatenPlacement.h));
    SDL_RenderCopy(renderer, numbEatenTexture, NULL, &numbEatenPlacement);
    numbEatenPlacement.x -= drawZone.w/20;
    numbEatenPlacement.w = drawZone.w/25;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &numbEatenPlacement);

    std::string scoreString = std::to_string(score->getScore());
    const char* scoreChar = scoreString.c_str();
    SDL_Surface* scoreSurface = TTF_RenderText_Blended(police, scoreChar, {255, 255, 255, 255});
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FreeSurface(scoreSurface);
    int nbEatenDigits = log10(score->getNumberEaten());
    SDL_Rect scorePlacement = {numbEatenPlacement.x + drawZone.w/8 + (drawZone.w/35)*nbEatenDigits, drawZone.h/3, 0, 0};
    SDL_QueryTexture(scoreTexture, NULL, NULL, &(scorePlacement.w), &(scorePlacement.h));
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scorePlacement);
}