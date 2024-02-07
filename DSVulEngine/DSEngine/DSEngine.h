#pragma once
#include "EntityManager.h"
#include "VulkanGraphics.h"
#include "MeshFactory.h"
const std::vector<Vertex> rectangle = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0
};

class DSEngine {
public:
    bool m_FramebufferResized;
    void Run();

private:
    const uint32_t DEFAULTWIDTH = 800;
    const uint32_t DEFAULTHEIGHT = 600;

    VulkanGraphics m_VulkanGraphics = {};
    GLFWwindow* m_Window;
    EntityManager m_EntityManager;

    void InitWindow();
    void Sandbox();
    void MainLoop();
    void Cleanup();

    void Tick();
};