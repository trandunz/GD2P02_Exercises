#include <iostream>
#include <conio.h>
#include <string>

#define ASCIIOFFSET 48

struct Vec3i
{
	int x = 0;
	int y = 0;
	int z = 0;
};

struct Plane
{
	Vec3i Point;
	Vec3i Normal;
};

enum class COLLISION_RESULT
{
	ON_PLANE,
	INFRONT,
	BEHIND
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
	return input;
}

COLLISION_RESULT Point_Plane_Collision(Plane _plane, Vec3i _point)
{
	float refrenceDistance = DotProduct(_plane.Normal, _plane.Point);
	float result = DotProduct(_plane.Normal, _point) - refrenceDistance;

	if (result > 0)
		return COLLISION_RESULT::INFRONT;
	else if (result < 0)
		return COLLISION_RESULT::BEHIND;
	else
		return COLLISION_RESULT::ON_PLANE;
}

int main()
{
	Plane plane;
	std::cout << "Define A Plane" << std::endl;
	std::cout << "--------------" << std::endl;
	std::cout << "A Point (x,y,z): (";
	plane.Point.x = GrabNumberInput() - ASCIIOFFSET;
	std::cout << (char)(plane.Point.x + ASCIIOFFSET) << ",";
	plane.Point.y = GrabNumberInput() - ASCIIOFFSET;
	std::cout << (char)(plane.Point.y + ASCIIOFFSET) << ",";
	plane.Point.z = GrabNumberInput() - ASCIIOFFSET;
	std::cout << (char)(plane.Point.z + ASCIIOFFSET) << ")" << std::endl;

	std::cout << "A Normal / Face Direction (x,y,z): (";
	plane.Normal.x = GrabNumberInput() - ASCIIOFFSET;
	std::cout << (char)(plane.Normal.x + ASCIIOFFSET) << ",";
	plane.Normal.y = GrabNumberInput() - ASCIIOFFSET;
	std::cout << (char)(plane.Normal.y + ASCIIOFFSET) << ",";
	plane.Normal.z = GrabNumberInput() - ASCIIOFFSET;
	std::cout << (char)(plane.Normal.z + ASCIIOFFSET) << ")" << std::endl;

	Vec3i point;
	std::cout << "Pick A Point For Intersection Test (x,y,z): (";
	point.x = GrabNumberInput() - ASCIIOFFSET;
	std::cout << (char)(point.x + ASCIIOFFSET) << ",";
	point.y = GrabNumberInput() - ASCIIOFFSET;
	std::cout << (char)(point.y + ASCIIOFFSET) << ",";
	point.z = GrabNumberInput() - ASCIIOFFSET;
	std::cout << (char)(point.z + ASCIIOFFSET) << ")" << std::endl;

	COLLISION_RESULT Result = Point_Plane_Collision(plane, point);

	switch (Result)
	{
	case COLLISION_RESULT::BEHIND:
		{
			std::cout << "Behind" << std::endl;
			break;
		}
	case COLLISION_RESULT::INFRONT:
		{
			std::cout << "InFront" << std::endl;
			break;
		}
	case COLLISION_RESULT::ON_PLANE:
		{
			std::cout << "On Plane" << std::endl;
			break;
		}
	default:
		break;
	}

	return 0;
}