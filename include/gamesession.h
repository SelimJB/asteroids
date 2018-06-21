#ifndef GAMESESSION
#define GAMESESSION

#include "gameobject.h"
#include "humancontrol.h"
#include "aicontrol.h"
#include "helper.h"

typedef std::list<GameObject *> GameObjectList;

class GameSession
{
  public:
	GameSession();
	void Update(float dt);
	void Draw(SDL_Renderer*);
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


	Ship *m_mainShip;
	HumanControl *m_humanControl;
	AIControl *m_AIControl;
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