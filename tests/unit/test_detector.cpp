#include <gtest/gtest.h>
#include "isp/frame.pb.h"
#include "detection/CameraDetector.hpp"

TEST(CameraDetectorTest, CameraDetectorReturnsMockDetections) {
    adas::perception::CameraDetector detector;
    adas::isp::ProcessedFrame frame;
    
    // Run detection
    auto result = detector.detect(frame);
    
    // Assert on the generated Protobuf fields
    EXPECT_EQ(result.header().frame_id(), "camera_front");
    EXPECT_EQ(result.header().sequence(), 1);
    
    ASSERT_EQ(result.detections_size(), 1);
    
    const auto& detection = result.detections(0);
    EXPECT_EQ(detection.object_id(), 101);
    EXPECT_EQ(detection.object_class(), adas::perception::OBJECT_CAR);
    EXPECT_FLOAT_EQ(detection.confidence(), 0.95f);
    EXPECT_FLOAT_EQ(detection.distance_m(), 15.5f);
    EXPECT_FLOAT_EQ(detection.relative_velocity_mps(), -2.0f);
    
    EXPECT_FLOAT_EQ(detection.bbox_2d().x(), 100.0f);
    EXPECT_FLOAT_EQ(detection.bbox_2d().y(), 150.0f);
    EXPECT_FLOAT_EQ(detection.bbox_2d().width(), 50.0f);
    EXPECT_FLOAT_EQ(detection.bbox_2d().height(), 40.0f);
}
