#include "gameobject.h"
#include "gamesession.h"

vector<list<GameObject*>*> GameObject::m_GameObjects {
	new list<GameObject*>(),
	new list<GameObject*>(),
	new list<GameObject*>()
};

GameObject::GameObject(){
	GameSession::PostGameObj(this);
}

void GameObject::Draw(SDL_Renderer* renderer){
	float x = m_pos.x, y = m_pos.y;
	// SDL_SetRenderDrawColor(renderer,0,255,255,255);
	for (vector<Point>::iterator i = m_DrawPoints.begin(); i != m_DrawPoints.end(); ++i)
	{
		SDL_RenderDrawLine(renderer, 
			i->x + x,
			i->y + y,
			((i+1) == m_DrawPoints.end() ? m_DrawPoints.begin() : (i+1))->x + x,
			((i+1) == m_DrawPoints.end() ? m_DrawPoints.begin() : (i+1))->y + y
		);
	}
}