#ifndef SKC_COLORTBLENTRY_H
#define SKC_COLORTBLENTRY_H

typedef struct SKC_colortbl_entry {
  unsigned short* p_palette;
  unsigned short offset;
  unsigned short cnt;
}
SKC_colortbl_entry;

#endif
