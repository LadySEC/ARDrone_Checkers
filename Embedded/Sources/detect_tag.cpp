#include "detect_tag.h"

// @function detectAndDisplay
Position detect( Mat i_frame)
{

    // Get the cosines of all corners
    vector<double> cos;

    Position new_pos ;
    new_pos.found = 0 ;

    int angles = 0;
    int i = 0;



    // Use Canny instead of threshold to catch squares with gradient shading
    Mat bw ;
    //Canny(i_frame, bw, 0,50,5) ;

	Canny(i_frame, bw, 0,50,5);
    
	//Find contours
    vector<vector<Point> > contours;

    Mat bw_clone = bw.clone() ;
    findContours(bw_clone, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    vector<Point> approx;


  for (int i = 0; i < contours.size(); i++)
    {
        // Approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.005, true);

        // Skip small or non-convex objects
        if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
            continue;

        if ( (approx.size() == 3) )
        {
            cv::Rect r = cv::boundingRect(contours[i]);
            new_pos.abs = r.x + (r.width/2);
            new_pos.ord = r.y + (r.height/2);
            new_pos.found = 1 ;
        }
        else if ( (approx.size() ==4))
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
                new_pos.found = 1 ;
            }
        }
        else
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
                new_pos.found = 1 ;
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
