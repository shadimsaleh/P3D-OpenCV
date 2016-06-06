#pragma once
#include <Content\ContentLoader.h>
#include <SFML\Graphics.hpp>
#include <Lagswitch\ECS\Pool.h>
#include <Graphics\Camera.h>

class Console;

class Game
{
public:
	Game();
	~Game();

	void Run(int width, int height, const std::string& title);
	
	void SetLoadFunction(void(*LoadFunc)(Game&, ContentLoader&));
	void SetUpdateFunction(void(*UpdateFunc)(Game&, float));
	void SetRenderFunction(void(*RenderFunc)(Game&, float));
	void SetGUIFunction(void(*GUIFunc)(Game&, sf::RenderWindow&));
	
	Pool& GetPool();
	ContentLoader& GetContentLoader();
	sf::RenderWindow& GetWindow();
	float GetDeltaTime();
	int GetFramesPerSecond();

private:
	void PreUpdateInternal();
	void PostUpdateInternal();
	void PreRenderInternal();
	void PostRenderInternal();

	void(*LoadFunc)(Game&, ContentLoader&);
	void(*UpdateFunc)(Game&, float);
	void(*RenderFunc)(Game&, float);
	void(*GUIFunc)(Game&, sf::RenderWindow&);

	Camera camera;
	sf::Clock clock;
	sf::Time deltaTime;
	sf::RenderWindow window;
	Pool pool;
	ContentLoader contentLoader;
	bool running;
	float fpsTimer;
	int frameCount;
	int framesPerSecond;

	static Game* instance;

	// Console Callbacks
	static void QuitCallback(Console* console, std::vector<std::string>& args);
	static void WindowInfoCallback(Console* console, std::vector<std::string>& args);
	static void HelpCallback(Console* console, std::vector<std::string>& args);
};