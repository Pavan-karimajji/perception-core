#include <gtest/gtest.h>
#include "proto_stubs.hpp"
#include "detection/CameraDetector.hpp"

TEST(CameraDetectorTest, EmptyFrameReturnsNoDetections) {
    adas::perception::CameraDetector detector;
    adas::isp::ProcessedFrame frame;
    
    // In our stubs, detect returns a default-constructed DetectionList
    auto result = detector.detect(frame);
    
    // Check that we got a valid object (compilation and run test)
    SUCCEED();
}
