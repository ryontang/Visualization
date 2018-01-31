#include<ros/ros.h>
#include<iostream>
#include<geometry_msgs/Point.h>
#include<visual_msgs/Points.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"generator_node");
    ros::NodeHandle nh("~");
    ros::Rate r(1);
    ros::Publisher points_pub = nh.advertise<visual_msgs::Points>("points",100);

    visual_msgs::Points point_set;

    //number of random dataset
    const int num_of_points = 10;
    

    for(int i=0;i<num_of_points;i++)
    {
        geometry_msgs::Point p;
        p.x = rand()%10;
        p.y = rand()%10;
        p.z = rand()%10;

        point_set.points.push_back(p);
    }

    while(ros::ok())
    {    
        points_pub.publish(point_set);
        r.sleep();
        ros::spinOnce();
    }
}
