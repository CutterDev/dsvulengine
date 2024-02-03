#include "DSModel.h"
void DSModel::Update(uint32_t currentImage, float swapChainWidth, float swapChainHeight, glm::vec3 position)
{
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBufferObject ubo;
    ubo.Model = glm::mat4(1.0f);
    ubo.Model = glm::translate(ubo.Model, position);
    ubo.Model = glm::rotate(ubo.Model , time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.View = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.Proj = glm::perspective(glm::radians(45.0f), swapChainWidth / swapChainHeight, 0.1f, 10.0f);
    

    ubo.Proj[1][1] *= -1;
    memcpy(UniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}

void DSModel::Draw(VkCommandBuffer commandBuffer)
{
    VkBuffer vertexBuffers[] = { VertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, IndexBuffer, 0, VK_INDEX_TYPE_UINT16);
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(IndiceCount), 1, 0, 0, 0);
}

void DSModel::Destroy(VkDevice& device)
{
    vkDestroyBuffer(device, IndexBuffer, nullptr);
    vkFreeMemory(device, IndexBufferMemory, nullptr);

    vkDestroyBuffer(device, VertexBuffer, nullptr);
    vkFreeMemory(device, VertexBufferMemory, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroyBuffer(device, UniformBuffers[i], nullptr);
        vkFreeMemory(device, UniformBuffersMemory[i], nullptr);
    }
}