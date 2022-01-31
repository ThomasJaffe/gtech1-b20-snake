#!/bin/bash

g++ -o snake dorian/main.cpp dorian/MainSDLWindow.cpp dorian/playground.cpp dorian/playgroundrenderer.cpp \
    dorian/score.cpp dorian/scorerenderer.cpp dorian/snake.cpp -lSDL2 -lSDL2_ttf