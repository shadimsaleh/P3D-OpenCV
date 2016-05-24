#include "Pool.h"

Pool::Pool() : systemCount(0), changed(false)
{
}

Pool::~Pool()
{
	for (size_t i = 0; i < systemCount; i++)
	{
		systems[i]->OnDispose();
	}
}

void Pool::Execute()
{
	if (changed) {
		NotifyChanges();
		changed = false;
	}

	for (size_t i = 0; i < systemCount; i++)
	{
		systems[i]->OnExecute();
	}
}

void Pool::NotifyChanges()
{
	int size = entities.size();
	for (size_t i = 0; i < size; i++)
	{
		Notify(entities[i]);
	}
}
