#include <iostream>

#include <tf/tf.h>

#include <esr_tracks_display/EsrTracksDisplay.h>

// in-file util functions
template<typename T>
static T DegToRad(T deg)
{
  return deg * M_PI / 180.0;
}
static int DegToRad(int deg); // never use int

using namespace esr_tracks_display;

EsrTracksDisplay::EsrTracksDisplay() {}

EsrTracksDisplay::~EsrTracksDisplay() {}

void EsrTracksDisplay::pushTrack(const esr_msgs::TrackConstPtr& track_msg)
{
  int id = track_msg->index;
  esr_msgs::Track track = *track_msg;
  boost::mutex::scoped_lock lock(tracks_mutex_);
  tracks_[id] = track;
}

void EsrTracksDisplay::clearTracks()
{
  boost::mutex::scoped_lock lock(tracks_mutex_);
  tracks_.clear();
}

geometry_msgs::PoseArrayPtr EsrTracksDisplay::getPoseArray()
{
  geometry_msgs::PoseArrayPtr ret(new geometry_msgs::PoseArray());
  ret->header.frame_id = output_frame_id_;
  ret->header.stamp = ros::Time::now();

  // TODO: are we using C++11?
  for (boost::unordered_map<int, esr_msgs::Track>::iterator it = tracks_.begin(); it != tracks_.end(); it++) {
    double bearing = DegToRad(it->second.azimuth);
    double vel_angle = bearing + atan2(it->second.lateral_rate, it->second.range_rate);
    double r = it->second.range;
    geometry_msgs::Pose pose;
    pose.position.x = r * cos(bearing);
    pose.position.y = r * sin(bearing);
    pose.position.z = 0;
    tf::poseTFToMsg(
      tf::Pose(
        tf::createQuaternionFromYaw(vel_angle),
        tf::Vector3(r*cos(bearing), r*sin(bearing), 0)),
      pose);
    ret->poses.push_back(pose);
  }
  return ret;
}

sensor_msgs::PointCloudPtr EsrTracksDisplay::getPointCloud()
{
  sensor_msgs::PointCloudPtr ret;
  return ret;
}
