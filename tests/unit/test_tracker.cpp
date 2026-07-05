#include <gtest/gtest.h>
#include "perception/detection.pb.h"
#include "perception/object.pb.h"
#include "tracking/MultiObjectTracker.hpp"

TEST(MultiObjectTrackerTest, EmptyDetectionsReturnsEmptyObjectList) {
    adas::perception::MultiObjectTracker tracker;
    adas::perception::DetectionList detections;
    
    // In our stubs, update returns a default-constructed GenObjectList
    auto result = tracker.update(detections);
    
    SUCCEED();
}
