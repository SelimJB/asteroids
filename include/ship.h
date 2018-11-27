#ifndef SHIP
#define SHIP

#include "gameobject.h"

class Ship : public GameObject
{
  public:
	enum ShipThrustStates
	{
		THRUSTOFF,
		THRUSTON,
		THRUSTREVERSE
	};
	enum ShipDirStates
	{
		CENTER,
		LEFT,
		RIGHT
	};
	~Ship();
	ShipDirStates m_DirState = CENTER;
	ShipThrustStates m_ThrustState = THRUSTOFF;
	// 
	int GetShipMoveState();
	bool m_ShipCanShoot = true;
	Ship();
	void TurnLeft(float deltaTime);
	void TurnRight(float deltaTime);
	void ThrustOn(float deltaTime);
	void ThrustReverse(float deltaTime);
	void ThrustOff(float deltaTime);
	void Shoot();
	bool IsColliding(GameObject *);
	void DoCollision(GameObject *);
	void UpdatePosition(float deltaTime); 
	void Log();
	bool m_isDeadLogInfo = false;
};

#endif