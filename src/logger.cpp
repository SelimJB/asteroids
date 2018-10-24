#include "logger.h"
#include "gamesession.h"
#include <iostream>
#include "ship.h"
#include "helper.h"
#include "configurationmanager.h"
using namespace std;

int Logger::FrameNum = 0;
ofstream *Logger::recordFile = new ofstream();

bool Logger::Switch_PythonScript = true;
bool Logger::Switch_GameSession = true;

void Logger::Initialize(string fileName)
{
	ConfigurationManager config = ConfigurationManager();
	Switch_PythonScript = config.GetFirstNodeValue<bool>("enable_python_script");
	Switch_GameSession = config.GetFirstNodeValue<bool>("Switch_GameSession");
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
		vector<float*> inputs = GameSession::m_sensors->GetIAInputs();
		for (size_t i = 0; i<inputs.size(); i++){
			if( inputs[i] == NULL ){
				*recordFile << 'X' << "\t";
			}
			else {
				*recordFile << *inputs[i] << "\t";
			}
		}
		*recordFile << output << "\t";
		*recordFile << GameSession::m_mainShip->m_isDeadLogInfo << "\n";
		if (GameSession::m_mainShip->m_isDeadLogInfo){
			GameSession::m_mainShip->m_isDeadLogInfo = false;
		}
	}
}

void Logger::LogInTextFile2()
{
	if (Switch_TxtLog)
	{
		int thrustOutput = GameSession::m_mainShip->m_ThrustState == 2 ? -1 : GameSession::m_mainShip->m_ThrustState;
		int dirOutput = GameSession::m_mainShip->m_DirState == 2 ? -1 : GameSession::m_mainShip->m_DirState;
		vector<float*> inputs = GameSession::m_sensors->GetIAInputs();
		for (size_t i = 0; i<inputs.size(); i++){
			if( inputs[i] == NULL ){
				*recordFile << 'X' << "\t";
			}
			else {
				*recordFile << *inputs[i] << "\t";
			}
		}
		*recordFile << thrustOutput << "\t";
		*recordFile << dirOutput << "\t";
		*recordFile << GameSession::m_mainShip->m_isDeadLogInfo << "\n";
		if (GameSession::m_mainShip->m_isDeadLogInfo){
			GameSession::m_mainShip->m_isDeadLogInfo = false;
		}
	}
}

void Logger::LogInTextFile3()
{
	if (Switch_TxtLog)
	{
		bool thrustOutput = GameSession::m_mainShip->m_ThrustState == 1 ? 1 : 0;
		bool backThrustOutput = GameSession::m_mainShip->m_ThrustState == 2 ? 1 : 0;
		bool leftOutput = GameSession::m_mainShip->m_DirState == 1 ? 1 : 0;
		bool rightOutput = GameSession::m_mainShip->m_DirState == 2 ? 1 : 0;
		vector<float*> inputs = GameSession::m_sensors->GetIAInputs();
		for (size_t i = 0; i<inputs.size(); i++){
			if( inputs[i] == NULL ){
				*recordFile << 'X' << "\t";
			}
			else {
				*recordFile << *inputs[i] << "\t";
			}
		}
		*recordFile << thrustOutput << "\t";
		*recordFile << backThrustOutput << "\t";
		*recordFile << leftOutput << "\t";
		*recordFile << rightOutput << "\t";
		*recordFile << GameSession::m_mainShip->m_isDeadLogInfo << "\n";
		if (GameSession::m_mainShip->m_isDeadLogInfo){
			GameSession::m_mainShip->m_isDeadLogInfo = false;
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