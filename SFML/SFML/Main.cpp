#include "Grass.h"
#include "Object.h"
#include "Math.h"
#include "Worm.h"

#define FIXED_DT 0.01666666666666666666f

sf::RenderWindow RenderWindow{};
sf::Event EventHandler{};
sf::Clock WorldTimer{};
std::vector<Grass*> Grasses{};
std::vector<Worm*> Worms{};

float PreviousFrame = 0.0f;
float DeltaTime = 0.0f;

void Start();
void Update();
void HandleEvents();
void Render();
int Cleanup();

void CalculateDeltaTime();

int main()
{
    RenderWindow.create(sf::VideoMode(800, 800), "Exercises 009.1 - 009.3");
    RenderWindow.setFramerateLimit(60);

    Start();
    Update();

    return Cleanup();
}

void Start()
{
    for (unsigned i = 0; i < 10; i++)
    {
        Grasses.emplace_back(new Grass(20, 0.04f, { 100.0f + 100 * i, 800 }));
    }

    Worms.emplace_back(new Worm({ 400.0f,400.0f }, 300, 1));
}

void Update()
{
    while (RenderWindow.isOpen())
    {
        CalculateDeltaTime();
        HandleEvents();

        for (auto& grass : Grasses)
        {
            grass->Update(DeltaTime);
        }

        sf::Vector2f mousePos = RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(RenderWindow));
        for (auto& worm : Worms)
        {
            worm->Update(DeltaTime, mousePos);
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
        
        if (EventHandler.type == sf::Event::MouseButtonPressed)
        {
        }
    }
}

void Render()
{
    RenderWindow.clear();

    for (auto& grass : Grasses)
    {
        RenderWindow.draw(*grass);
    }
    for (auto& worm : Worms)
    {
        RenderWindow.draw(*worm);
    }

    RenderWindow.display();
}

int Cleanup()
{
    CleanupVector(Grasses);
    CleanupVector(Worms);
    return 0;
}

void CalculateDeltaTime()
{
    float currentTime = WorldTimer.getElapsedTime().asSeconds();
    DeltaTime = currentTime - PreviousFrame;
    PreviousFrame = currentTime;
}
