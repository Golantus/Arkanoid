#include "Vector2D.h"
#include <math.h>


vector2D::vector2D(double x, double y)
    :x(x), y(y)
{
}

vector2D::vector2D(int x, int y)
    :x(x), y(y)
{
}

vector2D::vector2D()
    :x(0), y(0)
{
}

bool operator==(const vector2D& v1, const vector2D& v2)
{
	return ((v1.x == v2.x) && (v1.y == v2.y));
}
bool operator!=(const vector2D& v1, const vector2D& v2) 
{
	return ((v1.x != v2.x) || (v1.y != v2.y));
}


vector2D operator+(const vector2D& v1, const vector2D& v2)
{
	return vector2D{ v1.x + v2.x, v1.y + v2.y };
}
vector2D operator-(const vector2D& v1, const vector2D& v2)
{
	return vector2D{ v1.x - v2.x, v1.y - v2.y };
}
vector2D operator*(const vector2D& v1, double val)
{
	return vector2D{ v1.x * val, v1.y * val };
}
bool coollisionOfRectangleAndPoint(SDL_Rect r, point p)
{
	return (p.x >= r.x && p.x <= r.x + r.w && p.y >= r.y && p.y <= r.y + r.h);
}
