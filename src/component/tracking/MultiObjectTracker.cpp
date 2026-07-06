#include "perception/detection.pb.h"
#include "PerceptionCore__Outputs/gen_object_list.pb.h"
#include "MultiObjectTracker.hpp"

namespace adas { namespace perception {

GenObjectList MultiObjectTracker::update(const DetectionList& detections) {
    GenObjectList result;
    // TODO: Implement tracking
    // 1. Predict existing objects
    // 2. Associate detections to objects (Hungarian algorithm)
    // 3. Update matched objects
    // 4. Create new objects for unmatched detections
    // 5. Mark unmatched objects as coasting
    return result;
}

void MultiObjectTracker::reset() {
    // TODO: Clear all objects
}

}} // namespace adas::perception

