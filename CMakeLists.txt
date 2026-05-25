cmake_minimum_required(VERSION 3.0)

project(VulkanTriangle)

if(MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(OHOS)
  # -D OHOS_VERSION=4 (HarmonyOS 4 use API 10 begain support Vulkan)
  # -D OHOS_VERSION=5 (HarmonyOS 5 use API 19)
  # -D OHOS_VERSION=6 (HarmonyOS 6 use API 20) (default)
  if(NOT DEFINED OHOS_VERSION)
    set(OHOS_VERSION 6)
  endif()

  #add_library(${PROJECT_NAME} SHARED napi_init_10.cpp)
  add_library(${PROJECT_NAME} SHARED napi_init_19.cpp)
  target_compile_definitions(${PROJECT_NAME} PUBLIC OHOS)

  if(${OHOS_VERSION} EQUAL 4)
    target_compile_definitions(${PROJECT_NAME} PUBLIC OHOS_API_VERSION=10)
  elseif(${OHOS_VERSION} EQUAL 5)
    target_compile_definitions(${PROJECT_NAME} PUBLIC OHOS_API_VERSION=19)
  else(${OHOS_VERSION} EQUAL 6)
    target_compile_definitions(${PROJECT_NAME} PUBLIC OHOS_API_VERSION=20)
  endif()
  
  target_link_libraries(${PROJECT_NAME} 
    PUBLIC ace_napi.z
    PUBLIC hilog_ndk.z
    PUBLIC ace_ndk.z
    PUBLIC native_window
    PUBLIC native_vsync#10
    PUBLIC native_display_soloist#19
  )
else()
  add_executable(${PROJECT_NAME} ./main.cpp VkString.cpp)
  add_subdirectory(./thirdparty)
  add_dependencies(${PROJECT_NAME} glfw)

  target_link_libraries(${PROJECT_NAME} 
    PUBLIC glfw
  )
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC ./include
    PUBLIC ./thirdparty/glm/
)