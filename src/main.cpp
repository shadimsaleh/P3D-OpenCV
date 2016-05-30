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
#include <glm\gtc\matrix_transform.hpp>
#include <glm\glm.hpp>

struct Movement : public IComponent
{
	float dir;

	virtual void Reset() override
	{
	}
};

struct MeshRenderer : public IComponent
{
	MeshRenderer(Mesh& mesh, std::shared_ptr<Shader> shader) : mesh(mesh), shader(shader) { }

	Mesh mesh;
	std::shared_ptr<Shader> shader;

	virtual void Reset() override
	{
	}
};

struct Position : public IComponent
{
	glm::vec3 position;

	Position(const glm::vec3& pos) : position(pos) { }
	Position() { }

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
		group.AllOf<Position>();
	}

	virtual void OnExecute() override
	{
		int size = group.Size();
		for (size_t i = 0; i < size; i++)
		{
			auto meshRenderer = group[i]->Get<MeshRenderer>();
			auto position = group[i]->Get<Position>();

			glm::mat4 transform;
			transform = glm::translate(transform, position->position);

			meshRenderer->shader->Use();
			meshRenderer->shader->SetUniform("model", transform);
			meshRenderer->mesh.Draw(GL_TRIANGLES);
			meshRenderer->shader->Unuse();
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
	glEnable(GL_DEPTH_TEST);

	Pool pool;
	pool.AddSystem<RenderSystem>();
	EntityPtr entity = pool.CreateEntity();

	auto vao = std::make_shared<VertexArray>();
	content.Load<Mesh>("mesh")->SetVertexArray(vao);

	std::vector<VertexPositionColor> vertices{
		VertexPositionColor(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
		VertexPositionColor(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
		VertexPositionColor(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)),
		VertexPositionColor(glm::vec3(-0.5f, 0.5f, 0.0f),glm::vec4(0.5f, 0.25f, 0.5f, 1.0f))
	};

	std::vector<unsigned int> indices{
		0, 1, 3,
		1, 2, 3
	};

	vao->Bind();
	vao->Push(vertices, GL_STATIC_DRAW);
	vao->SetIndices(indices, GL_STATIC_DRAW);
	vao->Unbind();

	auto shader = content.Load<Shader>("resources/test");
	entity->Add<MeshRenderer>(*content.Load<Mesh>("mesh"), shader);
	entity->Add<Position>(glm::vec3(0, 0, 0));

	glm::mat4 view;

	shader->Use();
	shader->SetUniform("projection", glm::perspective<float>(45.0f, 800 / 600, 0.1f, 100.0f));
	view = glm::translate(view, glm::vec3(0, 0, -3.0f));
	shader->SetUniform("view", view);
	shader->Unuse();

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