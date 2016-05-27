#pragma once
#include <map>
#include <memory>
#include "IContent.h"

typedef std::shared_ptr<IContent> ContentPtr;

class ContentLoader
{
public:
	/**/
	template <typename T>
	std::shared_ptr<T> Load(const std::string& filename);

private:
	std::map<std::string, ContentPtr> content;
};

template<typename T>
inline std::shared_ptr<T> ContentLoader::Load(const std::string & filename)
{
	auto ptr = std::make_shared<IContent>();
	ptr->Load(filename);

	return ptr;
}