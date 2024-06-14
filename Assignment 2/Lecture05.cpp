//Lecture 05 based on creating and implementing Vec2 class

#include<iostream>

class Vec2f
{
public:
	float x = 0;
	float y = 0;

	Vec2f() {}

	Vec2f(float xin, float yin)
		: x(xin)
		, y(yin)
	{
	}

	Vec2f operator + (const Vec2f& rhs) const
	{
		return Vec2f(x + rhs.x, y + rhs.y);
	}

	void operator += (const Vec2f& rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}


	//Helps in chaining multiple values
	Vec2f& add(const Vec2f& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2f& scale(float s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vec2f rotate(float deg)
	{
		return *this;
	}

	float distance(const Vec2f& v)const
	{
		return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
	}
};

int L5main()
{

	Vec2f v1(100, 200);
	Vec2f v2(50, 75);
	Vec2f v3(1000, 2000);

	//Vec2 v3(v1.x + v2.x, v1.y + v2.y);
	//Vec2 v3 = v1 + v2;

	//v1.add(v2).add(v3);

	//so returning a reference to the current object helps in chaining multiple methods
	v1.scale(5.0f).rotate(30).add(v2);

	std::cout << v1.x << "," << v1.y;

	return 0;
}