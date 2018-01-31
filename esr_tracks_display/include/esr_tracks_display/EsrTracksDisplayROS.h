#ifndef ESR_TRACKS_DISPLAY_ROS_H
#define ESR_TRACKS_DISPLAY_ROS_H

#include <boost/thread/mutex.hpp>

#include <ros/ros.h>
#include <geometry_msgs/PoseArray.h>

#include <esr_msgs/Track.h>
#include <esr_msgs/Status.h>

#include <esr_tracks_display/EsrTracksDisplay.h>


namespace esr_tracks_display {

class EsrTracksDisplayROS
{
public:
  EsrTracksDisplayROS(ros::NodeHandle& n, ros::NodeHandle& pnh);
  ~EsrTracksDisplayROS();
private:
  void trackCb(const esr_msgs::TrackConstPtr& track_msg);
  void statusCb(const esr_msgs::StatusConstPtr& status_msg);
  void connectCb(const ros::SingleSubscriberPublisher& pub);
  void disconnectCb(const ros::SingleSubscriberPublisher& pub);

  ros::NodeHandle pnh_;  // Private nodehandle used to generate the hints in the connectCb.
  ros::Subscriber sub_; ///< Subscriber for image_transport
  ros::Publisher pub_poses_;  // Publisher for output PoseArray messages
  ros::Publisher pub_ptcloud_;  // Publisher for output PointCloud messages
  EsrTracksDisplay etd_;  // Instance of the EsrTracksDisplay conversion class.
  boost::mutex connect_mutex_;  // Prevents the connectCb and disconnectCb from being called until everything is initialized.
  size_t msg_count_;
};

} // namespace esr_tracks_display

#endif // ESR_TRACKS_DISPLAY_ROS_H
