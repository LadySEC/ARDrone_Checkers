#include "detect_tag.h"

int main()
{
	int i,j;
	Position pos ;

	//std::string color = "blue";
	//std::string form  = "circle" ;

	//-- 1. Read the video stream
	int m_ImgHeight = 240;
	int m_ImgWidth = 320;

	Mat Img_Source_YUV(m_ImgHeight,m_ImgWidth,CV_8UC2);
	Mat Img_Destination_Bgr(m_ImgHeight,m_ImgWidth,CV_8UC3);
	FILE * f;

	uchar* pYUVPixels;
	int Img_Size= (m_ImgWidth * m_ImgHeight*2);
	pYUVPixels = new uchar[Img_Size];
	printf("Demarrage Test Detection\n");
	while (1)
	{
		
		f=fopen("/tmp/video2_buffer","rb");
		if ( !f )
		{
			printf("fopen error\n");
		}


		fread(pYUVPixels,Img_Size,1,f);
		fclose(f);

		// Suppression du ready pour avoir une nouvelle photo
		
		do{
		i=remove("/tmp/video2_ready");
		}while(i!=0);
		
		//if ( i!=0 )
		//{
		//	printf("remove error\n");
		//}

		Img_Source_YUV.data= pYUVPixels;

		// on traite directement du HSV
		cvtColor(Img_Source_YUV,Img_Destination_Bgr,COLOR_YUV2GRAY_Y422);
		//cvtColor(Img_Source_YUV,Img_Destination_Bgr,CV_YUV2GRAY_Y422);


		/*if( Img_Destination.empty() )
		  {
		  printf(" --(!) No captured frame -- Break!");
		  break;
		  }*/

		//-- 2. Apply the classifier to the frame
		printf("Avant detect\n");
		pos = detect( Img_Destination_Bgr) ;
		printf("------------Apres detect\n");
		if (pos.found){
			printf(  "top a la vachette : x = %d ; y = %d\n ",  pos.abs, pos.ord) ;
		}
		else {
			printf("Pas encore trouve\n");
		}
		//int c = waitKey(10);
		//if( (char)c == 27 ) { break; } // escape
		usleep(200000);
	}
	return 0;
}






















