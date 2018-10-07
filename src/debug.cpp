#include "debug.h"
#include "gamesession.h"
using namespace std;

SDL_Renderer *Debug::renderer = NULL;

void Debug::Initialise(SDL_Renderer *r)
{
	renderer = r;
}

void Debug::ShowIndicators()
{
	if (Switch_ShowIndicators)
	{
		const GameObject *ast = GameSession::m_sensors->GetNearestAst();
		if (ast)
		{
			float *relativeSpeed = GameSession::m_sensors->GetRelativeSpeed(ast);
			float *commonSpeed = GameSession::m_sensors->GetCommonSpeed(ast);
			Point *dir = GameSession::m_sensors->GetDirectionVectorBetweenShipAndNearestAst(ast);
			Point *shipDir = GameSession::m_sensors->GetShipDirection();
			Debug::Draw(vector<Point>{Point(530,22), Point(530, 28)}, 0, 0, 255, 255);
			Debug::Draw(vector<Point>{Point(530,25), Point(530 + *relativeSpeed * 5, 25)}, 0, 0, 255, 255);
			Debug::Draw(vector<Point>{Point(460,22), Point(460, 28)}, 255, 0, 255, 255);
			Debug::Draw(vector<Point>{Point(460,25), Point(460 + *commonSpeed * 5, 25)}, 255, 0, 255, 255);
			Debug::Draw(vector<Point>{Point(600, 25), Point(600 + dir->x * 15, 25 + dir->y * 15)}, 255, 0, 0, 255);
			Debug::Draw(vector<Point>{Point(500, 25), Point(500 + shipDir->x * 15, 25 + shipDir->y * 15)}, 0, 255, 255, 255);
			Debug::Draw(vector<Point>{GameSession::m_mainShip->m_pos, ast->m_pos}, 0, 255, 0, 255);

			Debug::Draw(vector<Point>{
				Point(GameSession::m_mainShip->m_pos.x,GameSession::m_mainShip->m_pos.y), 
				Point(GameSession::m_mainShip->m_pos.x - GameSession::m_mainShip->m_axis.x*15, GameSession::m_mainShip->m_pos.y - GameSession::m_mainShip->m_axis.y*15)}, 
			0, 0, 255, 255);
			Debug::Draw(vector<Point>{
				Point(GameSession::m_mainShip->m_pos.x,GameSession::m_mainShip->m_pos.y), 
				Point(GameSession::m_mainShip->m_pos.x + shipDir->x*15, GameSession::m_mainShip->m_pos.y + shipDir->y*15)}, 
			255, 0, 0, 255);	
			Debug::Draw(vector<Point>{
				Point(GameSession::m_mainShip->m_pos.x,GameSession::m_mainShip->m_pos.y), 
				Point(GameSession::m_mainShip->m_pos.x - dir->x*15, GameSession::m_mainShip->m_pos.y - dir->y*15)}, 
			255, 0, 255, 255);						
			// Debug::Draw(vector<Point>{Point(530,22), Point(530, 28)}, 0, 0, 255, 255);

			delete relativeSpeed;
			delete commonSpeed;
			delete shipDir;
			delete dir;
		}
	}
}

void Debug::Draw(vector<Point> pts, char r, char v, char b, char o)
{
	if (Switch_Draw == true)
	{
		SDL_SetRenderDrawColor(renderer, r, v, b, o);
		for (vector<Point>::iterator i = pts.begin(); i != pts.end(); ++i)
		{
			SDL_RenderDrawLine(renderer,
							   i->x,
							   i->y,
							   ((i + 1) == pts.end() ? pts.begin() : (i + 1))->x,
							   ((i + 1) == pts.end() ? pts.begin() : (i + 1))->y);
		}
		SDL_SetRenderDrawColor(renderer, 100, 7, 2, 255);
	}
}