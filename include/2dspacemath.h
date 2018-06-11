#ifndef TOTO
#define TOTO
#include <math.h>
#include <iostream>
#include "SDL2/SDL.h"
#include <vector>
#include <list>
#include <time.h>
#include <stdlib.h>
#include "SDL2_gfxPrimitives.h"
using namespace std;







class Matrix2D{
	public:
	float a1_1, a1_2, a2_1, a2_2;
	Matrix2D(float a1_1,float a1_2,float a2_1,float a2_2);
	void Print();
};

class Point{
	public:
	Point(float x, float y);
	Point();
	void Print();
	float x,y;

};

Point operator*(Matrix2D const& m,Point const& p); 
Point operator*(int const& i,Point const& p);

class GameObject{
	public:
	static vector<GameObject*> m_GameObjectsList;
	// virtual void Draw(SDL_Renderer*) = 0;
	virtual void Draw(SDL_Renderer*);
	virtual void Update(float deltaTime)= 0;
	virtual bool Remove(){return false;}
	virtual ~GameObject(){};
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
	vector<Point> m_DrawPoints;

	// Sphere3f m_boundSphere;
	// int m_type;
	// unsigned int m_collisionFlags;
	// int m_lifeTimer;
};	












#endif