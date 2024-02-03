#pragma once

#include "DSSimpleModel.h"

class DSModelImproved: public DSSimpleModel
{
public:
    VkBuffer IndexBuffer;
    VkDeviceMemory IndexBufferMemory;
    uint32_t IndiceCount;
    void Draw(VkCommandBuffer commandBuffer);
    void Destroy(VkDevice& device);
};

