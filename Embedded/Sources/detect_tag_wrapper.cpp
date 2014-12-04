#include "detect_tag.h"
#include "detect_tag_wrapper.h"

extern "C" {

        Position detect_wrapper(char* i_color, char* i_form) 
	{
		std::string color = i_color;
		std::string form = i_form;

		return detect();
        }

//--- modif hugo 04/12/2015 ------------------------------------
	void reset_x_y_last(){
		resetReper_x_y_last();
	}
//--- modif hugo 04/12/2015 ------------------------------------
} 
