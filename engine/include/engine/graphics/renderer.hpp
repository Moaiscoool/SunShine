#pragma once
#include <engine/engine.hpp>

inline const SDL_Color Cyan = {0, 255, 255, 255};
inline const SDL_Color Black = {0, 0, 0, 255};
inline const SDL_Color Blue = {0, 0, 255, 255};
inline const SDL_Color Magenta = {255, 0, 255, 255};
inline const SDL_Color Gray = {128, 128, 128, 255};
inline const SDL_Color Green = {0, 128, 0, 255};
inline const SDL_Color Lime = {0, 255, 0, 255};
inline const SDL_Color Maroon = {128, 0, 0, 255};
inline const SDL_Color Navy = {0, 0, 128, 255};
inline const SDL_Color Olive = {128, 128, 0, 255};
inline const SDL_Color Purple = {128, 0, 128, 255};
inline const SDL_Color Red = {255, 0, 0, 255};
inline const SDL_Color Silver = {192, 192, 192, 255};
inline const SDL_Color Teal = {0, 128, 128, 255};
inline const SDL_Color White = {255, 255, 255, 255};
inline const SDL_Color Yellow = {255, 255, 0, 255};


int drawBackground(SDL_Renderer* renderer, SDL_Color color);
int drawRect(SDL_Renderer* renderer, float x, float y, float width, float height, SDL_Color color);