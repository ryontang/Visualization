#include <iostream>

#include <esr_tracks_display/EsrTracksDisplayROS.h>

int main(int argc, char **argv){
  ros::init(argc, argv, "esr_tracks_display");
  ros::NodeHandle n;
  ros::NodeHandle pnh("~");
  esr_tracks_display::EsrTracksDisplayROS etd_ros(n, pnh);
  ros::spin();

  return 0;
}
