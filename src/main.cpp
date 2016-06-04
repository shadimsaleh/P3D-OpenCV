#include <Core\Game.h>
#include <Content\MeshData.h>
#include <Components\Transform.h>
#include <Components\Mesh.h>
#include <Systems\MeshSystem.h>
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

void Load(Game& game, ContentLoader& loader)
{
	Pool& pool = game.GetPool();
	pool.AddSystem<MeshSystem>();

	auto mesh = loader.Load<MeshData>("test");
	mesh->SetVertices(std::vector<Vertex> {
		Vertex(glm::vec3(0, 1.0f, 0), glm::vec4(1, 0, 0, 1), glm::vec3(1), glm::vec2(1)),
		Vertex(glm::vec3(1.0f, -1.0f, 0), glm::vec4(0, 1, 0, 1), glm::vec3(1), glm::vec2(1)),
		Vertex(glm::vec3(-1.0f, -1.0f, 0), glm::vec4(0, 0, 1, 1), glm::vec3(1), glm::vec2(1))
	}, PrimitiveType::Triangles);

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