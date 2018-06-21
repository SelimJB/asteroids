#ifndef BULLET
#define BULLET

#include "gameobject.h"

class Bullet : public GameObject {
	public:
	Bullet(Point pos,Point axis);
	static int bulletnbr;
	int m_radius;
	void Update(float deltaTime);
	int m_time = 800;
	bool Remove();
	~Bullet();
	void CheckCollisions(); // Supress
	bool IsColliding(GameObject*);
	void DoCollision(GameObject*);
	void UpdatePosition(float deltaTime); // Change name to Update
};

#endif