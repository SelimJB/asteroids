#ifndef BULLET
#define BULLET

#include "gameobject.h"
#include "ast.h"

class Bullet : public GameObject {
	public:
	Bullet(Point pos,Point axis);
	static int bulletnbr;
	int m_radius;
	void Update(float deltaTime);
	int m_time = 800;
	bool Remove();
	~Bullet();
	bool Collid(Ast& ast);
	void CheckCollisions();
};

#endif