#include "debug.h"
using namespace std;

SDL_Renderer* Debug::renderer = NULL;

void Debug::Initialise(SDL_Renderer * r){
	renderer = r;
}

void Debug::Draw(vector<Point> pts){
	SDL_SetRenderDrawColor(renderer,0,255,0,255);
	for (vector<Point>::iterator i = pts.begin(); i != pts.end(); ++i)
	{
		SDL_RenderDrawLine(renderer, 
			i->x,
			i->y,
			((i+1) == pts.end() ? pts.begin() : (i+1))->x,
			((i+1) == pts.end() ? pts.begin() : (i+1))->y
		);
	}
	SDL_SetRenderDrawColor(renderer,100,7,2,255);
}