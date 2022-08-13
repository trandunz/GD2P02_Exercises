#pragma once
#include "Utility.h"
class CapsuleObject : public sf::Drawable
{
public:
    CapsuleObject(sf::Vector2f _startPos, sf::Vector2f _endPos, float _radius, float _mass, sf::Color _color);
    virtual ~CapsuleObject();

    void SetRenderWindow(sf::RenderWindow& _renderWindow);

    virtual void UpdatePhysics(float _dt);
    virtual void Update(float _dt);

    virtual void ApplyGravity(float _strength);
    virtual void ApplyForce(sf::Vector2f _force);
    virtual void CollideWithWindowBounds();

    virtual bool CheckCollision(CapsuleObject& _capsule);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void CollideCircleWithBounds(sf::CircleShape& _circle);
    void OffsetOtherShapes(sf::Shape& _thisShape, sf::Vector2f _amount);
    void OffsetShapes(sf::Vector2f _amount);

    sf::RenderWindow* m_RenderWindow = nullptr;

    sf::CircleShape Top;
    sf::CircleShape Bot;
    sf::RectangleShape Mid;

    float m_Radius = 0.0f;
    float m_Mass = 0.0f;
    float m_GravityStrength{};
    sf::Vector2f m_Velocity{};
    sf::Vector2f m_Acceleration{};
};

