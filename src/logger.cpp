#include "logger.h"
#include "gamesession.h"
#include <iostream>
#include "ship.h"

int Logger::FrameNum = 0;
ofstream* Logger::recordFile = new ofstream();

void Logger::Initialize(string fileName){
	if (Switch_TxtLog) {
		recordFile->open(fileName);
	}
}

void Logger::Release(){
	if (Switch_TxtLog)
		recordFile->close();
}

void Logger::LogInTextFile(){
	if (Switch_TxtLog){
		*recordFile << GameSession::m_mainShip->m_axis.x << "\t" 
				<< GameSession::m_mainShip->m_axis.y << "\n";
	}
}

void Logger::Log(GameObject* obj){
	if (Switch_GameObj){
		cout << "\tTYPE : " << obj->m_type << endl;
	}
}

void Logger::LogShip(){
	if (Switch_ShipAxis){
		cout << "\t (x, y) : (" 
			<< GameSession::m_mainShip->m_axis.x << ", " 
			<< GameSession::m_mainShip->m_axis.y << ")" << endl;
	}
	if (Switch_ShipPos){
		cout << "\t (x, y) : (" 
			<< GameSession::m_mainShip->m_pos.x << ", " 
			<< GameSession::m_mainShip->m_pos.y << ")" << endl;
	}	
}

void Logger::PrintFrame(){
	if (Switch_GameSession){
		FrameNum++;
		cout << "\n\n" << FrameNum << endl;
		if (Switch_GameObjNum) cout << "\tNbr : " << GameSession::GetGameObjNumber() << endl;
	}
	LogShip();
}
