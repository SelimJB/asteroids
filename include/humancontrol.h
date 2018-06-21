#ifndef HUMANCONTROL
#define HUMANCONTROL
#include "SDL2/SDL.h"
#include <iostream>
using namespace std;

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