#include "husky_highlevel_controller/HuskyHighlevelController.hpp"
#include <string>

namespace husky_highlevel_controller
{
    HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& node_handle) :
    node_handle_(node_handle) {}

    HuskyHighlevelController::~HuskyHighlevelController() {}

    void HuskyHighlevelController::laserScanCallback(const sensor_msgs::LaserScan& msg)
    {
        ROS_INFO("Read scan range_min: %f", msg.range_min);
        ROS_INFO("Read scan range_max: %f", msg.range_max);
    }

    void HuskyHighlevelController::listen()
    {
        std::string topic;
        if ( !node_handle_.getParam("laser/topic", topic) )
            ROS_ERROR("Could not find topic parameter!");

        int queue_size;
        if ( !node_handle_.getParam("laser/queue_size", queue_size) )
            ROS_ERROR("Could not find queue_size parameter!");

        laser_scan_subscriber_ = node_handle_.subscribe(
            topic,
            queue_size,
            &HuskyHighlevelController::laserScanCallback,
            this
        );
        ros::spin();
    }
} /* namespace */
