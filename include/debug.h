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
	static void Draw(std::vector<Point>, Color c);
	static void ShowIndicators();
	static const Point debugPos;
};

#endif