#include "Vec2.h"
#include <math.h>

Vec2::Vec2()
{

}

Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin)
{

}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	//TODO
	return Vec2(0, 0);
}

Vec2 Vec2::operator * (const float val) const
{
	return Vec2(x * val, y * val);
}

Vec2 Vec2::operator / (const float val) const
{
	//TODO
	return Vec2(0, 0);
}

bool Vec2::operator == (const Vec2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
	//TODO
	return false;
}

void Vec2::operator += (const Vec2& rhs)
{
	//TODO
}

void Vec2::operator -= (const Vec2& rhs)
{
	//TODO
}

void Vec2::operator *= (const Vec2& rhs)
{
	//TODO
}

void Vec2::operator /= (const Vec2& rhs)
{
	//TODO	
}

float Vec2::dist(const Vec2& rhs) const
{
	//TODO
	return 0;
}

float Vec2::length() const
{
	return 0.0f;
}
