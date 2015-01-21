#ifndef DETECT_TAG_H
#define DETECT_TAG_H

#include "opencv2/core/core.hpp"

#define IMG_PATH		"/tmp/video1_buffer"
#define IMG_READY_PATH	"/tmp/video1_ready"
#define IMG_WIDTH		1280
#define IMG_HEIGHT		720

// Valeurs seuils de détection des couleurs
#define C_R_MIN_R 90
#define C_R_MIN_G 0
#define C_R_MIN_B 0
#define C_R_MAX_R 255
#define C_R_MAX_G 70
#define C_R_MAX_B 60
#define	C_R_MIN_OFFSET_G 10
#define C_R_MIN_OFFSET_B 20

/*
#define C_G_MIN_R 0
#define C_G_MIN_G 65
#define C_G_MIN_B 0
#define C_G_MAX_R 50
#define C_G_MAX_G 255
#define C_G_MAX_B 65
#define	C_G_MIN_OFFSET_R 25
#define C_G_MIN_OFFSET_B 10
*/

#define C_G_MIN_R 0
#define C_G_MIN_G 70
#define C_G_MIN_B 0
#define C_G_MAX_R 75
#define C_G_MAX_G 255
#define C_G_MAX_B 65
#define	C_G_MIN_OFFSET_R 25
#define C_G_MIN_OFFSET_B 10

#define C_B_MIN_R 0
#define C_B_MIN_G 0
#define C_B_MIN_B 55
#define C_B_MAX_R 60
#define C_B_MAX_G 50
#define C_B_MAX_B 255
#define	C_B_MIN_OFFSET_R 15
#define C_B_MIN_OFFSET_G 15

// Paramétrages supplémentaires de la détection des couleurs
#define C_MIN_PIXELS		10
#define C_DOWNSCALING_STEP	5
#define C_WINDOW_LEFT		280
#define C_WINDOW_RIGHT		280
#define C_WINDOW_TOP		0
#define C_WINDOW_BOTTOM		0
#define C_DIST_TO_TARGET	360

// Centre de l'image croppée
#define C_IMG_CENTER_X		((IMG_WIDTH - C_WINDOW_LEFT - C_WINDOW_RIGHT)/2)
#define	C_IMG_CENTER_Y		((IMG_HEIGHT - C_WINDOW_TOP - C_WINDOW_BOTTOM)/2)

typedef struct {
	int abs;
	int ord;
	int bIsFound;
} T_Position;

// Tableau contenant les couleurs des cases
static char playgroundColors[9] = {
	'R', 'G', 'R',
	'G', 'B', 'G',
	'R', 'G', 'R'};

T_Position getPosition(int I_currentSquare, int I_destSquare);

// Wrapper getPosition
#ifdef __cplusplus
extern "C" {
#endif
	T_Position W_getPosition(int I_currentSquare, int I_destSquare); 
#ifdef __cplusplus
}
#endif

#endif // DETECT_TAG_H
