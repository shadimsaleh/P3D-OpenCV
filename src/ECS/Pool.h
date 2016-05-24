#pragma once
#include <ECS\ISystem.h>
#include <vector>
#include <memory>
#include <ECS/Entity.h>
#include <Events\Subject.h>

typedef std::shared_ptr<ISystem> SystemPtr;
typedef std::shared_ptr<Entity> EntityPtr;

class Pool : public Subject<EntityPtr>
{
public:
	Pool();
	~Pool();

	void Execute();

	template <typename T, typename... TArgs>
	void AddSystem(TArgs... args);

	template <typename... Args>
	EntityPtr CreateEntity(Args... args);

private:
	void NotifyChanges();

	std::vector<SystemPtr> systems;
	std::vector<EntityPtr> entities;
	int systemCount;
	bool changed;
};

template<typename T, typename ...TArgs>
inline void Pool::AddSystem(TArgs ...args)
{
	SystemPtr t = std::make_shared<T>(args...);
	systems.push_back(t);
	t->OnInitialize(*this);
	systemCount++;
}

template<typename ...Args>
inline EntityPtr Pool::CreateEntity(Args ...args)
{
	EntityPtr entity = std::make_shared<Entity>();
	entities.push_back(entity);
	changed = true;
	return entity;
}