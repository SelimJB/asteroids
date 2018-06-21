#include "bullet.h"
#include "ast.h"

int Bullet::bulletnbr = 0;

Bullet::Bullet(Point pos, Point axis){
	m_type = OBJ_BULLET;
	m_collisionFlag = OBJ_AST;
	bulletnbr++;
	m_pos = pos;
	// m_axis = axis;
	m_velocity = -10*axis;
	m_radius = 2;
	for (float i = 0; i < 2*M_PI; i+= 2*M_PI / 12){
		m_DrawPoints.push_back(Point(
			sin(i)*(m_radius),
			-cos(i)*(m_radius)
		));
	}	
}

Bullet::~Bullet(){
	bulletnbr--;
}

void Bullet::Update(float deltaTime){ 
	m_pos.x += m_velocity.x;
	m_pos.y += m_velocity.y;
    if (m_pos.x < 0) m_pos.x += WINDOW_SIZE;
    if (m_pos.x >= WINDOW_SIZE) m_pos.x -= WINDOW_SIZE;
    if (m_pos.y < 0) m_pos.y += WINDOW_SIZE_Y;
    if (m_pos.y >= WINDOW_SIZE_Y) m_pos.y -= WINDOW_SIZE_Y;
	m_time -= deltaTime;
	// Bullet Collisions
	CheckCollisions();
	// Bullet life end
	if (m_time < 0)
		m_isdead = true;
}

void Bullet::UpdatePosition(float deltaTime){
	m_pos.x += m_velocity.x;
	m_pos.y += m_velocity.y;
    if (m_pos.x < 0) m_pos.x += WINDOW_SIZE;
    if (m_pos.x >= WINDOW_SIZE) m_pos.x -= WINDOW_SIZE;
    if (m_pos.y < 0) m_pos.y += WINDOW_SIZE_Y;
    if (m_pos.y >= WINDOW_SIZE_Y) m_pos.y -= WINDOW_SIZE_Y;
	m_time -= deltaTime;
	if (m_time < 0)
		m_isdead = true;
}

void Bullet::DoCollision(GameObject* obj){
	obj->m_isdead = true;
	m_isdead = true;
}

bool Bullet::IsColliding(GameObject* obj){
	if (obj->m_type == OBJ_AST){
		Ast& ast = dynamic_cast<Ast&>(*obj);
		if (CollisionPointCircle(m_pos, ast.m_pos, ast.m_radius)){
			return true;
		}
	}
	return false;
}

void Bullet::CheckCollisions(){
	for (list<GameObject*>::iterator it = m_GameObjects[ASTS]->begin(); it != m_GameObjects[ASTS]->end(); it++)
	{
		GameObject& obj = **it;
		if (obj.m_type == OBJ_AST){
			Ast& ast = dynamic_cast<Ast&>(obj);
			if (CollisionPointCircle(m_pos, ast.m_pos, ast.m_radius)){
				ast.m_isdead = true;
				m_isdead = true;
			}
		}
	}
}

