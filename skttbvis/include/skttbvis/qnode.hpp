/**
 * @file /include/skttbvis/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef skttbvis_QNODE_HPP_
#define skttbvis_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>

#include <QStringListModel>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv_modules.hpp>
#include <iostream>
#include <cv_bridge/cv_bridge.h>
#include "geometry_msgs/Twist.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace skttbvis
{
  /*****************************************************************************
  ** Class
  *****************************************************************************/

  class QNode : public QThread
  {
    Q_OBJECT
  public:
    QNode(int argc, char** argv);
    virtual ~QNode();
    bool init();
    void run();
    void imgCallback(const sensor_msgs::Image::ConstPtr& msg);
    bool isReceived=false;
    cv::Mat img_gaz;
    cv::Mat resize_img;
    void go();
    void fast();
    void left();
    void slow();
    void stop();
    void right();
    ros::Publisher pub;
    geometry_msgs::Twist mytwist;


  Q_SIGNALS:
    void rosShutdown();
    void win_signal();
    
  private:
  ros::Subscriber sub;
    int init_argc;
    char** init_argv;
  };

}  // namespace s

#endif /* skttbvis_QNODE_HPP_ */
