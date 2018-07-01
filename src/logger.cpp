#include "logger.h"
#include "gamesession.h"
#include <iostream>
#include "ship.h"
#include "helper.h"
using namespace std;

int Logger::FrameNum = 0;
ofstream *Logger::recordFile = new ofstream();

void Logger::Initialize(string fileName)
{
	if (Switch_TxtLog)
	{
		recordFile->open(fileName);
	}
}

void Logger::Release()
{
	if (Switch_TxtLog)
		recordFile->close();
}

void Logger::LogInTextFile()
{
	if (Switch_TxtLog)
	{
		int output = GameSession::m_mainShip->m_ThrustState + GameSession::m_mainShip->m_DirState * 3;
		IAInputs inputs = GameSession::m_sensors->GetIAInputs();
		if (inputs.IsNearestAst){
			*recordFile << inputs.ShipAngle << "\t"
						<< *inputs.RelativeSpeed << "\t"
						<< *inputs.X_dirShipNearestAst << "\t"
						<< *inputs.Y_dirShipNearestAst << "\t"
						<< output << "\n";
		}
		else {
			*recordFile << inputs.ShipAngle << "\t"
						<< 'X' << "\t"
						<< 'X' << "\t"
						<< 'X' << "\t"
						<< output << "\n";
		}
	}
}

void Logger::Log(GameObject *obj)
{
	if (Switch_GameObj)
	{
		cout << "\tTYPE : " << obj->m_type << endl;
	}
}

void Logger::LogShip()
{
	if (Switch_ShipAxis)
	{
		cout << "\t (x, y) : ("
			 << GameSession::m_mainShip->m_axis.x << ", "
			 << GameSession::m_mainShip->m_axis.y << ")" << endl;
	}
	if (Switch_ShipPos)
	{
		cout << "\t (x, y) : ("
			 << GameSession::m_mainShip->m_pos.x << ", "
			 << GameSession::m_mainShip->m_pos.y << ")" << endl;
	}
}

void Logger::PrintFrame()
{
	if (Switch_GameSession)
	{
		FrameNum++;
		cout << "\n"
			 << FrameNum << endl;
		if (Switch_GameObjNum)
			cout << "\tNbr : " << GameSession::GetGameObjNumber() << endl;
	}
	LogShip();
}

void Logger::PrintPoint(const Point &p)
{
	cout << "\t( " << p.x << " , " << p.y << " ) " << endl;
}