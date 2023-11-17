/**
 * @file /include/skttbvis/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date November 2010
 **/
#ifndef skttbvis_MAIN_WINDOW_H
#define skttbvis_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv_modules.hpp>
#include <iostream>
#include <cv_bridge/cv_bridge.h>
/*****************************************************************************
** Namespace
*****************************************************************************/

namespace skttbvis
{
  /*****************************************************************************
  ** Interface [MainWindow]
  *****************************************************************************/
  /**
   * @brief Qt central, all operations relating to the view part here.
   */

  typedef struct HSV
{
  int hh, sh, vh,hl,sl,vl;
} hsv;

typedef struct LR{
  int p1,p2,p3;
}LR;

  class MainWindow : public QMainWindow
  {
    Q_OBJECT

  public:
    MainWindow(int argc, char** argv, QWidget* parent = 0);
    ~MainWindow();

    //QImage img_to_ui(cv::Mat img);
    cv::Mat org_img;
    cv::Mat white_line;
    cv::Mat red_line;
    cv::Mat blue_line;
    cv::Mat green_line;
    cv::Mat yello_line;
    LR gaus(cv::Mat img, hsv name);

    // cv::Mat region_of_interest(cv::Mat img_edges, cv::Point *points){
    //   cv::Mat img_mask = cv::Mat::zeros(img_edges.rows, img_edges.cols, CV_8UC1);
    //   const cv::Point* ppt[1]={points};
    //   int npt[]={4};
    //   fillPoly(img_mask,ppt,npt,1,cv::Scalar(255,255,255), cv::LINE_8);
    //   cv::Mat img_masked;
    //   bitwise_and(img_edges,img_mask,img_masked);
    //   return img_masked;
    // }

    //xy roicut(cv::Mat binary, int num);

  public Q_SLOTS:
     void forui();

          void on_slider1_valueChanged(int value);
          void on_slider1_2_valueChanged(int value);
          void on_slider2_valueChanged(int value);
          void on_slider2_2_valueChanged(int value);
          void on_slider3_valueChanged(int value);
          void on_slider3_2_valueChanged(int value);


  private:
    Ui::MainWindowDesign ui;
    QNode qnode;
  };

}  // namespace s

#endif  // skttbvis_MAIN_WINDOW_H
