#ifndef DETECT_TAG_H
#define DETECT_TAG_H
/*
#include "/opencv/include/opencv2/objdetect.hpp"
#include "opencv/include/opencv2/videoio.hpp"
#include "opencv/include/opencv2/highgui.hpp"
#include "opencv/include/opencv2/imgproc.hpp"*/
#include <\opencv\include\opencv\cv.h>
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
Position detect( Mat frame, std::string i_color, std::string i_form);

// Helper function to find a cosine of angle between vectors from pt0->pt1 and pt0->pt2
static double angle(Point pt1, Point pt2, Point pt0) ;

#endif // DETECT_TAG_H
