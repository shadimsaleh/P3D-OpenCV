#pragma once
#include <type_traits>
#include "IComponent.h"

typedef unsigned int ComponentId;

struct ComponentType
{
	template <typename T>
	static ComponentId Get() {
		static_assert(std::is_base_of<IComponent, T>::value && !std::is_same<IComponent, T>::value,
			"Class type must implement IComponent.");

		static ComponentId id = counter++;
		return id;
	}

private:
	static ComponentId counter;
};
