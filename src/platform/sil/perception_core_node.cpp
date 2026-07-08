#include <iostream>
#include <memory>
#include <vector>
// Real generated types - matches exactly what CameraDetector/MultiObjectTracker/
// FreeSpaceDetector's own .cpp files already include. This file used to include
// interfaces' proto_stubs.hpp instead (a placeholder struct GenObjectList {}/
// FreeSpaceContour {}/ProcessedFrame {}, predating these being wired to real
// protobuf types) - a struct-vs-class mismatch against the real classes below,
// invisible until something actually linked this file into a full executable
// (modules/sil, plan.md item 2) and hit LNK2001 on detect()/update()/
// detect_free_space(). No .proto file touched - proto_stubs.hpp is a plain
// C++ header, not a schema.
#include "isp/frame.pb.h"
#include "perception/detection.pb.h"
#include "PerceptionCore__Outputs/gen_object_list.pb.h"
#include "perception/free_space.pb.h"
#include "detection/CameraDetector.hpp"
#include "tracking/MultiObjectTracker.hpp"
#include "free_space/FreeSpaceDetector.hpp"

// If we are actually building with real ROS2, we would include real headers.
// Since this is a template/skeleton for the platform team, we provide a compile-friendly mock of the ROS2 Node structure.
#ifdef USING_ROS2
#include <rclcpp/rclcpp.hpp>
#else
namespace rclcpp {
    class Node {
    protected:
        std::string name_;
    public:
        Node(const std::string& name) : name_(name) {}
        virtual ~Node() = default;
        std::string get_name() const { return name_; }
    };
}
#endif

namespace adas { namespace perception {

class PerceptionCoreNode : public rclcpp::Node {
public:
    PerceptionCoreNode() : Node("perception_core_node") {
        std::cout << "PerceptionCoreNode (SIL): Initializing node: " << get_name() << std::endl;
        
        // Instantiate components
        detector_ = std::make_unique<CameraDetector>();
        tracker_ = std::make_unique<MultiObjectTracker>();
        free_space_detector_ = std::make_unique<FreeSpaceDetector>();
        
        // Setup ROS2 subscribers and publishers
        setup_pub_sub();
    }

    void on_frame_received(const adas::isp::ProcessedFrame& frame) {
        std::cout << "PerceptionCoreNode (SIL): Received new processed frame" << std::endl;
        
        // Run pipeline components
        auto detections = detector_->detect(frame);
        auto objects = tracker_->update(detections);
        auto free_space = free_space_detector_->detect_free_space(frame);

        // Publish outputs
        publish_outputs(detections, objects, free_space);
    }

private:
    void setup_pub_sub() {
        // TODO: Register actual ROS2 subscribers and publishers
        // subscription_ = this->create_subscription<...>(
        //     "/processed_frame", 10, std::bind(&PerceptionCoreNode::on_frame_received, this, std::placeholders::_1));
        // detections_pub_ = this->create_publisher<...>("/detections", 10);
        // objects_pub_ = this->create_publisher<...>("/objects", 10);
        // free_space_pub_ = this->create_publisher<...>("/free_space", 10);
        std::cout << "PerceptionCoreNode (SIL): Subscribers & publishers set up." << std::endl;
    }

    void publish_outputs(const DetectionList& detections, const GenObjectList& objects, const FreeSpaceContour& free_space) {
        // TODO: Publish messages to ROS2 topics
        std::cout << "PerceptionCoreNode (SIL): Publishing detections, objects, and free space" << std::endl;
    }

    std::unique_ptr<CameraDetector> detector_;
    std::unique_ptr<MultiObjectTracker> tracker_;
    std::unique_ptr<FreeSpaceDetector> free_space_detector_;
};

}} // namespace adas::perception

// Entry point for ROS2/SIL executable
// This is typically called by the ROS2 executor
void run_sil_node() {
    auto node = std::make_shared<adas::perception::PerceptionCoreNode>();
    // For SIL simulation / test execution
    adas::isp::ProcessedFrame dummy_frame;
    node->on_frame_received(dummy_frame);
}
