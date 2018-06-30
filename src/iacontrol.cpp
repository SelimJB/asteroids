#include "iacontrol.h"
#include "ship.h"
#include "gamesession.h"
#include <iostream>
using namespace std;

void IAControl::MooveShip(int input){	
	GameSession::m_mainShip->m_ThrustState = (Ship::ShipThrustStates) (input % 3);
	GameSession::m_mainShip->m_DirState = (Ship::ShipDirStates) (input / 3);
}