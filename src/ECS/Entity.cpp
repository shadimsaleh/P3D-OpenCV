#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

bool Entity::Has(ComponentId id)
{
	std::map<ComponentId, ComponentPtr>::iterator it = components.find(id);
	return it != components.end();
}
