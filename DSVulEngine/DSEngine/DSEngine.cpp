#include "DSEngine.h"

void DSEngine::Run()
{
    //
    // Initialization
    InitWindow();
    m_VulkanGraphics.Initialize(m_Window);

    //
    // Main loop
    MainLoop();
    Cleanup();
}
// Vulkan is used for the graphics card but does not create a Window.
// We need a Window to handle this.
void DSEngine::InitWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_Window = glfwCreateWindow(DEFAULTWIDTH, DEFAULTHEIGHT, "DSEngine", nullptr, nullptr);
}

void DSEngine::MainLoop()
{
    while (!glfwWindowShouldClose(m_Window)) {
        glfwPollEvents();
        Tick();
    }
}

void DSEngine::Tick()
{
    m_VulkanGraphics.DrawFrame();
}


void DSEngine::Cleanup()
{
    m_VulkanGraphics.Cleanup();
}
