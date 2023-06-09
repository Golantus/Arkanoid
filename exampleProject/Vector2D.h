#pragma once
#include <SDL.h>
struct vector2D
{
	double x;
	double y;
	vector2D(double x, double y);
	vector2D(int x, int y);
	vector2D();
};
typedef vector2D point;

bool operator==(const vector2D& v1, const vector2D& v2);
bool operator!=(const vector2D& v1, const vector2D& v2);

vector2D operator+(const vector2D& v1, const vector2D& v2);
vector2D operator-(const vector2D& v1, const vector2D& v2);
vector2D operator*(const vector2D& v1, double val);

bool coollisionOfRectangleAndPoint(SDL_Rect r, point p);
