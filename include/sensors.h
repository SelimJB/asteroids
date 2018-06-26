#ifndef SENSORS
#define SENSORS

class GameSession;
class GameObject;
class Point;

class Sensors
{
	public:
	const GameObject* GetNearestAst();
	float GetShipRadianAngle();
	Point* GetDirectionVectorBetweenShipAndNearestAst(const GameObject*);
	float* GetRelativeSpeed(const GameObject*);
	
};

#endif