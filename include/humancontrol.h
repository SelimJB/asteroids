#ifndef HUMANCONTROL
#define HUMANCONTROL
#include "SDL2/SDL.h"
#include <iostream>

class HumanControl
{
  private:
	SDL_Event *event;

  public:
	void Input();
	HumanControl()
	{
		event = new SDL_Event();
	}
};

#endif