#include "ModelFactory.h"

DSModel* CreateModel(
    VkDevice* device,
    VkPhysicalDevice physicalDevice,
    const std::vector<Vertex> vertices,
    uint32_t size,
    const std::vector<uint16_t> indices,
    uint32_t indicesSize
)
{
    DSModel* model = new DSModel();

    VkBuffer buffer;
    VkDeviceMemory memory;

    CreateVertexBuffer(device, physicalDevice, buffer, memory, vertices, size);

    VkBuffer indexBuffer;
    VkDeviceMemory indexMemory;
    CreateIndexBuffer(device, physicalDevice, indexBuffer, indexMemory, indices, indicesSize);

    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    model->UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    model->UniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    model->UniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        CreateBuffer(
            device,
            physicalDevice,
            bufferSize,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            model->UniformBuffers[i],
            model->UniformBuffersMemory[i]);

        vkMapMemory(*device, model->UniformBuffersMemory[i], 0, bufferSize, 0, &model->UniformBuffersMapped[i]);
    }


    model->VertexBuffer = buffer;
    model->VertexBufferMemory = memory;
    model->VertexCount = size;
    model->IndexBuffer = indexBuffer;
    model->IndexBufferMemory = indexMemory;
    model->IndiceCount = indicesSize;

    return model;
}

void CreateVertexBuffer(VkDevice* device, VkPhysicalDevice physicalDevice, VkBuffer& buffer, VkDeviceMemory& memory, const std::vector<Vertex> vertices, uint32_t size)
{
    VkDeviceSize bufferSize = sizeof(vertices[0]) * size;
    CreateBuffer(device, physicalDevice, bufferSize,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        buffer,
        memory
    );

    void* data;
    vkMapMemory(*device, memory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(*device, memory);
}

void CreateIndexBuffer(VkDevice* device, VkPhysicalDevice physicalDevice, VkBuffer& buffer, VkDeviceMemory& memory, const std::vector<uint16_t> indices, uint32_t size)
{
    VkDeviceSize bufferSize = sizeof(indices[0]) * size;

    CreateBuffer(device,
        physicalDevice,
        bufferSize,
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        buffer,
        memory);

    void* data;
    vkMapMemory(*device, memory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(*device, memory);
}

void CreateBuffer(VkDevice* device, VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, 
    VkBuffer& buffer, 
    VkDeviceMemory& bufferMemory) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(*device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(*device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(*device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(*device, buffer, bufferMemory, 0);
}

void CreateUniformBuffer()
{

}

uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    // Get The Physical Device Memory Properties with flags
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}