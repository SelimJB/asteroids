#include "sensors.h"
#include "gamesession.h"
#include "ast.h"
#include "math.h"
#include "debug.h"
#include "math.h"
#include "helper.h"
#include "logger.h"
using namespace std;

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
				ast = *it;
			}
		}
	}

	return ast;
}

float Sensors::GetShipRadianAngle(){
	return atan2(GameSession::m_mainShip->m_axis.x,GameSession::m_mainShip->m_axis.y);
}

Point* Sensors::GetDirectionVectorBetweenShipAndNearestAst(const GameObject* obj){
	if (obj == NULL){
		return NULL;
	}

	float x = GameSession::m_mainShip->m_pos.x - obj->m_pos.x;
	float y = GameSession::m_mainShip->m_pos.y - obj->m_pos.y;
	float norm = sqrt(pow(x,2) + pow(y,2));
	Point* res = new Point(x/norm, y/norm);
	return res;
};

float* Sensors::GetRelativeSpeed(const GameObject* obj){
	if (obj == NULL){
		return NULL;
	}

	const Point& vShip = GameSession::m_mainShip->m_velocity;
	const Point& vAst = obj->m_velocity;

	float *res = new float();
	float s = abs(vAst.x - vShip.x) > abs(vAst.y - vShip.y) ? 
				-( vAst.x - vShip.x ) / abs(vAst.x - vShip.x) : 
				( vAst.y - vShip.y ) / abs(vAst.y - vShip.y);
	*res = s*sqrt( pow(abs(vAst.x - vShip.x),2) + pow (abs(vAst.y - vShip.y),2));
	return res;	
};

IAInputs::~IAInputs(){
	delete X_dirShipNearestAst;
	delete Y_dirShipNearestAst;
	delete RelativeSpeed;
}

IAInputs Sensors::GetIAInputs(){
	const GameObject *ast = GameSession::m_sensors->GetNearestAst();
	float shipAngle = round(GameSession::m_sensors->GetShipRadianAngle() * 1000) / 1000;
	float *relativeSpeed = NULL, *dir_x = NULL, *dir_y = NULL;
	bool isNearestAst = false;
	if (ast != NULL){
		relativeSpeed = GameSession::m_sensors->GetRelativeSpeed(ast);
		*relativeSpeed = round(*relativeSpeed * 1000) / 1000;
		Point* dir = GameSession::m_sensors->GetDirectionVectorBetweenShipAndNearestAst(ast);
		dir_x = new float(round(dir->x * 1000) / 1000);
		dir_y = new float(round(dir->y * 1000) / 1000);
		isNearestAst = true;
		delete dir;
	}
	return IAInputs(shipAngle, dir_x, dir_y, relativeSpeed, isNearestAst);
}