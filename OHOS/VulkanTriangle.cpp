#include <VulkanTriangle.h>

#include <stdio.h>
#include <string>
/*
void MyPrint(const char *format, ...)
{
    va_list args;
    va_start(args, format);
#if defined(USE_HARMONY_OS_PLATFORM)
    OH_LOG_Print(LOG_APP, LOG_INFO, 0x1, "VulkanTriangle", format, args);//FIXME: Had BUG!!!
#else
    vprintf(format, args);
#endif
    va_end(args);
}
*/

/*
template<typename... Args>
void MyPrint(const std::string& format, Args... args) {
    //std::cout << first << " ";
    //print(rest...);  // 递归调用，展开剩余参数
#if defined(USE_HARMONY_OS_PLATFORM)
    OH_LOG_Print(LOG_APP, LOG_INFO, 0x1, "VulkanTriangle", format.c_str(), args...);//FIXME: Had BUG!!!
#else
    vprintf(format, args...);
#endif
}
*/

#if defined(USE_HARMONY_OS_PLATFORM)
#define MyPrint(fmt, ...)  OH_LOG_Print(LOG_APP, LOG_INFO, 0x1, "VulkanTriangle", fmt, ##__VA_ARGS__);
#else
#define MyPrint(fmt, ...) vprintf(fmt, ##__VA_ARGS__);
#endif

void PrintVkSurfaceTransformFlagBitsKHR(VkSurfaceTransformFlagBitsKHR stfb)
{
    switch (stfb)
    {
    case VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR:{MyPrint("VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR");}break;
    case VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR:{MyPrint("VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR");}break;
    case VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR:{MyPrint("VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR");}break;
    case VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR:{MyPrint("VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR");}break;
    case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR:{MyPrint("VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR");}break;
    case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR:{MyPrint("VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR");}break;
    case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR:{MyPrint("VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR");}break;
    case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR:{MyPrint("VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR");}break;
    case VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR:{MyPrint("VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR");}break;
    }
}

void PrintVkSurfaceTransformFlagsKHR(VkSurfaceTransformFlagsKHR stf)
{
    if((stf&VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)==VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR){PrintVkSurfaceTransformFlagBitsKHR(VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR);}
    if((stf&VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR)==VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR){PrintVkSurfaceTransformFlagBitsKHR(VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR);}
    if((stf&VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR)==VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR){PrintVkSurfaceTransformFlagBitsKHR(VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR);}
    if((stf&VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)==VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR){PrintVkSurfaceTransformFlagBitsKHR(VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR);}
    if((stf&VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR)==VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR){PrintVkSurfaceTransformFlagBitsKHR(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR);}
    if((stf&VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR)==VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR){PrintVkSurfaceTransformFlagBitsKHR(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR);}
    if((stf&VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR)==VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR){PrintVkSurfaceTransformFlagBitsKHR(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR);}
    if((stf&VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR)==VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR){PrintVkSurfaceTransformFlagBitsKHR(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR);}
    if((stf&VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR)==VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR){PrintVkSurfaceTransformFlagBitsKHR(VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR);}
}

static const uint32_t MY_VERT_SHADER_BIN[] = {0x07230203, 0x00010000, 0x000d000b, 0x0000004d, 0x00000000, 0x00020011, 0x00000001, 0x0006000b, 0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001, 0x0008000f, 0x00000000, 0x00000004, 0x6e69616d, 0x00000000, 0x00000017, 0x00000021, 0x0000003b, 0x00050048, 0x00000009, 0x00000000, 0x00000023, 0x00000000, 0x00030047, 0x00000009, 0x00000002, 0x00040047, 0x00000017, 0x0000000b, 0x0000002a, 0x00040047, 0x00000021, 0x0000001e, 0x00000000, 0x00050048, 0x00000039, 0x00000000, 0x0000000b, 0x00000000, 0x00050048, 0x00000039, 0x00000001, 0x0000000b, 0x00000001, 0x00050048, 0x00000039, 0x00000002, 0x0000000b, 0x00000003, 0x00050048, 0x00000039, 0x00000003, 0x0000000b, 0x00000004, 0x00030047, 0x00000039, 0x00000002, 0x00020013, 0x00000002, 0x00030021, 0x00000003, 0x00000002, 0x00030016, 0x00000006, 0x00000020, 0x0003001e, 0x00000009, 0x00000006, 0x00040020, 0x0000000a, 0x00000009, 0x00000009, 0x0004003b, 0x0000000a, 0x0000000b, 0x00000009, 0x00040015, 0x0000000c, 0x00000020, 0x00000001, 0x0004002b, 0x0000000c, 0x0000000d, 0x00000000, 0x00040020, 0x0000000e, 0x00000009, 0x00000006, 0x00040017, 0x00000011, 0x00000006, 0x00000002, 0x0004002b, 0x00000006, 0x00000014, 0x00000000, 0x0005002c, 0x00000011, 0x00000015, 0x00000014, 0x00000014, 0x00040020, 0x00000016, 0x00000001, 0x0000000c, 0x0004003b, 0x00000016, 0x00000017, 0x00000001, 0x00020014, 0x00000019, 0x0004002b, 0x00000006, 0x0000001d, 0xbf000000, 0x0005002c, 0x00000011, 0x0000001e, 0x00000014, 0x0000001d, 0x00040017, 0x0000001f, 0x00000006, 0x00000003, 0x00040020, 0x00000020, 0x00000003, 0x0000001f, 0x0004003b, 0x00000020, 0x00000021, 0x00000003, 0x0004002b, 0x00000006, 0x00000022, 0x3f800000, 0x0006002c, 0x0000001f, 0x00000023, 0x00000022, 0x00000014, 0x00000014, 0x0004002b, 0x0000000c, 0x00000026, 0x00000001, 0x0004002b, 0x00000006, 0x0000002a, 0x3f000000, 0x0005002c, 0x00000011, 0x0000002b, 0x0000002a, 0x0000002a, 0x0006002c, 0x0000001f, 0x0000002c, 0x00000014, 0x00000022, 0x00000014, 0x0004002b, 0x0000000c, 0x0000002f, 0x00000002, 0x0005002c, 0x00000011, 0x00000033, 0x0000001d, 0x0000002a, 0x0006002c, 0x0000001f, 0x00000034, 0x00000014, 0x00000014, 0x00000022, 0x00040017, 0x00000035, 0x00000006, 0x00000004, 0x00040015, 0x00000036, 0x00000020, 0x00000000, 0x0004002b, 0x00000036, 0x00000037, 0x00000001, 0x0004001c, 0x00000038, 0x00000006, 0x00000037, 0x0006001e, 0x00000039, 0x00000035, 0x00000006, 0x00000038, 0x00000038, 0x00040020, 0x0000003a, 0x00000003, 0x00000039, 0x0004003b, 0x0000003a, 0x0000003b, 0x00000003, 0x00040020, 0x00000042, 0x00000003, 0x00000035, 0x00040017, 0x0000004a, 0x00000019, 0x00000002, 0x00050036, 0x00000002, 0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x00050041, 0x0000000e, 0x0000000f, 0x0000000b, 0x0000000d, 0x0004003d, 0x00000006, 0x00000010, 0x0000000f, 0x0004003d, 0x0000000c, 0x00000018, 0x00000017, 0x000500aa, 0x00000019, 0x0000001a, 0x00000018, 0x0000000d, 0x000300f7, 0x0000001c, 0x00000000, 0x000400fa, 0x0000001a, 0x0000001b, 0x00000024, 0x000200f8, 0x0000001b, 0x0003003e, 0x00000021, 0x00000023, 0x000200f9, 0x0000001c, 0x000200f8, 0x00000024, 0x000500aa, 0x00000019, 0x00000027, 0x00000018, 0x00000026, 0x000300f7, 0x00000029, 0x00000000, 0x000400fa, 0x00000027, 0x00000028, 0x0000002d, 0x000200f8, 0x00000028, 0x0003003e, 0x00000021, 0x0000002c, 0x000200f9, 0x00000029, 0x000200f8, 0x0000002d, 0x000500aa, 0x00000019, 0x00000030, 0x00000018, 0x0000002f, 0x000300f7, 0x00000032, 0x00000000, 0x000400fa, 0x00000030, 0x00000031, 0x00000032, 0x000200f8, 0x00000031, 0x0003003e, 0x00000021, 0x00000034, 0x000200f9, 0x00000032, 0x000200f8, 0x00000032, 0x00050050, 0x0000004a, 0x0000004b, 0x00000030, 0x00000030, 0x000600a9, 0x00000011, 0x0000004c, 0x0000004b, 0x00000033, 0x00000015, 0x000200f9, 0x00000029, 0x000200f8, 0x00000029, 0x000700f5, 0x00000011, 0x00000045, 0x0000002b, 0x00000028, 0x0000004c, 0x00000032, 0x000200f9, 0x0000001c, 0x000200f8, 0x0000001c, 0x000700f5, 0x00000011, 0x00000044, 0x0000001e, 0x0000001b, 0x00000045, 0x00000029, 0x0005008e, 0x00000011, 0x0000003e, 0x00000044, 0x00000010, 0x00050051, 0x00000006, 0x0000003f, 0x0000003e, 0x00000000, 0x00050051, 0x00000006, 0x00000040, 0x0000003e, 0x00000001, 0x00070050, 0x00000035, 0x00000041, 0x0000003f, 0x00000040, 0x00000014, 0x00000022, 0x00050041, 0x00000042, 0x00000043, 0x0000003b, 0x0000000d, 0x0003003e, 0x00000043, 0x00000041, 0x000100fd, 0x00010038};

