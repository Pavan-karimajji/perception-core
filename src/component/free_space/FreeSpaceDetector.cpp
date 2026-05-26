#include "proto_stubs.hpp"
#include "FreeSpaceDetector.hpp"
#include "iostream"

namespace adas { namespace perception {

FreeSpaceContour FreeSpaceDetector::detect_free_space(const adas::isp::ProcessedFrame& frame) {
    FreeSpaceContour result;
    // TODO: Implement actual free space detection
    // 1. Run semantic segmentation model inference
    // 2. Extract contour boundary points from segmentations
    // 3. Populate FreeSpaceContour result
    std::cout << "FreeSpaceDetector: Detecting free space contour in frame" << std::endl;
    return result;
}

}} // namespace adas::perception
