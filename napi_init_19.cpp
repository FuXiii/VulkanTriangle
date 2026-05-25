#include <napi/native_api.h>
#include <hilog/log.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <native_window/external_window.h>
#include <arkui/native_node_napi.h>

#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <native_display_soloist/native_display_soloist.h>

#include <string>
#include <unordered_map>

#define LOG_PRINT_DOMAIN 0x1

ArkUI_NativeNodeAPI_1 *NODE_API_1 = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));

struct SurfaceData
{
    std::string id;
    ArkUI_NodeHandle handle;
    OH_ArkUI_SurfaceHolder *holder = nullptr;
    OH_ArkUI_SurfaceCallback *callback = nullptr;
    OH_DisplaySoloist *displaySoloist = nullptr;
};

std::unordered_map<std::string, SurfaceData *> SURFACE_DATA_MAP;

void OnDisplaySoloistFrameCallback(long long timestamp, long long targetTimestamp, void *data)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "OnDisplaySoloistFrameCallback", "on display soloist frame callback");
}

void OnSurfaceCreated(OH_ArkUI_SurfaceHolder *holder)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "OnSurfaceCreated", "on surface created");

    SurfaceData *surface_data = (SurfaceData *)OH_ArkUI_SurfaceHolder_GetUserData(holder);
    if (surface_data != nullptr)
    {
        OH_DisplaySoloist_Start(surface_data->displaySoloist, OnDisplaySoloistFrameCallback, nullptr);
    }
}

void OnSurfaceChanged(OH_ArkUI_SurfaceHolder *holder, uint64_t width, uint64_t height)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "OnSurfaceChanged", "on surface changed");
}

void OnSurfaceDestroyed(OH_ArkUI_SurfaceHolder *holder)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "OnSurfaceDestroyed", "on surface destroyed");

    SurfaceData *surface_data = (SurfaceData *)OH_ArkUI_SurfaceHolder_GetUserData(holder);
    if (surface_data != nullptr)
    {
        OH_DisplaySoloist_Stop(surface_data->displaySoloist);
        OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback(surface_data->holder, surface_data->callback);
        OH_ArkUI_SurfaceCallback_Dispose(surface_data->callback);
        OH_ArkUI_SurfaceHolder_Dispose(surface_data->holder); // 销毁surfaceHolder
    }
}

void OnSurfaceShow(OH_ArkUI_SurfaceHolder *holder)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "OnSurfaceShow", "on surface show");
}

void OnSurfaceHide(OH_ArkUI_SurfaceHolder *holder)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "OnSurfaceHide", "on surface hide");
}

/*
ArkUI侧：
    native.bindNode(this.xcomponentId, this.getUIContext().getFrameNodeById(this.xcomponentId))
*/
napi_value BindNode(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    size_t id_str_size = 0;
    napi_get_value_string_utf8(env, args[0], nullptr, 0, &id_str_size);
    std::string id_str(id_str_size, '\0');
    napi_get_value_string_utf8(env, args[0], &id_str[0], id_str_size + 1, &id_str_size);

    ArkUI_NodeHandle handle;
    OH_ArkUI_GetNodeHandleFromNapiValue(env, args[1], &handle);

    OH_ArkUI_SurfaceHolder *holder = OH_ArkUI_SurfaceHolder_Create(handle);

    auto surface_callback = OH_ArkUI_SurfaceCallback_Create(); // 创建SurfaceCallback
    OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(surface_callback, OnSurfaceCreated);
    OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(surface_callback, OnSurfaceChanged);
    OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(surface_callback, OnSurfaceDestroyed);
    OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(surface_callback, OnSurfaceShow);
    OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(surface_callback, OnSurfaceHide);

    OH_ArkUI_SurfaceHolder_AddSurfaceCallback(holder, surface_callback);

    OH_DisplaySoloist *display_soloist = OH_DisplaySoloist_Create(false);

    DisplaySoloist_ExpectedRateRange range;
    range.min = 30;
    range.max = 120;
    range.expected = 60;

    OH_DisplaySoloist_SetExpectedFrameRateRange(display_soloist, &range);

    SurfaceData *surface_data = new SurfaceData();
    surface_data->id = id_str;
    surface_data->handle = handle;
    surface_data->holder = holder;
    surface_data->callback = surface_callback;
    surface_data->displaySoloist = display_soloist;

    SURFACE_DATA_MAP[id_str] = surface_data;

    OH_ArkUI_SurfaceHolder_SetUserData(holder, surface_data);

    return nullptr;
}

napi_value UnbindNode(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    size_t id_str_size = 0;
    napi_get_value_string_utf8(env, args[0], nullptr, 0, &id_str_size);
    std::string id_str(id_str_size, '\0');
    napi_get_value_string_utf8(env, args[0], &id_str[0], id_str_size + 1, &id_str_size);

    auto find_result = SURFACE_DATA_MAP.find(id_str);
    if (find_result != SURFACE_DATA_MAP.end())
    {
        auto surface_data = find_result->second;

        OH_DisplaySoloist_Destroy(surface_data->displaySoloist);
        NODE_API_1->disposeNode(surface_data->handle);

        delete surface_data;
        SURFACE_DATA_MAP.erase(find_result);
    }

    return nullptr;
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
            napi_property_descriptor desc[] = {{"BindNode", nullptr, BindNode, nullptr, nullptr, nullptr, napi_default, nullptr}, {"UnbindNode", nullptr, UnbindNode, nullptr, nullptr, nullptr, napi_default, nullptr}};
            napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);

            OnVulkanInit();

            is_napi_define_properties = true;
            return exports;
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