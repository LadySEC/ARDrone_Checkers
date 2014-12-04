#include "detect_tag.h"


//--- modif hugo 04/12/2015 ------------------------------------
int x_last_found 	= 0;
int y_last_found 	= 0;
int repere_x_y_last 	= 0;

void resetReper_x_y_last(){
    repere_x_y_last 	= 0;
}
//--- modif hugo 04/12/2015 ------------------------------------


// @function detectAndDisplay
Position detect_wo_flux(Mat i_frame)
{

    // Get the cosines of all corners
    vector<double> cos;

    Position new_pos ;
    new_pos.found = 0 ;

    int angles = 0;
    int i = 0;



    // Use Canny instead of threshold to catch squares with gradient shading
    //Mat bw ;
    //Canny(i_frame, bw, 0,50,5) ;

    //Canny(i_frame, bw, 0,50,5);
    //Find contours
    //bw = i_frame;
	threshold(i_frame,i_frame,127,255,THRESH_BINARY_INV); 
	vector<vector<Point> > contours;


    //Mat frame_clone = i_frame.clone() ;
    //cvtColor( i_frame, bw, CV_BGR2GRAY );
    //threshold(bw,bw,127,255,ADAPTIVE_THRESH_GAUSSIAN_C);
    findContours(i_frame, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
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
            printf("Triangle Trouvé\n");
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
                printf("Rectangle Trouve\n");
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
                printf("Cercle Trouvé \n");
            }
        }
    }

    return new_pos ;
}

Position detect(){
int i,j;
Position pos;

    //-- 1. Read the video stream
    int m_ImgHeight = 720;
    int m_ImgWidth = 1280;

    Mat Img_Source_YUV(m_ImgHeight,m_ImgWidth,CV_8UC2);
    Mat Img_Destination_Bgr(m_ImgHeight,m_ImgWidth,CV_8UC3);
    FILE * f;

    uchar* pYUVPixels;
    int Img_Size= (m_ImgWidth * m_ImgHeight*2);
    pYUVPixels = new uchar[Img_Size];
    printf("Demarrage Test Detection\r\n");
    //while (1)
    //{

        f=fopen("/tmp/video1_buffer","rb");
        if ( !f )
        {
            printf("fopen error\r\n");
        }


        fread(pYUVPixels,Img_Size,1,f);
        fclose(f);

        // Suppression du ready pour avoir une nouvelle photo

        do{
            i=remove("/tmp/video1_ready");
        }while(i!=0);


        Img_Source_YUV.data= pYUVPixels;

        // on traite directement du HSV
        cvtColor(Img_Source_YUV,Img_Destination_Bgr,COLOR_YUV2GRAY_Y422);

        //-- 2. Apply the classifier to the frame
        //printf("Avant detect\n");
        pos = detect_wo_flux( Img_Destination_Bgr);
        //printf("------------Apres detect\n");


        if (pos.found){
            printf(  "Position Tag:  x = %d ; y = %d\r\n ",  pos.abs, pos.ord) ;

    	//--- modif hugo 04/12/2015 ------------------------------------
	    x_last_found = pos.abs;
    	    y_last_found = pos.ord;
	    repere_x_y_last ++;
	    // ! ! ! ! repere_x_y_last doit être remise à 0 lorsqu'elle est consommée par "calcul_order.c" ! ! ! !
    	//--- modif hugo 04/12/2015 ------------------------------------

        }
        else {
            printf("Pas encore trouve\r\n");

    	//--- modif hugo 04/12/2015 ------------------------------------
	    if(repere_x_y_last > 0)
            {
	       pos.abs 		= x_last_found;
    	       pos.ord 		= y_last_found;
	       pos.found 	= 1;
	       printf(  "Position Tag (--LAST FOUND -%d--): x = %d ; y = %d\r\n ",repere_x_y_last, pos.abs, pos.ord) ;
            }
    	//--- modif hugo 04/12/2015 ------------------------------------

        }
      //  usleep(200000);
    //}
        return pos;

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



/**
 * \fn 		
 * \brief 	Convert a RGB threshold in a YUV format
 *
 * \return 	ERROR: Something went wrong during the process, NO_ERROR: Success
 */

