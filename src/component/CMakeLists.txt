add_library(perception_core
    detection/CameraDetector.cpp
    tracking/MultiObjectTracker.cpp
    # classification/ObjectClassifier.cpp
    # free_space/FreeSpaceDetector.cpp
)
target_include_directories(perception_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(perception_core PUBLIC AdasInterfaces::AdasInterfaces)
