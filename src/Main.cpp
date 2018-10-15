#include <Python.h>
#include <stdexcept>
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
#include "scriptmanager.h"
using namespace std;

const Uint32 fps = 60;
const Uint32 minimumFrameTime = 1000 / fps;

int main(int argc, char* args[]){
	ScriptManager* scriptManager;
	ScriptManager* scriptManager2;
	ScriptManager* scriptManager3;
	ScriptManager* scriptManager4;
	ScriptManager* scriptManager5;
	if (Logger::Switch_PythonScript){
		try {
			if (Logger::InputMode == 1){
				scriptManager = new ScriptManager("ia_ship", "GetOutput2");
				scriptManager2 = new ScriptManager("ia_ship", "GetThrustOutput");
				scriptManager3 = new ScriptManager("ia_ship", "GetDirOutput");
			}
			else if (Logger::InputMode == 0){
				scriptManager = new ScriptManager("ia_ship", "GetOutput");
			}	
			else if (Logger::InputMode == 2){
				scriptManager = new ScriptManager("ia_ship", "GetOutput3");
				scriptManager2 = new ScriptManager("ia_ship", "GetThrustBoolOutput");
				scriptManager3 = new ScriptManager("ia_ship", "GetReverseThrustBoolOutput");				
				scriptManager4 = new ScriptManager("ia_ship", "GetLeftBoolOutput");				
				scriptManager5 = new ScriptManager("ia_ship", "GetRightBoolOutput");				
			}		
		}
		catch (exception const& err){
			cout << err.what() << endl;
			return 0;
		}
	}

	GameSession* gameSession = new GameSession();
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDL2 Window", 500, 42, WINDOW_SIZE, WINDOW_SIZE_Y, 0); 
	// window = SDL_CreateWindow("SDL2 Window", 20, 20, WINDOW_SIZE, WINDOW_SIZE_Y, 0); 
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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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
		frameTime = SDL_GetTicks();
		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer,100,7,2,255);

		gameSession->Draw(renderer);
		gameSession->Update(deltaTime);

		if (Logger::InputMode == 0){
			Logger::LogInTextFile();
		}
		else if (Logger::InputMode == 1){
			Logger::LogInTextFile2();
		}
		else if (Logger::InputMode == 2){
			Logger::LogInTextFile3();
		}		
		Debug::ShowIndicators();
		
		
		// TODO : put it a GameSessionMethod
		if (Logger::Switch_PythonScript){
			if (Logger::InputMode == 1){
				scriptManager->GetOuput(gameSession->m_sensors->GetIAInputs());
				int thrustO = scriptManager2->GetOuput(std::vector<float*>{}); // TODO a surcharger pour avoir une version sans arguments
				int dirO = scriptManager3->GetOuput(std::vector<float*>{}); 
				gameSession->m_IAControl->MooveShip2(thrustO, dirO);
			}
			else if (Logger::InputMode == 0){
				int output = scriptManager->GetOuput(gameSession->m_sensors->GetIAInputs());
				gameSession->m_IAControl->MooveShip(output);
			}
			else if (Logger::InputMode == 2){
				scriptManager->GetOuput(gameSession->m_sensors->GetIAInputs());
				int oThurst = scriptManager2->GetOuput(std::vector<float*>{});
				int oReverse = scriptManager3->GetOuput(std::vector<float*>{});
				int oLeft = scriptManager4->GetOuput(std::vector<float*>{});
				int oRight = scriptManager5->GetOuput(std::vector<float*>{});
				gameSession->m_IAControl->MooveShip3(oThurst, oReverse, oLeft, oRight);
			}			
		}
		else {
			gameSession->m_humanControl->Input();
		}

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