static const uint32_t MY_FRAG_SHADER_BIN[] = {0x07230203, 0x00010000, 0x0008000b, 0x00000013, 0x00000000, 0x00020011, 0x00000001, 0x0006000b, 0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001, 0x0007000f, 0x00000004, 0x00000004, 0x6e69616d, 0x00000000, 0x00000009, 0x0000000c, 0x00030010, 0x00000004, 0x00000007, 0x00030003, 0x00000002, 0x000001c2, 0x00040005, 0x00000004, 0x6e69616d, 0x00000000, 0x00050005, 0x00000009, 0x4374756f, 0x726f6c6f, 0x00000000, 0x00040005, 0x0000000c, 0x6f6c6f63, 0x00000072, 0x00040047, 0x00000009, 0x0000001e, 0x00000000, 0x00040047, 0x0000000c, 0x0000001e, 0x00000000, 0x00020013, 0x00000002, 0x00030021, 0x00000003, 0x00000002, 0x00030016, 0x00000006, 0x00000020, 0x00040017, 0x00000007, 0x00000006, 0x00000004, 0x00040020, 0x00000008, 0x00000003, 0x00000007, 0x0004003b, 0x00000008, 0x00000009, 0x00000003, 0x00040017, 0x0000000a, 0x00000006, 0x00000003, 0x00040020, 0x0000000b, 0x00000001, 0x0000000a, 0x0004003b, 0x0000000b, 0x0000000c, 0x00000001, 0x0004002b, 0x00000006, 0x0000000e, 0x3f800000, 0x00050036, 0x00000002, 0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x0004003d, 0x0000000a, 0x0000000d, 0x0000000c, 0x00050051, 0x00000006, 0x0000000f, 0x0000000d, 0x00000000, 0x00050051, 0x00000006, 0x00000010, 0x0000000d, 0x00000001, 0x00050051, 0x00000006, 0x00000011, 0x0000000d, 0x00000002, 0x00070050, 0x00000007, 0x00000012, 0x0000000f, 0x00000010, 0x00000011, 0x0000000e, 0x0003003e, 0x00000009, 0x00000012, 0x000100fd, 0x00010038};

