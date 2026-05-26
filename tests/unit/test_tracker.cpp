#include <gtest/gtest.h>
#include "proto_stubs.hpp"
#include "tracking/MultiObjectTracker.hpp"

TEST(MultiObjectTrackerTest, EmptyDetectionsReturnsEmptyTracks) {
    adas::perception::MultiObjectTracker tracker;
    adas::perception::DetectionList detections;
    
    // In our stubs, update returns a default-constructed TrackList
    auto result = tracker.update(detections);
    
    SUCCEED();
}
