#include "Game.h"
#include <GL\glew.h>

Game::Game() : running(false), deltaTime(0.0f)
{
}

Game::~Game()
{
}

void Game::Run(int width, int height, const std::string& title)
{
	window.create(sf::VideoMode(width, height), title);

	glewExperimental = GL_TRUE;
	glewInit();

	if (LoadFunc != nullptr)
		LoadFunc(*this, contentLoader);

	running = true;
	while (running)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		PreUpdateInternal();
		
		if (UpdateFunc != nullptr)
			UpdateFunc(*this, deltaTime);

		PostUpdateInternal();

		PreRenderInternal();

		if (RenderFunc != nullptr)
			RenderFunc(*this, deltaTime);

		PostRenderInternal();
	}
}

void Game::PreUpdateInternal()
{
}

void Game::PostUpdateInternal()
{
	
}

void Game::PreRenderInternal()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::PostRenderInternal()
{
	pool.Execute();
	window.display();
}

void Game::SetLoadFunction(void(*LoadFunc)(Game&, ContentLoader &))
{
	this->LoadFunc = LoadFunc;
}

void Game::SetUpdateFunction(void(*UpdateFunc)(Game&, float))
{
	this->UpdateFunc = UpdateFunc;
}

void Game::SetRenderFunction(void(*RenderFunc)(Game&, float))
{
	this->RenderFunc = RenderFunc;
}

Pool & Game::GetPool()
{
	return pool;
}

ContentLoader & Game::GetContentLoader()
{
	return contentLoader;
}
