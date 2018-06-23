#include "sensors.h"
#include "gamesession.h"
#include "ast.h"
#include "math.h"

float GetDist(Point A, Point B){
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

const GameObject* Sensors::GetNearestAst(){
	GameObject* ast = NULL;
	float nearestDist = -1;

	GameObjectList::iterator it;
	for (it = GameSession::m_activeObjectList.begin(); it != GameSession::m_activeObjectList.end(); ++it)
	{
		if ((*it)->m_type == GameObject::OBJ_AST){
			float dist = GetDist((*it)->m_pos, GameSession::m_mainShip->m_pos);
			if (nearestDist == -1 || dist < nearestDist){
				nearestDist = dist;
				// ast = dynamic_cast<Ast*>(*it);
				ast = *it;
			}
		}
	}

	cout << "Dist : " << nearestDist << endl;

	return ast;
}
