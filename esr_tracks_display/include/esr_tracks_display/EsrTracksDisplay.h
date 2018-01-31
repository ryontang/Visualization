#ifndef ESR_TRACKS_DISPLAY_H
#define ESR_TRACKS_DISPLAY_H

#include <boost/unordered/unordered_map.hpp>

#include <boost/thread/mutex.hpp>

#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Pose.h>
#include <sensor_msgs/PointCloud.h>

#include <esr_msgs/Track.h>

namespace esr_tracks_display {

class EsrTracksDisplay
{
public:
  EsrTracksDisplay();
  ~EsrTracksDisplay();
  void pushTrack(const esr_msgs::TrackConstPtr& track_msg);
  void clearTracks();
  inline void set_output_frame(const std::string output_frame_id) { output_frame_id_ = output_frame_id; }
  geometry_msgs::PoseArrayPtr getPoseArray();
  sensor_msgs::PointCloudPtr getPointCloud();

private:
  std::string output_frame_id_;
  boost::unordered_map<int, esr_msgs::Track> tracks_;
  boost::mutex tracks_mutex_;  // preventing race condition of tracks_
};

} // namespace esr_tracks_display

#endif // ESR_TRACKS_DISPLAY_H
