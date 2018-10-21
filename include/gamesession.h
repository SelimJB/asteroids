#ifndef GAMESESSION
#define GAMESESSION

#include "humancontrol.h"
#include "iacontrol.h"
#include "helper.h"
#include "sensors.h"
#include "ship.h"

typedef std::list<GameObject *> GameObjectList;

class Sensors;
class GameObject; 

class GameSession
{
  public:
	static SDL_Event *m_event;
	friend Sensors; 
	GameSession();
	void Update(float dt);
	void Draw(SDL_Renderer*); // Moove the SDL_Renderer
	void DrawLives();

	static void PostGameObj(GameObject * obj)
	{
		m_activeObjectList.push_back(obj);
	}
	static int GetGameObjNumber(){
		return m_activeObjectList.size();
	}

	enum {
		CONTROL_THRUST_ON,
		CONTROL_THRUST_REVERSE,
		CONTROL_THRUST_OFF,
		CONTROL_RIGHT_ON,
		CONTROL_LEFT_ON,
		CONTROL_STOP_TURN,
		CONTROL_STOP,
		CONTROL_SHOOT,
		CONTROL_HYPERSPACE,
		CONTROL_PAUSE,
		CONTROL_AION,
		CONTROL_AIOFF
	};
	// void UseControl(int control);

	//score functions
	void IncrementScore(int inc) { m_score += inc; }
	void ResetScore() { m_score = 0; }

	//game related functions
	void StartGame();
	void StartNextWave();
	void LaunchAsteroidWave();
	void WaveOver();
	void GameOver();
	void KillShip(GameObject * ship);


	static Ship *m_mainShip; // ! static
	static Sensors *m_sensors; // ! static
	HumanControl *m_humanControl;
	IAControl *m_IAControl;
	bool m_bonusUsed;
	int m_screenW;
	int m_screenH;
	int m_spaceSize;
	float m_respawnTimer;
	float m_powerupTimer;
	int m_state;
	int m_score;
	int m_numLives;
	int m_waveNumber;
	int m_numAsteroids;
	bool m_AIOn;
	static bool m_quit;
	enum
	{
		STATE_PLAY,
		STATE_PAUSE,
		STATE_NEXTWAVE,
		STATE_GAMEOVER
	};


  private:
	static GameObjectList m_activeObjectList;
};

#endif