#pragma once
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include "IComponent.h"
#include "ComponentType.h"

typedef std::shared_ptr<IComponent> ComponentPtr;

class Entity
{
public:
	Entity();
	~Entity();

	template <typename T, typename... TArgs>
	void Add(TArgs... args);

	template <typename T>
	void Remove();

	template <typename T>
	std::shared_ptr<T> Get();

	template <typename T>
	bool Has();

	bool Has(ComponentId id);

private:
	std::map<ComponentId, ComponentPtr> components;
};

template<typename T, typename ...TArgs>
inline void Entity::Add(TArgs... args)
{
	ComponentPtr t = std::make_shared<T>(args...);
	components[ComponentType::Get<T>()] = t;
}

template<typename T>
inline void Entity::Remove()
{
	ComponentId id = ComponentType::Get<T>();
	components.erase(id);
}

template<typename T>
inline std::shared_ptr<T> Entity::Get()
{
	return std::static_pointer_cast<T>(components[ComponentType::Get<T>()]);

}
template<typename T>
inline bool Entity::Has()
{
	return Has(ComponentType::Get<T>());
}
