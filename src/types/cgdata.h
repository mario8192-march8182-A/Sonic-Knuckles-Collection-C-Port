#ifndef SKC_CGDATA_H
#define SKC_CGDATA_H

typedef struct SKC_cg_data {
  unsigned short cnt;
  struct {
    unsigned char* cg_ptr;
    unsigned short offset;
  }
  data[];
}
SKC_cg_data;

#endif
