#include "debug.h"
#include "gamesession.h"
using namespace std;

SDL_Renderer *Debug::renderer = NULL;
const Point Debug::debugPos = Point(650,50);

void Debug::Initialise(SDL_Renderer *r)
{
	renderer = r;
}

void DrawGaugeIndicator(float indicator, Point pos, Color color){
	Debug::Draw(vector<Point>{Point(pos.x, pos.y - 4), Point(pos.x, pos.y + 4)}, color);
	Debug::Draw(vector<Point>{Point(pos.x+1, pos.y - 4), Point(pos.x+1, pos.y + 4)}, color);
	Debug::Draw(vector<Point>{Point(pos.x-1, pos.y - 4), Point(pos.x-1, pos.y + 4)}, color);
	Debug::Draw(vector<Point>{pos, Point(pos.x + indicator * 5, pos.y+1)}, color);	
	Debug::Draw(vector<Point>{pos, Point(pos.x + indicator * 5, pos.y-1)}, color);	
	Debug::Draw(vector<Point>{pos, Point(pos.x + indicator * 5, pos.y)}, color);	
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
			DrawGaugeIndicator(*commonSpeed, debugPos, Color(255, 0, 255, 130));
			DrawGaugeIndicator(*relativeSpeed, debugPos + Point(70,0), Color(0, 0, 255, 130));
			Debug::Draw(vector<Point>{debugPos + Point(140, 0), debugPos + Point(140, 0) + 15*(*dir)}, Color(255,0,0,130));
			Debug::Draw(vector<Point>{debugPos + Point(40, 0), debugPos + Point(40, 0) + 15*(*shipDir)}, Color(0,255,255,130));

			Debug::Draw(vector<Point>{GameSession::m_mainShip->m_pos, ast->m_pos}, Color(0,255,0,130));
			Debug::Draw(vector<Point>{
				Point(GameSession::m_mainShip->m_pos.x,GameSession::m_mainShip->m_pos.y), 
				Point(GameSession::m_mainShip->m_pos - 15*GameSession::m_mainShip->m_axis)}, 
				Color(0,0,255,255)
			);
			Debug::Draw(vector<Point>{
				Point(GameSession::m_mainShip->m_pos.x,GameSession::m_mainShip->m_pos.y),
				Point(GameSession::m_mainShip->m_pos + 15*(*shipDir)) },
				Color(255,0,0,255)
			);
			Debug::Draw(vector<Point>{
				Point(GameSession::m_mainShip->m_pos.x,GameSession::m_mainShip->m_pos.y), 
				Point(GameSession::m_mainShip->m_pos - 15*(*dir))}, 
				Color(255,0,255,255)
			);

			delete relativeSpeed;
			delete commonSpeed;
			delete shipDir;
			delete dir;
		}
	}
}

void Debug::Draw(vector<Point> pts, Color c)
{
	if (Switch_Draw == true)
	{
		SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
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