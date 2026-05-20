// TODO: ROS2 node adapter for perception-core
// Subscribes to: /processed_frame (from adas-isp)
// Publishes:     /detections, /tracks, /free_space
//
// This is written by the platform team, NOT algo developers.
// It wraps CameraDetector + MultiObjectTracker in ROS2 pub/sub.
