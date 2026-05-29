#include <napi/native_api.h>
#include <string>
#include <hilog/log.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <native_window/external_window.h>
#include <native_vsync/native_vsync.h>
#include <unordered_map>

#include <VulkanTriangle.h>

VulkanTriangle VULKAN_TRIANGLE;

#define LOG_PRINT_DOMAIN 0x1
#define VSYNC_NAME "VulkanTriangleVSync"
OH_NativeVSync *NATIVE_VSYNC = nullptr;

void OnVsync(long long timestamp, void *data)
{
    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_PRINT_DOMAIN, "VulkanTriangle", "OnVsync %{public}lld.", timestamp);
    // TODO: Rendering Loop
    VULKAN_TRIANGLE.Draw(timestamp * 0.001);
    OH_NativeVSync_RequestFrame(NATIVE_VSYNC, &OnVsync, nullptr);
}

void OnSurfaceCreated(OH_NativeXComponent *component, void *window)
{
    OHNativeWindow *native_window = static_cast<OHNativeWindow *>(window);
    VULKAN_TRIANGLE.CreateSurface(native_window);
    // TODO: Create VkSurface

    {
        NATIVE_VSYNC = OH_NativeVSync_Create(VSYNC_NAME, strlen(VSYNC_NAME));

        OH_NativeVSync_RequestFrame(NATIVE_VSYNC, &OnVsync, nullptr);

        long long period = 0;
        OH_NativeVSync_GetPeriod(NATIVE_VSYNC, &period);
    }
}

void OnSurfaceChanged(OH_NativeXComponent *component, void *window)
{
    OHNativeWindow *nativeWindow = static_cast<OHNativeWindow *>(window);

    // TODO: Recreate VkSurface and update state
}

void OnSurfaceDestroyed(OH_NativeXComponent *component, void *window)
{
    OHNativeWindow *nativeWindow = static_cast<OHNativeWindow *>(window);

    {
        OH_NativeVSync_Destroy(NATIVE_VSYNC);
        NATIVE_VSYNC = nullptr;
    }

    // TODO: Destroy VkSurface
}

void DispatchTouchEvent(OH_NativeXComponent *component, void *window)
{
    OHNativeWindow *nativeWindow = static_cast<OHNativeWindow *>(window);
}

void OnNativeXComponentInit(OH_NativeXComponent *nativeXComponent)
{
    uint64_t id_size = OH_XCOMPONENT_ID_LEN_MAX + 1;
    char id[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};

    if (OH_NativeXComponent_GetXComponentId(nativeXComponent, id, &id_size) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS)
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Init", "OH_NativeXComponent_GetXComponentId(nativeXComponent, id, id_size) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS");
        return;
    }

    OH_NativeXComponent_Callback callback;
    callback.OnSurfaceCreated = OnSurfaceCreated;     // surface创建成功后触发，开发者可以从中获取native window的句柄
    callback.OnSurfaceChanged = OnSurfaceChanged;     // surface发生变化后触发，开发者可以从中获取native window的句柄以及XComponent的变更信息
    callback.OnSurfaceDestroyed = OnSurfaceDestroyed; // surface销毁时触发，开发者可以在此释放资源
    callback.DispatchTouchEvent = DispatchTouchEvent; // XComponent的touch事件回调接口，开发者可以从中获得此次touch事件的信息

    OH_NativeXComponent_RegisterCallback(nativeXComponent, &callback);
}

void OnVulkanInit()
{
    // TODO: Init Vulkan
}

extern "C"
{
    static napi_value Init(napi_env env, napi_value exports)
    {
        static bool is_napi_define_properties = false;
        if (!is_napi_define_properties)
        {
            napi_property_descriptor desc[] = {
                //{"myAdd", nullptr, MyAdd, nullptr, nullptr, nullptr, napi_default, nullptr}
            };
            napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);

            OnVulkanInit();

            is_napi_define_properties = true;
            return exports;
        }

        {
            napi_status status;
            napi_value xcomponent_object = nullptr;
            status = napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &xcomponent_object);
            if (status != napi_ok)
            {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Init", "napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &xcomponent_object)");
                return nullptr;
            }

            OH_NativeXComponent *native_xcomponent = nullptr;
            status = napi_unwrap(env, xcomponent_object, reinterpret_cast<void **>(&native_xcomponent));
            if (status != napi_ok)
            {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Init", "napi_unwrap(env, xcomponent_object, reinterpret_cast<void **>(&native_xcomponent))");
                return nullptr;
            }

            {
                OnNativeXComponentInit(native_xcomponent);
            }
        }

        return exports;
    }
}

static napi_module VULKAN_TRIANGLE_MODULE = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "VulkanTriangle",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterVulkanTriangleModule()
{
    napi_module_register(&VULKAN_TRIANGLE_MODULE);
}