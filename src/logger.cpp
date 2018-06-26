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
		const GameObject *ast = GameSession::m_sensors->GetNearestAst();
		float shipAngle = GameSession::m_sensors->GetShipRadianAngle();
		float *relativeSpeed = GameSession::m_sensors->GetRelativeSpeed(ast);
		Point *dir = GameSession::m_sensors->GetDirectionVectorBetweenShipAndNearestAst(ast);

		*recordFile << shipAngle << "\t"
					<< "aze" << "\t"
					<< "aze" << "\n";
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