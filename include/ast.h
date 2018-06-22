#ifndef AST
#define AST

#include "gameobject.h"

class Ast : public GameObject {
	public: 
	float m_radius = 22;
	Ast(int size);
	Ast(int size, Point pos);
	~Ast();
	private:
	int m_astSize = 3;
	int m_granularityMax = 15;
	int m_granularityMin = 7;
	int m_radiusVariation = 5;
	void UpdatePosition(float deltaTime); 
};

#endif