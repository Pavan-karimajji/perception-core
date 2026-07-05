#include <iostream>
#include <memory>
#include "isp/frame.pb.h"
#include "perception/object.pb.h"
#include "perception/free_space.pb.h"
#include "detection/CameraDetector.hpp"
#include "tracking/MultiObjectTracker.hpp"
#include "free_space/FreeSpaceDetector.hpp"

// Standalone test executable
// Simulates reading a frame, running detection, tracking, and free space detection.
int main(int argc, char* argv[]) {
    std::cout << "========================================" << std::endl;
    std::cout << "Starting perception_standalone test..." << std::endl;
    std::cout << "========================================" << std::endl;

    // 1. Instantiate the algorithm components
    auto detector = std::make_unique<adas::perception::CameraDetector>();
    auto tracker = std::make_unique<adas::perception::MultiObjectTracker>();
    auto free_space_detector = std::make_unique<adas::perception::FreeSpaceDetector>();

    // 2. Simulate pipeline execution on a dummy frame
    adas::isp::ProcessedFrame dummy_frame;
    std::cout << "[Pipeline] Injecting dummy frame..." << std::endl;

    auto detections = detector->detect(dummy_frame);
    auto objects = tracker->update(detections);
    auto free_space = free_space_detector->detect_free_space(dummy_frame);

    std::cout << "[Pipeline] Pipeline step execution completed successfully." << std::endl;
    std::cout << "========================================" << std::endl;
    return 0;
}
