#include "DSModelImproved.h"

void DSModelImproved::Draw(VkCommandBuffer commandBuffer)
{
    VkBuffer vertexBuffers[] = { VertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, IndexBuffer, 0, VK_INDEX_TYPE_UINT16);
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(IndiceCount), 1, 0, 0, 0);
}

void DSModelImproved::Destroy(VkDevice& device)
{
    vkDestroyBuffer(device, IndexBuffer, nullptr);
    vkFreeMemory(device, IndexBufferMemory, nullptr);

    DSSimpleModel::Destroy(device);
}