#ifndef SKC_DEV_H
#define SKC_DEV_H

#include "types/cgdata.h"

void bitdevr(unsigned char* p_destination, unsigned char* p_source);
void divdevset(unsigned short id);
void divdevset2(SKC_cg_data* p_data);
void mapdevr(unsigned short* p_destination, unsigned char* p_source, unsigned short offset);
unsigned short unlze(unsigned char** pp_destination, unsigned char* p_source);
void unlze_moduled(unsigned char* p_destination, unsigned char* p_source);

#endif
