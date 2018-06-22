#ifndef BULLET
#define BULLET

#include "gameobject.h"

class Bullet : public GameObject {
	public:
	Bullet(Point pos,Point axis);
	static int bulletnbr;
	int m_radius;
	int m_time = 800;
	bool Remove();
	~Bullet();
	bool IsColliding(GameObject*);
	void DoCollision(GameObject*);
	void UpdatePosition(float deltaTime);
};

#endif