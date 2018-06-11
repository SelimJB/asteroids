#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "helper.h"
class Ship;

class GameObject{
	private:
	public:
	virtual ~GameObject(){};
	enum ObjectsType {
		SHIPS,
		ASTS,
		BULLETS
	};
	static vector<list<GameObject*>*> m_GameObjects;	
	static vector<GameObject*> m_GameObjectsList;
	// virtual void Draw(SDL_Renderer*) = 0;
	virtual void Draw(SDL_Renderer*);
	virtual void Update(float deltaTime)= 0;
	// virtual bool Remove(){return false;}
	Point m_pos;
	Point m_axis;
	Point m_normal;
	// float m_angle;
	Point m_velocity;
	float m_acceleration;
	float m_angVelocity;
	float m_dragFactor;
	bool m_active;
	float m_size;
	bool m_isdead = false;
	vector<Point> m_DrawPoints;
	static Ship* m_ship;
	// Sphere3f m_boundSphere;
	// int m_type;
	// unsigned int m_collisionFlags;
	// int m_lifeTimer;
};	


#endif