#pragma once
#include <Content\ContentLoader.h>
#include <SFML\Graphics.hpp>
#include <Lagswitch\ECS\Pool.h>	
#include <Graphics\Camera.h>

class Game
{
public:
	Game();
	~Game();

	void Run(int width, int height, const std::string& title);
	void SetLoadFunction(void(*LoadFunc)(Game&, ContentLoader&));
	void SetUpdateFunction(void(*UpdateFunc)(Game&, float));
	void SetRenderFunction(void(*RenderFunc)(Game&, float));
	Pool& GetPool();
	ContentLoader& GetContentLoader();
	sf::RenderWindow& GetWindow();

private:
	void PreUpdateInternal();
	void PostUpdateInternal();
	void PreRenderInternal();
	void PostRenderInternal();

	void(*LoadFunc)(Game&, ContentLoader&);
	void(*UpdateFunc)(Game&, float);
	void(*RenderFunc)(Game&, float);

	sf::RenderWindow window;
	Pool pool;
	ContentLoader contentLoader;
	Camera camera;
	float deltaTime;
	bool running;
};