VulkanTriangle::VulkanTriangle()
{
    MyPrint("Hello VulkanTriangle  %{public}s",u8"This is test str");
#if defined(USE_WINDOWS_PLATFORM)
    HMODULE library = LoadLibraryA("vulkan-1.dll");
    if (!library)
    {
        throw std::runtime_error("Can not found vulkan loader(vulkan-1.dll)!");
    }

    driver.vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(library, "vkGetInstanceProcAddr");
    assert(driver.vkGetInstanceProcAddr && "vkGetInstanceProcAddr");
#elif defined(USE_LINUX_PLATFORM) || defined(USE_HARMONY_OS_PLATFORM)
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

    //auto version_major = VK_VERSION_MAJOR(support_vulkan_version);
    auto version_major = VK_API_VERSION_MAJOR(support_vulkan_version);
    //auto version_minor = VK_VERSION_MINOR(support_vulkan_version);
    auto version_minor = VK_API_VERSION_MINOR(support_vulkan_version);
    //auto version_patch = VK_VERSION_PATCH(support_vulkan_version);
    auto version_patch = VK_API_VERSION_PATCH(support_vulkan_version);

    MyPrint("Support Vulkan: %{public}u.%{public}u.%{public}u\n", version_major, version_minor, version_patch);

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
    //vk_application_info.apiVersion = support_vulkan_version;
    vk_application_info.apiVersion = VK_API_VERSION_1_0;

    std::vector<std::string> enable_instance_layers;
    {
        uint32_t instance_layer_count = 0;
        driver.vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr);
        std::vector<VkLayerProperties> layer_properties(instance_layer_count);
        driver.vkEnumerateInstanceLayerProperties(&instance_layer_count, layer_properties.data());

        for (auto &layer_property : layer_properties)
        {
            MyPrint("[layer]: %{public}s - (%{public}s)\n", layer_property.layerName, layer_property.description);

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
            MyPrint("[instance-extension]: %{public}s\n", extension_property.extensionName);

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
#elif defined(USE_HARMONY_OS_PLATFORM)
            else if (std::string(extension_property.extensionName) == std::string("VK_OHOS_surface")) // VK_OHOS_SURFACE_EXTENSION_NAME
            {
                enabled_instance_extensions.push_back(extension_property.extensionName);
            }
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

    VkResult result = driver.vkCreateInstance(&vk_instance_create_info, nullptr, &this->instance);
    if (result != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateInstance failed!");
    }
    else
    {
        MyPrint("vkCreateInstance success\n");
    }

    driver.vkDestroyInstance = (PFN_vkDestroyInstance)driver.vkGetInstanceProcAddr(this->instance, "vkDestroyInstance");
    assert(driver.vkDestroyInstance && "vkDestroyInstance");

    driver.vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)driver.vkGetInstanceProcAddr(this->instance, "vkEnumeratePhysicalDevices");
    assert(driver.vkEnumeratePhysicalDevices && "vkEnumeratePhysicalDevices");

    driver.vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)driver.vkGetInstanceProcAddr(this->instance, "vkGetPhysicalDeviceProperties");
    assert(driver.vkGetPhysicalDeviceProperties && "vkEnumeratePhysicalDevices");

    driver.vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)driver.vkGetInstanceProcAddr(this->instance, "vkEnumerateDeviceExtensionProperties");
    assert(driver.vkEnumerateDeviceExtensionProperties && "vkEnumerateDeviceExtensionProperties");

    driver.vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)driver.vkGetInstanceProcAddr(this->instance, "vkGetPhysicalDeviceFormatProperties");
    assert(driver.vkGetPhysicalDeviceFormatProperties && "vkGetPhysicalDeviceFormatProperties");

    driver.vkCreateDevice = (PFN_vkCreateDevice)driver.vkGetInstanceProcAddr(this->instance, "vkCreateDevice");
    assert(driver.vkCreateDevice && "vkCreateDevice");

    driver.vkDestroyDevice = (PFN_vkDestroyDevice)driver.vkGetInstanceProcAddr(this->instance, "vkDestroyDevice");
    assert(driver.vkDestroyDevice && "vkDestroyDevice");

    driver.vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)driver.vkGetInstanceProcAddr(this->instance, "vkGetDeviceProcAddr");
    assert(driver.vkGetDeviceProcAddr && "vkGetDeviceProcAddr");

    driver.vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)driver.vkGetInstanceProcAddr(this->instance, "vkGetPhysicalDeviceQueueFamilyProperties");
    assert(driver.vkGetPhysicalDeviceQueueFamilyProperties && "vkGetPhysicalDeviceQueueFamilyProperties");

    driver.vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)driver.vkGetInstanceProcAddr(this->instance, "vkGetPhysicalDeviceMemoryProperties");
    assert(driver.vkGetPhysicalDeviceMemoryProperties && "vkGetPhysicalDeviceMemoryProperties");

    uint32_t physcial_device_count = 0;
    result = driver.vkEnumeratePhysicalDevices(this->instance, &physcial_device_count, nullptr);
    if (result != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("vkEnumeratePhysicalDevices get count failed!");
    }

    std::vector<VkPhysicalDevice> physcail_devices(physcial_device_count);
    result = driver.vkEnumeratePhysicalDevices(this->instance, &physcial_device_count, physcail_devices.data());
    if (result != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("vkEnumeratePhysicalDevices failed!");
    }

    std::string target_physical_device_name;
    for (VkPhysicalDevice physcail_devices_item : physcail_devices)
    {
        VkPhysicalDeviceProperties vk_physical_device_properties = {};
        driver.vkGetPhysicalDeviceProperties(physcail_devices_item, &vk_physical_device_properties);

        if (vk_physical_device_properties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            this->targetPhysicalDevice = physcail_devices_item;
            target_physical_device_name = std::string(vk_physical_device_properties.deviceName);
            break;
        }
        else if (vk_physical_device_properties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
        {
            this->targetPhysicalDevice = physcail_devices_item;
            target_physical_device_name = std::string(vk_physical_device_properties.deviceName);
        }
    }

    if (this->targetPhysicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("Not found suitable GPU!");
    }
    else
    {
        MyPrint("Select Physical Device: %{public}s\n", target_physical_device_name.c_str());
    }

    uint32_t queue_family_count = 0;
    driver.vkGetPhysicalDeviceQueueFamilyProperties(this->targetPhysicalDevice, &queue_family_count, nullptr);
    std::vector<VkQueueFamilyProperties> vk_queue_family_properties(queue_family_count);
    driver.vkGetPhysicalDeviceQueueFamilyProperties(this->targetPhysicalDevice, &queue_family_count, vk_queue_family_properties.data());

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
        driver.vkEnumerateDeviceExtensionProperties(this->targetPhysicalDevice, nullptr, &device_extension_count, nullptr);
        std::vector<VkExtensionProperties> extension_properties(device_extension_count);
        driver.vkEnumerateDeviceExtensionProperties(this->targetPhysicalDevice, nullptr, &device_extension_count, extension_properties.data());

        for (auto &extension_property : extension_properties)
        {
            MyPrint("[device-extension]: %{public}s\n", extension_property.extensionName);

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

    result = driver.vkCreateDevice(this->targetPhysicalDevice, &vk_device_create_info, nullptr, &this->device);
    if (result != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateDevice failed!");
    }
    MyPrint("vkCreateDevice success\n");

    {
        driver.vkCreateImage = (PFN_vkCreateImage)driver.vkGetDeviceProcAddr(this->device, "vkCreateImage");
        assert(driver.vkCreateImage && "vkCreateImage");

        driver.vkDestroyImage = (PFN_vkDestroyImage)driver.vkGetDeviceProcAddr(this->device, "vkDestroyImage");
        assert(driver.vkDestroyImage && "vkDestroyImage");

        driver.vkCreateImageView = (PFN_vkCreateImageView)driver.vkGetDeviceProcAddr(this->device, "vkCreateImageView");
        assert(driver.vkCreateImageView && "vkCreateImageView");

        driver.vkDestroyImageView = (PFN_vkDestroyImageView)driver.vkGetDeviceProcAddr(this->device, "vkDestroyImageView");
        assert(driver.vkDestroyImageView && "vkDestroyImageView");

        driver.vkCreateCommandPool = (PFN_vkCreateCommandPool)driver.vkGetDeviceProcAddr(this->device, "vkCreateCommandPool");
        assert(driver.vkCreateCommandPool && "vkCreateCommandPool");

        driver.vkDestroyCommandPool = (PFN_vkDestroyCommandPool)driver.vkGetDeviceProcAddr(this->device, "vkDestroyCommandPool");
        assert(driver.vkDestroyCommandPool && "vkDestroyCommandPool");

        driver.vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)driver.vkGetDeviceProcAddr(this->device, "vkAllocateCommandBuffers");
        assert(driver.vkAllocateCommandBuffers && "vkAllocateCommandBuffers");

        driver.vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)driver.vkGetDeviceProcAddr(this->device, "vkFreeCommandBuffers");
        assert(driver.vkFreeCommandBuffers && "vkFreeCommandBuffers");

        driver.vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)driver.vkGetDeviceProcAddr(this->device, "vkGetBufferMemoryRequirements");
        assert(driver.vkGetBufferMemoryRequirements && "vkGetBufferMemoryRequirements");

        driver.vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)driver.vkGetDeviceProcAddr(this->device, "vkGetImageMemoryRequirements");
        assert(driver.vkGetImageMemoryRequirements && "vkGetImageMemoryRequirements");

        driver.vkAllocateMemory = (PFN_vkAllocateMemory)driver.vkGetDeviceProcAddr(this->device, "vkAllocateMemory");
        assert(driver.vkAllocateMemory && "vkAllocateMemory");

        driver.vkFreeMemory = (PFN_vkFreeMemory)driver.vkGetDeviceProcAddr(this->device, "vkFreeMemory");
        assert(driver.vkFreeMemory && "vkFreeMemory");

        driver.vkBindImageMemory = (PFN_vkBindImageMemory)driver.vkGetDeviceProcAddr(this->device, "vkBindImageMemory");
        assert(driver.vkBindImageMemory && "vkBindImageMemory");

        driver.vkBindBufferMemory = (PFN_vkBindBufferMemory)driver.vkGetDeviceProcAddr(this->device, "vkBindBufferMemory");
        assert(driver.vkBindBufferMemory && "vkBindBufferMemory");

        driver.vkCreateBuffer = (PFN_vkCreateBuffer)driver.vkGetDeviceProcAddr(this->device, "vkCreateBuffer");
        assert(driver.vkCreateBuffer && "vkCreateBuffer");

        driver.vkDestroyBuffer = (PFN_vkDestroyBuffer)driver.vkGetDeviceProcAddr(this->device, "vkDestroyBuffer");
        assert(driver.vkDestroyBuffer && "vkDestroyBuffer");

        driver.vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)driver.vkGetDeviceProcAddr(this->device, "vkBeginCommandBuffer");
        assert(driver.vkBeginCommandBuffer && "vkBeginCommandBuffer");

        driver.vkEndCommandBuffer = (PFN_vkEndCommandBuffer)driver.vkGetDeviceProcAddr(this->device, "vkEndCommandBuffer");
        assert(driver.vkEndCommandBuffer && "vkEndCommandBuffer");

        driver.vkMapMemory = (PFN_vkMapMemory)driver.vkGetDeviceProcAddr(this->device, "vkMapMemory");
        assert(driver.vkMapMemory && "vkMapMemory");

        driver.vkUnmapMemory = (PFN_vkUnmapMemory)driver.vkGetDeviceProcAddr(this->device, "vkUnmapMemory");
        assert(driver.vkUnmapMemory && "vkUnmapMemory");

        driver.vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)driver.vkGetDeviceProcAddr(this->device, "vkCmdPipelineBarrier");
        assert(driver.vkCmdPipelineBarrier && "vkCmdPipelineBarrier");

        driver.vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)driver.vkGetDeviceProcAddr(this->device, "vkCmdCopyBufferToImage");
        assert(driver.vkCmdCopyBufferToImage && "vkCmdCopyBufferToImage");

        driver.vkQueueSubmit = (PFN_vkQueueSubmit)driver.vkGetDeviceProcAddr(this->device, "vkQueueSubmit");
        assert(driver.vkQueueSubmit && "vkQueueSubmit");

        driver.vkCreateFence = (PFN_vkCreateFence)driver.vkGetDeviceProcAddr(this->device, "vkCreateFence");
        assert(driver.vkCreateFence && "vkCreateFence");

        driver.vkDestroyFence = (PFN_vkDestroyFence)driver.vkGetDeviceProcAddr(this->device, "vkDestroyFence");
        assert(driver.vkDestroyFence && "vkDestroyFence");

        driver.vkWaitForFences = (PFN_vkWaitForFences)driver.vkGetDeviceProcAddr(this->device, "vkWaitForFences");
        assert(driver.vkWaitForFences && "vkWaitForFences");

        driver.vkCreateShaderModule = (PFN_vkCreateShaderModule)driver.vkGetDeviceProcAddr(this->device, "vkCreateShaderModule");
        assert(driver.vkCreateShaderModule && "vkCreateShaderModule");

        driver.vkDestroyShaderModule = (PFN_vkDestroyShaderModule)driver.vkGetDeviceProcAddr(this->device, "vkDestroyShaderModule");
        assert(driver.vkDestroyShaderModule && "vkDestroyShaderModule");

        driver.vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)driver.vkGetDeviceProcAddr(this->device, "vkCreateDescriptorPool");
        assert(driver.vkCreateDescriptorPool && "vkCreateDescriptorPool");

        driver.vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)driver.vkGetDeviceProcAddr(this->device, "vkDestroyDescriptorPool");
        assert(driver.vkDestroyDescriptorPool && "vkDestroyDescriptorPool");

        driver.vkCreateRenderPass = (PFN_vkCreateRenderPass)driver.vkGetDeviceProcAddr(this->device, "vkCreateRenderPass");
        assert(driver.vkCreateRenderPass && "vkCreateRenderPass");

        driver.vkDestroyRenderPass = (PFN_vkDestroyRenderPass)driver.vkGetDeviceProcAddr(this->device, "vkDestroyRenderPass");
        assert(driver.vkDestroyRenderPass && "vkDestroyRenderPass");

        driver.vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)driver.vkGetDeviceProcAddr(this->device, "vkCreateGraphicsPipelines");
        assert(driver.vkCreateGraphicsPipelines && "vkCreateGraphicsPipelines");

        driver.vkDestroyPipeline = (PFN_vkDestroyPipeline)driver.vkGetDeviceProcAddr(this->device, "vkDestroyPipeline");
        assert(driver.vkDestroyPipeline && "vkDestroyPipeline");

        driver.vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)driver.vkGetDeviceProcAddr(this->device, "vkCreateDescriptorSetLayout");
        assert(driver.vkCreateDescriptorSetLayout && "vkDestroyPipeline");

        driver.vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)driver.vkGetDeviceProcAddr(this->device, "vkDestroyDescriptorSetLayout");
        assert(driver.vkDestroyDescriptorSetLayout && "vkDestroyDescriptorSetLayout");

        driver.vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)driver.vkGetDeviceProcAddr(this->device, "vkAcquireNextImageKHR");
        assert(driver.vkAcquireNextImageKHR && "vkAcquireNextImageKHR");

        driver.vkCreateSampler = (PFN_vkCreateSampler)driver.vkGetDeviceProcAddr(this->device, "vkCreateSampler");
        assert(driver.vkCreateSampler && "vkCreateSampler");

        driver.vkDestroySampler = (PFN_vkDestroySampler)driver.vkGetDeviceProcAddr(this->device, "vkDestroySampler");
        assert(driver.vkDestroySampler && "vkDestroySampler");

        driver.vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)driver.vkGetDeviceProcAddr(this->device, "vkAllocateDescriptorSets");
        assert(driver.vkAllocateDescriptorSets && "vkAllocateDescriptorSets");

        driver.vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets)driver.vkGetDeviceProcAddr(this->device, "vkFreeDescriptorSets");
        assert(driver.vkFreeDescriptorSets && "vkFreeDescriptorSets");

        driver.vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)driver.vkGetDeviceProcAddr(this->device, "vkUpdateDescriptorSets");
        assert(driver.vkUpdateDescriptorSets && "vkUpdateDescriptorSets");

        driver.vkCreateFramebuffer = (PFN_vkCreateFramebuffer)driver.vkGetDeviceProcAddr(this->device, "vkCreateFramebuffer");
        assert(driver.vkCreateFramebuffer && "vkCreateFramebuffer");

        driver.vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)driver.vkGetDeviceProcAddr(this->device, "vkDestroyFramebuffer");
        assert(driver.vkDestroyFramebuffer && "vkDestroyFramebuffer");

        driver.vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)driver.vkGetDeviceProcAddr(this->device, "vkCmdBeginRenderPass");
        assert(driver.vkCmdBeginRenderPass && "vkCmdBeginRenderPass");

        driver.vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)driver.vkGetDeviceProcAddr(this->device, "vkCmdEndRenderPass");
        assert(driver.vkCmdEndRenderPass && "vkCmdEndRenderPass");

        driver.vkCmdBindPipeline = (PFN_vkCmdBindPipeline)driver.vkGetDeviceProcAddr(this->device, "vkCmdBindPipeline");
        assert(driver.vkCmdBindPipeline && "vkCmdBindPipeline");

        driver.vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)driver.vkGetDeviceProcAddr(this->device, "vkCmdBindDescriptorSets");
        assert(driver.vkCmdBindDescriptorSets && "vkCmdBindDescriptorSets");

        driver.vkCmdSetViewport = (PFN_vkCmdSetViewport)driver.vkGetDeviceProcAddr(this->device, "vkCmdSetViewport");
        assert(driver.vkCmdSetViewport && "vkCmdSetViewport");

        driver.vkCmdSetScissor = (PFN_vkCmdSetScissor)driver.vkGetDeviceProcAddr(this->device, "vkCmdSetScissor");
        assert(driver.vkCmdSetScissor && "vkCmdSetScissor");

        driver.vkCmdPushConstants = (PFN_vkCmdPushConstants)driver.vkGetDeviceProcAddr(this->device, "vkCmdPushConstants");
        assert(driver.vkCmdPushConstants && "vkCmdPushConstants");

        driver.vkCmdDraw = (PFN_vkCmdDraw)driver.vkGetDeviceProcAddr(this->device, "vkCmdDraw");
        assert(driver.vkCmdDraw && "vkCmdDraw");
    }

    driver.vkGetDeviceQueue = (PFN_vkGetDeviceQueue)driver.vkGetDeviceProcAddr(this->device, "vkGetDeviceQueue");
    assert(driver.vkGetDeviceQueue && "vkGetDeviceQueue");

    driver.vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)driver.vkGetDeviceProcAddr(this->device, "vkCreatePipelineLayout");
    assert(driver.vkCreatePipelineLayout && "vkCreatePipelineLayout");

    driver.vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)driver.vkGetDeviceProcAddr(this->device, "vkDestroyPipelineLayout");
    assert(driver.vkDestroyPipelineLayout && "vkDestroyPipelineLayout");

    driver.vkQueuePresentKHR = (PFN_vkQueuePresentKHR)driver.vkGetDeviceProcAddr(this->device, "vkQueuePresentKHR");
    assert(driver.vkQueuePresentKHR && "vkQueuePresentKHR");

    driver.vkGetDeviceQueue(this->device, graphics_queue_family_index, 0, &this->queue);

    uint32_t queue_family_index = graphics_queue_family_index;

    VkPhysicalDeviceMemoryProperties vk_physical_device_memory_properties = {};
    driver.vkGetPhysicalDeviceMemoryProperties(this->targetPhysicalDevice, &vk_physical_device_memory_properties);

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

    MyPrint("visible coherent memory index: %{public}u\n", visible_coherent_memory_index);
    MyPrint("device local memory index: %{public}u\n", device_local_memory_index);

    if (visible_coherent_memory_index == std::numeric_limits<uint32_t>::max() || device_local_memory_index == std::numeric_limits<uint32_t>::max())
    {
        throw std::runtime_error("Can not find support memory!");
    }

    VkCommandPoolCreateInfo vk_command_pool_create_info = {};
    vk_command_pool_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    vk_command_pool_create_info.pNext = nullptr;
    vk_command_pool_create_info.flags = 0;
    vk_command_pool_create_info.queueFamilyIndex = queue_family_index;
    driver.vkCreateCommandPool(this->device, &vk_command_pool_create_info, nullptr, &this->commandPool);
}

