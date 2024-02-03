#include "DSSimpleModel.h"

void DSSimpleModel::Draw(VkCommandBuffer commandBuffer)
{
    VkBuffer vertexBuffers[] = { VertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

    vkCmdDraw(commandBuffer, VertexCount, 1, 0, 0);
}

void DSSimpleModel::Destroy(VkDevice& device)
{
    vkDestroyBuffer(device, VertexBuffer, nullptr);
    vkFreeMemory(device, VertexBufferMemory, nullptr);
}