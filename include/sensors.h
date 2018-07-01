#ifndef SENSORS
#define SENSORS

#include <vector>
class GameSession;
class GameObject;
class Point;
class IAInputs;

class Sensors
{
  public:
	const GameObject *GetNearestAst();
	float GetShipRadianAngle();
	Point *GetDirectionVectorBetweenShipAndNearestAst(const GameObject *);
	float *GetRelativeSpeed(const GameObject *);
	IAInputs GetIAInputs();
};

class IAInputs
{
  public:
	float ShipAngle;
	float* X_dirShipNearestAst;
	float* Y_dirShipNearestAst;
	float* RelativeSpeed;
	bool IsNearestAst;
	~IAInputs();
	IAInputs(float shipAngle, float* x_dirShipNearestAst, float* y_dirShipNearestAst, float* relativeSpeed, bool isNearestAst) 
		: ShipAngle(shipAngle), X_dirShipNearestAst(x_dirShipNearestAst), Y_dirShipNearestAst(y_dirShipNearestAst), RelativeSpeed(relativeSpeed), IsNearestAst(isNearestAst) {}
};

#endif