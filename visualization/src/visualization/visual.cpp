#include<ros/ros.h>
#include<visualization/visual.hpp>
#include<geometry_msgs/Pose.h>
#include<visualization_msgs/Marker.h>
#include<visual_msgs/Points.h>
#include<std_msgs/ColorRGBA.h>
namespace vis{

    visualizer::visualizer(ros::NodeHandle* n)
    {
        r_marker_pub = n->advertise<visualization_msgs::Marker>("radar_Markers",10);
        radar_sub = n->subscribe("radar_points",1000,&visualizer::cb_radar,this);
    }

    void visualizer::cb_radar(const visual_msgs::Points& msg)
    {
        ROS_INFO("I heard something");
        visualization_msgs::Marker marker;
        marker.header.frame_id="map";
        marker.header.stamp=ros::Time();
        marker.ns = "vis";
        marker.id = 0;
        marker.type = visualization_msgs::Marker::SPHERE_LIST;
        marker.action = visualization_msgs::Marker::ADD;
        
        //maker.pose decide the origin of SPHERE_LIST
        marker.pose.position.x=0;
        marker.pose.position.y=0;
        marker.pose.position.z=0;
        marker.pose.orientation.x=0;
        marker.pose.orientation.y=0;
        marker.pose.orientation.z=0;
        marker.pose.orientation.w=1;

        //marker.points contain all points needed to display
        marker.points=msg.points;

        //sphere in 1m x 1m x 1m cube
        marker.scale.x=1;
        marker.scale.y=1;
        marker.scale.z=1;

        //set color of point separately, and colors size should equal to points size
        for(int i=0; i<10; i++)
        {
            std_msgs::ColorRGBA c;
            c.a=1;
            c.r=i/10.;
            c.g=i;
            c.b=i/10.;
            marker.colors.push_back(c);
        }

        r_marker_pub.publish(marker);
    }


};
