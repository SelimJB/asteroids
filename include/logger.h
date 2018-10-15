#ifndef LOGGER
#define LOGGER

#include <map>
#include <fstream>
#include <string>

class GameObject;
class GameSession;

static const std::string fileName = "misc/Inputs.txt"; // Put in the config file

class Point;

class Logger
{
	private:
	// Put in config file
	static bool Switch_GameSession;
	static const bool Switch_GameObj = false;
	static const bool Switch_ShipAxis = false;
	static const bool Switch_ShipPos = false;
	static const bool Switch_GameObjNum = false;
	static std::ofstream *recordFile;
  public:
	static const bool Switch_TxtLog = true;
	// TODO modifier ça 
	// 0 : 1 Output
	// 1 : 2 Output
	static const int InputMode = 2;
	static bool Switch_PythonScript;
  	static void Initialize(std::string fileName);
	static void Release();
	static int FrameNum;
	static void Log(GameObject *);
	static void PrintFrame();
	static void LogShip();
	static void LogInTextFile();
	static void LogInTextFile2();
	static void LogInTextFile3();
	static void PrintPoint(const Point&);
};

#endif