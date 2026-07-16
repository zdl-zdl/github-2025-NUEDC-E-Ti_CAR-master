#ifndef _gray_h
#define _gray_h
#include "headfile.h"

typedef struct{
	uint8_t io[8];	// 8路一字排开，io[0]最左，io[7]最右
} GRAY_Struct;

void Gray_Update(void);

extern GRAY_Struct gray;


#endif