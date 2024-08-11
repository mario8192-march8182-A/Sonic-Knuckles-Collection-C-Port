#ifndef COLORTBLENTRY_H
#define COLORTBLENTRY_H

typedef struct colortbl_entry {
  unsigned short* p_palette;
  unsigned short offset;
  unsigned short cnt;
}
colortbl_entry;

#endif
