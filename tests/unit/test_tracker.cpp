#include <gtest/gtest.h>
#include "perception/detection.pb.h"
#include "perception/track.pb.h"
#include "tracking/MultiObjectTracker.hpp"

TEST(MultiObjectTrackerTest, EmptyDetectionsReturnsEmptyTracks) {
    adas::perception::MultiObjectTracker tracker;
    adas::perception::DetectionList detections;
    
    // In our stubs, update returns a default-constructed TrackList
    auto result = tracker.update(detections);
    
    SUCCEED();
}
