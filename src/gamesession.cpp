#include "gamesession.h"

GameSession::GameSession(){
}

void GameSession::Update(float dt){

}

void GameSession::Draw(){

}

void GameSession::DrawLives(){

}

void GameSession::LaunchAsteroidWave(){
	for (int i = 0;i<20;i++){
		m_activeObj.push_back(new Ast(GetRandomInt(2,4)));
	}
}