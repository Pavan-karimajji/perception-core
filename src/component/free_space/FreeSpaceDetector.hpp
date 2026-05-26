#pragma once
#include "perception/IFreeSpaceDetector.hpp"

namespace adas { namespace perception {

/// @brief ML-based camera free space contour detector
/// TODO: Implement actual free space contour detection
class FreeSpaceDetector : public IFreeSpaceDetector {
public:
    FreeSpaceDetector() = default;
    ~FreeSpaceDetector() override = default;

    FreeSpaceContour detect_free_space(const adas::isp::ProcessedFrame& frame) override;
};

}} // namespace adas::perception
