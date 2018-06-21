#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "helper.h"

class Ship;

class GameObject{
	private:
	public:
	virtual ~GameObject(){};
	GameObject();
	enum ObjectsType {
		SHIPS,
		ASTS,
		BULLETS
	};
	static vector<list<GameObject*>*> m_GameObjects;	
	virtual void Draw(SDL_Renderer*);
	virtual void Update(float deltaTime)= 0;
	virtual bool IsColliding(GameObject*) {return false;};
	// virtual bool Remove(){return false;}
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
	vector<Point> m_DrawPoints;
	static Ship* m_ship;
	// Sphere3f m_boundSphere;
	// int m_type;
	// unsigned int m_collisionFlags;
	// int m_lifeTimer;

	enum {
		OBJ_NONE = 0x00000001,
		OBJ_SHIP = 0x00000010,
		OBJ_AST = 0x00000100,
		OBJ_TARGET = 0x00001000,
		OBJ_BULLET = 0x00010000
	};
	unsigned int m_type;
	unsigned int m_collisionFlag;
	virtual void DoCollision(GameObject*){};
	virtual void UpdatePosition(float deltaTime)=0; // Change name to Update	
};	


#endif