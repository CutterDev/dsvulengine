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

#include "Bindings.h"

const int MAX_FRAMES_IN_FLIGHT = 2;

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
    void ClearUniforms(VkDevice& device);

    void Translate(glm::vec3 position);
};

