#pragma once
#include <SFML/Graphics.hpp>
using Vec2 = sf::Vector2f;

enum class BEZIERTYPE
{
	LINEAR = 0,
	QUADRATIC,
	CUBIC
};

class BezierLine : public sf::Drawable
{
public:
	BezierLine(Vec2 _startPos, Vec2 _endPos, unsigned _fidelity = 100);
	BezierLine(Vec2 _startPos, Vec2 _endPos, Vec2 _pivot, unsigned _fidelity = 100);
	BezierLine(Vec2 _startPos, Vec2 _endPos, Vec2 _pivotA, Vec2 _pivotB, unsigned _fidelity = 100);

	void HandleMouseEvents(sf::RenderWindow& _window, sf::Event& _event);
	void Update(sf::RenderWindow& _window, float _dt = 0.0f);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void CreateStartAndEndPoints();
	void CreateAnchorPoints();
	Vec2 LinearBezier(unsigned& _i);
	Vec2 QuadraticBezier(Vec2 _startPos, Vec2 _endPos, Vec2 _pivot, unsigned& _i);
	Vec2 CubicBezier(Vec2 _startPos, Vec2 _endPos, Vec2 _pivotA, Vec2 _pivotB, unsigned& _i);

	Vec2 Lerp(Vec2 _a, Vec2 _b, float _t);

	BEZIERTYPE m_CurveType{ BEZIERTYPE::LINEAR };
	unsigned m_Fidelity{ 100 };
	Vec2 m_AnchorA{};
	bool m_AnchorASelected{ false };
	Vec2 m_AnchorB{};
	bool m_AnchorBSelected{ false };
	Vec2 m_StartPos{};
	Vec2 m_EndPos{};
	std::vector<sf::CircleShape> m_EndPoints{};
	sf::VertexArray m_Line{sf::PrimitiveType::Lines};
};

