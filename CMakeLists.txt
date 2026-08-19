cmake_minimum_required(VERSION 3.10)

project(VulkanTriangle)

if(MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(VULKAN_TRIANGLE_SOURCE_FILE ./VulkanTriangle.h ./VulkanTriangle.cpp VkString.cpp)

if(OHOS)
  # -D OHOS_VERSION=4 (HarmonyOS 4 use API 10 begain support Vulkan)
  # -D OHOS_VERSION=5 (HarmonyOS 5 use API 19)
  # -D OHOS_VERSION=6 (HarmonyOS 6 use API 20) (default)
  if(NOT DEFINED OHOS_VERSION)
    set(OHOS_VERSION 6)
  endif()

  message("Use OHOS_VERSION = ${OHOS_VERSION}")

  if(${OHOS_VERSION} EQUAL 4)
    add_library(${PROJECT_NAME} SHARED napi_init_10.cpp ${VULKAN_TRIANGLE_SOURCE_FILE})
    target_compile_definitions(${PROJECT_NAME} PUBLIC OHOS_API_VERSION=10)
    target_link_libraries(${PROJECT_NAME} 
      PUBLIC native_vsync
    )
  elseif(${OHOS_VERSION} EQUAL 5)
    add_library(${PROJECT_NAME} SHARED napi_init_19.cpp ${VULKAN_TRIANGLE_SOURCE_FILE})
    target_compile_definitions(${PROJECT_NAME} PUBLIC OHOS_API_VERSION=19)
    target_link_libraries(${PROJECT_NAME} 
      PUBLIC native_display_soloist
    )
  else(${OHOS_VERSION} EQUAL 6)
    add_library(${PROJECT_NAME} SHARED napi_init_20.cpp ${VULKAN_TRIANGLE_SOURCE_FILE})
    target_compile_definitions(${PROJECT_NAME} PUBLIC OHOS_API_VERSION=20)
  endif()
  target_compile_definitions(${PROJECT_NAME} PUBLIC OHOS)
  
  target_link_libraries(${PROJECT_NAME} 
    PUBLIC ace_napi.z
    PUBLIC hilog_ndk.z
    PUBLIC ace_ndk.z
    PUBLIC native_window
  )
else()
  #add_executable(${PROJECT_NAME} ./main.cpp VkString.cpp)
  #add_executable(${PROJECT_NAME} ./VulkanTriangle.h ./VulkanTriangle.cpp VkString.cpp)
  add_executable(${PROJECT_NAME} ${VULKAN_TRIANGLE_SOURCE_FILE})
  add_subdirectory(./thirdparty)
  add_dependencies(${PROJECT_NAME} glfw)

  target_link_libraries(${PROJECT_NAME} 
    PUBLIC glfw
  )
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC ./
    PUBLIC ./include
    PUBLIC ./thirdparty/glm/
)