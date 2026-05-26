#pragma once
#include "perception/IObjectDetector.hpp"
#include "perception/detection.pb.h"

namespace adas { namespace perception {

/// @brief ML-based camera object detector
/// TODO: Implement actual detection logic
class CameraDetector : public IObjectDetector {
public:
    CameraDetector() = default;
    ~CameraDetector() override = default;

    DetectionList detect(const adas::isp::ProcessedFrame& frame) override;

private:
    // TODO: Add model inference engine, config, etc.
};

}} // namespace adas::perception
