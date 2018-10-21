#include "gamesession.h"
#include "gameobject.h"
#include "ast.h"
#include "ship.h"
#include "sensors.h"
using namespace std;

GameObjectList GameSession::m_activeObjectList;

Ship* GameSession::m_mainShip = new Ship();
Sensors* GameSession::m_sensors = new Sensors();
SDL_Event* GameSession::m_event = new SDL_Event();
bool GameSession::m_quit = false;

GameSession::GameSession()
{
	m_humanControl = new HumanControl();
	m_IAControl = new IAControl();
}

void GameSession::Update(float dt)
{
	GameObjectList::iterator gameObj1 = m_activeObjectList.begin();
	while (gameObj1 != m_activeObjectList.end() && m_activeObjectList.size() != 0)
	// for (gameObj1 = m_activeObjectList.begin(); gameObj1 != m_activeObjectList.end(); ++gameObj1)
	{
		// Update position
		if ((*gameObj1)->m_active)
			(*gameObj1)->UpdatePosition(dt);
		else{
			++gameObj1;
			continue;
		}

		// Check for collisions
		if ((*gameObj1)->m_collisionFlag != GameObject::OBJ_NONE)
		{
			GameObjectList::iterator gameObj2;
			for (gameObj2 = m_activeObjectList.begin(); gameObj2 != m_activeObjectList.end(); ++gameObj2)
			{
				{
					if (gameObj1 == gameObj2)
						continue;
					if ((*gameObj2)->m_active && ((*gameObj1)->m_collisionFlag & (*gameObj2)->m_type) && (*gameObj1)->IsColliding(*gameObj2))
					{
						(*gameObj1)->DoCollision(*gameObj2);
					}
				}
			}
		}
		
		if (gameObj1==m_activeObjectList.end())
			break;
		
		if ((*gameObj1)->m_isdead){
			delete *gameObj1;
			list<GameObject*>::iterator prev = gameObj1++;
			m_activeObjectList.erase(prev);
		}

		++gameObj1;
	}
}

void GameSession::Draw(SDL_Renderer* renderer){
	GameObjectList::iterator it = m_activeObjectList.begin();
	for (it = m_activeObjectList.begin(); it != m_activeObjectList.end(); ++it){
		(*it)->Draw(renderer);
	}
}

void GameSession::DrawLives(){

}

void GameSession::LaunchAsteroidWave()
{
	for (int i = 0; i < 25; i++)
	{
		new Ast(GetRandomInt(1,2));
	}
}