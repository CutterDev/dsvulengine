#include "MeshFactory.h"

MeshComponent MeshFactory::CreateMeshComponent(glm::mat4* transform, const std::vector<Vertex>* vertices, const std::vector<uint16_t>* indices)
{
    MeshComponent meshComponent(vertices);

    MeshData meshData = { };
    meshData.Transform = transform;
    meshData.Vertices = vertices;
    meshData.Indices = indices;
    Meshes.push_back(meshData);

    return meshComponent;
}