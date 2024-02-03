#pragma once
#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

#include <stdexcept>
#include <array>
#include <vector>

const int MAX_FRAMES_IN_FLIGHT = 2;

struct UniformBufferObject {
    alignas(16) glm::mat4 Model;
    alignas(16) glm::mat4 View;
    alignas(16) glm::mat4 Proj;
};

struct Vertex {
    glm::vec2 Pos;
    glm::vec3 Color;

    // We need to tell Vulkan how to pass this data format to the Vertex Shader once its been uplaoded to memoru
    static VkVertexInputBindingDescription GetBindingDesc()
    {
        VkVertexInputBindingDescription bindingDescription{};

        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex); // stride in memory per vertex
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, Pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, Color);

        return attributeDescriptions;
    }
};


class DSModel
{
public:
    VkBuffer VertexBuffer;
    VkDeviceMemory VertexBufferMemory;
    uint32_t VertexCount;
    VkBuffer IndexBuffer;
    VkDeviceMemory IndexBufferMemory;
    uint32_t IndiceCount;

    std::vector<VkBuffer> UniformBuffers;
    std::vector<VkDeviceMemory> UniformBuffersMemory;
    std::vector<void*> UniformBuffersMapped;

    std::vector<VkDescriptorSet> DescriptorSets;

    DSModel() {
        VertexBuffer = {};
        VertexBufferMemory = {};
        VertexCount = 0;
        IndexBuffer = {};
        IndexBufferMemory = {};
        IndiceCount = 0;
    }

    virtual void Update(uint32_t currentImage, float swapChainWidth, float swapChainHeight, glm::vec3 position);
    virtual void Draw(VkCommandBuffer commandBuffer);
    virtual void Destroy(VkDevice& device);

    void Translate(glm::vec3 position);
};

