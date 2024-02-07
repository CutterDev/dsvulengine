#pragma once
#include <vector>

#include "IComponent.h"
#include "Bindings.h"
// Vertices Component
class MeshComponent : public IComponent
{
    const std::vector<Vertex>* Vertices;

public:
    MeshComponent(const std::vector<Vertex>* vertices)
    {
        Vertices = vertices;
    }

    void Update() override;
};

