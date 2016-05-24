#include "Group.h"

Group::Group() : pool(nullptr)
{
}

Group::~Group()
{
	pool->Detach(this);
}

void Group::OnNotify(EntityPtr entity)
{
	bool matches = true;

	matches = CheckAllOf(entity);
	if (!matches) return;

	matches = CheckOneOf(entity);
	if (!matches) return;

	matches = CheckExclude(entity);
	if (!matches) return;

	entities.push_back(entity);
}

void Group::SetPool(Pool& pool)
{
	this->pool = &pool;
	pool.Attach(this);
}

bool Group::CheckAllOf(EntityPtr entity)
{
	bool matches = true;
	int size = allof.size();
	if (size == 0)
		return true;
	
	for (size_t i = 0; i < size; i++)
	{
		matches &= entity->Has(allof[i]);
	}

	return matches;
}

bool Group::CheckOneOf(EntityPtr entity)
{
	int size = oneof.size();
	if (size == 0)
		return true;

	for (size_t i = 0; i < size; i++)
	{
		if (entity->Has(oneof[i])) {
			return true;
		}
	}

	return false;
}

bool Group::CheckExclude(EntityPtr entity)
{
	int size = exclude.size();
	if (size == 0)
		return true;

	for (size_t i = 0; i < size; i++)
	{
		if (entity->Has(exclude[i])) {
			return false;
		}
	}

	return true;
}

int Group::Size()
{
	return entities.size();
}

EntityPtr Group::Get(size_t i)
{
	return entities[i];
}

EntityPtr Group::operator[](size_t i) const
{
	return entities[i];
}
