#include "ast.h"


Ast::~Ast(){
	if (m_astSize > 1){
		new Ast(m_astSize-1,m_pos);
		new Ast(m_astSize-1,m_pos);
		new Ast(m_astSize-1,m_pos);
	}
}

Ast::Ast(int size) : m_astSize(size) {
	m_type = OBJ_AST;
	m_collisionFlag = OBJ_NONE;
	m_granularityMax = 6 + 3 * m_astSize;
	m_granularityMin = 4 + m_astSize;
	m_radius = 5.5 * pow(2,m_astSize-1);
	m_radiusVariation = 1 + (m_astSize-1)*2;
	m_velocity = Point(
		GetRandomFloat(-2,2),
		GetRandomFloat(-2,2)
	);
	m_angVelocity = GetRandomFloat(5,100);
	m_pos = Point(
		GetRandomBool() ? GetRandomFloat(0,WINDOW_SIZE / 3) : GetRandomFloat(WINDOW_SIZE / 2, WINDOW_SIZE),
		GetRandomBool() ? GetRandomFloat(0,WINDOW_SIZE_Y / 3) : GetRandomFloat(WINDOW_SIZE_Y / 2, WINDOW_SIZE_Y)
	);	
	int granularity = GetRandomInt(m_granularityMin,m_granularityMax);
	for (float i = 0; i < 2*M_PI; i+= 2*M_PI / granularity){
		m_DrawPoints.push_back(Point(
			sin(i)*(m_radiusVariation*GetRandomFloat(-1,1)+m_radius),
			-cos(i)*(m_radiusVariation*GetRandomFloat(-1,1)+m_radius)
		));
	}
	m_GameObjects[ASTS]->push_front(this);
}

Ast::Ast(int size,Point pos) : m_astSize(size) {
	m_type = OBJ_AST;
	m_collisionFlag = OBJ_NONE;
	m_pos = pos;
	m_granularityMax = 6 + 3 * m_astSize;
	m_granularityMin = 4 + m_astSize;
	m_radius = 5.5 * pow(2,m_astSize-1);
	m_radiusVariation = 1 + (m_astSize-1)*2;
	m_velocity = Point(
		GetRandomFloat(-2,2), 
		GetRandomFloat(-2,2) 
	);
	m_angVelocity = GetRandomFloat(5,100);
	int granularity = GetRandomInt(m_granularityMin,m_granularityMax);
	for (float i = 0; i < 2*M_PI; i+= 2*M_PI / granularity){
		m_DrawPoints.push_back(Point(
			sin(i)*(m_radiusVariation*GetRandomFloat(-1,1)+m_radius),
			-cos(i)*(m_radiusVariation*GetRandomFloat(-1,1)+m_radius)
		));
	}
	m_GameObjects[ASTS]->push_front(this);
}

void Ast::Update(float deltaTime){
	m_pos.x += m_velocity.x;
	m_pos.y += m_velocity.y;
    if (m_pos.x < 0) m_pos.x += WINDOW_SIZE;
    if (m_pos.x >= WINDOW_SIZE) m_pos.x -= WINDOW_SIZE;
    if (m_pos.y < 0) m_pos.y += WINDOW_SIZE_Y;
    if (m_pos.y >= WINDOW_SIZE_Y) m_pos.y -= WINDOW_SIZE_Y;		
	float dA = - m_angVelocity * deltaTime / 1000;
	Matrix2D rotMatrix = getRotationMatrix2(dA);	
	FormRotation(m_DrawPoints,rotMatrix);
}

void Ast::UpdatePosition(float deltaTime){
	m_pos.x += m_velocity.x;
	m_pos.y += m_velocity.y;
    if (m_pos.x < 0) m_pos.x += WINDOW_SIZE;
    if (m_pos.x >= WINDOW_SIZE) m_pos.x -= WINDOW_SIZE;
    if (m_pos.y < 0) m_pos.y += WINDOW_SIZE_Y;
    if (m_pos.y >= WINDOW_SIZE_Y) m_pos.y -= WINDOW_SIZE_Y;		
	float dA = - m_angVelocity * deltaTime / 1000;
	Matrix2D rotMatrix = getRotationMatrix2(dA);	
	FormRotation(m_DrawPoints,rotMatrix);
}
