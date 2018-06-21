#ifndef SHIP
#define SHIP

#include "gameobject.h"

class Ship : public GameObject{
	public:
	enum ShipThrustStates {
		THRUSTON,
		THRUSTREVERSE,
		THRUSTOFF
	};
	enum ShipDirStates {
		LEFT,
		RIGHT,
		CENTER
	};	
	~Ship();
	ShipDirStates m_DirState = CENTER;
	ShipThrustStates m_ThrustState = THRUSTOFF;
	bool m_ShipCanShoot = true;
	// void Draw(SDL_Renderer*);
	Ship();
	void Update(float deltaTime);
	void TurnLeft(float deltaTime);
	void TurnRight(float deltaTime);
	void ThrustOn(float deltaTime);
	void ThrustReverse(float deltaTime);
	void ThrustOff(float deltaTime);
	void Shoot();
	void ShipCheckCollision();	// TODO delet
	bool IsColliding(GameObject*);
	void DoCollision(GameObject*);
	void UpdatePosition(float deltaTime); // Change name to Update
	void Log();
};

#endif