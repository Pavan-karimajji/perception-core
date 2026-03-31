cmake_minimum_required(VERSION 3.22)
project(adas-perception-core VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Find shared interfaces
find_package(AdasInterfaces REQUIRED)

# Algo library (pure C++, no middleware)
add_library(perception_core
    src/detection/CameraDetector.cpp
    src/tracking/MultiObjectTracker.cpp
    # src/classification/ObjectClassifier.cpp
    # src/free_space/FreeSpaceDetector.cpp
)
target_include_directories(perception_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(perception_core PUBLIC AdasInterfaces::AdasInterfaces)

# Select adapter based on target
if(TARGET_TYPE STREQUAL "sil")
    # add_subdirectory(adapters/ros2)
elseif(TARGET_TYPE STREQUAL "autosar")
    # add_subdirectory(adapters/autosar)
elseif(TARGET_TYPE STREQUAL "standalone")
    # add_subdirectory(adapters/standalone)
endif()

# Tests
if(BUILD_TESTING)
    # add_subdirectory(tests/unit)
endif()
