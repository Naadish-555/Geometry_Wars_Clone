//Lecture 05 based on creating and implementing Vec2 class

#include<iostream>

class Vec2
{
public:
	float x = 0;
	float y = 0;

	Vec2() {}

	Vec2(float xin, float yin)
		: x(xin)
		, y(yin)
	{
	}

	Vec2 operator + (const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	void operator += (const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}


	//Helps in chaining multiple values
	Vec2& add(const Vec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2& scale(float s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vec2 rotate(float deg)
	{
		return *this;
	}

	float dist(const Vec2& v)const
	{
		return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
	}
};

int main()
{

	Vec2 v1(100, 200);
	Vec2 v2(50, 75);
	Vec2 v3(1000, 2000);

	//Vec2 v3(v1.x + v2.x, v1.y + v2.y);
	//Vec2 v3 = v1 + v2;

	//v1.add(v2).add(v3);

	//so returning a reference to the current object helps in chaining multiple methods
	v1.scale(5.0f).rotate(30).add(v2);

	std::cout << v1.x << "," << v1.y;

	return 0;
}