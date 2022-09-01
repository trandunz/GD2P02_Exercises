#include "LiquidShape.h"
#include "ConvexPolygon.h"

#define FIXED_DT 0.01666666666666666666f

sf::RenderWindow RenderWindow;
sf::Event EventHandler;
sf::Clock WorldTimer;
std::vector<Object*> Objects{};
std::vector<CapsuleObject*> CapsuleObjects{};
std::vector<ConvexPolygon*> Polygons{};
Mesh Triangle(
    { 
        {{0.5f,0.0f}, sf::Color::Red},
        {{0.0f,-0.5f}, sf::Color::Red},
        {{-0.5f,0.0f}, sf::Color::Red}
    });

float PreviousFrame = 0.0f;
float DeltaTime = 0.0f;

void Start();
void Update();
void HandleEvents();
void Render();
int Cleanup();

void CalculateDeltaTime();
void ApplyGravity(float _strength);

int main()
{
    RenderWindow.create(sf::VideoMode(800, 800), "Exercises 003.1 - 003.3");
    RenderWindow.setFramerateLimit(60);

    Start();
    Update();

    return Cleanup();
}

void Start()
{
    Objects.emplace_back(new Object({ 200,500 }, 1));
    Objects.emplace_back(new Object({ 600,500 }, 1));

    CapsuleObjects.emplace_back(new CapsuleObject({ 380, 400 }, { 380, 450 }, 20.0f, 1, sf::Color::Red));
    CapsuleObjects.emplace_back(new CapsuleObject({ 400, 200 }, { 400, 250 }, 20.0f, 1, sf::Color::Green));

    //Polygons.emplace_back(new ConvexPolygon({ 0,0 }, 1));
    //Polygons.back()->Scale(200.0f);
    //Polygons.back()->SetPosition({ 400, 400 });

    for (auto& mover : Objects)
    {
        mover->SetRenderWindow(RenderWindow);
    }
    for (auto& capsule : CapsuleObjects)
    {
        capsule->SetRenderWindow(RenderWindow);
    }
    for (auto& polygon : Polygons)
    {
        polygon->SetRenderWindow(RenderWindow);
    }

    Triangle.Scale(500.0f);
    Triangle.SetPosition({ 400, 400 });
}

void Update()
{
    while (RenderWindow.isOpen())
    {
        CalculateDeltaTime();
        HandleEvents();
        ApplyGravity(588.6f);

        bool triangleCollided = false;
        for (auto& object : Objects)
        {
            if (Triangle.TrianglePointCollision(object->GetPosition()))
            {
                sf::Vector2f repulsiveForce = Normalize(object->GetPosition()- Triangle.GetCentre());
                object->ApplyForce(repulsiveForce * 10000.0f);
            }
            object->UpdatePhysics(FIXED_DT);
            object->Update(DeltaTime);
        }

        for (auto& capsule : CapsuleObjects)
        {
            for (auto& otherCapsule : CapsuleObjects)
            {
                if (otherCapsule != capsule)
                {
                    capsule->CheckCollision(*otherCapsule);
                }
            }
            capsule->UpdatePhysics(FIXED_DT);
            capsule->Update(DeltaTime);
        }

        for (auto& polygon : Polygons)
        {
            polygon->UpdatePhysics(FIXED_DT);
            polygon->Update(DeltaTime);
        }

        Render();
    }
}

void HandleEvents()
{
    while (RenderWindow.pollEvent(EventHandler))
    {
        if (EventHandler.type == sf::Event::Closed)
            RenderWindow.close();
        
        if (EventHandler.type == sf::Event::MouseButtonPressed &&
            sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            for (auto& mover : Objects)
            {
                mover->ApplyForce({ 1000.0f, -50000.0f });
            }
            for (auto& polygon : Polygons)
            {
                polygon->ApplyForce({ 1000.0f, -50000.0f });
            }
        }
    }

}

void Render()
{
    RenderWindow.clear();

    RenderWindow.draw(Triangle);
    for (auto& mover : Objects)
    {
        RenderWindow.draw(*mover);
    }
    for (auto& capsule : CapsuleObjects)
    {
        RenderWindow.draw(*capsule);
    }
    for (auto& polygon : Polygons)
    {
        RenderWindow.draw(*polygon);
    }

    RenderWindow.display();
}

int Cleanup()
{
    for (auto& mover : Objects)
    {
        if (mover)
            delete mover;
        mover = nullptr;
    }
    Objects.clear();
    Objects.resize(0);

    for (auto& capsule : CapsuleObjects)
    {
        if (capsule)
            delete capsule;
        capsule = nullptr;
    }
    CapsuleObjects.clear();
    CapsuleObjects.resize(0);

    for (auto& polygon : Polygons)
    {
        if (polygon)
            delete polygon;
        polygon = nullptr;
    }
    Polygons.clear();
    Polygons.resize(0);

    return 0;
}

void CalculateDeltaTime()
{
    float currentTime = WorldTimer.getElapsedTime().asSeconds();
    DeltaTime = currentTime - PreviousFrame;
    PreviousFrame = currentTime;
}

void ApplyGravity(float _strength)
{
    for (auto& mover : Objects)
    {
        mover->ApplyGravity(_strength);
    }
    for (auto& capsule : CapsuleObjects)
    {
        capsule->ApplyGravity(_strength);
    }
    for (auto& polygon : Polygons)
    {
        polygon->ApplyGravity(_strength);
    }
}
