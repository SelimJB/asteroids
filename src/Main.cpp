#include "SDL2/SDL.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "bullet.h"
#include "ast.h"
#include "ship.h"
using namespace std;

const Uint32 fps = 60;
const Uint32 minimumFrameTime = 1000 / fps;

int main(int argc, char* args[]){
	cout << "YOYOYOYO" << endl;
	srand(time(NULL));
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

	bool quit = false;
	SDL_Event event;
	Uint32 frameTime;
	Uint32 lastFrameTime = 0;
	Uint32 deltaTime = 0;
	
	// Ast generation
	vector<Ast *> asts;
	for (int i = 0;i<20;i++){
		asts.push_back(new Ast(GetRandomInt(2,4)));
	}
	
	int i = 0;
	int j = 255;
	while (!quit) {
		i = (i + 1) % 255;  
		j = (j - 1) % 255;  
		j+=255;
		frameTime = SDL_GetTicks();

		// Input management
		while( SDL_PollEvent( &event ) != 0 && GameObject::m_ship != NULL){
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }			
            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            if( currentKeyStates[ SDL_SCANCODE_UP ] )
            {
                GameObject::m_ship->m_ThrustState = Ship::THRUSTON;
            }
            else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
            {
                GameObject::m_ship->m_ThrustState = Ship::THRUSTREVERSE;
            }
            else
            {
                GameObject::m_ship->m_ThrustState = Ship::THRUSTOFF;
            }		
            if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
            {
            	GameObject::m_ship->m_DirState = Ship::LEFT;
            }
            else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
            {
            	GameObject::m_ship->m_DirState = Ship::RIGHT;
            }	
            else
            {
            	GameObject::m_ship->m_DirState = Ship::CENTER;
            }
			if (currentKeyStates[ SDL_SCANCODE_SPACE ])
			{
 				GameObject::m_ship->Shoot();
			}
			else 			
			{
				GameObject::m_ship->m_ShipCanShoot = true;
			}	
		}		

		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer,i*5,7*j,2*j,255);

		for (vector<list<GameObject*>*>::iterator vectIt = GameObject::m_GameObjects.begin(); vectIt!=GameObject::m_GameObjects.end(); vectIt++){

			list<GameObject*>::iterator it = (*vectIt)->begin();
			while (it != (*vectIt)->end() && (*vectIt)->size() != 0)
			{
				// Ship **it;
				(*it)->Update(deltaTime);
				(*it)->Draw(renderer);				
				if ((*it)->m_isdead){
					delete *it;
					list<GameObject*>::iterator prev = it++;
					(*vectIt)->erase(prev);				
				}
				else ++it;
			}				
		}

		SDL_RenderPresent(renderer);
		if ((SDL_GetTicks() - frameTime) < minimumFrameTime)
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));
	}

	SDL_DestroyRenderer(renderer); 
	SDL_DestroyWindow(window); 
	SDL_Quit(); 

	return 1;
}
