#include "CameraDetector.hpp"
#include "isp/frame.pb.h"
#include <iostream>

namespace adas { namespace perception {

DetectionList CameraDetector::detect(const adas::isp::ProcessedFrame& frame) {
    DetectionList result;
    
    // Set header fields using Protobuf API
    auto* header = result.mutable_header();
    header->set_frame_id("camera_front");
    header->set_sequence(1);
    
    // Add a mock detection (a detected car)
    auto* detection = result.add_detections();
    detection->set_object_id(101);
    detection->set_object_class(OBJECT_CAR);
    detection->set_confidence(0.95f);
    detection->set_distance_m(15.5f);
    detection->set_relative_velocity_mps(-2.0f);
    
    // Set 2D Bounding Box
    auto* bbox = detection->mutable_bbox_2d();
    bbox->set_x(100.0f);
    bbox->set_y(150.0f);
    bbox->set_width(50.0f);
    bbox->set_height(40.0f);

    std::cout << "CameraDetector: Detected a car at 15.5m with confidence 0.95" << std::endl;
    return result;
}

}} // namespace adas::perception


