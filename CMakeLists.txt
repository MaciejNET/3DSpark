cmake_minimum_required(VERSION 3.28)
project(3DSpark)

set(CMAKE_CXX_STANDARD 17)

find_library(GLFW_LIBRARY NAMES glfw3 PATHS "${CMAKE_SOURCE_DIR}/dependencies/lib")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/include")

if(APPLE)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    find_library(COREGRAPHICS_LIBRARY CoreGraphics)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COCOA_LIBRARY Cocoa)
endif()

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(3DSpark
        src/main.cpp
        src/glad.c
        dependencies/include/stb_image.h
        include/Entities/Entity.h
        src/Events/EventBus.cpp
        src/Managers/InputManager.cpp
        src/Managers/WindowManager.cpp
        include/Renderer.h
        src/Renderer.cpp
        include/Engine.h
        src/Engine.cpp
        include/Entities/RectangularEntity.h
        src/Entities/RectangularEntity.cpp
        include/Texture/Texture.h
        include/Texture/ColorTexture.h
        include/Managers/TextureManager.h
        src/Managers/TextureManager.cpp
        include/Texture/ImageTexture.h
        include/Entities/SphereEntity.h
        src/Entities/SphereEntity.cpp
        include/Entities/CylinderEntity.h
        src/Entities/CylinderEntity.cpp
        include/Entities/ConeEntity.h
        src/Entities/ConeEntity.cpp)

if(APPLE)
    target_link_libraries(3DSpark ${GLFW_LIBRARY} ${COREFOUNDATION_LIBRARY} ${COREGRAPHICS_LIBRARY} ${IOKIT_LIBRARY} ${COCOA_LIBRARY})
else()
    target_link_libraries(3DSpark ${GLFW_LIBRARY})
endif()