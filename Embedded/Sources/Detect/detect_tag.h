#ifndef DETECT_TAG_H
#define DETECT_TAG_H

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cv.h>
#include <cmath>
#include <QtDebug>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

// @function detectAndDisplay
bool detectAndDisplay( Mat frame, String i_color, String i_form, int *io_x, int *io_y);

// Helper function to find a cosine of angle between vectors from pt0->pt1 and pt0->pt2
static double angle(Point pt1, Point pt2, Point pt0) ;

#endif // DETECT_TAG_H