VulkanTriangle::~VulkanTriangle()
{
    for (VkFramebuffer vk_frame_buffeer_item : this->frameBuffers)
    {
        driver.vkDestroyFramebuffer(this->device, vk_frame_buffeer_item, nullptr);
    }

    driver.vkDestroyPipeline(this->device, this->pipeline, nullptr);

    driver.vkDestroyPipelineLayout(this->device, this->pipelineLayout, nullptr);

    driver.vkDestroyRenderPass(this->device, this->renderPass, nullptr);
    driver.vkDestroyDescriptorPool(this->device, this->descriptorPool, nullptr);

    for (VkImageView &vk_image_view_item : this->swapchainImageViews)
    {
        driver.vkDestroyImageView(this->device, vk_image_view_item, nullptr);
    }

    // driver.vkFreeCommandBuffers(vk_device, vk_command_pool, 1, &vk_command_buffer);

    driver.vkDestroyCommandPool(this->device, this->commandPool, nullptr);

    driver.vkDestroySwapchainKHR(this->device, this->swapchain, nullptr);
    driver.vkDestroySurfaceKHR(this->instance, this->surface, nullptr);

    driver.vkDestroyDevice(this->device, nullptr);
    MyPrint("vkDestroyDevice success\n");

    driver.vkDestroyInstance(this->instance, nullptr);
    MyPrint("vkDestroyInstance success\n");
}

