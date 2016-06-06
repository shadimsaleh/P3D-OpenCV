#include "Console.h"
#include <imgui\imgui.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

Console* Console::instance = nullptr;

Console::Console()
{
}

Console::~Console()
{
	delete instance;
}

Console * Console::Instance()
{
	if (instance == nullptr) 
	{
		instance = new Console();
	}

	return instance;
}

void Console::Draw()
{
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiSetCond_FirstUseEver);
	if (!ImGui::Begin("Console"))
	{
		ImGui::End();
		return;
	}

	ImGui::BeginChild("ScrollingConsole", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
	
	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::Selectable("Clear")) 
			ClearLog();

		if (ImGui::Selectable(""))

		ImGui::EndPopup();
	}

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));
	
	for (int i = 0; i < log.size(); i++)
	{
		std::string item = log[i];
		ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		
		if (item.find("[error]") != std::string::npos)
			color = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
		else if (strncmp(item.c_str(), "# ", 2) == 0) 
			color = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
		
		ImGui::PushStyleColor(ImGuiCol_Text, color);
		ImGui::TextUnformatted(item.c_str());
		ImGui::PopStyleColor();
	}

	if (scrollToBottom)
		ImGui::SetScrollHere();
	scrollToBottom = false;
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::Separator();

	if (ImGui::InputText("Input", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		char* input_end = buffer + strlen(buffer);
		
		while (input_end > buffer && input_end[-1] == ' ') 
		{
			input_end--;
			*input_end = 0;
		}
			
		if (buffer[0])
		{
			std::string input(buffer);
			std::istringstream stream(input);

			std::vector<std::string> words{
				std::istream_iterator<std::string>{ stream },
				std::istream_iterator<std::string>{}
			};

			if (commands.find(words[0]) != commands.end()) 
			{
				std::string command = words[0];
				words.erase(words.begin());
				Print(buffer);
				commands[command](this, words);
			}
			else
			{
				Error("Input isn't recognized as a valid command.");
			}
		}

		strcpy_s(buffer, "");
	}

	if (ImGui::IsItemHovered() || (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
		ImGui::SetKeyboardFocusHere(-1);

	ImGui::End();
}

void Console::RegisterCommand(const std::string & command, void(*callback)(Console*, std::vector<std::string>&))
{
	commands[command] = callback;
}

void Console::Print(const std::string& string, bool highlight)
{
	log.push_back((highlight ? "# " : "") + string);
	scrollToBottom = true;
}

void Console::Error(const std::string& string)
{
	log.push_back("[error] " + string);
	scrollToBottom = true;
}

void Console::ClearLog()
{
	log.erase(log.begin(), log.end());
}
