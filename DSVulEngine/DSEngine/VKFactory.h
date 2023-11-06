#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

class VKFactory {
    public:
        VKFactory();
        ~VKFactory();
private:

    VkInstance m_Instance;
    void CreateInstance();
};