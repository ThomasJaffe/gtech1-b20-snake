#ifndef SCORERENDERER_HPP
#define SCORERENDERER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


class Score;

class ScoreRenderer{
    public:
        ScoreRenderer();
        ~ScoreRenderer();

        void draw(Score* score);
        int Init(SDL_Renderer* renderer, SDL_Rect drawZone);

    private:
        SDL_Rect drawZone;
        SDL_Renderer* renderer;
        TTF_Font* police;
};

#endif