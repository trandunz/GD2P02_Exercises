#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

sf::RenderWindow* RenderWindow = nullptr;
sf::Event EventHandle;

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
	if (RenderWindow != nullptr)
	{
		RenderWindow->create(sf::VideoMode(_size.x, _size.y), _title, _style, _settings);
	}
	else
	{
		RenderWindow = new sf::RenderWindow(sf::VideoMode(_size.x, _size.y), _title, _style, _settings);
	}
}

void Start()
{

}

void Update()
{
	while (RenderWindow->isOpen())
	{
		PollEvents();
		Render();
	}
}

void PollEvents()
{
	if (RenderWindow->pollEvent(EventHandle))
	{
		if (EventHandle.type == sf::Event::Closed)
		{
			RenderWindow->close();
		}
	}
}

void Render()
{
	RenderWindow->clear();

	RenderWindow->display();
}

int Cleanup()
{
	if (RenderWindow != nullptr)
		delete RenderWindow;
	RenderWindow = nullptr;

	return 0;
}
