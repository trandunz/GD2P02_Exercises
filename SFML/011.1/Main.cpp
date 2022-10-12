#include "BezierLine.h"

sf::RenderWindow RenderWindow{};
sf::Event EventHandler{};
BezierLine* ABezierLine{ nullptr };

void Start();
void Update();
void HandleEvents();
void Render();
int Cleanup();

int main()
{
    RenderWindow.create(sf::VideoMode(800, 800), "Exercises 011.1");
    RenderWindow.setFramerateLimit(60);

    Start();
    Update();

    return Cleanup();
}

void Start()
{
    ABezierLine = new BezierLine({ 50,400 }, { 750,400 }, {200,200}, { 600,600 });
}

void Update()
{
    while (RenderWindow.isOpen())
    {
        HandleEvents();

        if (ABezierLine)
            ABezierLine->Update(RenderWindow);
            
        Render();
    }
}

void HandleEvents()
{
    while (RenderWindow.pollEvent(EventHandler))
    {
        if (EventHandler.type == sf::Event::Closed)
            RenderWindow.close();

        if (EventHandler.type == sf::Event::KeyPressed
            && EventHandler.key.code == sf::Keyboard::Escape)
            RenderWindow.close();

        if (ABezierLine)
            ABezierLine->HandleMouseEvents(RenderWindow, EventHandler);
    }

}

void Render()
{
    RenderWindow.clear();

    RenderWindow.draw(*ABezierLine);

    RenderWindow.display();
}

int Cleanup()
{
    if (ABezierLine)
        delete ABezierLine;

    return 0;
}
