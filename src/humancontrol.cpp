#include "humancontrol.h"
#include "ship.h"
#include "gamesession.h"


void HumanControl::Input(){
		// Input management
		while( SDL_PollEvent( event ) != 0 && GameSession::m_mainShip != NULL){
            if( event->type == SDL_QUIT )
            {
                GameSession::m_quit = true;
            }			
            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            if( currentKeyStates[ SDL_SCANCODE_UP ] )
            {
                GameSession::m_mainShip->m_ThrustState = Ship::THRUSTON;
            }
            else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
            {
                GameSession::m_mainShip->m_ThrustState = Ship::THRUSTREVERSE;
            }
            else
            {
                GameSession::m_mainShip->m_ThrustState = Ship::THRUSTOFF;
            }		
            if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
            {
            	GameSession::m_mainShip->m_DirState = Ship::LEFT;
            }
            else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
            {
            	GameSession::m_mainShip->m_DirState = Ship::RIGHT;
            }	
            else
            {
            	GameSession::m_mainShip->m_DirState = Ship::CENTER;
            }
			if (currentKeyStates[ SDL_SCANCODE_SPACE ])
			{
 				GameSession::m_mainShip->Shoot();
			}
			else 			
			{
				GameSession::m_mainShip->m_ShipCanShoot = true;
			}	
		}	
}