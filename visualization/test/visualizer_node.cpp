#include <ros/ros.h>
#include <iostream>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Pose.h>
#include <visualization/visual.hpp>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "visualizer_node");
    ros::NodeHandle nh("~");
    vis::visualizer v(&nh);
    ros::spin();

}

