/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/skttbvis/main_window.hpp"
#include <QImage>
#include <QString>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace skttbvis
{




using namespace Qt;
hsv yello, white, green, blue, red;

LR L,R,P;
/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget* parent) : QMainWindow(parent), qnode(argc, argv)
{
  ui.setupUi(this);  // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

  setWindowIcon(QIcon(":/images/icon.png"));

  qnode.init();

  QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
  QObject::connect(&qnode, SIGNAL(win_signal()), this, SLOT(forui()));

  white.hh=0,white.hl=0,white.sh=0,white.sl=0,white.vh=255,white.vl=98;//검은선으로보

yello.hh=210,yello.hl=86,yello.sh=255,yello.sl=20,yello.vh=255,yello.vl=60;
red.hh=0,red.hl=0,red.sh=0,red.sl=0,red.vh=255,red.vl=10;
green.hh=255,green.hl=0,green.sh=255,green.sl=10,green.vh=0,green.vl=0;
blue.hh=180,blue.hl=0,blue.sh=255,blue.sl=255,blue.vh=255,blue.vl=255;
    

}

MainWindow::~MainWindow()
{
}

void MainWindow::forui()
{
  org_img = qnode.img_gaz;
  cv::resize(org_img, org_img, cv::Size(360, 240), 0, 0, CV_INTER_LINEAR);
  //QImage pict = img_to_ui(org_img);


 cv::Mat gaus_img;
  cv::GaussianBlur(org_img, gaus_img, cv::Size(0, 0), 1);
cv::Mat resize_img;
  cv::resize(gaus_img, resize_img, cv::Size(360, 240));

//cv::Mat binary_img;
  //cv::cvtColor(resize_img, binary_img, cv::COLOR_BGR2GRAY);


    L =gaus(resize_img, white);


  QImage pict(resize_img.data, resize_img.cols, resize_img.rows, resize_img.step, QImage::Format_RGB888);
    pict = pict.rgbSwapped();
  ui.label->setPixmap(QPixmap::fromImage(pict));


     cv::subtract(cv::Scalar(255, 255, 255), resize_img, resize_img);

    R =gaus(resize_img, yello);
    //green_line=gaus(resize_img, green);


    cv::Point pt1(0, 25);
    cv::Point pt2(360, 25);
    cv::line(resize_img, pt1, pt2, cv::Scalar(0, 255, 0), 2);

    cv::Point pt3(0, 65);
    cv::Point pt4(360, 65);
    cv::line(resize_img, pt3, pt4, cv::Scalar(0, 255, 0), 2);

    cv::Point pt5(0, 105);
    cv::Point pt6(360, 105);
    cv::line(resize_img, pt5, pt6, cv::Scalar(0, 255, 0), 2);

   
    if(L.p3<3&&R.p1<160&&R.p2<290){
      qnode.left();
    }
    
    else{qnode.go();}

 QString text1 = QString("%1, %2, %3, %4, %5, %6").arg(L.p1).arg(L.p2).arg(L.p3).arg(R.p1).arg(R.p2).arg(R.p3);
    ui.label_3->setText(text1);

  QImage pict10(resize_img.data, resize_img.cols, resize_img.rows, resize_img.step, QImage::Format_RGB888);
    pict10 = pict10.rgbSwapped();
  ui.label_10->setPixmap(QPixmap::fromImage(pict10));

  // QImage pict123(resize_img.data, swap_res.cols, swap_res.rows, swap_res.step, QImage::Format_RGB888);
  //   pict123 = pict123.rgbSwapped();
  // ui.label_2->setPixmap(QPixmap::fromImage(pict123));

   qnode.isReceived=false;

}

LR MainWindow::gaus(cv::Mat img, hsv name){
// binary and erode, dilate

    cv::Mat hsv_img;
    cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);

    cv::Mat hsv_mask;
    cv::inRange(hsv_img, cv::Scalar(name.hl, name.sl, name.vl),
                cv::Scalar(name.hh, name.sh, name.vh), hsv_mask);

 cv::inRange(hsv_img, cv::Scalar(white.hl, white.sl, white.vl),
                cv::Scalar(name.hh, white.sh, white.vh), white_line);
  
  
  QImage pict3(white_line.data, white_line.cols, white_line.rows, white_line.step, QImage::Format_Grayscale8);
    pict3 = pict3.rgbSwapped();
  ui.label_9->setPixmap(QPixmap::fromImage(pict3));


  QImage pict9(hsv_mask.data, hsv_mask.cols, hsv_mask.rows, hsv_mask.step, QImage::Format_Grayscale8);
      pict9 = pict9.rgbSwapped();
  ui.label_2->setPixmap(QPixmap::fromImage(pict9));
  


     std::vector<cv::Point> Wpoints;
      cv::findNonZero(hsv_mask, Wpoints);
      int targety1 = 25;
      cv::Point minPoint1;  
      int targety2 = 65;
      cv::Point minPoint2;  
      int targety3 = 105;
      cv::Point minPoint3;
      for (std::vector<cv::Point>::const_iterator it = Wpoints.begin(); it != Wpoints.end(); ++it) {
       const cv::Point& point = *it;
        if (point.y == targety1) {
            if (minPoint1.x == 0 || point.x < minPoint1.x) {
              if(point.x!=1)
                minPoint1 = point;
            }
        }
        else if(point.y==targety2){
           if (minPoint2.x == 0 || point.x < minPoint2.x) {
              if(point.x!=1)
                minPoint2 = point;
            }
        }
        else if(point.y==targety3){
            if (minPoint3.x == 0 || point.x < minPoint3.x) {            
                if(point.x!=1)
                minPoint3 = point;
            }
        }
      }

    LR P;

    P.p1=minPoint1.x;
    P.p2=minPoint2.x;
    P.p3=minPoint3.x;
    
    return P;
    
}
  
/*****************************************************************************
** Functions
*****************************************************************************/
void MainWindow::on_slider1_valueChanged(int value)
{
   yello.hh=value;// QString text1 = QString("%1").arg(white.hh);
   //ui.label_3->setText(text1);
}
void MainWindow::on_slider1_2_valueChanged(int value){
    yello.hl=value;QString text6 = QString("%1").arg(yello.hl);
  ui.label_6->setText(text6);
}
void MainWindow::on_slider2_valueChanged(int value){
    yello.sh=value;QString text2 = QString("%1").arg(yello.sh);
  ui.label_4->setText(text2);
}
void MainWindow::on_slider2_2_valueChanged(int value){
    yello.sl=value;QString text7 = QString("%1").arg(yello.sl);
  ui.label_7->setText(text7);
}
void MainWindow::on_slider3_valueChanged(int value){
    yello.vh=value; QString text3 = QString("%1").arg(yello.vh);
  ui.label_5->setText(text3);
}

void MainWindow::on_slider3_2_valueChanged(int value){
  yello.vl=value;QString text8 = QString("%1").arg(yello.vl);
  ui.label_8->setText(text8);
}

}  // namespace skttbvis
