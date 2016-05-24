#pragma once
#include <Events\IObserver.h>
#include <ECS\Entity.h>
#include <ECS\IComponent.h>
#include <ECS\Pool.h>

typedef std::shared_ptr<Entity> EntityPtr;

class Group : public IObserver<EntityPtr>
{
public:
	Group();
	~Group();

	virtual void OnNotify(EntityPtr entity) override;

	void SetPool(Pool& pool);

	template <typename T>
	void AllOf();

	template <typename T>
	void OneOf();

	template <typename T>
	void Exclude();
	
	bool CheckAllOf(EntityPtr entity);
	bool CheckOneOf(EntityPtr entity);
	bool CheckExclude(EntityPtr entity);
	
	int Size();
	EntityPtr Get(size_t i);

	EntityPtr operator[](size_t i) const;

private:
	Pool* pool;
	std::vector<int> allof;
	std::vector<int> oneof;
	std::vector<int> exclude;

	std::vector<EntityPtr> entities;
};

template<typename T>
inline void Group::AllOf()
{
	allof.push_back(ComponentType::Get<T>());
}

template<typename T>
inline void Group::OneOf()
{
	oneof.push_back(ComponentType::Get<T>());
}

template<typename T>
inline void Group::Exclude()
{
	exclude.push_back(ComponentType::Get<T>());
}
