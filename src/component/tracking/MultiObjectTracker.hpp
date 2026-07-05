#pragma once
#include "perception/IObjectTracker.hpp"

namespace adas { namespace perception {

class MultiObjectTracker : public IObjectTracker {
public:
    MultiObjectTracker() = default;
    ~MultiObjectTracker() override = default;

    GenObjectList update(const DetectionList& detections) override;
    void reset() override;

private:
    // TODO: Track state, Kalman filters, assignment logic
};

}} // namespace adas::perception
