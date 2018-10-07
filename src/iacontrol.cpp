#include "iacontrol.h"
#include "ship.h"
#include "gamesession.h"
#include <iostream>
using namespace std;

void IAControl::MooveShip(int input){	
	GameSession::m_mainShip->m_ThrustState = (Ship::ShipThrustStates) (input % 3);
	GameSession::m_mainShip->m_DirState = (Ship::ShipDirStates) (input / 3);
}

void IAControl::MooveShip2(int thrustInput, int dirInput){
	GameSession::m_mainShip->m_ThrustState = (Ship::ShipThrustStates) (thrustInput == -1 ? 2 : thrustInput);
	GameSession::m_mainShip->m_DirState = (Ship::ShipDirStates) (dirInput == -1 ? 2 : dirInput);
}

void IAControl::MooveShip3(int thrust, int reverse, int left, int right){
	if (thrust == 1)
		GameSession::m_mainShip->m_ThrustState = (Ship::ShipThrustStates) 1;
	else if (reverse == 1)
		GameSession::m_mainShip->m_ThrustState = (Ship::ShipThrustStates) 2;
	else
		GameSession::m_mainShip->m_ThrustState = (Ship::ShipThrustStates) 0;
	if (left == 1)
		GameSession::m_mainShip->m_DirState = (Ship::ShipDirStates) 1;
	else if (right == 1)
		GameSession::m_mainShip->m_DirState = (Ship::ShipDirStates) 2;
	else
		GameSession::m_mainShip->m_DirState = (Ship::ShipDirStates) 0;
}