#pragma once
#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>

#include <stdexcept>
#include <array>
#include <vector>

#include "DSModel.h"

DSModel* CreateModel(
    VkDevice* device,
    VkPhysicalDevice physicalDevice,
    const std::vector<Vertex>* vertices,
    uint32_t size,
    const std::vector<uint16_t>* indices,
    uint32_t indicesSize
);
void CreateVertexBuffer(VkDevice* device, VkPhysicalDevice physicalDevice, VkBuffer& buffer, VkDeviceMemory& memory, const std::vector<Vertex> vertices, uint32_t size);

void CreateIndexBuffer(VkDevice* device, VkPhysicalDevice physicalDevice, VkBuffer& buffer, VkDeviceMemory& memory, const std::vector<uint16_t> indices, uint32_t size);

void CreateBuffer(VkDevice* device, VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
    VkBuffer& buffer,
    VkDeviceMemory& bufferMemory);

uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);