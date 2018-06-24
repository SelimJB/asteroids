#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "helper.h"

class GameObject
{
  private:
  public:
	virtual ~GameObject(){};
	GameObject();
	enum ObjectsType
	{
		SHIPS,
		ASTS,
		BULLETS
	};
	unsigned int m_type;
	unsigned int m_collisionFlag;
	virtual void DoCollision(GameObject *){};
	virtual void UpdatePosition(float deltaTime) = 0;
	virtual void Draw(SDL_Renderer *);
	virtual bool IsColliding(GameObject *) { return false; };
	Point m_pos;
	Point m_axis;
	Point m_normal;
	// float m_angle;
	Point m_velocity;
	float m_acceleration;
	float m_angVelocity;
	float m_dragFactor;
	bool m_active = true;
	float m_size;
	bool m_isdead = false;
	std::vector<Point> m_DrawPoints;

	enum
	{
		OBJ_NONE = 0x00000001,
		OBJ_SHIP = 0x00000010,
		OBJ_AST = 0x00000100,
		OBJ_TARGET = 0x00001000,
		OBJ_BULLET = 0x00010000
	};
};

#endif