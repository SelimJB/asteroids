#include "ship.h"
#include "bullet.h"
#include "ast.h"

Ship::Ship(){
	m_pos = Point(20,20);
	m_axis = Point(0,1);
	m_normal = Point(1,0);
	m_collisionFlag = OBJ_AST;
	m_type = OBJ_SHIP;
	m_acceleration = 0.0075;
	m_angVelocity = 360;
	m_dragFactor = 0.00052;
	m_DrawPoints.push_back(Point(0,-5));
	m_DrawPoints.push_back(Point(-5,9));
	m_DrawPoints.push_back(Point(0,4));
	m_DrawPoints.push_back(Point(5,9));
	m_GameObjects[SHIPS]->push_back(this);
}

void Ship::Shoot(){
	if (m_ShipCanShoot){
		Bullet* bibi = new Bullet(m_pos,m_axis);
		m_GameObjects[BULLETS]->push_back(bibi);
		m_ShipCanShoot = false;
	}
}

void Ship::TurnRight(float deltaTime){
	float dA = m_angVelocity * deltaTime / 1000;
	Matrix2D rotMatrix = getRotationMatrix2(dA);
	m_axis = rotMatrix * m_axis; 
	m_normal = rotMatrix * m_normal;
	FormRotation(m_DrawPoints,rotMatrix);
}

void Ship::TurnLeft(float deltaTime){
	float dA = - m_angVelocity * deltaTime / 1000;
	Matrix2D rotMatrix = getRotationMatrix2(dA);
	m_axis = rotMatrix * m_axis; 
	m_normal = rotMatrix * m_normal;
	FormRotation(m_DrawPoints,rotMatrix);
}

void Ship::ThrustOn(float deltaTime){
	m_velocity.y = m_velocity.y - m_acceleration*deltaTime*m_axis.y - m_velocity.y*m_dragFactor*deltaTime;
	m_velocity.x = m_velocity.x - m_acceleration*deltaTime*m_axis.x - m_velocity.x*m_dragFactor*deltaTime;
}

void Ship::ThrustReverse(float deltaTime){
	m_velocity.y = m_velocity.y + m_acceleration*deltaTime*m_axis.y - m_velocity.y*m_dragFactor*deltaTime;
	m_velocity.x = m_velocity.x + m_acceleration*deltaTime*m_axis.x - m_velocity.x*m_dragFactor*deltaTime;
}

void Ship::ThrustOff(float deltaTime){
	m_velocity.x -= m_velocity.x*m_dragFactor*deltaTime;
	m_velocity.y -= m_velocity.y*m_dragFactor*deltaTime;
}

// Enlever le WINDOWS SIZE CODE EN DUR
void Ship::Update(float deltaTime){
	if (m_DirState == CENTER){
	}
	else if (m_DirState == LEFT){
		TurnLeft(deltaTime);
	}	
	else if (m_DirState == RIGHT){
		TurnRight(deltaTime);
	}
	if (m_ThrustState == THRUSTOFF){
		ThrustOff(deltaTime);
	}
	else if (m_ThrustState == THRUSTON){
		ThrustOn(deltaTime);
	}	
	else if (m_ThrustState == THRUSTREVERSE){
		ThrustReverse(deltaTime);
	}		
	ShipCheckCollision();
	m_pos.x += m_velocity.x;
	m_pos.y += m_velocity.y;
    if (m_pos.x < 0) m_pos.x += WINDOW_SIZE;
    if (m_pos.x >= WINDOW_SIZE) m_pos.x -= WINDOW_SIZE;
    if (m_pos.y < 0) m_pos.y += WINDOW_SIZE_Y;
    if (m_pos.y >= WINDOW_SIZE_Y) m_pos.y -= WINDOW_SIZE_Y;	
}

void Ship::UpdatePosition(float deltaTime){
	if (m_DirState == CENTER){
	}
	else if (m_DirState == LEFT){
		TurnLeft(deltaTime);
	}	
	else if (m_DirState == RIGHT){
		TurnRight(deltaTime);
	}
	if (m_ThrustState == THRUSTOFF){
		ThrustOff(deltaTime);
	}
	else if (m_ThrustState == THRUSTON){
		ThrustOn(deltaTime);
	}	
	else if (m_ThrustState == THRUSTREVERSE){
		ThrustReverse(deltaTime);
	}		
	m_pos.x += m_velocity.x;
	m_pos.y += m_velocity.y;
    if (m_pos.x < 0) m_pos.x += WINDOW_SIZE;
    if (m_pos.x >= WINDOW_SIZE) m_pos.x -= WINDOW_SIZE;
    if (m_pos.y < 0) m_pos.y += WINDOW_SIZE_Y;
    if (m_pos.y >= WINDOW_SIZE_Y) m_pos.y -= WINDOW_SIZE_Y;	
}

void Ship::DoCollision(GameObject* obj){
	m_pos = Point(WINDOW_SIZE/2,WINDOW_SIZE_Y/2);
}

void Ship::ShipCheckCollision(){
	for (list<GameObject*>::iterator it = m_GameObjects[ASTS]->begin(); it != m_GameObjects[ASTS]->end(); it++)
	{
		GameObject& obj = **it;
		if (obj.m_type == OBJ_AST){
			Ast& ast = dynamic_cast<Ast&>(obj);
			if (
				CollisionSegCircle(m_DrawPoints[0]+m_pos,m_DrawPoints[1]+m_pos,ast.m_pos,ast.m_radius) ||
				CollisionSegCircle(m_DrawPoints[1]+m_pos,m_DrawPoints[3]+m_pos,ast.m_pos,ast.m_radius) ||
				CollisionSegCircle(m_DrawPoints[3]+m_pos,m_DrawPoints[0]+m_pos,ast.m_pos,ast.m_radius) ||
				CollisionPointCircle(m_DrawPoints[3]+m_pos,ast.m_pos,ast.m_radius) ||
				CollisionPointCircle(m_DrawPoints[0]+m_pos,ast.m_pos,ast.m_radius) ||
				CollisionPointCircle(m_DrawPoints[1]+m_pos,ast.m_pos,ast.m_radius) 
			){
				// m_isdead = true;
				m_pos = Point(WINDOW_SIZE/2,WINDOW_SIZE_Y/2);
			}
		}
	}
}

bool Ship::IsColliding(GameObject* obj){
	if (obj->m_type == OBJ_AST){
		Ast& ast = dynamic_cast<Ast&>(*obj);
		if (
			CollisionSegCircle(m_DrawPoints[0]+m_pos,m_DrawPoints[1]+m_pos,ast.m_pos,ast.m_radius) ||
			CollisionSegCircle(m_DrawPoints[1]+m_pos,m_DrawPoints[3]+m_pos,ast.m_pos,ast.m_radius) ||
			CollisionSegCircle(m_DrawPoints[3]+m_pos,m_DrawPoints[0]+m_pos,ast.m_pos,ast.m_radius) ||
			CollisionPointCircle(m_DrawPoints[3]+m_pos,ast.m_pos,ast.m_radius) ||
			CollisionPointCircle(m_DrawPoints[0]+m_pos,ast.m_pos,ast.m_radius) ||
			CollisionPointCircle(m_DrawPoints[1]+m_pos,ast.m_pos,ast.m_radius) 
		){
			return true;
		}
	}
	return false;
}

Ship::~Ship(){
}

void Ship::Log(){
	cout << "\tType : SHIP" << endl;
}