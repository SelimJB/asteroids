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
	std::vector<float*> GetIAInputs();
};

#endif