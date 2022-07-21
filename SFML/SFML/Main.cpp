#include "Triangle_Tool.h"
#include "box2d/box2d.h"

sf::RenderWindow RenderWindow;
sf::Event EventHandle;
Shape_Tool TriangleCutter;
Triangle_Tool TriangleTool;

void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings);

void Start();
void Update();
void PollEvents();
void Render();

int Cleanup();

int main()
{
	InitRenderWindow({ 800, 800 }, "Title", sf::Style::Default, sf::ContextSettings());

	Start();
	Update();
	Render();

	return Cleanup();
}

void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings)
{
	RenderWindow.create(sf::VideoMode(_size.x, _size.y), _title, _style, _settings);
}

void Start()
{

}

void Update()
{
	while (RenderWindow.isOpen())
	{
		PollEvents();

		

		Render();
	}
}

void PollEvents()
{
	if (RenderWindow.pollEvent(EventHandle))
	{
		if (EventHandle.type == sf::Event::Closed)
		{
			RenderWindow.close();
		}
		if (EventHandle.type == sf::Event::KeyPressed
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			TriangleCutter.ResetShape();
		}
		if (EventHandle.type == sf::Event::KeyPressed
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			TriangleTool.ResetShape();
		}

		std::cout << TriangleTool.CheckForLineIntersection(TriangleCutter) << std::endl;

		
		TriangleCutter.HandleMouseInput(EventHandle, RenderWindow);
		TriangleTool.HandleMouseInput(EventHandle, RenderWindow);
	}
}

void Render()
{
	RenderWindow.clear();

	RenderWindow.draw(TriangleCutter);
	RenderWindow.draw(TriangleTool);
	

	RenderWindow.display();
}

int Cleanup()
{

	return 0;
}
