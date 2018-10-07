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
	float GetDirectionRadianAngle();
	float GetDirectionBetweenShipAndNearestAstRadianAngle(const GameObject* obj);
	Point *GetDirectionVectorBetweenShipAndNearestAst(const GameObject *);
	Point *GetShipDirection();
	Point *GetVectorBetweenShipAndNearestAst(const GameObject *);
	float *GetRelativeSpeed(const GameObject *);
	float *GetCommonSpeed(const GameObject *);
	std::vector<float*> GetIAInputs();
};

#endif