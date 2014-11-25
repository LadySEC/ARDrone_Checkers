// Version de test 25 Nov
// Le detect est un cercle 



#ifndef DETECT_TAG_H
#define DETECT_TAG_H

#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/video/video.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv/cv.h>
#include <cmath>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

struct Position
{
    int abs ;
    int ord ;
    int found ;
};

// @function detect
Position detect( Mat frame);

// Helper function to find a cosine of angle between vectors from pt0->pt1 and pt0->pt2
static double angle(Point pt1, Point pt2, Point pt0) ;

#endif // DETECT_TAG_H
