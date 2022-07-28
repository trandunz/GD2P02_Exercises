#include "LiquidShape.h"

LiquidShape::LiquidShape(sf::Vector2f _position, sf::Vector2f _size)
{
    m_Mesh = new sf::RectangleShape(_size);
    m_Mesh->setOrigin(m_Mesh->getLocalBounds().width / 2, m_Mesh->getLocalBounds().height / 2);
    m_Mesh->setPosition(_position);
    m_Mesh->setFillColor({156, 211, 219, 125});
}

LiquidShape::~LiquidShape()
{
    if (m_Mesh)
        delete m_Mesh;
    m_Mesh = nullptr;
}

bool LiquidShape::CheckForCollisions(std::vector<Movers*>& _objects)
{
    bool hasCollided = false;
    for (auto& object : _objects)
    {
        if (m_Mesh->getGlobalBounds().intersects(object->GetGlobalBounds()))
        {
            ApplyFriction(*object);
            hasCollided = true;
        }
    }
    return hasCollided;
}

void LiquidShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_Mesh)
        target.draw(*m_Mesh);
}

void LiquidShape::ApplyFriction(Movers& _object)
{
    float objectSpeed = Mag(_object.GetVelocity());
    if (objectSpeed <= 0)
    {
        return;
    }
    float area = _object.GetReferenceArea();
    float waterDensity = 0.997f;
    float waterDragCoefficient = 0.345f;
    sf::Vector2f unitVelocity = Normalize(_object.GetVelocity());
    

    sf::Vector2f dragForce = (unitVelocity * -1.0f) * ((waterDragCoefficient * waterDensity * (objectSpeed * objectSpeed) * area) / 2.0f);
    _object.ApplyForce(dragForce);
}
