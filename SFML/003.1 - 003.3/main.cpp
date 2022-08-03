#include "LiquidShape.h"

#define FIXED_DT 0.01666666666666666666f

sf::RenderWindow RenderWindow;
sf::Event EventHandler;
sf::Clock WorldTimer;
std::vector<Object*> MoverObjects{};
LiquidShape WaterBody{ {200,700},{400,200} };

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
    MoverObjects.emplace_back(new Object({ 200,500 }, 1));
    MoverObjects.emplace_back(new Object({ 600,500 }, 1));

    for (auto& mover : MoverObjects)
    {
        mover->SetRenderWindow(RenderWindow);
    }
}

void Update()
{
    while (RenderWindow.isOpen())
    {
        CalculateDeltaTime();
        HandleEvents();
        ApplyGravity(588.6f);

        WaterBody.CheckForCollisions(MoverObjects);

        for (auto& mover : MoverObjects)
        {
            mover->UpdatePhysics(FIXED_DT);
            mover->Update(DeltaTime);
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
            for (auto& mover : MoverObjects)
            {
                mover->ApplyForce({ 0, -50000.0f });
            }
        }
    }

}

void Render()
{
    RenderWindow.clear();

    for (auto& mover : MoverObjects)
    {
        RenderWindow.draw(*mover);
    }
    RenderWindow.draw(WaterBody);

    RenderWindow.display();
}

int Cleanup()
{
    for (auto& mover : MoverObjects)
    {
        if (mover)
            delete mover;
        mover = nullptr;
    }
    MoverObjects.clear();
    MoverObjects.resize(0);

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
    for (auto& mover : MoverObjects)
    {
        mover->ApplyGravity(_strength);
    }
}
