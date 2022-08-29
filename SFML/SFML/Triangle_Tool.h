#pragma once
#include "Shape_Tool.h"
#include <vector>
class Triangle_Tool :
    public Shape_Tool
{
public:
    Triangle_Tool();
    virtual void Update() override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void HandleMouseInput(sf::Event& _event, sf::RenderWindow& _renderWindow) override;
    bool CheckForLineIntersection(Shape_Tool& _line);

private:
    sf::VertexArray m_IntersectArea;
    std::vector<sf::CircleShape> m_IntersectionPoints{};
};

