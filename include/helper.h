#ifndef HELPER
#define HELPER

#include <math.h>
#include <iostream>
#include "SDL2/SDL.h"
#include <vector>
#include <list>
#include <time.h>
#include <string>
#include <stdlib.h>
#include "SDL2_gfxPrimitives.h"
#include "logger.h"

const int WINDOW_SIZE = 640, WINDOW_SIZE_Y = 480;

class Matrix2D{
	public:
	float a1_1, a1_2, a2_1, a2_2;
	Matrix2D(float a1_1,float a1_2,float a2_1,float a2_2);
	void Print();
};

class Point{
	public:
	Point(float x, float y);
	Point();
	void Print();
	float x,y;

};

Point operator*(Matrix2D const& m,Point const& p); 
Point operator*(int const& i,Point const& p);
float operator*(Point const& a,Point const& b);
Point operator+(Point const& a,Point const& b);
Point operator-(Point const& a,Point const& b);

void FormRotation(std::vector<Point>&,Matrix2D);
Matrix2D getRotationMatrix2(float angle);
float radianConv(float angle);
int GetRandomInt(int min,int max);
float GetRandomFloat(int min, int max);
bool GetRandomBool();
bool CollisionDroite(Point A, Point B, Point C, float r);
bool CollisionSegCircle(Point A, Point B, Point C, float r);
bool CollisionPointCircle(Point A,Point C,float r);
#endif