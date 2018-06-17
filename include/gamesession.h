#ifndef GAMESESSION
#define GAMESESSION

#include "gameobject.h"
#include "humancontrol.h"
#include "aicontrol.h"
#include "ast.h"


typedef std::list<GameObject *> GameObjectList;

class GameSession
{
  public:

	GameSession();
	void Update(float dt);
	void Draw();
	void DrawLives();

	void PostGameObj(GameObject * obj)
	{
		m_activeObj.push_back(obj);
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

	void IncrementScore(int inc) { m_score += inc; }
	void ResetScore() { m_score = 0; }

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
	GameObjectList m_activeObj;
};

#endif