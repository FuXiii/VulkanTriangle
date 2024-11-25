#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
#define USE_WINDOWS_PLATFORM
#elif defined(__linux) || defined(__linux__)
#define USE_LINUX_PLATFORM
#elif defined(__APPLE__)
#define USE_APPLE_PLATFORM
#endif

#if defined(USE_WINDOWS_PLATFORM)
#include <Windows.h>
#elif defined(USE_LINUX_PLATFORM) || defined(USE_APPLE_PLATFORM)
#include <dlfcn.h>
#include <stdlib.h>
#endif

#include <vulkan/vulkan.h>

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <GLFW/glfw3.h>

#include <glm/ext.hpp>

#include "VkString.h"

static const uint32_t MY_VERT_SHADER_BIN[] = {0x07230203, 0x00010000, 0x0008000b, 0x00000034, 0x00000000, 0x00020011, 0x00000001, 0x0006000b, 0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001, 0x0008000f, 0x00000000, 0x00000004, 0x6e69616d, 0x00000000, 0x00000008, 0x00000016, 0x0000001f, 0x00030003, 0x00000002, 0x000001c2, 0x00040005, 0x00000004, 0x6e69616d, 0x00000000, 0x00060005, 0x00000008, 0x565f6c67, 0x65747265, 0x646e4978, 0x00007865, 0x00060005, 0x00000014, 0x505f6c67, 0x65567265, 0x78657472, 0x00000000, 0x00060006, 0x00000014, 0x00000000, 0x505f6c67, 0x7469736f, 0x006e6f69, 0x00070006, 0x00000014, 0x00000001, 0x505f6c67, 0x746e696f, 0x657a6953, 0x00000000, 0x00070006, 0x00000014, 0x00000002, 0x435f6c67, 0x4470696c, 0x61747369, 0x0065636e, 0x00070006, 0x00000014, 0x00000003, 0x435f6c67, 0x446c6c75, 0x61747369, 0x0065636e, 0x00030005, 0x00000016, 0x00000000, 0x00040005, 0x0000001f, 0x6f6c6f63, 0x00000072, 0x00040047, 0x00000008, 0x0000000b, 0x0000002a, 0x00050048, 0x00000014, 0x00000000, 0x0000000b, 0x00000000, 0x00050048, 0x00000014, 0x00000001, 0x0000000b, 0x00000001, 0x00050048, 0x00000014, 0x00000002, 0x0000000b, 0x00000003, 0x00050048, 0x00000014, 0x00000003, 0x0000000b, 0x00000004, 0x00030047, 0x00000014, 0x00000002, 0x00040047, 0x0000001f, 0x0000001e, 0x00000000, 0x00020013, 0x00000002, 0x00030021, 0x00000003, 0x00000002, 0x00040015, 0x00000006, 0x00000020, 0x00000001, 0x00040020, 0x00000007, 0x00000001, 0x00000006, 0x0004003b, 0x00000007, 0x00000008, 0x00000001, 0x0004002b, 0x00000006, 0x0000000a, 0x00000000, 0x00020014, 0x0000000b, 0x00030016, 0x0000000f, 0x00000020, 0x00040017, 0x00000010, 0x0000000f, 0x00000004, 0x00040015, 0x00000011, 0x00000020, 0x00000000, 0x0004002b, 0x00000011, 0x00000012, 0x00000001, 0x0004001c, 0x00000013, 0x0000000f, 0x00000012, 0x0006001e, 0x00000014, 0x00000010, 0x0000000f, 0x00000013, 0x00000013, 0x00040020, 0x00000015, 0x00000003, 0x00000014, 0x0004003b, 0x00000015, 0x00000016, 0x00000003, 0x0004002b, 0x0000000f, 0x00000017, 0x00000000, 0x0004002b, 0x0000000f, 0x00000018, 0xbf000000, 0x0004002b, 0x0000000f, 0x00000019, 0x3f800000, 0x0007002c, 0x00000010, 0x0000001a, 0x00000017, 0x00000018, 0x00000017, 0x00000019, 0x00040020, 0x0000001b, 0x00000003, 0x00000010, 0x00040017, 0x0000001d, 0x0000000f, 0x00000003, 0x00040020, 0x0000001e, 0x00000003, 0x0000001d, 0x0004003b, 0x0000001e, 0x0000001f, 0x00000003, 0x0006002c, 0x0000001d, 0x00000020, 0x00000019, 0x00000017, 0x00000017, 0x0004002b, 0x00000006, 0x00000023, 0x00000001, 0x0004002b, 0x0000000f, 0x00000027, 0x3f000000, 0x0007002c, 0x00000010, 0x00000028, 0x00000027, 0x00000027, 0x00000017, 0x00000019, 0x0006002c, 0x0000001d, 0x0000002a, 0x00000017, 0x00000019, 0x00000017, 0x0004002b, 0x00000006, 0x0000002d, 0x00000002, 0x0007002c, 0x00000010, 0x00000031, 0x00000018, 0x00000027, 0x00000017, 0x00000019, 0x0006002c, 0x0000001d, 0x00000033, 0x00000017, 0x00000017, 0x00000019, 0x00050036, 0x00000002, 0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x0004003d, 0x00000006, 0x00000009, 0x00000008, 0x000500aa, 0x0000000b, 0x0000000c, 0x00000009, 0x0000000a, 0x000300f7, 0x0000000e, 0x00000000, 0x000400fa, 0x0000000c, 0x0000000d, 0x00000021, 0x000200f8, 0x0000000d, 0x00050041, 0x0000001b, 0x0000001c, 0x00000016, 0x0000000a, 0x0003003e, 0x0000001c, 0x0000001a, 0x0003003e, 0x0000001f, 0x00000020, 0x000200f9, 0x0000000e, 0x000200f8, 0x00000021, 0x0004003d, 0x00000006, 0x00000022, 0x00000008, 0x000500aa, 0x0000000b, 0x00000024, 0x00000022, 0x00000023, 0x000300f7, 0x00000026, 0x00000000, 0x000400fa, 0x00000024, 0x00000025, 0x0000002b, 0x000200f8, 0x00000025, 0x00050041, 0x0000001b, 0x00000029, 0x00000016, 0x0000000a, 0x0003003e, 0x00000029, 0x00000028, 0x0003003e, 0x0000001f, 0x0000002a, 0x000200f9, 0x00000026, 0x000200f8, 0x0000002b, 0x0004003d, 0x00000006, 0x0000002c, 0x00000008, 0x000500aa, 0x0000000b, 0x0000002e, 0x0000002c, 0x0000002d, 0x000300f7, 0x00000030, 0x00000000, 0x000400fa, 0x0000002e, 0x0000002f, 0x00000030, 0x000200f8, 0x0000002f, 0x00050041, 0x0000001b, 0x00000032, 0x00000016, 0x0000000a, 0x0003003e, 0x00000032, 0x00000031, 0x0003003e, 0x0000001f, 0x00000033, 0x000200f9, 0x00000030, 0x000200f8, 0x00000030, 0x000200f9, 0x00000026, 0x000200f8, 0x00000026, 0x000200f9, 0x0000000e, 0x000200f8, 0x0000000e, 0x000100fd, 0x00010038};

static const uint32_t MY_FRAG_SHADER_BIN[] = {0x07230203, 0x00010000, 0x0008000b, 0x00000013, 0x00000000, 0x00020011, 0x00000001, 0x0006000b, 0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001, 0x0007000f, 0x00000004, 0x00000004, 0x6e69616d, 0x00000000, 0x00000009, 0x0000000c, 0x00030010, 0x00000004, 0x00000007, 0x00030003, 0x00000002, 0x000001c2, 0x00040005, 0x00000004, 0x6e69616d, 0x00000000, 0x00050005, 0x00000009, 0x4374756f, 0x726f6c6f, 0x00000000, 0x00040005, 0x0000000c, 0x6f6c6f63, 0x00000072, 0x00040047, 0x00000009, 0x0000001e, 0x00000000, 0x00040047, 0x0000000c, 0x0000001e, 0x00000000, 0x00020013, 0x00000002, 0x00030021, 0x00000003, 0x00000002, 0x00030016, 0x00000006, 0x00000020, 0x00040017, 0x00000007, 0x00000006, 0x00000004, 0x00040020, 0x00000008, 0x00000003, 0x00000007, 0x0004003b, 0x00000008, 0x00000009, 0x00000003, 0x00040017, 0x0000000a, 0x00000006, 0x00000003, 0x00040020, 0x0000000b, 0x00000001, 0x0000000a, 0x0004003b, 0x0000000b, 0x0000000c, 0x00000001, 0x0004002b, 0x00000006, 0x0000000e, 0x3f800000, 0x00050036, 0x00000002, 0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x0004003d, 0x0000000a, 0x0000000d, 0x0000000c, 0x00050051, 0x00000006, 0x0000000f, 0x0000000d, 0x00000000, 0x00050051, 0x00000006, 0x00000010, 0x0000000d, 0x00000001, 0x00050051, 0x00000006, 0x00000011, 0x0000000d, 0x00000002, 0x00070050, 0x00000007, 0x00000012, 0x0000000f, 0x00000010, 0x00000011, 0x0000000e, 0x0003003e, 0x00000009, 0x00000012, 0x000100fd, 0x00010038};