void VulkanTriangle::CreateSurface(void *window,uint32_t width, uint32_t height)
{
    MyPrint("VulkanTriangle::CreateSurface(width = %{public}u, height = %{public}u)\n",width,height);
    if (window == nullptr)
    {
        throw std::runtime_error("Can not get window when surface create!");
    }

#if defined(USE_WINDOWS_PLATFORM) || defined(USE_LINUX_PLATFORM)
    glfwCreateWindowSurface(this->instance, (GLFWwindow *)window, NULL, &this->surface);
#elif defined(USE_HARMONY_OS_PLATFORM)
    driver.vkCreateSurfaceOHOS = (PFN_vkCreateSurfaceOHOS)driver.vkGetInstanceProcAddr(this->instance, "vkCreateSurfaceOHOS");
    assert(driver.vkCreateSurfaceOHOS && "vkCreateSurfaceOHOS");

    VkSurfaceCreateInfoOHOS vk_surface_create_info_ohos = {};
    vk_surface_create_info_ohos.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    vk_surface_create_info_ohos.pNext = nullptr;
    vk_surface_create_info_ohos.flags = 0;
    vk_surface_create_info_ohos.window = (OHNativeWindow *)window;

   VkResult result= driver.vkCreateSurfaceOHOS(this->instance, &vk_surface_create_info_ohos, nullptr, &this->surface);
    if(result==VkResult::VK_SUCCESS)
    {
        MyPrint("vkCreateSurfaceOHOS success\n");
    } else{
                MyPrint("[Error] vkCreateSurfaceOHOS failed!\n");
    }
#else
    throw std::runtime_error("Not compatible with this platform!");
#endif

    driver.vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)driver.vkGetInstanceProcAddr(this->instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
    assert(driver.vkGetPhysicalDeviceSurfaceFormatsKHR && "vkGetPhysicalDeviceSurfaceFormatsKHR");

    driver.vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)driver.vkGetInstanceProcAddr(this->instance, "vkDestroySurfaceKHR");
    assert(driver.vkDestroySurfaceKHR && "vkDestroySurfaceKHR");

    driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)driver.vkGetInstanceProcAddr(this->instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
    assert(driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR && "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");

    driver.vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)driver.vkGetDeviceProcAddr(this->device, "vkCreateSwapchainKHR");
    assert(driver.vkCreateSwapchainKHR && "vkCreateSwapchainKHR");

    driver.vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)driver.vkGetDeviceProcAddr(this->device, "vkDestroySwapchainKHR");
    assert(driver.vkDestroySwapchainKHR && "vkDestroySwapchainKHR");

    VkSurfaceCapabilitiesKHR vk_surface_capabilities_khr = {};
    driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->targetPhysicalDevice, this->surface, &vk_surface_capabilities_khr);
{
        MyPrint("CreateSurface::vk_surface_capabilities_khr:");
        PrintVkSurfaceTransformFlagsKHR(vk_surface_capabilities_khr.supportedTransforms);
}
    
