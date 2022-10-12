#include "BezierLine.h"


BezierLine::BezierLine(Vec2 _startPos, Vec2 _endPos, unsigned _fidelity)
{
	m_StartPos = _startPos;
	m_EndPos = _endPos;
	m_Fidelity = _fidelity;;
	m_AnchorA = m_StartPos;
	m_AnchorB = m_EndPos;
	m_Line.resize(m_Fidelity);
	CreateStartAndEndPoints();
	CreateAnchorPoints();
}

BezierLine::BezierLine(Vec2 _startPos, Vec2 _endPos, Vec2 _pivot, unsigned _fidelity)
{
	m_StartPos = _startPos;
	m_EndPos = _endPos;
	m_Fidelity = _fidelity;
	m_CurveType = BEZIERTYPE::QUADRATIC;
	m_AnchorA = _pivot;
	m_AnchorB = m_EndPos;
	m_Line.resize(m_Fidelity);
	CreateStartAndEndPoints();
	CreateAnchorPoints();
}

BezierLine::BezierLine(Vec2 _startPos, Vec2 _endPos, Vec2 _pivotA, Vec2 _pivotB, unsigned _fidelity)
{
	m_StartPos = _startPos;
	m_EndPos = _endPos;
	m_Fidelity = _fidelity;
	m_CurveType = BEZIERTYPE::CUBIC;
	m_AnchorA = _pivotA;
	m_AnchorB = _pivotB;
	m_Line.resize(m_Fidelity);
	CreateStartAndEndPoints();
	CreateAnchorPoints();
}

void BezierLine::HandleMouseEvents(sf::RenderWindow& _window, sf::Event& _event)
{
	Vec2 mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
	if (_event.type == sf::Event::MouseButtonPressed)
	{
		if (m_EndPoints[2].getGlobalBounds().contains(mousePos))
		{
			m_AnchorASelected = true;
			
		}
		else if (m_EndPoints[3].getGlobalBounds().contains(mousePos))
		{
			m_AnchorBSelected = true;
		}
	}
	else if (_event.type == sf::Event::MouseButtonReleased)
	{
		m_AnchorASelected = false;
		m_AnchorBSelected = false;
	}
}

void BezierLine::Update(sf::RenderWindow& _window, float _dt)
{
	Vec2 mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));

	switch (m_CurveType)
	{
	case BEZIERTYPE::QUADRATIC:
	{
		if (m_AnchorASelected)
		{
			m_AnchorA = mousePos;
		}
		m_EndPoints[2].setPosition(m_AnchorA);

		for (unsigned i = 0; i < m_Fidelity; i++)
			m_Line[i] = { QuadraticBezier(m_StartPos, m_EndPos, m_AnchorA, i),sf::Color::White };
		break;
	}
	case BEZIERTYPE::CUBIC:
	{
		if (m_AnchorASelected)
		{
			m_AnchorA = mousePos;
		}
		else if (m_AnchorBSelected)
		{
			m_AnchorB = mousePos;
		}
		m_EndPoints[2].setPosition(m_AnchorA);
		m_EndPoints[3].setPosition(m_AnchorB);

		for (unsigned i = 0; i < m_Fidelity; i++)
			m_Line[i] = { CubicBezier(m_StartPos, m_EndPos, m_AnchorA, m_AnchorB, i),sf::Color::White };
		break;
	}
	default:
	
		for (unsigned i = 0; i < m_Fidelity; i++)
			m_Line[i] = { LinearBezier(i),sf::Color::White };
		break;
	}
}

void BezierLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& point : m_EndPoints)
		target.draw(point);

	target.draw(m_Line);
}

void BezierLine::CreateStartAndEndPoints()
{
	m_EndPoints.emplace_back(sf::CircleShape(5.0f));
	m_EndPoints.back().setPosition(m_StartPos);
	m_EndPoints.back().setOrigin(m_EndPoints.back().getRadius(), m_EndPoints.back().getRadius());
	m_EndPoints.back().setFillColor(sf::Color::White);

	m_EndPoints.emplace_back(sf::CircleShape(5.0f));
	m_EndPoints.back().setPosition(m_EndPos);
	m_EndPoints.back().setOrigin(m_EndPoints.back().getRadius(), m_EndPoints.back().getRadius());
	m_EndPoints.back().setFillColor(sf::Color::White);
}

void BezierLine::CreateAnchorPoints()
{
	m_EndPoints.emplace_back(sf::CircleShape(5.0f));
	m_EndPoints.back().setPosition(m_AnchorA);
	m_EndPoints.back().setOrigin(m_EndPoints.back().getRadius(), m_EndPoints.back().getRadius());
	m_EndPoints.back().setFillColor(sf::Color::White);

	m_EndPoints.emplace_back(sf::CircleShape(5.0f));
	m_EndPoints.back().setPosition(m_AnchorB);
	m_EndPoints.back().setOrigin(m_EndPoints.back().getRadius(), m_EndPoints.back().getRadius());
	m_EndPoints.back().setFillColor(sf::Color::White);
}

Vec2 BezierLine::LinearBezier(unsigned& _i)
{
	return Lerp(m_StartPos, m_EndPos, (float)_i / m_Fidelity);
}

Vec2 BezierLine::QuadraticBezier(Vec2 _startPos, Vec2 _endPos, Vec2 _pivot, unsigned& _i)
{
	Vec2 a = Lerp(_startPos, _pivot, (float)_i / m_Fidelity);
	Vec2 b = Lerp(_pivot, _endPos, (float)_i / m_Fidelity);
	return Lerp(a, b, (float)_i / m_Fidelity);
}

Vec2 BezierLine::CubicBezier(Vec2 _startPos, Vec2 _endPos, Vec2 _pivotA, Vec2 _pivotB, unsigned& _i)
{
	Vec2 a = QuadraticBezier(_startPos, _pivotB, _pivotA, _i);
	Vec2 b = QuadraticBezier(_pivotA, _endPos, _pivotB, _i);
	return Lerp(a, b, (float)_i / m_Fidelity);
}

Vec2 BezierLine::Lerp(Vec2 _a, Vec2 _b, float _t)
{
	return _a + (_b - _a) * _t;
}