struct VkDriver
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = nullptr;
    PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion = nullptr;
    PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties = nullptr;
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties = nullptr;
    PFN_vkCreateInstance vkCreateInstance = nullptr;
    PFN_vkDestroyInstance vkDestroyInstance = nullptr;

    PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices = nullptr;
    PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties = nullptr;
    PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties = nullptr;

    PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties = nullptr;

    PFN_vkCreateDevice vkCreateDevice = nullptr;
    PFN_vkDestroyDevice vkDestroyDevice = nullptr;

    PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr = nullptr;

    PFN_vkCreatePipelineLayout vkCreatePipelineLayout = nullptr;
    PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout = nullptr;
    PFN_vkGetDeviceQueue vkGetDeviceQueue = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties = nullptr;
    PFN_vkQueuePresentKHR vkQueuePresentKHR = nullptr;

    PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties = nullptr;

    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR = nullptr;

    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR = nullptr;
    PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR = nullptr;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR = nullptr;
    PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR = nullptr;

    PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR = nullptr;

    PFN_vkCreateImage vkCreateImage = nullptr;
    PFN_vkDestroyImage vkDestroyImage = nullptr;

    PFN_vkCreateImageView vkCreateImageView = nullptr;
    PFN_vkDestroyImageView vkDestroyImageView = nullptr;

    PFN_vkCreateCommandPool vkCreateCommandPool = nullptr;
    PFN_vkDestroyCommandPool vkDestroyCommandPool = nullptr;

    PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers = nullptr;
    PFN_vkFreeCommandBuffers vkFreeCommandBuffers = nullptr;

    PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements = nullptr;
    PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements = nullptr;

    PFN_vkAllocateMemory vkAllocateMemory = nullptr;
    PFN_vkFreeMemory vkFreeMemory = nullptr;

    PFN_vkBindImageMemory vkBindImageMemory = nullptr;
    PFN_vkBindBufferMemory vkBindBufferMemory = nullptr;

    PFN_vkCreateBuffer vkCreateBuffer = nullptr;
    PFN_vkDestroyBuffer vkDestroyBuffer = nullptr;

    PFN_vkBeginCommandBuffer vkBeginCommandBuffer = nullptr;
    PFN_vkEndCommandBuffer vkEndCommandBuffer = nullptr;

    PFN_vkMapMemory vkMapMemory = nullptr;
    PFN_vkUnmapMemory vkUnmapMemory = nullptr;

    PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier = nullptr;

    PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage = nullptr;

    PFN_vkQueueSubmit vkQueueSubmit = nullptr;

    PFN_vkCreateFence vkCreateFence = nullptr;
    PFN_vkDestroyFence vkDestroyFence = nullptr;

    PFN_vkWaitForFences vkWaitForFences = nullptr;

    PFN_vkCreateShaderModule vkCreateShaderModule = nullptr;
    PFN_vkDestroyShaderModule vkDestroyShaderModule = nullptr;

    PFN_vkCreateDescriptorPool vkCreateDescriptorPool = nullptr;
    PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool = nullptr;

    PFN_vkCreateRenderPass vkCreateRenderPass = nullptr;
    PFN_vkDestroyRenderPass vkDestroyRenderPass = nullptr;

    PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines = nullptr;
    PFN_vkDestroyPipeline vkDestroyPipeline = nullptr;

    PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout = nullptr;
    PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout = nullptr;

    PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR = nullptr;

    PFN_vkCreateSampler vkCreateSampler = nullptr;
    PFN_vkDestroySampler vkDestroySampler = nullptr;

    PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets = nullptr;
    PFN_vkFreeDescriptorSets vkFreeDescriptorSets = nullptr;

    PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets = nullptr;

    PFN_vkCreateFramebuffer vkCreateFramebuffer = nullptr;
    PFN_vkDestroyFramebuffer vkDestroyFramebuffer = nullptr;

    PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass = nullptr;
    PFN_vkCmdEndRenderPass vkCmdEndRenderPass = nullptr;
    PFN_vkCmdBindPipeline vkCmdBindPipeline = nullptr;
    PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets = nullptr;
    PFN_vkCmdSetViewport vkCmdSetViewport = nullptr;
    PFN_vkCmdSetScissor vkCmdSetScissor = nullptr;

    PFN_vkCmdPushConstants vkCmdPushConstants = nullptr;
    PFN_vkCmdDraw vkCmdDraw = nullptr;
};

int main()
{
    VkDriver driver = {};

#if defined(USE_WINDOWS_PLATFORM)
    HMODULE library = LoadLibraryA("vulkan-1.dll");
    if (!library)
    {
        throw std::runtime_error("Can not found vulkan loader(vulkan-1.dll)!");
    }

    driver.vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(library, "vkGetInstanceProcAddr");
    assert(driver.vkGetInstanceProcAddr && "vkGetInstanceProcAddr");
#elif defined(USE_LINUX_PLATFORM)
    void *library = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
    if (!library)
    {
        library = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
    }

    if (!library)
    {
        throw std::runtime_error("Can not found vulkan loader(libvulkan.so/libvulkan.so.1)!");
    }

    driver.vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)dlsym(library, "vkGetInstanceProcAddr");
    assert(driver.vkGetInstanceProcAddr && "vkGetInstanceProcAddr");
#elif defined(USE_APPLE_PLATFORM)
    void *library = dlopen("libvulkan.dylib", RTLD_NOW | RTLD_LOCAL);
    if (!library)
    {
        library = dlopen("libvulkan.1.dylib", RTLD_NOW | RTLD_LOCAL);
    }
    if (!library)
    {
        library = dlopen("libMoltenVK.dylib", RTLD_NOW | RTLD_LOCAL);
    }
    if (!library)
    {
        library = dlopen("vulkan.framework/vulkan", RTLD_NOW | RTLD_LOCAL);
    }
    if (!library)
    {
        library = dlopen("MoltenVK.framework/MoltenVK", RTLD_NOW | RTLD_LOCAL);
    }
    if (!library && getenv("DYLD_FALLBACK_LIBRARY_PATH") == NULL)
    {
        library = dlopen("/usr/local/lib/libvulkan.dylib", RTLD_NOW | RTLD_LOCAL);
    }

    if (!library)
    {
        throw std::runtime_error("Can not found vulkan loader(MoltenVK)!");
    }

    driver.vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)dlsym(library, "vkGetInstanceProcAddr");
    assert(driver.vkGetInstanceProcAddr && "vkGetInstanceProcAddr");
#else
    throw std::runtime_error("Not compatible with this platform!");