{
       vk_surface_capabilities_khr.currentExtent.width= width;
       vk_surface_capabilities_khr.currentExtent.height= height;
}

    this->surfaceWidth = vk_surface_capabilities_khr.currentExtent.width;
    this->surfaceHeight = vk_surface_capabilities_khr.currentExtent.height;

    driver.vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)driver.vkGetInstanceProcAddr(this->instance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
    assert(driver.vkGetPhysicalDeviceSurfacePresentModesKHR && "vkGetPhysicalDeviceSurfacePresentModesKHR");

    uint32_t swapchain_present_mode_count = 0;
    driver.vkGetPhysicalDeviceSurfacePresentModesKHR(this->targetPhysicalDevice, this->surface, &swapchain_present_mode_count, nullptr);
    if (swapchain_present_mode_count != 0)
    {
        this->presentModes.resize(swapchain_present_mode_count);
        driver.vkGetPhysicalDeviceSurfacePresentModesKHR(this->targetPhysicalDevice, this->surface, &swapchain_present_mode_count, this->presentModes.data());
    }

    for (VkPresentModeKHR present_mode_item : this->presentModes)
    {
        if (present_mode_item == VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR)
        {
            this->isSwapchainSupportFifo = true;
        }
    }

    {
        uint32_t surface_format_count = 0;
        driver.vkGetPhysicalDeviceSurfaceFormatsKHR(this->targetPhysicalDevice, this->surface, &surface_format_count, nullptr);
        std::vector<VkSurfaceFormatKHR> surface_formats(surface_format_count);
        driver.vkGetPhysicalDeviceSurfaceFormatsKHR(this->targetPhysicalDevice, this->surface, &surface_format_count, surface_formats.data());
        for (auto &surface_format : surface_formats)
        {
            VkFormatProperties vk_format_properties = {};
            driver.vkGetPhysicalDeviceFormatProperties(this->targetPhysicalDevice, surface_format.format, &vk_format_properties);
            if ((vk_format_properties.optimalTilingFeatures & VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT && surface_format.colorSpace == VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                this->targetSwapchainFormat = surface_format.format;
                break;
            }
        }
    }

    if (this->targetSwapchainFormat == VkFormat::VK_FORMAT_UNDEFINED)
    {
        throw std::runtime_error("Can not find a appropriate format for swapchain as color attachment!");
    }

    MyPrint("swapchain use %{public}s format\n", to_string(this->targetSwapchainFormat).c_str());

    VkSwapchainCreateInfoKHR vk_swapchain_create_info_khr = {};
    vk_swapchain_create_info_khr.sType = VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    vk_swapchain_create_info_khr.pNext = nullptr;
    vk_swapchain_create_info_khr.flags = 0;
    vk_swapchain_create_info_khr.surface = this->surface;
    vk_swapchain_create_info_khr.minImageCount = std::max(vk_surface_capabilities_khr.minImageCount, vk_surface_capabilities_khr.maxImageCount);
    vk_swapchain_create_info_khr.imageFormat = this->targetSwapchainFormat;
    vk_swapchain_create_info_khr.imageColorSpace = this->targetSwapchainColorSpace;
    vk_swapchain_create_info_khr.imageExtent = vk_surface_capabilities_khr.currentExtent;
    //vk_swapchain_create_info_khr.imageExtent = vk_surface_capabilities_khr.minImageExtent;
    vk_swapchain_create_info_khr.imageArrayLayers = 1;
    vk_swapchain_create_info_khr.imageUsage = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    vk_swapchain_create_info_khr.imageSharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
    vk_swapchain_create_info_khr.queueFamilyIndexCount = 0;
    vk_swapchain_create_info_khr.pQueueFamilyIndices = nullptr;
    vk_swapchain_create_info_khr.preTransform = vk_surface_capabilities_khr.currentTransform;
    vk_swapchain_create_info_khr.compositeAlpha = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    vk_swapchain_create_info_khr.presentMode = this->isSwapchainSupportFifo ? VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR : this->presentModes[0];
    vk_swapchain_create_info_khr.clipped = VK_TRUE;
    vk_swapchain_create_info_khr.oldSwapchain = VK_NULL_HANDLE;
    MyPrint("CreateSurface::swapchain extent: (with = %{public}u, height = %{public}u)",vk_swapchain_create_info_khr.imageExtent.width,vk_swapchain_create_info_khr.imageExtent.height);
    driver.vkCreateSwapchainKHR(this->device, &vk_swapchain_create_info_khr, nullptr, &this->swapchain);
    {
        MyPrint("CreateSurface::vkCreateSwapchainKHR:");
        PrintVkSurfaceTransformFlagsKHR(vk_swapchain_create_info_khr.preTransform);
}

    driver.vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)driver.vkGetDeviceProcAddr(this->device, "vkGetSwapchainImagesKHR");
    assert(driver.vkGetSwapchainImagesKHR && "vkGetSwapchainImagesKHR");
    MyPrint("0");
    uint32_t swapchain_image_count = 0;
    MyPrint("0.2");
    driver.vkGetSwapchainImagesKHR(this->device, this->swapchain, &swapchain_image_count, nullptr);
    MyPrint("0.1.1");
    this->swapchainImages.resize(swapchain_image_count);
    MyPrint("0.1.2");
    driver.vkGetSwapchainImagesKHR(this->device, this->swapchain, &swapchain_image_count, this->swapchainImages.data());
    MyPrint("0.1.3");
    
    MyPrint("0.1");
    if (this->swapchainImages.empty())
    {
    MyPrint("0.1.4");
        
        throw std::runtime_error("Can not get swapchain images!");
    }
    MyPrint("1");
    this->swapchainImageViews.resize(swapchain_image_count);
    for (uint32_t swapchain_image_view_index = 0; swapchain_image_view_index < swapchain_image_count; swapchain_image_view_index++)
    {
        VkImageViewCreateInfo vk_image_view_create_info = {};
        vk_image_view_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        vk_image_view_create_info.pNext = nullptr;
        vk_image_view_create_info.flags = 0;
        vk_image_view_create_info.image = this->swapchainImages[swapchain_image_view_index];
        vk_image_view_create_info.viewType = VkImageViewType ::VK_IMAGE_VIEW_TYPE_2D;
        vk_image_view_create_info.format = this->targetSwapchainFormat;
        vk_image_view_create_info.components.r = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R;
        vk_image_view_create_info.components.g = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G;
        vk_image_view_create_info.components.b = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B;
        vk_image_view_create_info.components.a = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A;
        vk_image_view_create_info.subresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
        vk_image_view_create_info.subresourceRange.baseMipLevel = 0;
        vk_image_view_create_info.subresourceRange.levelCount = 1;
        vk_image_view_create_info.subresourceRange.baseArrayLayer = 0;
        vk_image_view_create_info.subresourceRange.layerCount = 1;

        driver.vkCreateImageView(this->device, &vk_image_view_create_info, nullptr, &this->swapchainImageViews[swapchain_image_view_index]);
    }

    VkShaderModule my_vertex_shader_module = VK_NULL_HANDLE;
    VkShaderModule my_fragment_shader_module = VK_NULL_HANDLE;
    {
        VkShaderModuleCreateInfo vk_shader_module_create_info = {};
        vk_shader_module_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        vk_shader_module_create_info.pNext = 0;
        vk_shader_module_create_info.flags = 0;
        vk_shader_module_create_info.codeSize = sizeof(MY_VERT_SHADER_BIN);
        vk_shader_module_create_info.pCode = MY_VERT_SHADER_BIN;

        VkResult result = driver.vkCreateShaderModule(this->device, &vk_shader_module_create_info, nullptr, &my_vertex_shader_module);
        if (result != VkResult::VK_SUCCESS)
        {
            throw std::runtime_error("Can not create vertex shader module!");
        }

        vk_shader_module_create_info.codeSize = sizeof(MY_FRAG_SHADER_BIN);
        vk_shader_module_create_info.pCode = MY_FRAG_SHADER_BIN;

        result = driver.vkCreateShaderModule(this->device, &vk_shader_module_create_info, nullptr, &my_fragment_shader_module);
        if (result != VkResult::VK_SUCCESS)
        {
            throw std::runtime_error("Can not create fragment shader module!");
        }
    }

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

        VkResult result = driver.vkCreateDescriptorPool(this->device, &vk_descriptor_pool_create_info, nullptr, &this->descriptorPool);
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
        color_attachment_description.format = this->targetSwapchainFormat;
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

        driver.vkCreateRenderPass(this->device, &vk_render_pass_create_info, nullptr, &this->renderPass);
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
    vk_viewport.width = vk_surface_capabilities_khr.currentExtent.width;
    vk_viewport.height = vk_surface_capabilities_khr.currentExtent.height;
    vk_viewport.minDepth = 0;
    vk_viewport.maxDepth = 1;

    VkRect2D scissor = {};
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = vk_surface_capabilities_khr.currentExtent.width;
    scissor.extent.height = vk_surface_capabilities_khr.currentExtent.height;

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

    VkPushConstantRange vk_push_constant_range = {};
    vk_push_constant_range.stageFlags = VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
    vk_push_constant_range.offset = 0;
    vk_push_constant_range.size = sizeof(float);

    VkPipelineLayoutCreateInfo vk_pipeline_layout_create_info = {};
    vk_pipeline_layout_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    vk_pipeline_layout_create_info.pNext = nullptr;
    vk_pipeline_layout_create_info.flags = 0;
    vk_pipeline_layout_create_info.setLayoutCount = 0;
    vk_pipeline_layout_create_info.pSetLayouts = nullptr;
    vk_pipeline_layout_create_info.pushConstantRangeCount = 1;
    vk_pipeline_layout_create_info.pPushConstantRanges = &vk_push_constant_range;

    driver.vkCreatePipelineLayout(this->device, &vk_pipeline_layout_create_info, nullptr, &this->pipelineLayout);
    MyPrint("2");
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
    vk_graphics_pipeline_create_info.layout = this->pipelineLayout;
    vk_graphics_pipeline_create_info.renderPass = this->renderPass;
    vk_graphics_pipeline_create_info.subpass = 0;
    vk_graphics_pipeline_create_info.basePipelineHandle = VK_NULL_HANDLE;
    vk_graphics_pipeline_create_info.basePipelineIndex = 0;

    VkResult pipeline_create_result = driver.vkCreateGraphicsPipelines(this->device, VK_NULL_HANDLE, 1, &vk_graphics_pipeline_create_info, nullptr, &this->pipeline);
    if (pipeline_create_result != VkResult::VK_SUCCESS)
    {
        MyPrint("pipeline_create_result: %{public}u\n", pipeline_create_result);
        throw std::runtime_error("Can not create rendering pipeline!");
    }

    driver.vkDestroyShaderModule(this->device, my_fragment_shader_module, nullptr);
    driver.vkDestroyShaderModule(this->device, my_vertex_shader_module, nullptr);

    for (uint32_t swapchain_image_view_index = 0; swapchain_image_view_index < this->swapchainImageViews.size(); swapchain_image_view_index++)
    {
        std::vector<VkImageView> frame_buffer;
        frame_buffer.push_back(this->swapchainImageViews[swapchain_image_view_index]);

        VkFramebufferCreateInfo vk_frame_buffer_create_info = {};
        vk_frame_buffer_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        vk_frame_buffer_create_info.pNext = nullptr;
        vk_frame_buffer_create_info.flags = 0;
        vk_frame_buffer_create_info.renderPass = this->renderPass;
        vk_frame_buffer_create_info.attachmentCount = frame_buffer.size();
        vk_frame_buffer_create_info.pAttachments = frame_buffer.data();
        vk_frame_buffer_create_info.width = vk_surface_capabilities_khr.currentExtent.width;
        vk_frame_buffer_create_info.height = vk_surface_capabilities_khr.currentExtent.height;
        vk_frame_buffer_create_info.layers = 1;

        VkFramebuffer vk_frame_buffer = VK_NULL_HANDLE;
        VkResult frame_buffer_create_result = driver.vkCreateFramebuffer(this->device, &vk_frame_buffer_create_info, nullptr, &vk_frame_buffer);
        if (frame_buffer_create_result != VkResult::VK_SUCCESS)
        {
            throw std::runtime_error("Can not create Framebuffer!");
        }

        this->frameBuffers.push_back(vk_frame_buffer);
    }
    
    MyPrint("[CreateSurface] END");
}

