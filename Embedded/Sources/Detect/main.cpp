#include "detect_tag.h"



// @function main
int main( void )
{

    VideoCapture capture ;
    Mat frame;

    position pos ;

    String color = "red";
    String form  = "rectangle" ;

    //-- 1. Read the video stream
    //capture.open( -1 );
    capture.open( 1);
    if ( ! capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

    while ( capture.read(frame))
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 2. Apply the classifier to the frame
        pos = detect( frame, color, form ) ;
        if (pos.found)
            qDebug() << QString( (form+"_"+color).c_str()) << " : x = " << pos.abs << " ; y = " << pos.ord ;

        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }
    return 0;
}






















