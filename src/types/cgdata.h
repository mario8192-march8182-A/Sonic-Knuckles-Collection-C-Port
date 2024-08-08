#ifndef CGDATA_H
#define CGDATA_H

typedef struct cg_data_entry {
  unsigned char* tiles_ptr;
  unsigned short offset;
}
cg_data_entry;

typedef struct cg_data {
  unsigned short cnt;
  cg_data_entry data[];
}
cg_data;

#endif
