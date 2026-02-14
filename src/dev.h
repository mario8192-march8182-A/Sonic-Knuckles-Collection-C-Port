#ifndef SKC_DEV_H
#define SKC_DEV_H

void bitdevr(unsigned char* p_destination, unsigned char* p_source);
void mapdevr(unsigned short* p_destination, unsigned char* p_source, unsigned short offset);
unsigned short unlze(unsigned char** pp_destination, unsigned char* p_source);
void unlze_moduled(unsigned char* p_destination, unsigned char* p_source);

#endif
