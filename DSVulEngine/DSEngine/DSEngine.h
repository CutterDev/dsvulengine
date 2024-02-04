#pragma once
#include "VulkanGraphics.h"

class DSEngine {
public:
    bool m_FramebufferResized;
    void Run();

private:
    const uint32_t DEFAULTWIDTH = 800;
    const uint32_t DEFAULTHEIGHT = 600;

    VulkanGraphics m_VulkanGraphics = {};
    GLFWwindow* m_Window;

    void InitWindow();
    void MainLoop();
    void Cleanup();

    void Tick();
};