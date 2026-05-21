#include "proto_stubs.hpp"
#include "CameraDetector.hpp"
#include "iostream"

namespace adas { namespace perception {

DetectionList CameraDetector::detect(const adas::isp::ProcessedFrame& frame) {
    DetectionList result;
    // TODO: Implement actual detection
    // 1. Preprocess frame
    // 2. Run DNN inference (ONNX/TensorRT)
    // 3. Post-process: NMS, thresholding
    // 4. Populate DetectionList
    std::cout << "CameraDetector: Detecting objects in frame " << std::endl;
    return result;
}

}} // namespace adas::perception

