#ifndef LOGGER
#define LOGGER

#include <map>

class GameObject;
class GameSession;

class Logger
{
	private:
	static const bool Switch_GameObj = false;
	static const bool Switch_GameSession = false;
	
  public:
	static int FrameNum;
	static void Log(GameObject *);
	static void PrintFrame();
};

#endif