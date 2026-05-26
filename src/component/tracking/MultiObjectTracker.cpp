#include "perception/detection.pb.h"
#include "perception/track.pb.h"
#include "MultiObjectTracker.hpp"

namespace adas { namespace perception {

TrackList MultiObjectTracker::update(const DetectionList& detections) {
    TrackList result;
    // TODO: Implement tracking
    // 1. Predict existing tracks
    // 2. Associate detections to tracks (Hungarian algorithm)
    // 3. Update matched tracks
    // 4. Create new tracks for unmatched detections
    // 5. Mark unmatched tracks as coasting
    return result;
}

void MultiObjectTracker::reset() {
    // TODO: Clear all tracks
}

}} // namespace adas::perception

