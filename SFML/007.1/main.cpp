#include "SpringJoint.h"

#define FIXED_DT 0.01666666666666666666f

sf::RenderWindow RenderWindow;
sf::Event EventHandler;
sf::Clock WorldTimer;
std::vector<Object*> Objects{};
std::vector<SpringJoint*> SpringJoints{};

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
    RenderWindow.create(sf::VideoMode(800, 800), "Exercises 007.1");
    RenderWindow.setFramerateLimit(60);

    Start();
    Update();

    return Cleanup();
}

void Start()
{
    Objects.emplace_back(new Object({ 400,100 }, BODYTYPE::STATIC));
    for (int i = 0; i < 10; i++)
    {
        Objects.emplace_back(new Object({ 400,120 + (20.0f * i) }, BODYTYPE::DYNAMIC));
    }

    for (int i = 0; i < 10; i++)
    {
        SprintJointDef springJoint;
        springJoint.BodyA = Objects[i];
        springJoint.BodyB = Objects[i + 1];
        springJoint.Constant = 1.0f;
        springJoint.Length = 0.0f;
        SpringJoints.emplace_back(new SpringJoint(springJoint));
    }

    for (auto& mover : Objects)
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
        ApplyGravity(9.81f);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f mousePos = RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(RenderWindow));
            Objects[10]->SetPosition(mousePos);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2f mousePos = RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(RenderWindow));
            Objects[0]->SetPosition(mousePos);
        }

        for (auto& spring : SpringJoints)
        {
            spring->PhysicsUpdate(FIXED_DT);
            spring->Update(DeltaTime);
        }
        for (auto& mover : Objects)
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
            for (auto& mover : Objects)
            {
                mover->ApplyForce({ 1000.0f, -50000.0f });
            }
        }
    }

}

void Render()
{
    RenderWindow.clear();

    for (auto& spring : SpringJoints)
    {
        RenderWindow.draw(*spring);
    }
    for (auto& mover : Objects)
    {
        RenderWindow.draw(*mover);
    }

    RenderWindow.display();
}

int Cleanup()
{
    CleanupVector(Objects);
    CleanupVector(SpringJoints);

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
    for (auto& object : Objects)
    {
        object->ApplyGravity(_strength / FIXED_DT);
    }
}
