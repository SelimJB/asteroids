#include "gamesession.h"
#include "ast.h"

GameObjectList GameSession::m_activeObjectList;

GameSession::GameSession()
{
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
		if ((*gameObj1)->m_type == GameObject::OBJ_BULLET){
			Logger::Log(*gameObj1);
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
	for (int i = 0; i < 1; i++)
	{
		new Ast(4,Point(i*100,200));
	}
}