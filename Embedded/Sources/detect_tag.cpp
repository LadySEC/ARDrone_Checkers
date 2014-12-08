#include "detect_tag.h"
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "global.h"
#include "../../Common/log.h"

using namespace std;
using namespace cv;

/**
 * \fn Vec3b yuv2rgb(Vec3b I_pixel_yuv)
 * \brief Conversion d'un pixel YUV en RGB
 *
 * \param  Vec4b I_pixel_yuv : pixel YUV
 * \return Vec3b pixel RGB issue de la conversion
 */
Vec3b yuv2rgb(Vec4b I_pixel_yuv)
{
	int c0 = 22987;
	int c1 = -11698;
	int c2 = -5636;
	int c3 = 29049;
	
	int y = I_pixel_yuv[1];
	int cb = I_pixel_yuv[0] - 128;
	int cr = I_pixel_yuv[2] - 128;

	int b = y + (((c3 * cb) + (1 << 13)) >> 14);
	int g = y + (((c2 * cb + c1 * cr) + (1 << 13)) >> 14);
	int r = y + (((c0 * cr) + (1 << 13)) >> 14);

	if (r < 0) r = 0;
	else if (r > 255) r = 255;

	if (g < 0) g = 0;
	else if (g > 255) g = 255;

	if (b < 0) b = 0;
	else if (b > 255) b = 255;
	
	return {(uchar)r, (uchar)g, (uchar)b};
}


char getMainColor(Vec3b I_pixelRGB) {
	uchar r, g, b;
	r = I_pixelRGB[0];
	g = I_pixelRGB[1];
	b = I_pixelRGB[2];
	if (r > C_R_MIN_R && r <= C_R_MAX_R && g > C_R_MIN_G && g <= C_R_MAX_G && b > C_R_MIN_B && b < C_R_MAX_B) return 'R';
	if (r > C_B_MIN_R && r <= C_B_MAX_R && g > C_B_MIN_G && g <= C_B_MAX_G && b > C_B_MIN_B && b < C_B_MAX_B) return 'B';
	if (r > C_G_MIN_R && r <= C_G_MAX_R && g > C_G_MIN_G && g <= C_G_MAX_G && b > C_G_MIN_B && b < C_G_MAX_B) return 'G';
	return 'U';
}


Mat readImageFromFile(char * I_pathToFile) {
	FILE * f;
	Mat Img_YUV(IMG_HEIGHT,IMG_WIDTH,CV_8UC2);
	int Img_Size = IMG_WIDTH * IMG_HEIGHT*2;
    unsigned char* pYUVPixels = new unsigned char[Img_Size];

	f=fopen(I_pathToFile,"rb");
	if (!f) {
		//LOG_WriteLevel(LOG_ERROR, "detect_tag: fopen error");
	}
	
	fread(pYUVPixels,Img_Size,1,f);
	fclose(f);
	
	Img_YUV.data = pYUVPixels;
	
	return Img_YUV;
}


void freeImage(Mat IO_Img) {
	free(IO_Img.data);
}


void nextImage() {
	int err;
	// Suppression du fichier ready pour avoir une nouvelle image
	do {
		err = remove(IMG_READY_PATH);
	} while(err != 0);
}


T_Position getSquarePosition(int I_currentSquare, int I_destSquare) {
	T_Position squarePos = {0, 0};
	if(I_destSquare= 5){
		switch(I_currentSquare) {
			case 1 : squarePos = {360,-360};
			break;
			case 2 : squarePos = {0,-360};
			break;
			case 3 : squarePos = {-360,-360};
			break;
			case 4 : squarePos = {360,0};
			break;
			case 5 : squarePos = {0,0};
			break;
			case 6 : squarePos = {-360,0};
			break;
			case 7 : squarePos = {360,360};
			break;
			case 8 : squarePos = {0,360};
			break;
			case 9 : squarePos = {-360,360};
			break;
		}
	}
	else{
		switch(I_destSquare) {
			case 1 : squarePos = {-360,360};
			break;
			case 2 : squarePos = {0,360};
			break;
			case 3 : squarePos = {360,360};
			break;
			case 4 : squarePos = {-360,0};
			break;
			case 5 : squarePos = {0,0};
			break;
			case 6 : squarePos = {360,0};
			break;
			case 7 : squarePos = {-360,-360};
			break;
			case 8 : squarePos = {0,-360};
			break;
			case 9 : squarePos = {360,-360};
			break;
		}
	}
	return squarePos;
}


T_Position getPosition(int I_currentSquare, int I_destSquare) {
	int 		i,j;
	long long	posX, posY;
	T_Position	squarePos = {0, 0};
	T_Position	pixelPos;
	Vec4b		pixelYUV;
	Vec3b		pixelRGB;
	std::vector<T_Position> pixelsTarget;
	
	// On vérifie que le numéro de la case demandée est bien entre 1 et 9
	// sinon on retourne la position {0, 0} pour ne demander aucun mouvement
	if (I_destSquare < 1 || I_destSquare > 9) return squarePos;
	if (I_currentSquare < 1 || I_currentSquare > 9) return squarePos;

    Mat img = readImageFromFile((char*)IMG_PATH);
	
	// Sous-échantillonnage de l'image
	for (i=C_WINDOW_LEFT; i<img.cols-C_WINDOW_RIGHT; i+=C_DOWNSCALING_STEP) {
		for (j=C_WINDOW_TOP; j<img.rows-C_WINDOW_BOTTOM; j+=C_DOWNSCALING_STEP) {
			// On récupère un pixel YUV particulier puis on le convertit en RGB
			pixelYUV = img.at<Vec4b>(j, i);
			pixelRGB = yuv2rgb(pixelYUV);
			// On recherche uniquement les pixels de couleur de la case de destination
			if (getMainColor(pixelRGB) == playgroundColors[I_destSquare-1]) {
				pixelPos = {i, j};
				pixelsTarget.push_back(pixelPos);
				printf("PUTAIN ON A TROUVE MAGGLE\n");
			}
		}
	}
	
	// Si on détecte un nombre suffisant de pixels de la couleur voulue,
	// on calcule la la position moyenne de ces pixels
	if (pixelsTarget.size() > C_MIN_PIXELS) {
		posX = 0;
		posY = 0;
		for (int i=0; i<pixelsTarget.size(); i++) {
			pixelPos = pixelsTarget.at(i);
			posX += pixelPos.abs;
			posY += pixelPos.ord;
		}
		posX /= pixelsTarget.size();
		posY /= pixelsTarget.size();
		squarePos = {(int)posX, (int)posY};
	// Sinon, on donne la direction de la case de destination
	} else {
		squarePos = getSquarePosition(I_currentSquare, I_destSquare);
	}

	freeImage(img);
	nextImage();
	
	return squarePos;
}

// Wrapper getPosition
extern "C" {
    T_Position W_getPosition(int I_currentSquare, int I_destSquare) {
		return getPosition(I_currentSquare, I_destSquare);
    }
}
