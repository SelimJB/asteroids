#ifndef DEBUG
#define DEBUG

#include "helper.h"

class Debug
{
	static SDL_Renderer *renderer;
	static const bool Switch_Draw = true;
	static const bool Switch_ShowIndicators = true;

public:
	static void Initialise(SDL_Renderer *);
	static void Draw(std::vector<Point>, char r, char v, char b, char o);
	static void ShowIndicators();
};

#endif