#include "logger.h"
#include "gamesession.h"
#include <iostream>
using namespace std;

int Logger::FrameNum = 0;

void Logger::Log(GameObject* obj){
	if (Switch_GameObj)
		cout << "\tTYPE : " << obj->m_type << endl;
}

void Logger::PrintFrame(){
	if (Switch_GameSession){
		FrameNum++;
		cout << "\n\n" << FrameNum << endl;
		cout << "\tNbr : " << GameSession::GetGameObjNumber() << endl;
	}
}
