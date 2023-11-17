/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/skttbvis/qnode.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace skttbvis
{
  /*****************************************************************************
  ** Implementation
  *****************************************************************************/

  QNode::QNode(int argc, char** argv) : init_argc(argc), init_argv(argv)
  {
  }

  QNode::~QNode()
  {
    if (ros::isStarted())
    {
      ros::shutdown();  // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
    wait();
  }

  bool QNode::init()
  {
    ros::init(init_argc, init_argv, "skttbvis");
    if (!ros::master::check())
    {
      return false;
    }
    ros::start();  // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n; 
    sub =n.subscribe("/camera/image",1000,&QNode::imgCallback,this);
    pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    // Add your ros communications here.
    start();
    return true;
  }

  void QNode::imgCallback(const sensor_msgs::Image::ConstPtr& msg){
    
  if (isReceived==false)
  {

    img_gaz = cv::Mat(cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8)->image);
          Q_EMIT win_signal();
          isReceived = true;
  }  
  
  else
  {
    return;
  }

}  
void QNode::run()
  { 
  
    ros::Rate loop_rate(33);
          mytwist.angular.z=0.0;
          mytwist.linear.x=0.0;

    while (ros::ok())
    {  ros::spinOnce();
      loop_rate.sleep();
    }
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    Q_EMIT rosShutdown();  // used to signal the gui for a shutdown (useful to roslaunch)
  }

  void QNode::go()
  {
          mytwist.angular.z=0.0;
          mytwist.linear.x=0.5;
          
              pub.publish(mytwist);


  }

    void QNode::slow(){
    mytwist.linear.x=0.1;

    pub.publish(mytwist);
    
  }


  void QNode::fast(){

    mytwist.linear.x=0.35;

    pub.publish(mytwist);
    
  }


  void QNode::left(){
      mytwist.linear.x=0.15;
      mytwist.angular.z= 0.5;
    
    pub.publish(mytwist);
    
  }

void QNode::stop()
{  
   mytwist.linear.x=0.0;
   mytwist.angular.z=0.0;

    pub.publish(mytwist);

  }
 
  void QNode::right(){
      mytwist.linear.x=0.15;
      mytwist.angular.z= -0.3;
    
    pub.publish(mytwist);
    
  } 
}  // namespace s