void VulkanTriangle::Draw(float time)
{
    // static float game_time = 0;
    // static auto previous_point = std::chrono::steady_clock::now();
    // auto current_point = std::chrono::steady_clock::now();
    // const std::chrono::duration<float> delta = current_point - previous_point;
    // previous_point = current_point;
    // game_time += delta.count();
    
    //MyPrint("time = %{public}f",time);
    if((int)time%5==0)
    {
        VkSurfaceCapabilitiesKHR vk_surface_capabilities_khr = {};
        driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->targetPhysicalDevice, this->surface, &vk_surface_capabilities_khr);
        {
            static size_t index=0;
            //MyPrint("%{public}u Draw::vk_surface_capabilities_khr:Support Transform:",index);
            //PrintVkSurfaceTransformFlagsKHR(vk_surface_capabilities_khr.supportedTransforms);
            MyPrint("%{public}u Draw::vk_surface_capabilities_khr:Current Transform:",index);
            PrintVkSurfaceTransformFlagsKHR(vk_surface_capabilities_khr.currentTransform);
            MyPrint("\n");
            index++;
        }
    }

    static auto previous_point = time;
    auto current_point = time;
    float delta = current_point - previous_point;
    previous_point = current_point;

    float scale = (std::sin(time * 0.5) + 1) * 0.5; //[0, 1]

    uint32_t next_image_index = UINT32_MAX;

    VkFence require_next_image_fence = VK_NULL_HANDLE;
    {
        VkFenceCreateInfo vk_fence_create_info = {};
        vk_fence_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        vk_fence_create_info.pNext = nullptr;
        vk_fence_create_info.flags = 0;

        driver.vkCreateFence(this->device, &vk_fence_create_info, nullptr, &require_next_image_fence);
    }
    VkResult next_image_require_result = driver.vkAcquireNextImageKHR(this->device, this->swapchain, UINT64_MAX - 1, VK_NULL_HANDLE, require_next_image_fence, &next_image_index);
    if (next_image_require_result == VkResult::VK_ERROR_OUT_OF_DATE_KHR || next_image_require_result == VkResult::VK_SUBOPTIMAL_KHR)
    {
        driver.vkDestroyFence(this->device, require_next_image_fence, nullptr);

        VkSurfaceCapabilitiesKHR vk_surface_capabilities_khr = {};
        driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->targetPhysicalDevice, this->surface, &vk_surface_capabilities_khr);
        {
            MyPrint("Draw::vk_surface_capabilities_khr:");
            PrintVkSurfaceTransformFlagsKHR(vk_surface_capabilities_khr.supportedTransforms);
        }

        MyPrint("new (width = %{public}u, height = %{public}u)\n", vk_surface_capabilities_khr.currentExtent.width, vk_surface_capabilities_khr.currentExtent.height);

        if (vk_surface_capabilities_khr.currentExtent.width == 0 || vk_surface_capabilities_khr.currentExtent.height == 0)
        {
            // TODO: not drawing
            return;
        }

        //  TODO: resize in here
        {
            for (auto &vk_frame_buffer : this->frameBuffers)
            {
                driver.vkDestroyFramebuffer(this->device, vk_frame_buffer, nullptr);
            }
            this->frameBuffers.clear();

            for (auto &swapchain_image_view : this->swapchainImageViews)
            {
                driver.vkDestroyImageView(this->device, swapchain_image_view, nullptr);
            }
            this->swapchainImageViews.clear();
            this->swapchainImages.clear();

            VkSwapchainKHR old_swapchain = this->swapchain;
            VkSwapchainCreateInfoKHR vk_swapchain_create_info_khr = {};
            vk_swapchain_create_info_khr.sType = VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            vk_swapchain_create_info_khr.pNext = nullptr;
            vk_swapchain_create_info_khr.flags = 0;
            vk_swapchain_create_info_khr.surface = this->surface;
            vk_swapchain_create_info_khr.minImageCount = std::max(vk_surface_capabilities_khr.minImageCount, vk_surface_capabilities_khr.maxImageCount);
            vk_swapchain_create_info_khr.imageFormat = this->targetSwapchainFormat;
            vk_swapchain_create_info_khr.imageColorSpace = this->targetSwapchainColorSpace;
            vk_swapchain_create_info_khr.imageExtent = vk_surface_capabilities_khr.currentExtent;
            vk_swapchain_create_info_khr.imageArrayLayers = 1;
            vk_swapchain_create_info_khr.imageUsage = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
            vk_swapchain_create_info_khr.imageSharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
            vk_swapchain_create_info_khr.queueFamilyIndexCount = 0;
            vk_swapchain_create_info_khr.pQueueFamilyIndices = nullptr;
            vk_swapchain_create_info_khr.preTransform = vk_surface_capabilities_khr.currentTransform;
            vk_swapchain_create_info_khr.compositeAlpha = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            vk_swapchain_create_info_khr.presentMode = this->isSwapchainSupportFifo ? VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR : this->presentModes[0];
            vk_swapchain_create_info_khr.clipped = VK_TRUE;
            vk_swapchain_create_info_khr.oldSwapchain = old_swapchain;
            MyPrint("Draw::swapchain extent: (with = %{public}u, height = %{public}u)",vk_swapchain_create_info_khr.imageExtent.width,vk_swapchain_create_info_khr.imageExtent.height);
            VkResult new_create_swapchain_result = driver.vkCreateSwapchainKHR(this->device, &vk_swapchain_create_info_khr, nullptr, &this->swapchain);
    {
        MyPrint("Draw::vkCreateSwapchainKHR:");
        PrintVkSurfaceTransformFlagsKHR(vk_swapchain_create_info_khr.preTransform);
}
            if (new_create_swapchain_result == VkResult::VK_SUCCESS)
            {
                driver.vkDestroySwapchainKHR(this->device, vk_swapchain_create_info_khr.oldSwapchain, nullptr);
                // driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->targetPhysicalDevice, this->surface, &vk_surface_capabilities_khr);

                this->surfaceWidth = vk_surface_capabilities_khr.currentExtent.width;
                this->surfaceHeight = vk_surface_capabilities_khr.currentExtent.height;
                
                MyPrint("Draw::vkCreateSwapchainKHR::SUCCESS");
            } 
        else
            {
                MyPrint("[Alarm] Draw::vkCreateSwapchainKHR::%{public}u",new_create_swapchain_result);
                //MyPrint("Support Vulkan: .%{public}u.%{public}u\n", version_major, version_minor, version_patch);
            }

            uint32_t swapchain_image_count = 0;
            driver.vkGetSwapchainImagesKHR(this->device, this->swapchain, &swapchain_image_count, nullptr);
            this->swapchainImages.resize(swapchain_image_count);
            driver.vkGetSwapchainImagesKHR(this->device, this->swapchain, &swapchain_image_count, this->swapchainImages.data());

            if (this->swapchainImages.empty())
            {
                throw std::runtime_error("Can not get swapchain images!");
            }

            this->swapchainImageViews.resize(swapchain_image_count);
            for (uint32_t swapchain_image_view_index = 0; swapchain_image_view_index < swapchain_image_count; swapchain_image_view_index++)
            {
                VkImageViewCreateInfo vk_image_view_create_info = {};
                vk_image_view_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                vk_image_view_create_info.pNext = nullptr;
                vk_image_view_create_info.flags = 0;
                vk_image_view_create_info.image = this->swapchainImages[swapchain_image_view_index];
                vk_image_view_create_info.viewType = VkImageViewType ::VK_IMAGE_VIEW_TYPE_2D;
                vk_image_view_create_info.format = this->targetSwapchainFormat;
                vk_image_view_create_info.components.r = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R;
                vk_image_view_create_info.components.g = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G;
                vk_image_view_create_info.components.b = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B;
                vk_image_view_create_info.components.a = VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A;
                vk_image_view_create_info.subresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
                vk_image_view_create_info.subresourceRange.baseMipLevel = 0;
                vk_image_view_create_info.subresourceRange.levelCount = 1;
                vk_image_view_create_info.subresourceRange.baseArrayLayer = 0;
                vk_image_view_create_info.subresourceRange.layerCount = 1;

                driver.vkCreateImageView(this->device, &vk_image_view_create_info, nullptr, &this->swapchainImageViews[swapchain_image_view_index]);
            }

            for (uint32_t swapchain_image_view_index = 0; swapchain_image_view_index < swapchainImageViews.size(); swapchain_image_view_index++)
            {
                std::vector<VkImageView> frame_buffers;
                frame_buffers.push_back(swapchainImageViews[swapchain_image_view_index]);

                VkFramebufferCreateInfo vk_frame_buffer_create_info = {};
                vk_frame_buffer_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
                vk_frame_buffer_create_info.pNext = nullptr;
                vk_frame_buffer_create_info.flags = 0;
                vk_frame_buffer_create_info.renderPass = this->renderPass;
                vk_frame_buffer_create_info.attachmentCount = frame_buffers.size();
                vk_frame_buffer_create_info.pAttachments = frame_buffers.data();
                vk_frame_buffer_create_info.width = vk_surface_capabilities_khr.currentExtent.width;
                vk_frame_buffer_create_info.height = vk_surface_capabilities_khr.currentExtent.height;
                vk_frame_buffer_create_info.layers = 1;

                VkFramebuffer vk_frame_buffer = VK_NULL_HANDLE;
                VkResult frame_buffer_create_result = driver.vkCreateFramebuffer(this->device, &vk_frame_buffer_create_info, nullptr, &vk_frame_buffer);
                if (frame_buffer_create_result != VkResult::VK_SUCCESS)
                {
                    throw std::runtime_error("Can not create Framebuffer!");
                }

                this->frameBuffers.push_back(vk_frame_buffer);
            }
        }
        return;
    }

    {
        driver.vkWaitForFences(this->device, 1, &require_next_image_fence, VK_TRUE, UINT64_MAX);
        driver.vkDestroyFence(this->device, require_next_image_fence, nullptr);
    }

    VkCommandBuffer vk_command_buffer = VK_NULL_HANDLE;
    {
        VkCommandBufferAllocateInfo vk_command_buffer_allocate_info = {};
        vk_command_buffer_allocate_info.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        vk_command_buffer_allocate_info.pNext = nullptr;
        vk_command_buffer_allocate_info.commandPool = this->commandPool;
        vk_command_buffer_allocate_info.level = VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        vk_command_buffer_allocate_info.commandBufferCount = 1;
        driver.vkAllocateCommandBuffers(this->device, &vk_command_buffer_allocate_info, &vk_command_buffer);
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
    vk_render_pass_begin_info.renderPass = this->renderPass;
    vk_render_pass_begin_info.framebuffer = this->frameBuffers[next_image_index];
    vk_render_pass_begin_info.renderArea.offset.x = 0;
    vk_render_pass_begin_info.renderArea.offset.y = 0;
    vk_render_pass_begin_info.renderArea.extent.width = this->surfaceWidth;
    vk_render_pass_begin_info.renderArea.extent.height = this->surfaceHeight;
    // vk_render_pass_begin_info.renderArea.extent.width = 512;
    // vk_render_pass_begin_info.renderArea.extent.height = 512;
    vk_render_pass_begin_info.clearValueCount = vk_clear_values.size();
    vk_render_pass_begin_info.pClearValues = vk_clear_values.data();

    VkViewport vk_viewport = {};
    vk_viewport.x = 0;
    vk_viewport.y = 0;
    vk_viewport.width = this->surfaceWidth;
    vk_viewport.height = this->surfaceHeight;
    vk_viewport.minDepth = 0;
    vk_viewport.maxDepth = 1;

    VkRect2D scissor = {};
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = this->surfaceWidth;
    scissor.extent.height = this->surfaceHeight;

    driver.vkCmdBeginRenderPass(vk_command_buffer, &vk_render_pass_begin_info, VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE);
    driver.vkCmdBindPipeline(vk_command_buffer, VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, this->pipeline);
    driver.vkCmdSetViewport(vk_command_buffer, 0, 1, &vk_viewport);
    driver.vkCmdSetScissor(vk_command_buffer, 0, 1, &scissor);
    driver.vkCmdPushConstants(vk_command_buffer, this->pipelineLayout, VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(float), &scale);
    driver.vkCmdDraw(vk_command_buffer, 3, 1, 0, 0);

    driver.vkCmdEndRenderPass(vk_command_buffer);

    driver.vkEndCommandBuffer(vk_command_buffer);

    VkFence fence = VK_NULL_HANDLE;
    {
        VkFenceCreateInfo vk_fence_create_info = {};
        vk_fence_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        vk_fence_create_info.pNext = nullptr;
        vk_fence_create_info.flags = 0;

        driver.vkCreateFence(this->device, &vk_fence_create_info, nullptr, &fence);
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

    driver.vkQueueSubmit(this->queue, 1, &vk_submit_info, fence);
    driver.vkWaitForFences(this->device, 1, &fence, VK_TRUE, UINT64_MAX);
    driver.vkDestroyFence(this->device, fence, nullptr);
    driver.vkFreeCommandBuffers(this->device, this->commandPool, 1, &vk_command_buffer);

    VkPresentInfoKHR vk_present_info_khr = {};
    vk_present_info_khr.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    vk_present_info_khr.pNext = nullptr;
    vk_present_info_khr.waitSemaphoreCount = 0;
    vk_present_info_khr.pWaitSemaphores = nullptr;
    vk_present_info_khr.swapchainCount = 1;
    vk_present_info_khr.pSwapchains = &this->swapchain;
    vk_present_info_khr.pImageIndices = &next_image_index;
    vk_present_info_khr.pResults = nullptr;

    // TODO: load vkQueuePresentKHR(...) by TVulkanLoader
    driver.vkQueuePresentKHR(this->queue, &vk_present_info_khr);
    // Vulkan loop
}

#if defined(USE_WINDOWS_PLATFORM) || defined(USE_LINUX_PLATFORM)
int main()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Can not init glfw!");
    }

    GLFWwindow *window;
    int window_width = 512;
    int window_height = 512;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(window_width, window_height, "VulkanTriangle", NULL, NULL);

    VulkanTriangle vulkan_triangle;
    vulkan_triangle.CreateSurface(window);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        vulkan_triangle.Draw(glfwGetTime());
    }

    return 0;
}
#endif