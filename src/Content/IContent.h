#pragma once
#include <string>

struct IContent
{
	virtual void Load(const std::string& filename) = 0;
};