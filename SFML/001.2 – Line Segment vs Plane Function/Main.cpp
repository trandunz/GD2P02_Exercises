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

inline float DotProduct(Vec3i _v1, Vec3i _v2)
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

	Line line;
	std::cout << "First Point On Line (x,y,z): (";
	line.Point1.x = GrabNumberInput();
	std::cout << (char)(line.Point1.x + ASCIIOFFSET) << ",";
	line.Point1.y = GrabNumberInput();
	std::cout << (char)(line.Point1.y + ASCIIOFFSET) << ",";
	line.Point1.z = GrabNumberInput();
	std::cout << (char)(line.Point1.z + ASCIIOFFSET) << ")" << std::endl;

	std::cout << "Second Point On Line (x,y,z): (";
	line.Point2.x = GrabNumberInput();
	std::cout << (char)(line.Point2.x + ASCIIOFFSET) << ",";
	line.Point2.y = GrabNumberInput();
	std::cout << (char)(line.Point2.y + ASCIIOFFSET) << ",";
	line.Point2.z = GrabNumberInput();
	std::cout << (char)(line.Point2.z + ASCIIOFFSET) << ")" << std::endl;

	bool Result = Line_Plane_Collision(plane, line);

	if (Result)
		std::cout << "Successful Collision" << std::endl;
	else
		std::cout << "No Collision" << std::endl;

	return 0;
}