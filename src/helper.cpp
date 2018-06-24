#include "helper.h"
using namespace std;

void FormRotation(vector<Point> &pts,Matrix2D m){
	for (vector<Point>::iterator i = pts.begin(); i != pts.end(); ++i){
		*i = m*(*i);
	}
};

Matrix2D::Matrix2D(float a1_1,float a1_2,float a2_1,float a2_2){
	Matrix2D::a1_1 = a1_1;
	Matrix2D::a1_2 = a1_2;
	Matrix2D::a2_1 = a2_1;
	Matrix2D::a2_2 = a2_2;
}

Point::Point(float x,float y){
	Point::x = x;
	Point::y = y;
}

Point::Point(){
	x = 0;
	y = 0;
}

void Matrix2D::Print(){
	cout << "l1:("<<a1_1<<","<<a1_2<<") l2:"<<a2_1<<","<<a2_2<<")" <<endl; 
}

void Point::Print(){
	cout << "p:("<<x<<","<<y<<")"<<endl;
}



Matrix2D getRotationMatrix2(float angle){
	float rad = radianConv(angle);
	return Matrix2D(cos(rad),-sin(rad),sin(rad),cos(rad)); 
} 


float radianConv(float angle){
	return angle * M_PI / 180;
}



int GetRandomInt(int min,int max){
	return (rand() % (max-min)) + min;
}
float GetRandomFloat(int min, int max){
	return (rand() % (max-min) + min) * (rand()/(float) RAND_MAX);
}
bool GetRandomBool(){
	return (rand() % 2) ? true : false; 
}

Point operator*(Matrix2D const& m,Point const& p){
	float x = m.a1_1 * p.x + m.a1_2 * p.y;
	float y = m.a2_1 * p.x + m.a2_2 * p.y;
	return Point(x,y);
}
Point operator*(int const& i,Point const& p){
	return Point(i*p.x,i*p.y);
}
Point operator-(Point const& a,Point const& b){
	return Point(a.x-b.x,a.y-b.y);
}
Point operator+(Point const& a,Point const& b){
	return Point(a.x+b.x,a.y+b.y);
}
float operator*(Point const& a,Point const& b){
	return a.x*b.x + a.y*b.y;
}

// Droite AB, cercle de centre C rayon r
bool CollisionDroite(Point A, Point B, Point C, float r){
	Point u = B - A;
	Point AC = C - A;
	float num = u.x*AC.y - u.y*AC.x;
	if (num<0)
		num = -num;
	float denum = sqrt(u.x*u.x + u.y*u.y);
	float CI = num / denum;
	if (CI <= r)
		return true;
	else
		return false;
}

bool CollisionSegCircle(Point A, Point B, Point C, float r){
	if (CollisionDroite(A,B,C,r) == false)
		return false;
	Point AB,AC,BC;
	AB = B - A;
	AC = C - A;
	BC = C - B;
	float pscal1 = AB*AC;
	float pscal2 = (-1*AB)*BC;
	if (pscal1>=0 && pscal2>=0){
		return true;
	}
	else
		return false;
}

bool CollisionPointCircle(Point A,Point C,float r){
	return pow(C.x - A.x,2) + pow(C.y - A.y,2) <= pow(r,2);
}