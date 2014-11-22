#include "detect_tag.h"

// @function detectAndDisplay
position detect( Mat i_frame, String i_color, String i_form)
{

    position new_pos ;
    new_pos.found = false ;

    int angles ;

    Mat HSV  ;
    cvtColor(i_frame,HSV,CV_BGR2HSV);

    Mat im_color ;
    if (i_color == "blue")
        inRange(HSV,cv::Scalar(100,50,100),cv::Scalar(150,255,255),im_color);
    else if (i_color == "red")
        inRange(HSV,cv::Scalar(0,150,100),cv::Scalar(20,255,255),im_color);
    else if (i_color == "green")
        inRange(HSV,cv::Scalar(30,50,50),cv::Scalar(80,255,255),im_color);

    // Use Canny instead of threshold to catch squares with gradient shading
    Mat bw ;
    Canny(im_color, bw, 0,50,5) ;

    //Find contours
    vector<vector<Point> > contours;
    findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    vector<Point> approx;

    if (i_form == "triangle")
        angles = 3 ;
    else if (i_form == "rectangle")
        angles = 4 ;
    else if (i_form == "circle")
        angles = 0 ;


    for (int i = 0; i < contours.size(); i++)
    {
        // Approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.005, true);

        // Skip small or non-convex objects
        if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
            continue;

        if ( (approx.size() == 3) && (i_form == "triangle") )
        {
            cv::Rect r = cv::boundingRect(contours[i]);
            new_pos.abs = r.x + (r.width/2);
            new_pos.ord = r.y + (r.height/2);
            new_pos.found = true ;
        }
        else if ( (approx.size() ==4) && (i_form == "rectangle"))
        {
            // Get the cosines of all corners
            vector<double> cos;
            for (int j = 2; j < approx.size()+1; j++)
                cos.push_back(angle(approx[j%approx.size()], approx[j-2], approx[j-1]));
            // Sort ascending the cosine values
            sort(cos.begin(), cos.end());
            // Get the lowest and the highest cosine
            double mincos = cos.front();
            double maxcos = cos.back();
            // Use the degrees obtained above and the number of vertices
            // to determinemoi the shape of the contour
            if (approx.size() == 4 && mincos >= -0.1 && maxcos <= 0.3)
            {
                cv::Rect r = cv::boundingRect(contours[i]);
                new_pos.abs = r.x + (r.width/2);
                new_pos.ord = r.y + (r.height/2);
                new_pos.found = true ;
            }
        }
        else if ( i_form == "circle")
        {
            // Detect and label circles
            double area = contourArea(contours[i]);
            Rect r = boundingRect(contours[i]);
            int radius = r.width / 2;
            if (abs(1 - ((double)r.width / r.height)) <= 0.2 && abs(1 - (area / (CV_PI * pow(radius, 2)))) <= 0.2)
            {
                cv::Rect r = cv::boundingRect(contours[i]);
                new_pos.abs = r.x + (r.width/2);
                new_pos.ord = r.y + (r.height/2);
                new_pos.found = true ;
            }
        }
    }

    return new_pos ;
}


// Helper function to find a cosine of angle between vectors from pt0->pt1 and pt0->pt2
static double angle(Point pt1, Point pt2, Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}
