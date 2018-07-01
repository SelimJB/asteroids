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
			Point *dir = GameSession::m_sensors->GetDirectionVectorBetweenShipAndNearestAst(ast);
			Debug::Draw(vector<Point>{Point(600, 40), Point(600 + dir->x * (*relativeSpeed) * 3, 40 + dir->y * (*relativeSpeed) * 3)}, 255, 0, 0, 255);
			Debug::Draw(vector<Point>{GameSession::m_mainShip->m_pos, ast->m_pos}, 0, 255, 0, 255);
			delete relativeSpeed;
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