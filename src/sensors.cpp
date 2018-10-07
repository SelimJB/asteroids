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

// TESTER DES ANGLES
float Sensors::GetShipRadianAngle(){
	return atan2(GameSession::m_mainShip->m_axis.x,GameSession::m_mainShip->m_axis.y);
}

float Sensors::GetDirectionRadianAngle(){
	Point *shipDir = GameSession::m_sensors->GetShipDirection();
	float angle = atan2(-shipDir->x,-shipDir->y);
	delete shipDir;
	return angle;
}

float Sensors::GetDirectionBetweenShipAndNearestAstRadianAngle(const GameObject* obj){
	Point *dir = GameSession::m_sensors->GetDirectionVectorBetweenShipAndNearestAst(obj);
	float angle = atan2(dir->x, dir->y);
	delete dir;
	return angle;
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

Point* Sensors::GetShipDirection(){
	float x = GameSession::m_mainShip->m_velocity.x;
	float y = GameSession::m_mainShip->m_velocity.y;
	// float x = GameSession::m_mainShip->m_pos.x - WINDOW_SIZE / 2;
	// float y = GameSession::m_mainShip->m_pos.y - WINDOW_SIZE_Y / 2;
	float norm = sqrt(pow(x,2) + pow(y,2));
	if (norm == 0)
		return new Point(1, 0);
	Point* res = new Point(x/norm, y/norm);
	return res;
};

Point* Sensors::GetVectorBetweenShipAndNearestAst(const GameObject* obj){
	if (obj == NULL){
		return NULL;
	}

	float x = GameSession::m_mainShip->m_pos.x - obj->m_pos.x;
	float y = GameSession::m_mainShip->m_pos.y - obj->m_pos.y;
	Point* res = new Point(x, y);
	return res;
};


float* Sensors::GetRelativeSpeed(const GameObject* obj){
	if (obj == NULL){
		return NULL;
	}

	const Point& vShip = GameSession::m_mainShip->m_velocity;
	const Point& vAst = obj->m_velocity;

	float *res = new float();
	// float s = abs(vAst.x - vShip.x) > abs(vAst.y - vShip.y) ? 
	// 			-( vAst.x - vShip.x ) / abs(vAst.x - vShip.x) : 
	// 			( vAst.y - vShip.y ) / abs(vAst.y - vShip.y);
	// *res = s*sqrt( pow(abs(vAst.x - vShip.x),2) + pow (abs(vAst.y - vShip.y),2));
	*res = sqrt( pow(abs(vAst.x - vShip.x),2) + pow (abs(vAst.y - vShip.y),2));
	return res;	
};

float* Sensors::GetCommonSpeed(const GameObject* obj){
	if (obj == NULL){
		return NULL;
	}

	const Point& vShip = GameSession::m_mainShip->m_velocity;
	const Point& vAst = obj->m_velocity;

	Point* dir = GetDirectionVectorBetweenShipAndNearestAst(obj);
	float projV = dir->x*vShip.x +dir->y*vShip.y;
	float projA = dir->x*vAst.x +dir->y*vAst.y;
	float *res = new float(projA-projV);
	// float s = abs(vAst.x - vShip.x) > abs(vAst.y - vShip.y) ? 
	// 			-( vAst.x - vShip.x ) / abs(vAst.x - vShip.x) : 
	// 			( vAst.y - vShip.y ) / abs(vAst.y - vShip.y);
	// *res = s*sqrt( pow(abs(vAst.x - vShip.x),2) + pow (abs(vAst.y - vShip.y),2));
	// *res = sqrt( pow(abs(vAst.x - vShip.x),2) + pow (abs(vAst.y - vShip.y),2));
	delete dir;
	return res;	
};

// LIBERER MEMOIRE
vector<float*> Sensors::GetIAInputs(){
	float *shipAngle = NULL,*dirAngle = NULL, *dirAstAngle = NULL, *relativeSpeed = NULL, *dir_x = NULL, *dir_y = NULL;
	bool isNearestAst = false;

	shipAngle = new float (round(GameSession::m_sensors->GetShipRadianAngle() * 1000) / 1000);
	dirAngle = new float (round(GameSession::m_sensors->GetDirectionRadianAngle() * 1000) / 1000);

	const GameObject *ast = GameSession::m_sensors->GetNearestAst();
	if (ast != NULL){
		// relativeSpeed = GameSession::m_sensors->GetRelativeSpeed(ast);
		relativeSpeed = GameSession::m_sensors->GetCommonSpeed(ast);
		*relativeSpeed = round(*relativeSpeed * 1000) / 1000;
		// Point* dir = GameSession::m_sensors->GetDirectionVectorBetweenShipAndNearestAst(ast);
		Point* dir = GameSession::m_sensors->GetVectorBetweenShipAndNearestAst(ast);
		dir_x = new float(round(dir->x * 1000) / 1000);
		dir_y = new float(round(dir->y * 1000) / 1000);
		dirAstAngle = new float (round(GameSession::m_sensors->GetDirectionBetweenShipAndNearestAstRadianAngle(ast) * 1000) / 1000);
		isNearestAst = true;
		delete dir;
	}	
	// cout << *shipAngle << " | " << *dirAngle << " | " << *relativeSpeed << " | " << *dirAstAngle << endl;
	// return vector<float*>{shipAngle, dirAngle, dirAstAngle, dir_x, dir_y, relativeSpeed};
	return vector<float*>{dirAngle, dir_x, dir_y, relativeSpeed};
}