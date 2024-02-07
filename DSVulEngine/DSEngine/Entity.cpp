#include "Entity.h"

void Entity::AddComponent(IComponent component)
{
    m_Components.push_back(component);
}

void Entity::RemoveComponent(IComponent component)
{
}

void Entity::UpdateComponents()
{
    for (IComponent& component : m_Components)
    {
        component.Update();
    }
}