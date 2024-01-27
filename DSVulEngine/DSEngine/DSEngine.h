#pragma once
#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <limits> // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp
#include <stdexcept>
#include <cstdlib>

#include <vector>
#include <optional>
#include <set>
#include <array>

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

const std::vector<Vertex> vertices = {
    {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

struct QueueFamilyIndices {
    std::optional<uint32_t> GraphicsFamily;
    std::optional<uint32_t> PresentFamily;

    bool IsComplete() {
        return GraphicsFamily.has_value() && PresentFamily.has_value();
    } 
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR Capabilities;
    std::vector<VkSurfaceFormatKHR> Formats;
    std::vector<VkPresentModeKHR> PresentModes;
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


class DSEngine {
public:
    bool m_FramebufferResized;
    void Run();

private:
    const int MAX_FRAMES_IN_FLIGHT = 2;
    const uint32_t DEFAULTWIDTH = 800;
    const uint32_t DEFAULTHEIGHT = 600;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    uint32_t m_CurrentFrame = 0;

    GLFWwindow* m_Window;

    VkInstance m_Instance;

    VkDebugUtilsMessengerEXT m_DebugMessenger;

    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;

    VkDevice m_Device;

    VkQueue m_GraphicsQueue;
    VkQueue m_PresentQueue;
    
    
    VkDeviceMemory m_VertexBufferMemory;
    VkBuffer m_VertexBuffer;

    VkSurfaceKHR m_Surface;
    VkSwapchainKHR m_SwapChain;
    std::vector<VkImage> m_SwapChainImages;
    VkFormat m_SwapChainImageFormat;
    VkExtent2D m_SwapChainExtent;
    std::vector<VkImageView> m_SwapChainImageViews;
    std::vector<VkFramebuffer> m_SwapChainFramebuffers;

    VkRenderPass m_RenderPass;
    VkPipelineLayout m_PipelineLayout;
    VkPipeline m_GraphicsPipeline;

    VkCommandPool m_CommandPool;

    std::vector <VkCommandBuffer> m_CommandBuffers;
    std::vector <VkSemaphore> m_ImageAvailableSemaphores;
    std::vector <VkSemaphore> m_RenderFinishedSemaphores;
    std::vector <VkFence> m_InFlightFences;

    void InitWindow();
    void InitVulkan();
    void MainLoop();
    void Cleanup();

    void DrawFrame();

    void CreateInstance();
    void SetupDebugMessenger();
    void CreateSurface();
    void PickPhysicalDevice();
    void CreateLogicalDevice();
    void CreateSwapChain();
    void RecreateSwapChain();
    void CreateImageViews();
    void CreateRenderPass();
    void CreateGraphicsPipeline();
    void CreateFramebuffers();
    void CreateCommandPool();
    void CreateVertexBuffer();
    void CreateCommandBuffers();
    void CreateSyncObjects();

    void CleanupSwapChain();

    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    VkShaderModule CreateShaderModule(const std::vector<char>& code);

    std::vector<const char*> GetRequiredExtensions();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    bool CheckValidationLayerSupport();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    VkResult CreateDebugUtilsMessengerEXT
    (
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger
    );
    void DestroyDebugUtilsMessengerEXT
    (
        VkInstance instance,
        VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks* pAllocator
    );
};

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

static std::vector<char> ReadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}