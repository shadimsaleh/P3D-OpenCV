#pragma once
#include <map>
#include <memory>
#include "IContent.h"

typedef std::shared_ptr<IContent> ContentPtr;

class ContentLoader
{
public:
	template <typename T, typename... TArgs>
	std::shared_ptr<T> Load(const std::string& filename, TArgs... args);

private:
	std::map<std::string, ContentPtr> content;
};

template<typename T, typename... TArgs>
inline std::shared_ptr<T> ContentLoader::Load(const std::string & filename, TArgs... args)
{
	if (content.find(filename) == content.end()) 
	{
		std::shared_ptr<IContent> ptr(std::make_shared<T>(args...));
		std::shared_ptr<T> ptrCast = std::static_pointer_cast<T>(ptr);
		if (!ptrCast->Load(filename))
		{
			return nullptr;
		}

		content[filename] = ptr;
		return ptrCast;
	}

	return std::static_pointer_cast<T>(content[filename]);
}