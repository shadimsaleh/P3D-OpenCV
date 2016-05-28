#pragma once
#include <string>

struct IContent
{
	virtual bool Load(const std::string& filename) = 0;
};