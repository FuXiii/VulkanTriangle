cmake_minimum_required(VERSION 3.0)

project(VulkanTriangle)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_subdirectory(./thirdparty)

add_executable(${PROJECT_NAME} ./main.cpp VkString.cpp)

add_dependencies(${PROJECT_NAME} glfw)

target_include_directories(${PROJECT_NAME}
    PUBLIC ./include
    PUBLIC ./thirdparty/glm/
    )

target_link_directories(${PROJECT_NAME} 
PUBLIC /thirdparty/glfw/src/
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
glfw
)

if(MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")
else()
endif()