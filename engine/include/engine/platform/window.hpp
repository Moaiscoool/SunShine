#pragma once
#include <SDL3/SDL.h>

int windowInit(SDL_Window** window, SDL_Renderer** renderer, const char* windowName, int width, int height);

int drawBackground(SDL_Renderer* renderer, SDL_Color color);

int drawRect(SDL_Renderer* renderer, float x, float y, float width, float height, SDL_Color color);