#endif
    uint32_t support_vulkan_version = VK_MAKE_API_VERSION(0, 0, 0, 0);
    {
        driver.vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion)driver.vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceVersion");
        if (driver.vkEnumerateInstanceVersion != nullptr)
        {
            driver.vkEnumerateInstanceVersion(&support_vulkan_version);
        }
        else
        {
            support_vulkan_version = VK_API_VERSION_1_0;
        }

        assert(support_vulkan_version && "Not support Vulkan!");
    }

    auto version_major = VK_VERSION_MAJOR(support_vulkan_version);
    auto version_minor = VK_VERSION_MINOR(support_vulkan_version);
    auto version_patch = VK_VERSION_PATCH(support_vulkan_version);

    std::cout << "Support Vulkan: " << version_major << "." << version_minor << "." << version_patch << std::endl;

    {
        driver.vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties)driver.vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceLayerProperties");
        assert(driver.vkEnumerateInstanceLayerProperties && "vkEnumerateInstanceLayerProperties");

        driver.vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties)driver.vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
        assert(driver.vkEnumerateInstanceExtensionProperties && "vkEnumerateInstanceExtensionProperties");
    }

    driver.vkCreateInstance = (PFN_vkCreateInstance)driver.vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkCreateInstance");
    assert(driver.vkCreateInstance && "vkCreateInstance");

    VkApplicationInfo vk_application_info = {};
    vk_application_info.sType = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vk_application_info.pNext = nullptr;
    vk_application_info.pApplicationName = nullptr;
    vk_application_info.applicationVersion = 0;
    vk_application_info.pEngineName = nullptr;
    vk_application_info.engineVersion = 0;
    vk_application_info.apiVersion = support_vulkan_version;

    std::vector<std::string> enable_instance_layers;
    {
        uint32_t instance_layer_count = 0;
        driver.vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr);
        std::vector<VkLayerProperties> layer_properties(instance_layer_count);
        driver.vkEnumerateInstanceLayerProperties(&instance_layer_count, layer_properties.data());

        for (auto &layer_property : layer_properties)
        {
            std::cout << "[layer]: " << layer_property.layerName << " - (" << layer_property.description << ")" << std::endl;

            if (std::string(layer_property.layerName) == std::string("VK_LAYER_KHRONOS_validation"))
            {
                enable_instance_layers.push_back(layer_property.layerName);
            }
        }
    }
    std::vector<const char *> instance_enabled_layers;
    for (auto &enable_layer : enable_instance_layers)
    {
        instance_enabled_layers.push_back(enable_layer.c_str());
    }

    std::vector<std::string> enabled_instance_extensions;
    {
        uint32_t instance_extension_count = 0;
        driver.vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, nullptr);
        std::vector<VkExtensionProperties> extension_properties(instance_extension_count);
        driver.vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, extension_properties.data());

        for (auto &extension_property : extension_properties)
        {
            std::cout << "[instance-extension]: " << extension_property.extensionName << std::endl;

            if (std::string(extension_property.extensionName) == std::string(VK_KHR_SURFACE_EXTENSION_NAME)) // "VK_KHR_surface"
            {
                enabled_instance_extensions.push_back(extension_property.extensionName);
            }
#if defined(USE_WINDOWS_PLATFORM)
            else if (std::string(extension_property.extensionName) == std::string("VK_KHR_win32_surface")) // VK_KHR_WIN32_SURFACE_EXTENSION_NAME
            {
                enabled_instance_extensions.push_back(extension_property.extensionName);
            }
#elif defined(USE_LINUX_PLATFORM)
            else if (std::string(extension_property.extensionName) == std::string("VK_KHR_wayland_surface")) // VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
            {
                enabled_instance_extensions.push_back(extension_property.extensionName);
            }
            else if (std::string(extension_property.extensionName) == std::string("VK_KHR_xlib_surface")) // VK_KHR_XLIB_SURFACE_EXTENSION_NAME
            {
                enabled_instance_extensions.push_back(extension_property.extensionName);
            }
            else if (std::string(extension_property.extensionName) == std::string("VK_KHR_xcb_surface")) // VK_KHR_XCB_SURFACE_EXTENSION_NAME
            {
                enabled_instance_extensions.push_back(extension_property.extensionName);
            }
#elif defined(USE_APPLE_PLATFORM)
            else if (std::string(extension_property.extensionName) == std::string("VK_EXT_metal_surface")) // VK_EXT_METAL_SURFACE_EXTENSION_NAME
            {
                enabled_instance_extensions.push_back(extension_property.extensionName);
            }
            /* Deprecated and has been superseded by the VK_EXT_metal_surface extension on 2018-10-01
                else if (std::string(extension_property.extensionName) == std::string("VK_MVK_macos_surface")) // VK_MVK_MACOS_SURFACE_EXTENSION_NAME
                {
                    enabled_instance_extensions.push_back(extension_property.extensionName);
                }
                else if (std::string(extension_property.extensionName) == std::string("VK_MVK_ios_surface")) // VK_MVK_IOS_SURFACE_EXTENSION_NAME
                {
                    enabled_instance_extensions.push_back(extension_property.extensionName);
                }
            */
#else
            throw std::runtime_error("Surface Not compatible with this platform!");
#endif
        }
    }

    if (enabled_instance_extensions.empty())
    {
        throw std::runtime_error("Can not find Surface extension support!");
    }

    std::vector<const char *> instance_enabled_extensions;
    for (auto &enable_extension : enabled_instance_extensions)
    {
        instance_enabled_extensions.push_back(enable_extension.c_str());
    }

    VkInstanceCreateInfo vk_instance_create_info = {};
    vk_instance_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vk_instance_create_info.pNext = nullptr;
    vk_instance_create_info.flags = 0;
    vk_instance_create_info.pApplicationInfo = &vk_application_info;
    vk_instance_create_info.enabledLayerCount = instance_enabled_layers.size();
    vk_instance_create_info.ppEnabledLayerNames = instance_enabled_layers.data();
    vk_instance_create_info.enabledExtensionCount = instance_enabled_extensions.size();
    vk_instance_create_info.ppEnabledExtensionNames = instance_enabled_extensions.data();

    VkInstance vk_instance = VK_NULL_HANDLE;
    VkResult result = driver.vkCreateInstance(&vk_instance_create_info, nullptr, &vk_instance);
    if (result != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateInstance failed!");
    }
    else
    {
        std::cout << "vkCreateInstance success" << std::endl;
    }

    driver.vkDestroyInstance = (PFN_vkDestroyInstance)driver.vkGetInstanceProcAddr(vk_instance, "vkDestroyInstance");
    assert(driver.vkDestroyInstance && "vkDestroyInstance");

    driver.vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)driver.vkGetInstanceProcAddr(vk_instance, "vkEnumeratePhysicalDevices");
    assert(driver.vkEnumeratePhysicalDevices && "vkEnumeratePhysicalDevices");

    driver.vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)driver.vkGetInstanceProcAddr(vk_instance, "vkGetPhysicalDeviceProperties");
    assert(driver.vkGetPhysicalDeviceProperties && "vkEnumeratePhysicalDevices");

    driver.vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)driver.vkGetInstanceProcAddr(vk_instance, "vkEnumerateDeviceExtensionProperties");
    assert(driver.vkEnumerateDeviceExtensionProperties && "vkEnumerateDeviceExtensionProperties");

    driver.vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)driver.vkGetInstanceProcAddr(vk_instance, "vkGetPhysicalDeviceFormatProperties");
    assert(driver.vkGetPhysicalDeviceFormatProperties && "vkGetPhysicalDeviceFormatProperties");

    driver.vkCreateDevice = (PFN_vkCreateDevice)driver.vkGetInstanceProcAddr(vk_instance, "vkCreateDevice");
    assert(driver.vkCreateDevice && "vkCreateDevice");

    driver.vkDestroyDevice = (PFN_vkDestroyDevice)driver.vkGetInstanceProcAddr(vk_instance, "vkDestroyDevice");
    assert(driver.vkDestroyDevice && "vkDestroyDevice");

    driver.vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)driver.vkGetInstanceProcAddr(vk_instance, "vkGetDeviceProcAddr");
    assert(driver.vkGetDeviceProcAddr && "vkGetDeviceProcAddr");

    driver.vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)driver.vkGetInstanceProcAddr(vk_instance, "vkGetPhysicalDeviceQueueFamilyProperties");
    assert(driver.vkGetPhysicalDeviceQueueFamilyProperties && "vkGetPhysicalDeviceQueueFamilyProperties");

    driver.vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)driver.vkGetInstanceProcAddr(vk_instance, "vkGetPhysicalDeviceMemoryProperties");
    assert(driver.vkGetPhysicalDeviceMemoryProperties && "vkGetPhysicalDeviceMemoryProperties");

    uint32_t physcial_device_count = 0;
    result = driver.vkEnumeratePhysicalDevices(vk_instance, &physcial_device_count, nullptr);
    if (result != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("vkEnumeratePhysicalDevices get count failed!");
    }

    std::vector<VkPhysicalDevice> physcail_devices(physcial_device_count);
    result = driver.vkEnumeratePhysicalDevices(vk_instance, &physcial_device_count, physcail_devices.data());
    if (result != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("vkEnumeratePhysicalDevices failed!");
    }

    VkPhysicalDevice target_physical_device = VK_NULL_HANDLE;
    std::string target_physical_device_name;
    for (VkPhysicalDevice physcail_devices_item : physcail_devices)
    {
        VkPhysicalDeviceProperties vk_physical_device_properties = {};
        driver.vkGetPhysicalDeviceProperties(physcail_devices_item, &vk_physical_device_properties);

        if (vk_physical_device_properties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            target_physical_device = physcail_devices_item;
            target_physical_device_name = std::string(vk_physical_device_properties.deviceName);
            break;
        }
        else if (vk_physical_device_properties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
        {
            target_physical_device = physcail_devices_item;
            target_physical_device_name = std::string(vk_physical_device_properties.deviceName);
        }
    }

    if (target_physical_device == VK_NULL_HANDLE)
    {
        throw std::runtime_error("Not found suitable GPU!");
    }
    else
    {
        std::cout << "Select Physical Device:" << target_physical_device_name << std::endl;
    }

    uint32_t queue_family_count = 0;
    driver.vkGetPhysicalDeviceQueueFamilyProperties(target_physical_device, &queue_family_count, nullptr);
    std::vector<VkQueueFamilyProperties> vk_queue_family_properties(queue_family_count);
    driver.vkGetPhysicalDeviceQueueFamilyProperties(target_physical_device, &queue_family_count, vk_queue_family_properties.data());

    std::vector<VkDeviceQueueCreateInfo> vk_device_queue_create_infos;
    uint32_t graphics_queue_family_index = 0;
    float queue_prioritie = 0;
    for (uint32_t queue_family_index = 0; queue_family_index < queue_family_count; queue_family_index++)
    {
        if (vk_queue_family_properties[queue_family_index].queueCount > 0 && (vk_queue_family_properties[queue_family_index].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) == VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT)
        {
            VkDeviceQueueCreateInfo vk_device_queue_create_info = {};
            vk_device_queue_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            vk_device_queue_create_info.pNext = nullptr;
            vk_device_queue_create_info.flags = 0;
            vk_device_queue_create_info.queueFamilyIndex = queue_family_index;
            vk_device_queue_create_info.queueCount = 1;
            vk_device_queue_create_info.pQueuePriorities = &queue_prioritie;
            vk_device_queue_create_infos.push_back(vk_device_queue_create_info);

            graphics_queue_family_index = vk_device_queue_create_info.queueFamilyIndex;

            break;
        }
    }

    if (vk_device_queue_create_infos.empty())
    {
        throw std::runtime_error("Not found support graphics queue!");
    }

    std::vector<std::string> enable_device_extensions;
    {
        // Provided by VK_VERSION_1_0
        uint32_t device_extension_count = 0;
        driver.vkEnumerateDeviceExtensionProperties(target_physical_device, nullptr, &device_extension_count, nullptr);
        std::vector<VkExtensionProperties> extension_properties(device_extension_count);
        driver.vkEnumerateDeviceExtensionProperties(target_physical_device, nullptr, &device_extension_count, extension_properties.data());

        for (auto &extension_property : extension_properties)
        {
            std::cout << "[device-extension]: " << extension_property.extensionName << std::endl;

            if (std::string(extension_property.extensionName) == std::string(VK_KHR_SWAPCHAIN_EXTENSION_NAME)) // "VK_KHR_swapchain"
            {
                enable_device_extensions.push_back(extension_property.extensionName);
            }
        }
    }

    if (enable_device_extensions.empty())
    {
        throw std::runtime_error("Can not find Swapchain extension!");
    }

    std::vector<const char *> device_enabled_extension_names;
    for (auto &enable_extension : enable_device_extensions)
    {
        device_enabled_extension_names.push_back(enable_extension.c_str());
    }

    VkDeviceCreateInfo vk_device_create_info = {};
    vk_device_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    vk_device_create_info.pNext = nullptr;
    vk_device_create_info.flags = 0;
    vk_device_create_info.queueCreateInfoCount = vk_device_queue_create_infos.size();
    vk_device_create_info.pQueueCreateInfos = vk_device_queue_create_infos.data();
    vk_device_create_info.enabledLayerCount = 0;
    vk_device_create_info.ppEnabledLayerNames = nullptr;
    vk_device_create_info.enabledExtensionCount = device_enabled_extension_names.size();
    vk_device_create_info.ppEnabledExtensionNames = device_enabled_extension_names.data();
    vk_device_create_info.pEnabledFeatures = nullptr;

    VkDevice vk_device = VK_NULL_HANDLE;
    result = driver.vkCreateDevice(target_physical_device, &vk_device_create_info, nullptr, &vk_device);
    if (result != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateDevice failed!");
    }
    std::cout << "vkCreateDevice success" << std::endl;

    {
        driver.vkCreateImage = (PFN_vkCreateImage)driver.vkGetDeviceProcAddr(vk_device, "vkCreateImage");
        assert(driver.vkCreateImage && "vkCreateImage");

        driver.vkDestroyImage = (PFN_vkDestroyImage)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyImage");
        assert(driver.vkDestroyImage && "vkDestroyImage");

        driver.vkCreateImageView = (PFN_vkCreateImageView)driver.vkGetDeviceProcAddr(vk_device, "vkCreateImageView");
        assert(driver.vkCreateImageView && "vkCreateImageView");

        driver.vkDestroyImageView = (PFN_vkDestroyImageView)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyImageView");
        assert(driver.vkDestroyImageView && "vkDestroyImageView");

        driver.vkCreateCommandPool = (PFN_vkCreateCommandPool)driver.vkGetDeviceProcAddr(vk_device, "vkCreateCommandPool");
        assert(driver.vkCreateCommandPool && "vkCreateCommandPool");

        driver.vkDestroyCommandPool = (PFN_vkDestroyCommandPool)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyCommandPool");
        assert(driver.vkDestroyCommandPool && "vkDestroyCommandPool");

        driver.vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)driver.vkGetDeviceProcAddr(vk_device, "vkAllocateCommandBuffers");
        assert(driver.vkAllocateCommandBuffers && "vkAllocateCommandBuffers");

        driver.vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)driver.vkGetDeviceProcAddr(vk_device, "vkFreeCommandBuffers");
        assert(driver.vkFreeCommandBuffers && "vkFreeCommandBuffers");

        driver.vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)driver.vkGetDeviceProcAddr(vk_device, "vkGetBufferMemoryRequirements");
        assert(driver.vkGetBufferMemoryRequirements && "vkGetBufferMemoryRequirements");

        driver.vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)driver.vkGetDeviceProcAddr(vk_device, "vkGetImageMemoryRequirements");
        assert(driver.vkGetImageMemoryRequirements && "vkGetImageMemoryRequirements");

        driver.vkAllocateMemory = (PFN_vkAllocateMemory)driver.vkGetDeviceProcAddr(vk_device, "vkAllocateMemory");
        assert(driver.vkAllocateMemory && "vkAllocateMemory");

        driver.vkFreeMemory = (PFN_vkFreeMemory)driver.vkGetDeviceProcAddr(vk_device, "vkFreeMemory");
        assert(driver.vkFreeMemory && "vkFreeMemory");

        driver.vkBindImageMemory = (PFN_vkBindImageMemory)driver.vkGetDeviceProcAddr(vk_device, "vkBindImageMemory");
        assert(driver.vkBindImageMemory && "vkBindImageMemory");

        driver.vkBindBufferMemory = (PFN_vkBindBufferMemory)driver.vkGetDeviceProcAddr(vk_device, "vkBindBufferMemory");
        assert(driver.vkBindBufferMemory && "vkBindBufferMemory");

        driver.vkCreateBuffer = (PFN_vkCreateBuffer)driver.vkGetDeviceProcAddr(vk_device, "vkCreateBuffer");
        assert(driver.vkCreateBuffer && "vkCreateBuffer");

        driver.vkDestroyBuffer = (PFN_vkDestroyBuffer)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyBuffer");
        assert(driver.vkDestroyBuffer && "vkDestroyBuffer");

        driver.vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)driver.vkGetDeviceProcAddr(vk_device, "vkBeginCommandBuffer");
        assert(driver.vkBeginCommandBuffer && "vkBeginCommandBuffer");

        driver.vkEndCommandBuffer = (PFN_vkEndCommandBuffer)driver.vkGetDeviceProcAddr(vk_device, "vkEndCommandBuffer");
        assert(driver.vkEndCommandBuffer && "vkEndCommandBuffer");

        driver.vkMapMemory = (PFN_vkMapMemory)driver.vkGetDeviceProcAddr(vk_device, "vkMapMemory");
        assert(driver.vkMapMemory && "vkMapMemory");

        driver.vkUnmapMemory = (PFN_vkUnmapMemory)driver.vkGetDeviceProcAddr(vk_device, "vkUnmapMemory");
        assert(driver.vkUnmapMemory && "vkUnmapMemory");

        driver.vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)driver.vkGetDeviceProcAddr(vk_device, "vkCmdPipelineBarrier");
        assert(driver.vkCmdPipelineBarrier && "vkCmdPipelineBarrier");

        driver.vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)driver.vkGetDeviceProcAddr(vk_device, "vkCmdCopyBufferToImage");
        assert(driver.vkCmdCopyBufferToImage && "vkCmdCopyBufferToImage");

        driver.vkQueueSubmit = (PFN_vkQueueSubmit)driver.vkGetDeviceProcAddr(vk_device, "vkQueueSubmit");
        assert(driver.vkQueueSubmit && "vkQueueSubmit");

        driver.vkCreateFence = (PFN_vkCreateFence)driver.vkGetDeviceProcAddr(vk_device, "vkCreateFence");
        assert(driver.vkCreateFence && "vkCreateFence");

        driver.vkDestroyFence = (PFN_vkDestroyFence)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyFence");
        assert(driver.vkDestroyFence && "vkDestroyFence");

        driver.vkWaitForFences = (PFN_vkWaitForFences)driver.vkGetDeviceProcAddr(vk_device, "vkWaitForFences");
        assert(driver.vkWaitForFences && "vkWaitForFences");

        driver.vkCreateShaderModule = (PFN_vkCreateShaderModule)driver.vkGetDeviceProcAddr(vk_device, "vkCreateShaderModule");
        assert(driver.vkCreateShaderModule && "vkCreateShaderModule");

        driver.vkDestroyShaderModule = (PFN_vkDestroyShaderModule)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyShaderModule");
        assert(driver.vkDestroyShaderModule && "vkDestroyShaderModule");

        driver.vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)driver.vkGetDeviceProcAddr(vk_device, "vkCreateDescriptorPool");
        assert(driver.vkCreateDescriptorPool && "vkCreateDescriptorPool");

        driver.vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyDescriptorPool");
        assert(driver.vkDestroyDescriptorPool && "vkDestroyDescriptorPool");

        driver.vkCreateRenderPass = (PFN_vkCreateRenderPass)driver.vkGetDeviceProcAddr(vk_device, "vkCreateRenderPass");
        assert(driver.vkCreateRenderPass && "vkCreateRenderPass");

        driver.vkDestroyRenderPass = (PFN_vkDestroyRenderPass)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyRenderPass");
        assert(driver.vkDestroyRenderPass && "vkDestroyRenderPass");

        driver.vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)driver.vkGetDeviceProcAddr(vk_device, "vkCreateGraphicsPipelines");
        assert(driver.vkCreateGraphicsPipelines && "vkCreateGraphicsPipelines");

        driver.vkDestroyPipeline = (PFN_vkDestroyPipeline)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyPipeline");
        assert(driver.vkDestroyPipeline && "vkDestroyPipeline");

        driver.vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)driver.vkGetDeviceProcAddr(vk_device, "vkCreateDescriptorSetLayout");
        assert(driver.vkCreateDescriptorSetLayout && "vkDestroyPipeline");

        driver.vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyDescriptorSetLayout");
        assert(driver.vkDestroyDescriptorSetLayout && "vkDestroyDescriptorSetLayout");

        driver.vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)driver.vkGetDeviceProcAddr(vk_device, "vkAcquireNextImageKHR");
        assert(driver.vkAcquireNextImageKHR && "vkAcquireNextImageKHR");

        driver.vkCreateSampler = (PFN_vkCreateSampler)driver.vkGetDeviceProcAddr(vk_device, "vkCreateSampler");
        assert(driver.vkCreateSampler && "vkCreateSampler");

        driver.vkDestroySampler = (PFN_vkDestroySampler)driver.vkGetDeviceProcAddr(vk_device, "vkDestroySampler");
        assert(driver.vkDestroySampler && "vkDestroySampler");

        driver.vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)driver.vkGetDeviceProcAddr(vk_device, "vkAllocateDescriptorSets");
        assert(driver.vkAllocateDescriptorSets && "vkAllocateDescriptorSets");

        driver.vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets)driver.vkGetDeviceProcAddr(vk_device, "vkFreeDescriptorSets");
        assert(driver.vkFreeDescriptorSets && "vkFreeDescriptorSets");

        driver.vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)driver.vkGetDeviceProcAddr(vk_device, "vkUpdateDescriptorSets");
        assert(driver.vkUpdateDescriptorSets && "vkUpdateDescriptorSets");

        driver.vkCreateFramebuffer = (PFN_vkCreateFramebuffer)driver.vkGetDeviceProcAddr(vk_device, "vkCreateFramebuffer");
        assert(driver.vkCreateFramebuffer && "vkCreateFramebuffer");

        driver.vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyFramebuffer");
        assert(driver.vkDestroyFramebuffer && "vkDestroyFramebuffer");

        driver.vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)driver.vkGetDeviceProcAddr(vk_device, "vkCmdBeginRenderPass");
        assert(driver.vkCmdBeginRenderPass && "vkCmdBeginRenderPass");

        driver.vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)driver.vkGetDeviceProcAddr(vk_device, "vkCmdEndRenderPass");
        assert(driver.vkCmdEndRenderPass && "vkCmdEndRenderPass");

        driver.vkCmdBindPipeline = (PFN_vkCmdBindPipeline)driver.vkGetDeviceProcAddr(vk_device, "vkCmdBindPipeline");
        assert(driver.vkCmdBindPipeline && "vkCmdBindPipeline");

        driver.vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)driver.vkGetDeviceProcAddr(vk_device, "vkCmdBindDescriptorSets");
        assert(driver.vkCmdBindDescriptorSets && "vkCmdBindDescriptorSets");

        driver.vkCmdSetViewport = (PFN_vkCmdSetViewport)driver.vkGetDeviceProcAddr(vk_device, "vkCmdSetViewport");
        assert(driver.vkCmdSetViewport && "vkCmdSetViewport");

        driver.vkCmdSetScissor = (PFN_vkCmdSetScissor)driver.vkGetDeviceProcAddr(vk_device, "vkCmdSetScissor");
        assert(driver.vkCmdSetScissor && "vkCmdSetScissor");

        driver.vkCmdPushConstants = (PFN_vkCmdPushConstants)driver.vkGetDeviceProcAddr(vk_device, "vkCmdPushConstants");
        assert(driver.vkCmdPushConstants && "vkCmdPushConstants");

        driver.vkCmdDraw = (PFN_vkCmdDraw)driver.vkGetDeviceProcAddr(vk_device, "vkCmdDraw");
        assert(driver.vkCmdDraw && "vkCmdDraw");
    }

    driver.vkGetDeviceQueue = (PFN_vkGetDeviceQueue)driver.vkGetDeviceProcAddr(vk_device, "vkGetDeviceQueue");
    assert(driver.vkGetDeviceQueue && "vkGetDeviceQueue");

    driver.vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)driver.vkGetDeviceProcAddr(vk_device, "vkCreatePipelineLayout");
    assert(driver.vkCreatePipelineLayout && "vkCreatePipelineLayout");

    driver.vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)driver.vkGetDeviceProcAddr(vk_device, "vkDestroyPipelineLayout");
    assert(driver.vkDestroyPipelineLayout && "vkDestroyPipelineLayout");

    driver.vkQueuePresentKHR = (PFN_vkQueuePresentKHR)driver.vkGetDeviceProcAddr(vk_device, "vkQueuePresentKHR");
    assert(driver.vkQueuePresentKHR && "vkQueuePresentKHR");

    VkQueue vk_queue = VK_NULL_HANDLE;
    driver.vkGetDeviceQueue(vk_device, graphics_queue_family_index, 0, &vk_queue);

    // code here
    auto vulkan_code = [&]() {
        uint32_t queue_family_index = graphics_queue_family_index;
        VkPhysicalDevice vk_physical_device = target_physical_device;

        VkPhysicalDeviceMemoryProperties vk_physical_device_memory_properties = {};
        driver.vkGetPhysicalDeviceMemoryProperties(vk_physical_device, &vk_physical_device_memory_properties);

        uint32_t visible_coherent_memory_index = std::numeric_limits<uint32_t>::max();
        uint32_t device_local_memory_index = std::numeric_limits<uint32_t>::max();

        for (uint32_t memory_type_index = 0; memory_type_index < vk_physical_device_memory_properties.memoryTypeCount; memory_type_index++)
        {
            VkMemoryType memory_type = vk_physical_device_memory_properties.memoryTypes[memory_type_index];
            if (((memory_type.propertyFlags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) && ((memory_type.propertyFlags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
            {
                static VkDeviceSize visible_coherent_memory_max_size = 0;
                if (vk_physical_device_memory_properties.memoryHeaps[memory_type.heapIndex].size > visible_coherent_memory_max_size)
                {
                    visible_coherent_memory_max_size = vk_physical_device_memory_properties.memoryHeaps[memory_type.heapIndex].size;
                    visible_coherent_memory_index = memory_type_index;
                };
            }

            if ((memory_type.propertyFlags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) == VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            {
                static VkDeviceSize device_local_memory_max_size = 0;
                if (vk_physical_device_memory_properties.memoryHeaps[memory_type.heapIndex].size > device_local_memory_max_size)
                {
                    device_local_memory_max_size = vk_physical_device_memory_properties.memoryHeaps[memory_type.heapIndex].size;
                    device_local_memory_index = memory_type_index;
                }
            }
        }

        std::cout << "visible coherent memory index:" << visible_coherent_memory_index << std::endl;
        std::cout << "device local memory index:" << device_local_memory_index << std::endl;

        if (visible_coherent_memory_index == std::numeric_limits<uint32_t>::max() || device_local_memory_index == std::numeric_limits<uint32_t>::max())
        {
            throw std::runtime_error("Can not find support memory!");
        }

        if (!glfwInit())
        {
            throw std::runtime_error("Can not init glfw!");
        }

        GLFWwindow *window;
        int window_width = 512;
        int window_height = 512;
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(window_width, window_height, "VulkanTriangle", NULL, NULL);
        VkSurfaceKHR vk_surface_khr = VK_NULL_HANDLE;
        glfwCreateWindowSurface(vk_instance, window, NULL, &vk_surface_khr);

        driver.vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)driver.vkGetInstanceProcAddr(vk_instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
        assert(driver.vkGetPhysicalDeviceSurfaceFormatsKHR && "vkGetPhysicalDeviceSurfaceFormatsKHR");

        driver.vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)driver.vkGetInstanceProcAddr(vk_instance, "vkDestroySurfaceKHR");
        assert(driver.vkDestroySurfaceKHR && "vkDestroySurfaceKHR");

        driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)driver.vkGetInstanceProcAddr(vk_instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
        assert(driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR && "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");

        driver.vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)driver.vkGetDeviceProcAddr(vk_device, "vkCreateSwapchainKHR");
        assert(driver.vkCreateSwapchainKHR && "vkCreateSwapchainKHR");

        driver.vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)driver.vkGetDeviceProcAddr(vk_device, "vkDestroySwapchainKHR");
        assert(driver.vkDestroySwapchainKHR && "vkDestroySwapchainKHR");

        VkSurfaceCapabilitiesKHR vk_surface_capabilities_khr = {};
        driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk_physical_device, vk_surface_khr, &vk_surface_capabilities_khr);

        driver.vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)driver.vkGetInstanceProcAddr(vk_instance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
        assert(driver.vkGetPhysicalDeviceSurfacePresentModesKHR && "vkGetPhysicalDeviceSurfacePresentModesKHR");

        uint32_t swapchain_present_mode_count = 0;
        std::vector<VkPresentModeKHR> vk_present_mode_khrs;
        driver.vkGetPhysicalDeviceSurfacePresentModesKHR(vk_physical_device, vk_surface_khr, &swapchain_present_mode_count, nullptr);
        if (swapchain_present_mode_count != 0)
        {
            vk_present_mode_khrs.resize(swapchain_present_mode_count);
            driver.vkGetPhysicalDeviceSurfacePresentModesKHR(vk_physical_device, vk_surface_khr, &swapchain_present_mode_count, vk_present_mode_khrs.data());
        }

        bool is_swapchain_support_fifo = false;
        for (VkPresentModeKHR present_mode_item : vk_present_mode_khrs)
        {
            if (present_mode_item == VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR)
            {
                is_swapchain_support_fifo = true;
            }
        }

        VkFormat target_swapchain_format = VkFormat::VK_FORMAT_UNDEFINED;
        VkColorSpaceKHR target_swapchain_color_space = VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        {
            uint32_t surface_format_count = 0;
            driver.vkGetPhysicalDeviceSurfaceFormatsKHR(vk_physical_device, vk_surface_khr, &surface_format_count, nullptr);
            std::vector<VkSurfaceFormatKHR> surface_formats(surface_format_count);
            driver.vkGetPhysicalDeviceSurfaceFormatsKHR(vk_physical_device, vk_surface_khr, &surface_format_count, surface_formats.data());
            for (auto &surface_format : surface_formats)
            {
                VkFormatProperties vk_format_properties = {};
                driver.vkGetPhysicalDeviceFormatProperties(vk_physical_device, surface_format.format, &vk_format_properties);
                if ((vk_format_properties.optimalTilingFeatures & VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT && surface_format.colorSpace == VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                {
                    target_swapchain_format = surface_format.format;
                    break;
                }
            }
        }

        if (target_swapchain_format == VkFormat::VK_FORMAT_UNDEFINED)
        {
            throw std::runtime_error("Can not find a appropriate format for swapchain as color attachment!");
        }

        std::cout << "swapchain use " << to_string(target_swapchain_format) << " format" << std::endl;

        VkSwapchainCreateInfoKHR vk_swapchain_create_info_khr = {};
        vk_swapchain_create_info_khr.sType = VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        vk_swapchain_create_info_khr.pNext = nullptr;
        vk_swapchain_create_info_khr.flags = 0;
        vk_swapchain_create_info_khr.surface = vk_surface_khr;
        vk_swapchain_create_info_khr.minImageCount = std::max(vk_surface_capabilities_khr.minImageCount, vk_surface_capabilities_khr.maxImageCount);
        vk_swapchain_create_info_khr.imageFormat = target_swapchain_format;
        vk_swapchain_create_info_khr.imageColorSpace = target_swapchain_color_space;
        vk_swapchain_create_info_khr.imageExtent = vk_surface_capabilities_khr.currentExtent;
        vk_swapchain_create_info_khr.imageArrayLayers = 1;
        vk_swapchain_create_info_khr.imageUsage = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        vk_swapchain_create_info_khr.imageSharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
        vk_swapchain_create_info_khr.queueFamilyIndexCount = 0;
        vk_swapchain_create_info_khr.pQueueFamilyIndices = nullptr;
        vk_swapchain_create_info_khr.preTransform = vk_surface_capabilities_khr.currentTransform;
        vk_swapchain_create_info_khr.compositeAlpha = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        vk_swapchain_create_info_khr.presentMode = is_swapchain_support_fifo ? VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR : vk_present_mode_khrs[0];
        vk_swapchain_create_info_khr.clipped = VK_TRUE;
        vk_swapchain_create_info_khr.oldSwapchain = VK_NULL_HANDLE;

        VkSwapchainKHR vk_swapchain_khr = VK_NULL_HANDLE;
        driver.vkCreateSwapchainKHR(vk_device, &vk_swapchain_create_info_khr, nullptr, &vk_swapchain_khr);

        driver.vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)driver.vkGetDeviceProcAddr(vk_device, "vkGetSwapchainImagesKHR");
        assert(driver.vkGetSwapchainImagesKHR && "vkGetSwapchainImagesKHR");

        uint32_t swapchain_image_count = 0;
        driver.vkGetSwapchainImagesKHR(vk_device, vk_swapchain_khr, &swapchain_image_count, nullptr);
        std::vector<VkImage> swapchain_images(swapchain_image_count);
        driver.vkGetSwapchainImagesKHR(vk_device, vk_swapchain_khr, &swapchain_image_count, swapchain_images.data());

        if (swapchain_images.empty())
        {
            throw std::runtime_error("Can not get swapchain images!");
        }

        std::vector<VkImageView> swapchain_image_views(swapchain_image_count);
        for (uint32_t swapchain_image_view_index = 0; swapchain_image_view_index < swapchain_image_count; swapchain_image_view_index++)
        {
            VkImageViewCreateInfo vk_image_view_create_info = {};
            vk_image_view_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            vk_image_view_create_info.pNext = nullptr;
            vk_image_view_create_info.flags = 0;
            vk_image_view_create_info.image = swapchain_images[swapchain_image_view_index];
            vk_image_view_create_info.viewType = VkImageViewType ::VK_IMAGE_VIEW_TYPE_2D;
            vk_image_view_create_info.format = target_swapchain_format;
            vk_image_view_create_info.components.r = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R;
            vk_image_view_create_info.components.g = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G;
            vk_image_view_create_info.components.b = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B;
            vk_image_view_create_info.components.a = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A;
            vk_image_view_create_info.subresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
            vk_image_view_create_info.subresourceRange.baseMipLevel = 0;
            vk_image_view_create_info.subresourceRange.levelCount = 1;
            vk_image_view_create_info.subresourceRange.baseArrayLayer = 0;
            vk_image_view_create_info.subresourceRange.layerCount = 1;

            driver.vkCreateImageView(vk_device, &vk_image_view_create_info, nullptr, &swapchain_image_views[swapchain_image_view_index]);
        }

        VkCommandPool vk_command_pool = VK_NULL_HANDLE;
        VkCommandPoolCreateInfo vk_command_pool_create_info = {};
        vk_command_pool_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        vk_command_pool_create_info.pNext = nullptr;
        vk_command_pool_create_info.flags = 0;
        vk_command_pool_create_info.queueFamilyIndex = queue_family_index;
        driver.vkCreateCommandPool(vk_device, &vk_command_pool_create_info, nullptr, &vk_command_pool);

        // <Init Vulkan resource>

        VkShaderModule my_vertex_shader_module = VK_NULL_HANDLE;
        VkShaderModule my_fragment_shader_module = VK_NULL_HANDLE;
        {
            VkShaderModuleCreateInfo vk_shader_module_create_info = {};
            vk_shader_module_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            vk_shader_module_create_info.pNext = 0;
            vk_shader_module_create_info.flags = 0;
            vk_shader_module_create_info.codeSize = sizeof(MY_VERT_SHADER_BIN);
            vk_shader_module_create_info.pCode = MY_VERT_SHADER_BIN;

            VkResult result = driver.vkCreateShaderModule(vk_device, &vk_shader_module_create_info, nullptr, &my_vertex_shader_module);
            if (result != VkResult::VK_SUCCESS)
            {
                throw std::runtime_error("Can not create vertex shader module!");
            }

            vk_shader_module_create_info.codeSize = sizeof(MY_FRAG_SHADER_BIN);
            vk_shader_module_create_info.pCode = MY_FRAG_SHADER_BIN;

            result = driver.vkCreateShaderModule(vk_device, &vk_shader_module_create_info, nullptr, &my_fragment_shader_module);
            if (result != VkResult::VK_SUCCESS)
            {
                throw std::runtime_error("Can not create fragment shader module!");
            }
        }

        VkDescriptorPool vk_descriptor_pool = VK_NULL_HANDLE;
        {
            std::vector<VkDescriptorPoolSize> vk_descriptor_pool_sizes = {};
            {
                VkDescriptorPoolSize vk_descriptor_pool_size;
                vk_descriptor_pool_size.descriptorCount = 1000;

                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_SAMPLER;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
                vk_descriptor_pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
                vk_descriptor_pool_sizes.push_back(vk_descriptor_pool_size);
            }

            VkDescriptorPoolCreateInfo vk_descriptor_pool_create_info = {};
            vk_descriptor_pool_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            vk_descriptor_pool_create_info.pNext = nullptr;
            vk_descriptor_pool_create_info.flags = VkDescriptorPoolCreateFlagBits::VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
            vk_descriptor_pool_create_info.maxSets = vk_descriptor_pool_sizes.size() * 1000;
            vk_descriptor_pool_create_info.poolSizeCount = vk_descriptor_pool_sizes.size();
            vk_descriptor_pool_create_info.pPoolSizes = vk_descriptor_pool_sizes.data();

            VkResult result = driver.vkCreateDescriptorPool(vk_device, &vk_descriptor_pool_create_info, nullptr, &vk_descriptor_pool);
            if (result != VkResult::VK_SUCCESS)
            {
                throw std::runtime_error("Can not create VkDescriptorPool!");
            }
        }

        VkAttachmentReference color_attachment = {};
        {
            color_attachment.attachment = 0;
            color_attachment.layout = VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        }

        VkSubpassDescription color_pass = {};
        {
            color_pass.flags = 0;
            color_pass.pipelineBindPoint = VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS;
            color_pass.inputAttachmentCount = 0;
            color_pass.pInputAttachments = nullptr;
            color_pass.colorAttachmentCount = 1;
            color_pass.pColorAttachments = &color_attachment;
            color_pass.pResolveAttachments = nullptr;
            color_pass.pDepthStencilAttachment = nullptr;
            color_pass.preserveAttachmentCount = 0;
            color_pass.pPreserveAttachments = nullptr;
        }

        VkAttachmentDescription color_attachment_description = {};
        {
            color_attachment_description.flags = 0;
            color_attachment_description.format = target_swapchain_format;
            color_attachment_description.samples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
            color_attachment_description.loadOp = VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR;
            color_attachment_description.storeOp = VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE;
            color_attachment_description.stencilLoadOp = VkAttachmentLoadOp ::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            color_attachment_description.stencilStoreOp = VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
            color_attachment_description.initialLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
            color_attachment_description.finalLayout = VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        }

        std::vector<VkAttachmentDescription> vk_attachment_descriptions;
        vk_attachment_descriptions.push_back(color_attachment_description);

        VkRenderPass vk_render_pass = VK_NULL_HANDLE;
        {
            VkRenderPassCreateInfo vk_render_pass_create_info = {};
            vk_render_pass_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
            vk_render_pass_create_info.pNext = nullptr;
            vk_render_pass_create_info.flags = 0;
            vk_render_pass_create_info.attachmentCount = vk_attachment_descriptions.size();
            vk_render_pass_create_info.pAttachments = vk_attachment_descriptions.data();
            vk_render_pass_create_info.subpassCount = 1;
            vk_render_pass_create_info.pSubpasses = &color_pass;
            vk_render_pass_create_info.dependencyCount = 0;
            vk_render_pass_create_info.pDependencies = nullptr;

            driver.vkCreateRenderPass(vk_device, &vk_render_pass_create_info, nullptr, &vk_render_pass);
        }

        VkPipelineShaderStageCreateInfo vertex_shader_stage = {};
        vertex_shader_stage.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertex_shader_stage.pNext = nullptr;
        vertex_shader_stage.flags = 0;
        vertex_shader_stage.stage = VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
        vertex_shader_stage.module = my_vertex_shader_module;
        vertex_shader_stage.pName = "main";
        vertex_shader_stage.pSpecializationInfo = nullptr;

        VkPipelineShaderStageCreateInfo fragment_shader_stage = {};
        fragment_shader_stage.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragment_shader_stage.pNext = nullptr;
        fragment_shader_stage.flags = 0;
        fragment_shader_stage.stage = VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
        fragment_shader_stage.module = my_fragment_shader_module;
        fragment_shader_stage.pName = "main";
        fragment_shader_stage.pSpecializationInfo = nullptr;

        std::vector<VkPipelineShaderStageCreateInfo> shader_stages;
        shader_stages.push_back(vertex_shader_stage);
        shader_stages.push_back(fragment_shader_stage);

        VkPipelineInputAssemblyStateCreateInfo vk_pipeline_input_assembly_state_create_info = {};
        vk_pipeline_input_assembly_state_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        vk_pipeline_input_assembly_state_create_info.pNext = nullptr;
        vk_pipeline_input_assembly_state_create_info.flags = 0;
        vk_pipeline_input_assembly_state_create_info.topology = VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        vk_pipeline_input_assembly_state_create_info.primitiveRestartEnable = VK_FALSE;

        VkViewport vk_viewport = {};
        vk_viewport.x = 0;
        vk_viewport.y = 0;
        vk_viewport.width = window_width;
        vk_viewport.height = window_height;
        vk_viewport.minDepth = 0;
        vk_viewport.maxDepth = 1;

        VkRect2D scissor = {};
        scissor.offset.x = 0;
        scissor.offset.y = 0;
        scissor.extent.width = window_width;
        scissor.extent.height = window_height;

        VkPipelineViewportStateCreateInfo vk_pipeline_viewport_state_create_info = {};
        vk_pipeline_viewport_state_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        vk_pipeline_viewport_state_create_info.pNext = nullptr;
        vk_pipeline_viewport_state_create_info.flags = 0;
        vk_pipeline_viewport_state_create_info.viewportCount = 1;
        vk_pipeline_viewport_state_create_info.pViewports = &vk_viewport;
        vk_pipeline_viewport_state_create_info.scissorCount = 1;
        vk_pipeline_viewport_state_create_info.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo vk_pipeline_rasterization_state_create_info = {};
        vk_pipeline_rasterization_state_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        vk_pipeline_rasterization_state_create_info.pNext = nullptr;
        vk_pipeline_rasterization_state_create_info.flags = 0;
        vk_pipeline_rasterization_state_create_info.depthClampEnable = VK_FALSE;
        vk_pipeline_rasterization_state_create_info.rasterizerDiscardEnable = VK_FALSE;
        vk_pipeline_rasterization_state_create_info.polygonMode = VkPolygonMode::VK_POLYGON_MODE_FILL;
        vk_pipeline_rasterization_state_create_info.cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
        vk_pipeline_rasterization_state_create_info.frontFace = VkFrontFace::VK_FRONT_FACE_CLOCKWISE;
        vk_pipeline_rasterization_state_create_info.depthBiasEnable = VK_FALSE;
        vk_pipeline_rasterization_state_create_info.depthBiasConstantFactor = 0;
        vk_pipeline_rasterization_state_create_info.depthBiasClamp = 0;
        vk_pipeline_rasterization_state_create_info.depthBiasSlopeFactor = 0;
        vk_pipeline_rasterization_state_create_info.lineWidth = 1;

        VkPipelineColorBlendAttachmentState vk_pipeline_color_blend_attachment_state = {};
        vk_pipeline_color_blend_attachment_state.blendEnable = VK_FALSE;
        vk_pipeline_color_blend_attachment_state.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO;
        vk_pipeline_color_blend_attachment_state.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO;
        vk_pipeline_color_blend_attachment_state.colorBlendOp = VkBlendOp::VK_BLEND_OP_ADD;
        vk_pipeline_color_blend_attachment_state.srcAlphaBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO;
        vk_pipeline_color_blend_attachment_state.dstAlphaBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO;
        vk_pipeline_color_blend_attachment_state.alphaBlendOp = VkBlendOp::VK_BLEND_OP_ADD;
        vk_pipeline_color_blend_attachment_state.colorWriteMask = VkColorComponentFlagBits::VK_COLOR_COMPONENT_R_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_G_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_B_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_A_BIT;

        VkPipelineColorBlendStateCreateInfo vk_pipeline_color_blend_state_create_info = {};
        vk_pipeline_color_blend_state_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        vk_pipeline_color_blend_state_create_info.pNext = nullptr;
        vk_pipeline_color_blend_state_create_info.flags = 0;
        vk_pipeline_color_blend_state_create_info.logicOpEnable = VK_FALSE;
        vk_pipeline_color_blend_state_create_info.logicOp = VkLogicOp::VK_LOGIC_OP_AND;
        vk_pipeline_color_blend_state_create_info.attachmentCount = 1;
        vk_pipeline_color_blend_state_create_info.pAttachments = &vk_pipeline_color_blend_attachment_state;
        vk_pipeline_color_blend_state_create_info.blendConstants[0] = 0;
        vk_pipeline_color_blend_state_create_info.blendConstants[1] = 0;
        vk_pipeline_color_blend_state_create_info.blendConstants[2] = 0;
        vk_pipeline_color_blend_state_create_info.blendConstants[3] = 0;

        std::vector<VkDynamicState> vk_dynamic_states;
        vk_dynamic_states.push_back(VkDynamicState::VK_DYNAMIC_STATE_VIEWPORT);
        vk_dynamic_states.push_back(VkDynamicState::VK_DYNAMIC_STATE_SCISSOR);

        VkPipelineDynamicStateCreateInfo vk_pipeline_dynamic_state_create_info = {};
        vk_pipeline_dynamic_state_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        vk_pipeline_dynamic_state_create_info.pNext = nullptr;
        vk_pipeline_dynamic_state_create_info.flags = 0;
        vk_pipeline_dynamic_state_create_info.dynamicStateCount = vk_dynamic_states.size();
        vk_pipeline_dynamic_state_create_info.pDynamicStates = vk_dynamic_states.data();

        VkPipelineLayout vk_pipeline_layout = VK_NULL_HANDLE;

        VkPipelineLayoutCreateInfo vk_pipeline_layout_create_info = {};
        vk_pipeline_layout_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        vk_pipeline_layout_create_info.pNext = nullptr;
        vk_pipeline_layout_create_info.flags = 0;
        vk_pipeline_layout_create_info.setLayoutCount = 0;
        vk_pipeline_layout_create_info.pSetLayouts = nullptr;
        vk_pipeline_layout_create_info.pushConstantRangeCount = 0;
        vk_pipeline_layout_create_info.pPushConstantRanges = nullptr;

        driver.vkCreatePipelineLayout(vk_device, &vk_pipeline_layout_create_info, nullptr, &vk_pipeline_layout);

        VkPipelineVertexInputStateCreateInfo vk_pipeline_vertex_input_state_create_info = {};
        vk_pipeline_vertex_input_state_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vk_pipeline_vertex_input_state_create_info.pNext = nullptr;
        vk_pipeline_vertex_input_state_create_info.flags = 0;
        vk_pipeline_vertex_input_state_create_info.vertexBindingDescriptionCount = 0;
        vk_pipeline_vertex_input_state_create_info.pVertexBindingDescriptions = nullptr;
        vk_pipeline_vertex_input_state_create_info.vertexAttributeDescriptionCount = 0;
        vk_pipeline_vertex_input_state_create_info.pVertexAttributeDescriptions = nullptr;

        VkPipelineTessellationStateCreateInfo vk_pipeline_tessellation_state_create_info = {};
        vk_pipeline_tessellation_state_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
        vk_pipeline_tessellation_state_create_info.pNext = nullptr;
        vk_pipeline_tessellation_state_create_info.flags = 0;
        vk_pipeline_tessellation_state_create_info.patchControlPoints = 0;

        VkPipelineMultisampleStateCreateInfo vk_pipeline_multisample_state_create_info = {};
        vk_pipeline_multisample_state_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        vk_pipeline_multisample_state_create_info.pNext = nullptr;
        vk_pipeline_multisample_state_create_info.flags = 0;
        vk_pipeline_multisample_state_create_info.rasterizationSamples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
        vk_pipeline_multisample_state_create_info.sampleShadingEnable = VK_FALSE;
        vk_pipeline_multisample_state_create_info.minSampleShading = 1;
        vk_pipeline_multisample_state_create_info.pSampleMask = nullptr;
        vk_pipeline_multisample_state_create_info.alphaToCoverageEnable = VK_FALSE;
        vk_pipeline_multisample_state_create_info.alphaToOneEnable = VK_FALSE;

        VkPipelineDepthStencilStateCreateInfo vk_pipeline_depth_stencil_state_create_info = {};
        vk_pipeline_depth_stencil_state_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        vk_pipeline_depth_stencil_state_create_info.pNext = nullptr;
        vk_pipeline_depth_stencil_state_create_info.flags = 0;
        vk_pipeline_depth_stencil_state_create_info.depthTestEnable = VK_TRUE;
        vk_pipeline_depth_stencil_state_create_info.depthWriteEnable = VK_TRUE;
        vk_pipeline_depth_stencil_state_create_info.depthCompareOp = VkCompareOp::VK_COMPARE_OP_LESS_OR_EQUAL;
        vk_pipeline_depth_stencil_state_create_info.depthBoundsTestEnable = VK_FALSE;
        vk_pipeline_depth_stencil_state_create_info.stencilTestEnable = VK_FALSE;
        vk_pipeline_depth_stencil_state_create_info.front = {};
        vk_pipeline_depth_stencil_state_create_info.back = {};
        vk_pipeline_depth_stencil_state_create_info.minDepthBounds = 0;
        vk_pipeline_depth_stencil_state_create_info.maxDepthBounds = 0;

        VkGraphicsPipelineCreateInfo vk_graphics_pipeline_create_info = {};
        vk_graphics_pipeline_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        vk_graphics_pipeline_create_info.pNext = nullptr;
        vk_graphics_pipeline_create_info.flags = 0;
        vk_graphics_pipeline_create_info.stageCount = shader_stages.size();
        vk_graphics_pipeline_create_info.pStages = shader_stages.data();
        vk_graphics_pipeline_create_info.pVertexInputState = &vk_pipeline_vertex_input_state_create_info;
        vk_graphics_pipeline_create_info.pInputAssemblyState = &vk_pipeline_input_assembly_state_create_info;
        vk_graphics_pipeline_create_info.pTessellationState = &vk_pipeline_tessellation_state_create_info;
        vk_graphics_pipeline_create_info.pViewportState = &vk_pipeline_viewport_state_create_info;
        vk_graphics_pipeline_create_info.pRasterizationState = &vk_pipeline_rasterization_state_create_info;
        vk_graphics_pipeline_create_info.pMultisampleState = &vk_pipeline_multisample_state_create_info;
        vk_graphics_pipeline_create_info.pDepthStencilState = &vk_pipeline_depth_stencil_state_create_info;
        vk_graphics_pipeline_create_info.pColorBlendState = &vk_pipeline_color_blend_state_create_info;
        vk_graphics_pipeline_create_info.pDynamicState = &vk_pipeline_dynamic_state_create_info;
        vk_graphics_pipeline_create_info.layout = vk_pipeline_layout;
        vk_graphics_pipeline_create_info.renderPass = vk_render_pass;
        vk_graphics_pipeline_create_info.subpass = 0;
        vk_graphics_pipeline_create_info.basePipelineHandle = VK_NULL_HANDLE;
        vk_graphics_pipeline_create_info.basePipelineIndex = 0;

        VkPipeline volume_pipeline = VK_NULL_HANDLE;
        VkResult volume_pipeline_create_result = driver.vkCreateGraphicsPipelines(vk_device, VK_NULL_HANDLE, 1, &vk_graphics_pipeline_create_info, nullptr, &volume_pipeline);
        if (volume_pipeline_create_result != VkResult::VK_SUCCESS)
        {
            std::cout << "volume_pipeline_create_result:" << volume_pipeline_create_result << std::endl;
            throw std::runtime_error("Can not create rendering pipeline!");
        }

        // Descriptor Set

        // FrameBuffer
        std::vector<VkFramebuffer> vk_frame_buffers;
        for (uint32_t swapchain_image_view_index = 0; swapchain_image_view_index < swapchain_image_views.size(); swapchain_image_view_index++)
        {
            std::vector<VkImageView> frame_buffer;
            frame_buffer.push_back(swapchain_image_views[swapchain_image_view_index]);

            VkFramebufferCreateInfo vk_frame_buffer_create_info = {};
            vk_frame_buffer_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            vk_frame_buffer_create_info.pNext = nullptr;
            vk_frame_buffer_create_info.flags = 0;
            vk_frame_buffer_create_info.renderPass = vk_render_pass;
            vk_frame_buffer_create_info.attachmentCount = frame_buffer.size();
            vk_frame_buffer_create_info.pAttachments = frame_buffer.data();
            vk_frame_buffer_create_info.width = window_width;
            vk_frame_buffer_create_info.height = window_height;
            vk_frame_buffer_create_info.layers = 1;

            VkFramebuffer vk_frame_buffer = VK_NULL_HANDLE;
            VkResult frame_buffer_create_result = driver.vkCreateFramebuffer(vk_device, &vk_frame_buffer_create_info, nullptr, &vk_frame_buffer);
            if (frame_buffer_create_result != VkResult::VK_SUCCESS)
            {
                throw std::runtime_error("Can not create Framebuffer!");
            }

            vk_frame_buffers.push_back(vk_frame_buffer);
        }

        glm::vec3 camera_position = glm::vec3(0, 0, 0);
        glm::vec3 look_forward = glm::vec3(0, 0, 1);

        float bounding_box_pos[3];
        bounding_box_pos[0] = 0;
        bounding_box_pos[1] = 0;
        bounding_box_pos[2] = 0;

        float bounding_box_half_diagonal_vector[3];
        bounding_box_half_diagonal_vector[0] = 1;
        bounding_box_half_diagonal_vector[1] = 1;
        bounding_box_half_diagonal_vector[2] = 1;

        float bounding_box_forward_dir[3];
        bounding_box_forward_dir[0] = 0;
        bounding_box_forward_dir[1] = 0;
        bounding_box_forward_dir[2] = 1;
        // </Init Vulkan resource>

        float time = glfwGetTime();
        float previous_time = time;
        glm::vec2 previous_mouse_pos;

        float horizontal_angle = 0;
        float vertical_angle = 0;

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            uint32_t next_image_index = UINT32_MAX;

            VkFence require_next_image_fence = VK_NULL_HANDLE;
            {
                VkFenceCreateInfo vk_fence_create_info = {};
                vk_fence_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
                vk_fence_create_info.pNext = nullptr;
                vk_fence_create_info.flags = 0;

                driver.vkCreateFence(vk_device, &vk_fence_create_info, nullptr, &require_next_image_fence);
            }
            VkResult next_image_require_result = driver.vkAcquireNextImageKHR(vk_device, vk_swapchain_khr, UINT64_MAX - 1, VK_NULL_HANDLE, require_next_image_fence, &next_image_index);

            // if (next_image_require_result != VkResult::VK_SUCCESS)
            if (next_image_require_result == VkResult::VK_ERROR_OUT_OF_DATE_KHR)
            {
                driver.vkDestroyFence(vk_device, require_next_image_fence, nullptr);

                //  TODO: resize in here
                {
                    for (auto &vk_frame_buffer : vk_frame_buffers)
                    {
                        driver.vkDestroyFramebuffer(vk_device, vk_frame_buffer, nullptr);
                    }
                    vk_frame_buffers.clear();

                    for (auto &swapchain_image_view : swapchain_image_views)
                    {
                        driver.vkDestroyImageView(vk_device, swapchain_image_view, nullptr);
                    }
                    swapchain_image_views.clear();
                    swapchain_images.clear();

                    driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk_physical_device, vk_surface_khr, &vk_surface_capabilities_khr);

                    VkSwapchainCreateInfoKHR vk_swapchain_create_info_khr = {};
                    vk_swapchain_create_info_khr.sType = VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
                    vk_swapchain_create_info_khr.pNext = nullptr;
                    vk_swapchain_create_info_khr.flags = 0;
                    vk_swapchain_create_info_khr.surface = vk_surface_khr;
                    vk_swapchain_create_info_khr.minImageCount = std::max(vk_surface_capabilities_khr.minImageCount, vk_surface_capabilities_khr.maxImageCount);
                    vk_swapchain_create_info_khr.imageFormat = target_swapchain_format;
                    vk_swapchain_create_info_khr.imageColorSpace = target_swapchain_color_space;
                    vk_swapchain_create_info_khr.imageExtent = vk_surface_capabilities_khr.currentExtent;
                    vk_swapchain_create_info_khr.imageArrayLayers = 1;
                    vk_swapchain_create_info_khr.imageUsage = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
                    vk_swapchain_create_info_khr.imageSharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
                    vk_swapchain_create_info_khr.queueFamilyIndexCount = 0;
                    vk_swapchain_create_info_khr.pQueueFamilyIndices = nullptr;
                    vk_swapchain_create_info_khr.preTransform = vk_surface_capabilities_khr.currentTransform;
                    vk_swapchain_create_info_khr.compositeAlpha = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
                    vk_swapchain_create_info_khr.presentMode = is_swapchain_support_fifo ? VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR : vk_present_mode_khrs[0];
                    vk_swapchain_create_info_khr.clipped = VK_TRUE;
                    vk_swapchain_create_info_khr.oldSwapchain = vk_swapchain_khr;

                    VkResult new_create_swapchain_result = driver.vkCreateSwapchainKHR(vk_device, &vk_swapchain_create_info_khr, nullptr, &vk_swapchain_khr);

                    if (new_create_swapchain_result == VkResult::VK_SUCCESS)
                    {
                        driver.vkDestroySwapchainKHR(vk_device, vk_swapchain_create_info_khr.oldSwapchain, nullptr);

                        window_width = vk_surface_capabilities_khr.currentExtent.width;
                        window_height = vk_surface_capabilities_khr.currentExtent.height;
                    }

                    driver.vkGetSwapchainImagesKHR(vk_device, vk_swapchain_khr, &swapchain_image_count, nullptr);
                    swapchain_images.resize(swapchain_image_count);
                    driver.vkGetSwapchainImagesKHR(vk_device, vk_swapchain_khr, &swapchain_image_count, swapchain_images.data());

                    if (swapchain_images.empty())
                    {
                        throw std::runtime_error("Can not get swapchain images!");
                    }

                    swapchain_image_views.resize(swapchain_image_count);
                    for (uint32_t swapchain_image_view_index = 0; swapchain_image_view_index < swapchain_image_count; swapchain_image_view_index++)
                    {
                        VkImageViewCreateInfo vk_image_view_create_info = {};
                        vk_image_view_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                        vk_image_view_create_info.pNext = nullptr;
                        vk_image_view_create_info.flags = 0;
                        vk_image_view_create_info.image = swapchain_images[swapchain_image_view_index];
                        vk_image_view_create_info.viewType = VkImageViewType ::VK_IMAGE_VIEW_TYPE_2D;
                        vk_image_view_create_info.format = target_swapchain_format;
                        vk_image_view_create_info.components.r = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R;
                        vk_image_view_create_info.components.g = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G;
                        vk_image_view_create_info.components.b = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B;
                        vk_image_view_create_info.components.a = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A;
                        vk_image_view_create_info.subresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
                        vk_image_view_create_info.subresourceRange.baseMipLevel = 0;
                        vk_image_view_create_info.subresourceRange.levelCount = 1;
                        vk_image_view_create_info.subresourceRange.baseArrayLayer = 0;
                        vk_image_view_create_info.subresourceRange.layerCount = 1;

                        driver.vkCreateImageView(vk_device, &vk_image_view_create_info, nullptr, &swapchain_image_views[swapchain_image_view_index]);
                    }

                    for (uint32_t swapchain_image_view_index = 0; swapchain_image_view_index < swapchain_image_views.size(); swapchain_image_view_index++)
                    {
                        std::vector<VkImageView> frame_buffer;
                        frame_buffer.push_back(swapchain_image_views[swapchain_image_view_index]);

                        VkFramebufferCreateInfo vk_frame_buffer_create_info = {};
                        vk_frame_buffer_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
                        vk_frame_buffer_create_info.pNext = nullptr;
                        vk_frame_buffer_create_info.flags = 0;
                        vk_frame_buffer_create_info.renderPass = vk_render_pass;
                        vk_frame_buffer_create_info.attachmentCount = frame_buffer.size();
                        vk_frame_buffer_create_info.pAttachments = frame_buffer.data();
                        vk_frame_buffer_create_info.width = window_width;
                        vk_frame_buffer_create_info.height = window_height;
                        vk_frame_buffer_create_info.layers = 1;

                        VkFramebuffer vk_frame_buffer = VK_NULL_HANDLE;
                        VkResult frame_buffer_create_result = driver.vkCreateFramebuffer(vk_device, &vk_frame_buffer_create_info, nullptr, &vk_frame_buffer);
                        if (frame_buffer_create_result != VkResult::VK_SUCCESS)
                        {
                            throw std::runtime_error("Can not create Framebuffer!");
                        }

                        vk_frame_buffers.push_back(vk_frame_buffer);
                    }
                }

                continue;
            }

            {
                driver.vkWaitForFences(vk_device, 1, &require_next_image_fence, VK_TRUE, UINT64_MAX);
                driver.vkDestroyFence(vk_device, require_next_image_fence, nullptr);
            }

            VkCommandBuffer vk_command_buffer = VK_NULL_HANDLE;
            {
                VkCommandBufferAllocateInfo vk_command_buffer_allocate_info = {};
                vk_command_buffer_allocate_info.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                vk_command_buffer_allocate_info.pNext = nullptr;
                vk_command_buffer_allocate_info.commandPool = vk_command_pool;
                vk_command_buffer_allocate_info.level = VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                vk_command_buffer_allocate_info.commandBufferCount = 1;
                driver.vkAllocateCommandBuffers(vk_device, &vk_command_buffer_allocate_info, &vk_command_buffer);
            }

            VkCommandBufferBeginInfo vk_command_buffer_begin_info = {};
            {
                vk_command_buffer_begin_info.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                vk_command_buffer_begin_info.pNext = nullptr;
                vk_command_buffer_begin_info.flags = 0;
                vk_command_buffer_begin_info.pInheritanceInfo = nullptr;
            }

            driver.vkBeginCommandBuffer(vk_command_buffer, &vk_command_buffer_begin_info);

            // draw command

            VkClearValue color_clear_value = {};
            color_clear_value.color.float32[0] = 0;
            color_clear_value.color.float32[1] = 0;
            color_clear_value.color.float32[2] = 0;
            color_clear_value.color.float32[3] = 0;

            std::vector<VkClearValue> vk_clear_values;
            vk_clear_values.push_back(color_clear_value);

            VkRenderPassBeginInfo vk_render_pass_begin_info = {};
            vk_render_pass_begin_info.sType = VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            vk_render_pass_begin_info.pNext = nullptr;
            vk_render_pass_begin_info.renderPass = vk_render_pass;
            vk_render_pass_begin_info.framebuffer = vk_frame_buffers[next_image_index];
            vk_render_pass_begin_info.renderArea.offset.x = 0;
            vk_render_pass_begin_info.renderArea.offset.y = 0;
            vk_render_pass_begin_info.renderArea.extent.width = window_width;
            vk_render_pass_begin_info.renderArea.extent.height = window_height;
            vk_render_pass_begin_info.clearValueCount = vk_clear_values.size();
            vk_render_pass_begin_info.pClearValues = vk_clear_values.data();

            {
                vk_viewport.width = window_width;
                vk_viewport.height = window_height;

                scissor.extent.width = window_width;
                scissor.extent.height = window_height;
            }

            driver.vkCmdBeginRenderPass(vk_command_buffer, &vk_render_pass_begin_info, VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE);
            driver.vkCmdBindPipeline(vk_command_buffer, VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, volume_pipeline);
            driver.vkCmdSetViewport(vk_command_buffer, 0, 1, &vk_viewport);
            driver.vkCmdSetScissor(vk_command_buffer, 0, 1, &scissor);
            driver.vkCmdDraw(vk_command_buffer, 3, 1, 0, 0);

            driver.vkCmdEndRenderPass(vk_command_buffer);

            driver.vkEndCommandBuffer(vk_command_buffer);

            VkFence fence = VK_NULL_HANDLE;
            {
                VkFenceCreateInfo vk_fence_create_info = {};
                vk_fence_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
                vk_fence_create_info.pNext = nullptr;
                vk_fence_create_info.flags = 0;

                driver.vkCreateFence(vk_device, &vk_fence_create_info, nullptr, &fence);
            }

            VkSubmitInfo vk_submit_info = {};
            vk_submit_info.sType = VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
            vk_submit_info.pNext = 0;
            vk_submit_info.waitSemaphoreCount = 0;
            vk_submit_info.pWaitSemaphores = nullptr;
            vk_submit_info.pWaitDstStageMask = nullptr;
            vk_submit_info.commandBufferCount = 1;
            vk_submit_info.pCommandBuffers = &vk_command_buffer;
            vk_submit_info.signalSemaphoreCount = 0;
            vk_submit_info.pSignalSemaphores = nullptr;

            driver.vkQueueSubmit(vk_queue, 1, &vk_submit_info, fence);
            driver.vkWaitForFences(vk_device, 1, &fence, VK_TRUE, UINT64_MAX);
            driver.vkDestroyFence(vk_device, fence, nullptr);
            driver.vkFreeCommandBuffers(vk_device, vk_command_pool, 1, &vk_command_buffer);

            VkPresentInfoKHR vk_present_info_khr = {};
            vk_present_info_khr.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
            vk_present_info_khr.pNext = nullptr;
            vk_present_info_khr.waitSemaphoreCount = 0;
            vk_present_info_khr.pWaitSemaphores = nullptr;
            vk_present_info_khr.swapchainCount = 1;
            vk_present_info_khr.pSwapchains = &vk_swapchain_khr;
            vk_present_info_khr.pImageIndices = &next_image_index;
            vk_present_info_khr.pResults = nullptr;

            // TODO: load vkQueuePresentKHR(...) by TVulkanLoader
            VkResult result = driver.vkQueuePresentKHR(vk_queue, &vk_present_info_khr);
            // Vulkan loop
        }

        for (VkFramebuffer vk_frame_buffeer_item : vk_frame_buffers)
        {
            driver.vkDestroyFramebuffer(vk_device, vk_frame_buffeer_item, nullptr);
        }

        driver.vkDestroyPipeline(vk_device, volume_pipeline, nullptr);

        driver.vkDestroyPipelineLayout(vk_device, vk_pipeline_layout, nullptr);

        driver.vkDestroyRenderPass(vk_device, vk_render_pass, nullptr);
        driver.vkDestroyDescriptorPool(vk_device, vk_descriptor_pool, nullptr);

        driver.vkDestroyShaderModule(vk_device, my_fragment_shader_module, nullptr);
        driver.vkDestroyShaderModule(vk_device, my_vertex_shader_module, nullptr);

        for (VkImageView &vk_image_view_item : swapchain_image_views)
        {
            driver.vkDestroyImageView(vk_device, vk_image_view_item, nullptr);
        }

        // driver.vkFreeCommandBuffers(vk_device, vk_command_pool, 1, &vk_command_buffer);

        driver.vkDestroyCommandPool(vk_device, vk_command_pool, nullptr);

        driver.vkDestroySwapchainKHR(vk_device, vk_swapchain_khr, nullptr);
        driver.vkDestroySurfaceKHR(vk_instance, vk_surface_khr, nullptr);
    };

    vulkan_code();

    driver.vkDestroyDevice(vk_device, nullptr);
    std::cout << "vkDestroyDevice success" << std::endl;

    driver.vkDestroyInstance(vk_instance, nullptr);
    std::cout << "vkDestroyInstance success" << std::endl;

    return 0;
}