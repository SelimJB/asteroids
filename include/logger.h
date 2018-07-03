#ifndef LOGGER
#define LOGGER

#include <map>
#include <fstream>
#include <string>

class GameObject;
class GameSession;

static const std::string fileName = "Inputs.txt"; // Put in the config file

class Point;

class Logger
{
	private:
	// Put in config file
	static const bool Switch_GameSession = false;
	static const bool Switch_GameObj = false;
	static const bool Switch_ShipAxis = false;
	static const bool Switch_ShipPos = false;
	static const bool Switch_GameObjNum = false;
	static const bool Switch_TxtLog = true;
	static std::ofstream *recordFile;
  public:
	static const bool Switch_PythonScript = true;
  	static void Initialize(std::string fileName);
	static void Release();
	static int FrameNum;
	static void Log(GameObject *);
	static void PrintFrame();
	static void LogShip();
	static void LogInTextFile();
	static void PrintPoint(const Point&);
};

#endif