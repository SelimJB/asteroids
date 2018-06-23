#include "SDL2/SDL.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "ast.h"
#include "bullet.h"
#include "ship.h"
#include "gamesession.h"
#include "logger.h"
#include "debug.h"
using namespace std;

const Uint32 fps = 60;
const Uint32 minimumFrameTime = 1000 / fps;

int main(int argc, char* args[]){
	GameSession* gameSession = new GameSession();
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDL2 Window", 100, 100, WINDOW_SIZE, WINDOW_SIZE_Y, 0); 
	if(window==NULL)
	{   
		printf("Could not create window: %s\n", SDL_GetError());
		return 1; 
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
	if(renderer == NULL)
	{
		printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
		return 1;
	}
	Logger::Initialize(fileName);
	Debug::Initialise(renderer);

	
	Uint32 frameTime;
	Uint32 lastFrameTime = 0;
	Uint32 deltaTime = 0;
	
	srand(time(NULL));

	// Ast generation
	gameSession->LaunchAsteroidWave();
	
	// GameLoop
	while (!GameSession::m_quit) {

		Logger::PrintFrame();
		Logger::LogInTextFile();
		frameTime = SDL_GetTicks();
		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer,100,7,2,255);


		// sensors
		gameSession->m_sensors->GetNearestAst();


		gameSession->m_humanControl->Input();
		gameSession->Update(deltaTime);
		gameSession->Draw(renderer);

		SDL_RenderPresent(renderer);

		if ((SDL_GetTicks() - frameTime) < minimumFrameTime)
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));
	}

	SDL_DestroyRenderer(renderer); 
	SDL_DestroyWindow(window); 
	SDL_Quit(); 

	Logger::Release();
	return 1;
}
