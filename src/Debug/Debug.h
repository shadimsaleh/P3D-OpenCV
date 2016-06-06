#pragma once
#include <Debug\Console.h>

Console* console = Console::Instance();

#define Print(string, highlight) console->Print(string, highlight)
#define PrintLine() console->PrintLine()
#define Error(string) console->Error(string)