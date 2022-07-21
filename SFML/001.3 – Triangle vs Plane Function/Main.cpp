#include <iostream>
#include <conio.h>
#include <string>

#define ASCIIOFFSET 48

struct Vec3i
{
	int x = 0;
	int y = 0;
	int z = 0;
	Vec3i operator - (Vec3i& _otherVector)
	{
		x -= _otherVector.x;
		y -= _otherVector.y;
		z -= _otherVector.z;
		return { x,y,z };
	}

	Vec3i operator * (float _scalar)
	{
		x *= _scalar;
		y *= _scalar;
		z *= _scalar;
		return { x,y,z };
	}
};

struct Vec3f
{
	float x = 0;
	float y = 0;
	float z = 0;
	Vec3f operator - (Vec3f& _otherVector)
	{
		x -= _otherVector.x;
		y -= _otherVector.y;
		z -= _otherVector.z;
		return { x,y,z };
	}

	Vec3f operator * (float _scalar)
	{
		x *= _scalar;
		y *= _scalar;
		z *= _scalar;
		return { x,y,z };
	}
};

struct Plane
{
	Vec3i Point;
	Vec3i Normal;
};

struct Line
{
	Vec3i Point1;
	Vec3i Point2;
};

struct Triangle
{
	Line Side1;
	Line Side2;
	Line Side3;
};

float Mag(Vec3i _v)
{
	return sqrtf((_v.x * _v.x) + (_v.y * _v.y) + (_v.z * _v.z));
}

float Length(Line _line)
{
	return sqrtf(((_line.Point2.x - _line.Point1.x) * (_line.Point2.x - _line.Point1.x)) + ((_line.Point2.y - _line.Point1.y) * (_line.Point2.y - _line.Point1.y)) + ((_line.Point2.z - _line.Point1.z) * (_line.Point2.z - _line.Point1.z)));
}

float DotProduct(Vec3i _v1, Vec3i _v2)
{
	return ((_v1.x * _v2.x) + (_v1.y * _v2.y) + (_v1.z * _v2.z));
}

int GrabNumberInput()
{
	int input = 0;
	while (input < ASCIIOFFSET || input > 58)
		input = _getch();
	return input - ASCIIOFFSET;
}

bool Line_Plane_Collision(Plane _plane, Line _line)
{
	float result = DotProduct(_plane.Normal, _plane.Point - _line.Point1) / DotProduct(_plane.Normal, _line.Point2 - _line.Point1);

	if (result >= 0 && result <= 1)
		return true;
	else
		return false;
}

bool Triangle_Plane_Collision(Plane _plane, Triangle _triangle)
{
	if (Line_Plane_Collision(_plane, _triangle.Side1))
	{
		return true;
	}
	if (Line_Plane_Collision(_plane, _triangle.Side2))
	{
		return true;
	}
	if (Line_Plane_Collision(_plane, _triangle.Side3))
	{
		return true;
	}

	return false;
}

float Lerp(float _start, float _end, float _ratio)
{
	return _start* (1 - _ratio) + _end * _ratio;
}

Vec3f GetPointOnLine(Line _line, float _ratio)
{
	return { Lerp(_line.Point1.x, _line.Point2.x, _ratio), Lerp(_line.Point1.y, _line.Point2.y, _ratio) , Lerp(_line.Point1.z, _line.Point2.z, _ratio) };
}

int main()
{
	Plane plane;
	std::cout << "Define A Plane" << std::endl;
	std::cout << "--------------" << std::endl;
	std::cout << "A Point (x,y,z): (";
	plane.Point.x = GrabNumberInput();
	std::cout << (char)(plane.Point.x + ASCIIOFFSET) << ",";
	plane.Point.y = GrabNumberInput();
	std::cout << (char)(plane.Point.y + ASCIIOFFSET) << ",";
	plane.Point.z = GrabNumberInput();
	std::cout << (char)(plane.Point.z + ASCIIOFFSET) << ")" << std::endl;

	std::cout << "A Normal / Face Direction (x,y,z): (";
	plane.Normal.x = GrabNumberInput();
	std::cout << (char)(plane.Normal.x + ASCIIOFFSET) << ",";
	plane.Normal.y = GrabNumberInput();
	std::cout << (char)(plane.Normal.y + ASCIIOFFSET) << ",";
	plane.Normal.z = GrabNumberInput();
	std::cout << (char)(plane.Normal.z + ASCIIOFFSET) << ")" << std::endl;

	Triangle triangle;
	std::cout << "First Point On Triangle (x,y,z): (";
	triangle.Side1.Point1.x = GrabNumberInput();
	std::cout << (char)(triangle.Side1.Point1.x + ASCIIOFFSET) << ",";
	triangle.Side1.Point1.y = GrabNumberInput();
	std::cout << (char)(triangle.Side1.Point1.y + ASCIIOFFSET) << ",";
	triangle.Side1.Point1.z = GrabNumberInput();
	std::cout << (char)(triangle.Side1.Point1.z + ASCIIOFFSET) << ")" << std::endl;

	std::cout << "Second Point On Triangle (x,y,z): (";
	triangle.Side2.Point1.x = GrabNumberInput();
	std::cout << (char)(triangle.Side2.Point1.x + ASCIIOFFSET) << ",";
	triangle.Side2.Point1.y = GrabNumberInput();
	std::cout << (char)(triangle.Side2.Point1.y + ASCIIOFFSET) << ",";
	triangle.Side2.Point1.z = GrabNumberInput();
	std::cout << (char)(triangle.Side2.Point1.z + ASCIIOFFSET) << ")" << std::endl;

	std::cout << "Third Point On Triangle (x,y,z): (";
	triangle.Side3.Point1.x = GrabNumberInput();
	std::cout << (char)(triangle.Side3.Point1.x + ASCIIOFFSET) << ",";
	triangle.Side3.Point1.y = GrabNumberInput();
	std::cout << (char)(triangle.Side3.Point1.y + ASCIIOFFSET) << ",";
	triangle.Side3.Point1.z = GrabNumberInput();
	std::cout << (char)(triangle.Side3.Point1.z + ASCIIOFFSET) << ")" << std::endl;

	triangle.Side1.Point2 = triangle.Side2.Point1;
	triangle.Side2.Point2 = triangle.Side3.Point1;
	triangle.Side3.Point2 = triangle.Side1.Point1;

	bool Result = Triangle_Plane_Collision(plane, triangle);

	if (Result)
		std::cout << "Successful Collision" << std::endl;
	else
		std::cout << "No Collision" << std::endl;

	return 0;
}