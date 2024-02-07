#pragma once
#include "MeshComponent.h"
#include "Bindings.h"

struct MeshData 
{
    const std::vector<Vertex>* Vertices;
    glm::mat4* Transform;
    const std::vector<uint16_t>* Indices;
};
class MeshFactory
{
public: 
    std::vector<MeshData> Meshes;
    static MeshFactory& Instance()
    {
        static MeshFactory instance;
        return instance;
    }
private:
    MeshFactory() {}

public: 
    MeshFactory(MeshFactory const&) = delete;
    void operator=(MeshFactory const&) = delete;
public:
    MeshComponent CreateMeshComponent(glm::mat4* transform, const std::vector<Vertex>* vertices, const std::vector<uint16_t>* indices);
};

