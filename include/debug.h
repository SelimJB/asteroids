#ifndef DEBUG
#define DEBUG

#include "helper.h"

class Debug
{
	static SDL_Renderer* renderer;
  public:
	static void Initialise(SDL_Renderer *); 
	static void Draw(std::vector<Point>);
};

#endif