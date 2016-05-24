#include <iostream>
#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <ECS\Pool.h>
#include <ECS\Entity.h>
#include <Events\IObserver.h>
#include <Events\Subject.h>
#include <ECS\Group.h>
#include <memory>

struct Movement : public IComponent
{
	float dir;

	virtual void Reset() override
	{
	}
};

struct Position : public IComponent
{
	float x;
	float y;

	Position(float x, float y) : x(x), y(y) { }

	virtual void Reset() override
	{
	}
};

struct MoveSystem : public ISystem
{
	Group group;

	virtual void OnInitialize(Pool& pool) override
	{
		group.SetPool(pool);
		group.OneOf<Position>();
		group.OneOf<Movement>();
	}

	virtual void OnExecute() override
	{
		int size = group.Size();
		for (size_t i = 0; i < size; i++)
		{
			auto entity = group[i];

			// Do whatever with entity.
		}
	}

	virtual void OnDispose() override
	{
	}
};

#if 1
int main() {
	sf::Window window(sf::VideoMode(800, 600), "OpenGL");

	Pool pool;
	pool.AddSystem<MoveSystem>();

	EntityPtr entity = pool.CreateEntity();
	entity->Add<Position>(0, 0);
	entity->Add<Movement>();

	bool running = true;
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

		pool.Execute();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_TRIANGLES);

		glVertex3f(0.5, 0.5, 0);
		glVertex3f(1.0, -0.5, 0);
		glVertex3f(0, -0.5, 0);

		glEnd();

		window.display();
	}
}
#endif

#if 0
int main() {
	Mat image;
	VideoCapture cap;

	cap.open(0);

	namedWindow("window", 1);

	while (1) {
		cap >> image;
		imshow("window", image);
		waitKey(33);
	}
	return 0;
}
#endif