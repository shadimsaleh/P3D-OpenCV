#include "Game.h"
#include <GL\glew.h>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <imgui\imgui.h>
#include <imgui-sfml\imgui-SFML.h>
#include <Debug\Debug.h>
#include <Debug\Console.h>

Game* Game::instance = nullptr;

Game::Game() : running(false), fpsTimer(0.0f), frameCount(0), framesPerSecond(0)
{
	assert(!instance);

	if (!instance) {
		instance = this;
	}
}

Game::~Game()
{
}

void Game::Run(int width, int height, const std::string& title)
{
	window.create(sf::VideoMode(width, height), title);
	
	Print("Window initialized succesfully.", false);
	
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	camera.SetPerspective(45.0f, float(width) / float(height), 0.1f, 1000.0f);
	camera.position = glm::vec3(0, 0, -3);
	
	if (err != GLEW_OK)
	{
		Error(std::string((const char*)glewGetErrorString(err)));
	}

	PrintLine();
	Print("Glew initialized successfully.", false);
	Print((const char*)glGetString(GL_VENDOR), false);
	Print((const char*)glGetString(GL_RENDERER), false);
	Print((const char*)glGetString(GL_VERSION), false);
	Print(std::string("Shading Language: " + std::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION))), false);
	PrintLine();

	ImGui::SFML::Init(window);

	Print("GUI module is safe and sound.", false);

	Console* console = Console::Instance();
	console->RegisterCommand("quit", Game::QuitCallback);
	console->RegisterCommand("info", Game::WindowInfoCallback);
	console->RegisterCommand("help", Game::HelpCallback);

	Print("Hello, welcome!", true);
	Print("Brought to you with <3 by Lagswitch Games.", true);
	Print("Type 'help' for a list of available commands", true);

	if (LoadFunc != nullptr)
		LoadFunc(*this, contentLoader);

	running = true;
	while (running)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
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
			UpdateFunc(*this, deltaTime.asSeconds());

		PostUpdateInternal();

		PreRenderInternal();

		if (RenderFunc != nullptr)
			RenderFunc(*this, deltaTime.asSeconds());

		PostRenderInternal();
	}

	Print("Shutting down, see you later!", true);

	ImGui::SFML::Shutdown();
}

void Game::PreUpdateInternal()
{
	clock.restart();
	ImGui::SFML::Update();
}

void Game::PostUpdateInternal()
{
	pool.Execute();
}

void Game::PreRenderInternal()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::PostRenderInternal()
{
	pool.Render();

	window.pushGLStates();

	if (GUIFunc != nullptr)
		GUIFunc(*this, window);

	ImGui::Render();
	window.popGLStates();
	window.display();

	deltaTime = clock.restart();
	fpsTimer += deltaTime.asSeconds();
	frameCount++;
	
	if (fpsTimer >= 1.0f)
	{
		framesPerSecond = frameCount;
		fpsTimer = 0.0f;
		frameCount = 0;
	}
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

void Game::SetGUIFunction(void(*GUIFunc)(Game &, sf::RenderWindow &))
{
	this->GUIFunc = GUIFunc;
}

Pool & Game::GetPool()
{
	return pool;
}

ContentLoader & Game::GetContentLoader()
{
	return contentLoader;
}

sf::RenderWindow & Game::GetWindow()
{
	return window;
}

float Game::GetDeltaTime()
{
	return deltaTime.asSeconds();
}

int Game::GetFramesPerSecond()
{
	return framesPerSecond;
}

Game * Game::Instance()
{
	return instance;
}

void Game::QuitCallback(Console* console, std::vector<std::string>& args)
{
	Print("Closing...", false);
	instance->running = false;
}

void Game::WindowInfoCallback(Console * console, std::vector<std::string>& args)
{
	sf::Vector2u size = instance->window.getSize();
	sf::ContextSettings settings = instance->window.getSettings();
	
	Print(std::string("Resolution: " + std::to_string(size.x) + "x" + std::to_string(size.y)), false);
	Print(std::string("Anti-Aliasing: " + std::to_string(settings.antialiasingLevel) + "x"), false);
	Print(std::string("Depth: " + std::to_string(settings.depthBits)), false);
	Print(std::string("Stencil: " + std::to_string(settings.stencilBits)), false);
	Print(std::string("OpenGL Context: " + std::to_string(settings.majorVersion) + "." + std::to_string(settings.minorVersion)), false);
}

void Game::HelpCallback(Console * console, std::vector<std::string>& args)
{
	Print("'quit': closes the application.", false);
	Print("'info': prints window and OpenGL context settings.", false);
}
