#pragma once
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <ECS/IComponent.h>
#include <ECS/ComponentType.h>

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
	ComponentPtr Get();

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
inline ComponentPtr Entity::Get()
{
	return components[ComponentType::Get<T>()];

}
template<typename T>
inline bool Entity::Has()
{
	return Has(ComponentType::Get<T>());
}
