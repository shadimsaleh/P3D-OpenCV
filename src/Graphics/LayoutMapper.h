#pragma once
#include <map>
#include <memory>
#include <Graphics\BufferLayout.h>

typedef unsigned int TypeId;
typedef std::shared_ptr<BufferLayout> BufferLayoutPtr;

struct LayoutMapper
{
	template <typename T>
	static TypeId GetId()
	{
		static TypeId id = counter++;
		return id;
	}

	template <typename T>
	static void SetLayout(BufferLayout* bufferLayout)
	{
		TypeId id = GetId<T>();
		map[id] = BufferLayoutPtr(bufferLayout);
	}

	template <typename T>
	static BufferLayoutPtr GetLayout() 
	{
		TypeId id = GetId<T>();
		if (map.find(id) == map.end()) 
		{
			return nullptr;
		}

		return map[id];
	}

private:
	static std::map<TypeId, BufferLayoutPtr> map;
	static TypeId counter;
};