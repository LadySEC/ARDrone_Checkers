#ifndef DETECT_TAG_WRAPPER_H
#define DETECT_TAG_WRAPPER_H


#ifdef __cplusplus
extern "C" {
#endif

	typedef struct 
	{
	    int abs;
	    int ord;
	    int found;
	}Position;

	Position detect_wrapper(char* i_color, char* i_form); 


#ifdef __cplusplus
}
#endif
#endif // DETECT_TAG_WRAPPER_H


  
