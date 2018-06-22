#ifndef LOGGER
#define LOGGER

#include <map>
#include <fstream>
#include <string>
using namespace std;

class GameObject;
class GameSession;

static const string fileName = "Inputs.txt"; // Put in the config file

class Logger
{
	private:
	// Put in config file
	static const bool Switch_GameObj = false;
	static const bool Switch_GameSession = true;
	static const bool Switch_Ship = true;
	static const bool Switch_GameObjNum = false;
	static const bool Switch_TxtLog = true;
	static ofstream *recordFile;
  public:
  	static void Initialize(string fileName);
	static void Release();
	static int FrameNum;
	static void Log(GameObject *);
	static void PrintFrame();
	static void LogShip();
	static void LogInTextFile();
};

#endif