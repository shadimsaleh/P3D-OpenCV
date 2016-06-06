#pragma once
#include <vector>
#include <map>
#include <string>

class Console
{
public:
	Console();
	
	static Console* Instance();
	void Draw();
	void RegisterCommand(const std::string& command, void(*callback)(Console*, std::vector<std::string>&));
	void Print(const std::string& string, bool highlight = false);
	void Error(const std::string& string);
	void ClearLog();

private:
	~Console();

	static Console* instance;

	char buffer[256];
	std::vector<std::string> log;
	std::map <std::string, void(*)(Console*, std::vector<std::string>&)> commands;
	bool scrollToBottom;
};