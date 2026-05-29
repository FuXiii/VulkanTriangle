#include <napi/native_api.h>
#include <hilog/log.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <native_window/external_window.h>
#include <arkui/native_node_napi.h>

#include <arkui/native_interface.h>
#include <arkui/native_node.h>

#include <string>
#include <unordered_map>

#include <VulkanTriangle.h>

VulkanTriangle VULKAN_TRIANGLE;

void MyLog(const std::string &str)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, 0x1, "Log", "%s", str.c_str());
}

ArkUI_NativeNodeAPI_1 *NODE_API_1 = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));

struct SurfaceData
{
    std::string id;
    ArkUI_NodeHandle handle;
    OH_ArkUI_SurfaceHolder *holder = nullptr;
    OH_ArkUI_SurfaceCallback *callback = nullptr;
};

std::unordered_map<std::string, SurfaceData *> SURFACE_DATA_MAP;

void OnArkUIXComponentFrameCallback(ArkUI_NodeHandle node, uint64_t timestamp, uint64_t targetTimestamp)
{
    MyLog("OnArkUIXComponentFrameCallback");
    VULKAN_TRIANGLE.Draw(timestamp * 0.001);
}

void OnSurfaceCreated(OH_ArkUI_SurfaceHolder *holder)
{
    MyLog("OnSurfaceCreated");
    auto native_window = OH_ArkUI_XComponent_GetNativeWindow(holder);
    VULKAN_TRIANGLE.CreateSurface(native_window);

    SurfaceData *surface_data = (SurfaceData *)OH_ArkUI_SurfaceHolder_GetUserData(holder);
}

void OnSurfaceChanged(OH_ArkUI_SurfaceHolder *holder, uint64_t width, uint64_t height)
{
    MyLog("OnSurfaceChanged");
}

void OnSurfaceDestroyed(OH_ArkUI_SurfaceHolder *holder)
{
    MyLog("OnSurfaceDestroyed");

    SurfaceData *surface_data = (SurfaceData *)OH_ArkUI_SurfaceHolder_GetUserData(holder);
    if (surface_data != nullptr)
    {
        OH_ArkUI_XComponent_UnregisterOnFrameCallback(surface_data->handle);
        MyLog("OH_ArkUI_XComponent_UnregisterOnFrameCallback");

        OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback(surface_data->holder, surface_data->callback);
        MyLog("OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback");

        OH_ArkUI_SurfaceCallback_Dispose(surface_data->callback);
        MyLog("OH_ArkUI_SurfaceCallback_Dispose");

        OH_ArkUI_SurfaceHolder_Dispose(surface_data->holder); // 销毁surfaceHolder
        MyLog("OH_ArkUI_SurfaceHolder_Dispose");
    }
}

void OnSurfaceShow(OH_ArkUI_SurfaceHolder *holder)
{
    MyLog("OnSurfaceShow");
}

void OnSurfaceHide(OH_ArkUI_SurfaceHolder *holder)
{
    MyLog("OnSurfaceHide");
}

/*
ArkUI侧：
    native.bindNode(this.xcomponentId, this.getUIContext().getFrameNodeById(this.xcomponentId))
*/
napi_value BindNode(napi_env env, napi_callback_info info)
{
    MyLog("BindNode");

    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    size_t id_str_size = 0;
    napi_get_value_string_utf8(env, args[0], nullptr, 0, &id_str_size);
    std::string id_str(id_str_size, '\0');
    napi_get_value_string_utf8(env, args[0], &id_str[0], id_str_size + 1, &id_str_size);

    ArkUI_NodeHandle handle;
    OH_ArkUI_GetNodeHandleFromNapiValue(env, args[1], &handle);
    MyLog("OH_ArkUI_GetNodeHandleFromNapiValue");

    OH_ArkUI_SurfaceHolder *holder = OH_ArkUI_SurfaceHolder_Create(handle);
    MyLog("OH_ArkUI_SurfaceHolder_Create");

    auto surface_callback = OH_ArkUI_SurfaceCallback_Create(); // 创建SurfaceCallback
    OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(surface_callback, OnSurfaceCreated);
    OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(surface_callback, OnSurfaceChanged);
    OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(surface_callback, OnSurfaceDestroyed);
    OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(surface_callback, OnSurfaceShow);
    OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(surface_callback, OnSurfaceHide);

    OH_ArkUI_XComponent_RegisterOnFrameCallback(handle, OnArkUIXComponentFrameCallback);

    MyLog("OH_ArkUI_SurfaceCallback_Create");
    MyLog("OH_ArkUI_XComponent_RegisterOnFrameCallback");

    OH_ArkUI_SurfaceHolder_AddSurfaceCallback(holder, surface_callback);
    MyLog("OH_ArkUI_SurfaceHolder_AddSurfaceCallback");

    OH_NativeXComponent_ExpectedRateRange range;
    range.min = 30;
    range.max = 120;
    range.expected = 60;
    OH_ArkUI_XComponent_SetExpectedFrameRateRange(handle, range); // 设置期望帧率
    MyLog("OH_ArkUI_XComponent_SetExpectedFrameRateRange");

    SurfaceData *surface_data = new SurfaceData();
    surface_data->id = id_str;
    surface_data->handle = handle;
    surface_data->holder = holder;
    surface_data->callback = surface_callback;

    SURFACE_DATA_MAP[id_str] = surface_data;
    MyLog("SURFACE_DATA_MAP[id_str] = surface_data");

    OH_ArkUI_SurfaceHolder_SetUserData(holder, surface_data);
    MyLog("OH_ArkUI_SurfaceHolder_SetUserData");

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

        NODE_API_1->disposeNode(surface_data->handle);
        MyLog("NODE_API_1->disposeNode(surface_data->handle)");

        delete surface_data;
        MyLog("delete surface_data");

        SURFACE_DATA_MAP.erase(find_result);
        MyLog("SURFACE_DATA_MAP.erase(find_result)");
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
            // clang-format off
            napi_property_descriptor desc[] = {
                {"BindNode", nullptr, BindNode, nullptr, nullptr, nullptr, napi_default, nullptr}, 
                {"UnbindNode", nullptr, UnbindNode, nullptr, nullptr, nullptr, napi_default, nullptr}
            };
            // clang-format on
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