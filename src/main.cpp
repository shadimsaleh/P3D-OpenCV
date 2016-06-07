#include <Core\Game.h>
#include <Content\MeshData.h>
#include <Components\Transform.h>
#include <Components\Mesh.h>
#include <Components\Tween.h>
#include <Systems\MeshSystem.h>
#include <Systems\TweenSystem.h>
#include <imgui\imgui.h>
#include <imgui-sfml\imgui-SFML.h>
#include <Data\LimitedQueue.h>
#include <Debug\Console.h>

void DeveloperSettings()
{

}

void DeveloperConsole()
{
	static Console* console = Console::Instance();
	console->Draw();
}

void DebugOverlay(Game& game)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::SetNextWindowContentWidth(350);
	ImGui::Begin("DebugOverlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

	ImGui::Text("Developer Debug Data");
	ImGui::Separator();
	ImGui::Text("Mouse Position (Screen): (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
	ImGui::Text("Frames Per Second: %i", game.GetFramesPerSecond());
	
	static LimitedQueue<float> queue(25);
	static float interval = 0.10f;
	interval += game.GetDeltaTime();
	
	if (interval > 0.10f || queue.Count() < queue.Maximum()) 
	{
		queue.Push(game.GetDeltaTime());
		interval = 0.0f;
	}

	ImGui::PlotLines("frame time", queue.Data(), queue.Size());

	static bool console = false;
	
	if (ImGui::Button("Console"))
		console = !console;

	if (console) 
		DeveloperConsole();

	ImGui::SameLine();

	static bool settings = false;

	if (ImGui::Button("Settings"))
		settings = !settings;

	if (settings)
		DeveloperSettings();

	ImGui::End();
}

std::vector<Vertex> CreatWorldCube(float spacing)
{
	int linenumber;
	//aldrabice!
	if (spacing <= 0.0625) { spacing = 0.0625; linenumber = 33; }
	if (spacing > 0.0625 && spacing <= 0.125) { spacing = 0.125; linenumber = 17; }
	if (spacing > 0.125 && spacing <= 0.25) { spacing = 0.25; linenumber = 9; }
	if (spacing > 0.25 && spacing <= 0.5) { spacing = 0.5; linenumber = 5; }
	if (spacing > 0.5 ) { spacing =1; linenumber = 3; }
	//fim da aldrabice

	std::vector<Vertex> data;

//Z Lines
		//BottomSide
		for (size_t i = 0; i < linenumber; i++)
		{
			data.push_back(Vertex(glm::vec3(-1+spacing*i, -1, -1), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
			data.push_back(Vertex(glm::vec3(-1+spacing*i, -1, 1 ), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
		}
		//TopSide
		for (size_t i = 0; i < linenumber; i++)
		{
			data.push_back(Vertex(glm::vec3(-1 + spacing*i, 1, -1), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
			data.push_back(Vertex(glm::vec3(-1 + spacing*i, 1, 1 ), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
		}
		//RightSide
		for (size_t i = 0; i < linenumber; i++)
		{
			data.push_back(Vertex(glm::vec3(-1, -1 + spacing*i, -1), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
			data.push_back(Vertex(glm::vec3(-1, -1 + spacing*i, 1 ), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
		}
		//LefttSide
		for (size_t i = 0; i < linenumber; i++)
		{
			data.push_back(Vertex(glm::vec3(1, -1 + spacing*i, -1), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
			data.push_back(Vertex(glm::vec3(1, -1 + spacing*i, 1), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
		}
//X Lines
		//BottomLines
		for (size_t i = 0; i < linenumber; i++)
		{
			data.push_back(Vertex(glm::vec3(-1, -1, -1 + spacing*i), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
			data.push_back(Vertex(glm::vec3(1, -1, -1 + spacing*i), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
		}
		//TopLines
		for (size_t i = 0; i < linenumber; i++)
		{
			data.push_back(Vertex(glm::vec3(-1, 1, -1 + spacing*i), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
			data.push_back(Vertex(glm::vec3(1, 1, -1 + spacing*i), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
		}

//Y Lines
		for (size_t i = 0; i < linenumber; i++)
		{
			data.push_back(Vertex(glm::vec3(-1, -1 , -1 + spacing*i), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
			data.push_back(Vertex(glm::vec3(-1, 1 , -1 + spacing*i), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
		}
	
		for (size_t i = 0; i < linenumber; i++)
		{
			data.push_back(Vertex(glm::vec3(1, -1 , -1 + spacing*i), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
			data.push_back(Vertex(glm::vec3(1, 1 , -1 + spacing*i), glm::vec4(1, 1, 1, 1), glm::vec3(1), glm::vec2(1)));
		}

	return data;
}

void Load(Game& game, ContentLoader& loader)
{
	Pool& pool = game.GetPool();
	pool.AddSystem<MeshSystem>();
	pool.AddSystem<TweenSystem>();


	auto cube = loader.Load<MeshData>("cubeWorld");
	cube->SetVertices(CreatWorldCube(0.25), PrimitiveType::Lines);

	auto mesh = loader.Load<MeshData>("test");
	mesh->SetVertices(std::vector<Vertex> {
		Vertex(glm::vec3(1.0f, 1.0f, 1), glm::vec4(1, 0, 0, 1), glm::vec3(1), glm::vec2(1)),
		Vertex(glm::vec3(1.0f, -1.0f, 1), glm::vec4(0, 1, 0, 1), glm::vec3(1), glm::vec2(1)),
		Vertex(glm::vec3(-1.0f, -1.0f, 1), glm::vec4(0, 0, 1, 1), glm::vec3(1), glm::vec2(1)),
		Vertex(glm::vec3(-1.0f, 1.0f, 1), glm::vec4(0.5, 0.5, 1, 1), glm::vec3(1), glm::vec2(1)),
		Vertex(glm::vec3(-1.0f, -1.0f, 1), glm::vec4(0, 0, 1, 1), glm::vec3(1), glm::vec2(1)),
		Vertex(glm::vec3(1.0f, 1.0f, 1), glm::vec4(1, 0, 0, 1), glm::vec3(1), glm::vec2(1))
	}, PrimitiveType::Triangles);

	auto cubeEntity = pool.CreateEntity();
	cubeEntity->Add<Mesh>(cube);
	cubeEntity->Add<Transform>();

	auto e = pool.CreateEntity();
	e->Add<Mesh>(mesh);
	e->Add<Transform>();
}

void Update(Game& game, float deltaTime)
{

}

void Render(Game& game, float deltaTime)
{

}

void OnGUI(Game& game, sf::RenderWindow& window)
{
	DebugOverlay(game);
}

int main()
{
	Game game;
	game.SetLoadFunction(Load);
	game.SetUpdateFunction(Update);
	game.SetRenderFunction(Render);
	game.SetGUIFunction(OnGUI);
	game.Run(1280, 720, "OpenCV");

	return 0;
}

#if 0
int main() {
	Mat image;
	VideoCapture cap;

	cap.open(0);

	namedWindow("window", 1);

	while (1) 
	{
		cap >> image;
		imshow("window", image);
		waitKey(33);
	}

	return 0;
}
#endif