#include "bullet.h"

int Bullet::bulletnbr = 0;

Bullet::Bullet(Point pos, Point axis){
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
	cout << "GaETHaN JTechidANl3sDENTs" << endl;
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

bool Bullet::Collid(Ast& ast){
	return pow(ast.m_pos.x - m_pos.x,2) + pow(ast.m_pos.y - m_pos.y,2) <= pow(ast.m_radius,2);
}

// void Bullet::CheckCollisions(){
// 	for (list<GameObject*>::iterator it = m_GameObjects[ASTS]->begin(); it != m_GameObjects[ASTS]->end(); it++)
// 	{
// 		Ast& a = dynamic_cast<Ast&>(**it);
// 		if (Collid(a)){
// 			cout << "coll"<<endl;
// 			a.m_isdead = true;
// 			m_isdead = true;
// 		}
// 	}
// }

void Bullet::CheckCollisions(){
	for (list<GameObject*>::iterator it = m_GameObjects[ASTS]->begin(); it != m_GameObjects[ASTS]->end(); it++)
	{
		Ast& a = dynamic_cast<Ast&>(**it);
		if (CollisionPointCircle(m_pos,a.m_pos,a.m_radius)){
			a.m_isdead = true;
			m_isdead = true;
		}
	}
}