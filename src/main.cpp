#include <iostream>
#include <SFML\Graphics.hpp>
#include <GL\glew.h>
#include <Lagswitch\ECS\Pool.h>
#include <Lagswitch\ECS\Entity.h>
#include <Lagswitch\ECS\IObserver.h>
#include <Lagswitch\ECS\Subject.h>
#include <Lagswitch\ECS\Group.h>
#include <memory>
#include <Content\ContentLoader.h>
#include <Graphics\Shader.h>
#include <Graphics\VertexArray.h>
#include <Graphics\BufferLayout.h>
#include <Graphics\Vertex\VertexPositionColor.h>
#include <Graphics\Mesh.h>

struct Movement : public IComponent
{
	float dir;

	virtual void Reset() override
	{
	}
};

struct MeshRenderer : public IComponent
{
	MeshRenderer(Mesh& mesh) : mesh(mesh) { }

	Mesh mesh;

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

struct RenderSystem : public ISystem
{
	Group group;

	virtual void OnInitialize(Pool& pool) override
	{
		group.SetPool(pool);
		group.AllOf<MeshRenderer>();
	}

	virtual void OnExecute() override
	{
		int size = group.Size();
		for (size_t i = 0; i < size; i++)
		{
			auto meshRenderer = group[i]->Get<MeshRenderer>();

			meshRenderer->mesh.Draw();
		}
	}

	virtual void OnDispose() override
	{
	}
};

#if 1
int main() {
	sf::Window window(sf::VideoMode(800, 600), "OpenGL");
	ContentLoader content;

	glewExperimental = GL_TRUE;
	glewInit();

	Pool pool;
	pool.AddSystem<RenderSystem>();

	auto vao = std::make_shared<VertexArray>();
	vao->Bind();

	std::vector<VertexPositionColor> vertices{
		VertexPositionColor(0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		VertexPositionColor(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
		VertexPositionColor(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
		VertexPositionColor(-0.5f, 0.5f, 0.0f, 0.5f, 0.25f, 0.5f, 1.0f)
	};

	std::vector<unsigned int> indices{
		0, 1, 3,
		1, 2, 3
	};

	vao->Push(vertices, GL_STATIC_DRAW);
	vao->SetIndices(indices, GL_STATIC_DRAW);

	vao->Unbind();

	content.Load<Mesh>("mesh")->SetVertexArray(vao);

	EntityPtr entity = pool.CreateEntity();
	entity->Add<MeshRenderer>(*content.Load<Mesh>("mesh"));

	auto shader = content.Load<Shader>("resources/test");

	shader->Use();

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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pool.Execute();

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