#include <esr_tracks_display/EsrTracksDisplayROS.h>

using namespace esr_tracks_display;

EsrTracksDisplayROS::EsrTracksDisplayROS(ros::NodeHandle& n, ros::NodeHandle& pnh):pnh_(pnh)
{
  boost::mutex::scoped_lock lock(connect_mutex_);

  // init EsrTracksDisplay // TODO: put it in reconf_callback
  etd_.set_output_frame("esr_frame");

  // subscription to esr track topic
  pub_poses_ = n.advertise<geometry_msgs::PoseArray>(
    "track_poses", 10,
    boost::bind(&EsrTracksDisplayROS::connectCb, this, _1),
    boost::bind(&EsrTracksDisplayROS::disconnectCb, this, _1)
  );

  pub_ptcloud_ = n.advertise<sensor_msgs::PointCloud>(
    "track_pointcloud", 10,
    boost::bind(&EsrTracksDisplayROS::connectCb, this, _1),
    boost::bind(&EsrTracksDisplayROS::disconnectCb, this, _1)
  );

  msg_count_ = 0;
}

EsrTracksDisplayROS::~EsrTracksDisplayROS()
{
  sub_.shutdown();
}

void EsrTracksDisplayROS::trackCb(const esr_msgs::TrackConstPtr& track_msg)
{
  etd_.pushTrack(track_msg);
  msg_count_++;
  if (msg_count_ == 20) { // publish every 20 message // TODO: make it a variable
    // TODO: PoseArray and PointCloud should be sync
    geometry_msgs::PoseArrayPtr poses = etd_.getPoseArray();
    sensor_msgs::PointCloudPtr ptcloud = etd_.getPointCloud();
    if (poses) {
      pub_poses_.publish(poses);
    }
    if (ptcloud) {
      pub_ptcloud_.publish(ptcloud);
    }
    etd_.clearTracks();
    msg_count_ = 0;
  }
}

void EsrTracksDisplayROS::statusCb(const esr_msgs::StatusConstPtr& status_msg) {}

void EsrTracksDisplayROS::connectCb(const ros::SingleSubscriberPublisher& pub)
{
  boost::mutex::scoped_lock lock(connect_mutex_);
  if (!sub_) { // && pub_.getNumSubscribers() > 0) {
    std::cout << "Connecting to esr Track topic." << std::endl;
    sub_ = pnh_.subscribe("/esr_can0_tracks", 10, &EsrTracksDisplayROS::trackCb, this);//it_.("image", 10, &DepthImageToLaserScanROS::depthCb, this, hints);
  }
}

void EsrTracksDisplayROS::disconnectCb(const ros::SingleSubscriberPublisher& pub) {}
