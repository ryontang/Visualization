#include<ros/ros.h>
#include<geometry_msgs/Pose.h>
#include<visual_msgs/Points.h>
namespace vis{
class visualizer
{
    public:
        visualizer(ros::NodeHandle* n);
        
        //publisher and subscriber   
        ros::Publisher r_marker_pub;
        ros::Subscriber radar_sub;

        //callback function
        void cb_radar(const visual_msgs::Points& msg);

};

};
