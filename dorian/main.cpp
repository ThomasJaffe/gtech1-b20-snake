#include "MainSDLWindow.hpp"
#include "snake.hpp"
#include "score.hpp"
#include "scorerenderer.hpp"
#include "playground.hpp"
#include "playgroundrenderer.hpp"

int main(void){
    Uint32 framerate = 30;
    int windowSize = 800;
    int tile_size = 10; 
    bool gameContinues = true;

    MainSDLWindow* mainWindow = new MainSDLWindow();
    bool failedInit = mainWindow->Init("Snake", 800, 800);
    if(failedInit){
        return 1;
    }

    SDL_Renderer* mainWindowRenderer = mainWindow->GetRenderer();
    SDL_Event event;

    Snake* mainSnake = new Snake(25, 25, RIGHT, 10);

    Playground* playground = new Playground(mainWindow->GetPlaygroundZone().w/tile_size, mainWindow->GetPlaygroundZone().h/tile_size);
    PlaygroundRenderer* playgroundGraphics = new PlaygroundRenderer();
    failedInit = playgroundGraphics->Init(mainWindowRenderer, mainWindow->GetPlaygroundZone(), tile_size);

    if(failedInit){
        return 1;
    }

    Score* score = new Score();
    ScoreRenderer* scoreGraphics = new ScoreRenderer();
    failedInit = scoreGraphics->Init(mainWindowRenderer, mainWindow->GetScoreZone());
    if(failedInit){
        return 1;
    }

    while (gameContinues){
        Uint32 frameTimeStart = SDL_GetTicks();

        SDL_SetRenderDrawColor(mainWindowRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mainWindowRenderer);

        playgroundGraphics->draw();

        gameContinues = mainSnake->Move(playground);

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
                return 0;
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.scancode == SDL_SCANCODE_DOWN){
                    mainSnake->ChangeDirection(DOWN);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_UP){
                    mainSnake->ChangeDirection(UP); 
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                    mainSnake->ChangeDirection(RIGHT);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
                    mainSnake->ChangeDirection(LEFT);
                }
            }
        }
        
        mainSnake->draw(mainWindow, tile_size);
        scoreGraphics->draw(score);

        SDL_RenderPresent(mainWindowRenderer);
        

        Uint32 timeSinceFrameStart = SDL_GetTicks() - frameTimeStart;
        if (timeSinceFrameStart < framerate){
            SDL_Delay(framerate - timeSinceFrameStart);
        }
    }

    delete mainWindow;
    return 0;
}