#ifndef SKC_COLORTBL_H
#define SKC_COLORTBL_H

typedef struct SKC_colortbl_entry {
  unsigned short* palette_ptr;
  unsigned short offset;
  unsigned short cnt;
}
SKC_colortbl_entry;

extern SKC_colortbl_entry colortbl[66];
extern unsigned short sega_color[64];
extern unsigned short opening_color[16];
extern unsigned short stageselect_color[64];
extern unsigned short menu_color[64];
extern unsigned short knuckles_color[16];
extern unsigned short angelisland1_color[48];
extern unsigned short angelisland12_color[48];
extern unsigned short angelisland2_color[48];
extern unsigned short angelislandboss_color[48];
extern unsigned short angelisland1water_color[64];
extern unsigned short angelisland2water_color[64];
extern unsigned short hydrocity1_color[48];
extern unsigned short hydrocity2_color[48];
extern unsigned short hydrocity1water_color[64];
extern unsigned short hydrocity2water_color[64];
extern unsigned short marblegarden_color[48];
extern unsigned short carnivalnight_color[48];
extern unsigned short carnivalnight2water_color[64];
extern unsigned short flyingbattery1_color[48];
extern unsigned short flyingbattery2_color[48];
extern unsigned short icecap1_color[48];
extern unsigned short icecap2_color[48];
extern unsigned short icecap2water_color[64];
extern unsigned short launchbase1_color[48];
extern unsigned short launchbase2_color[48];
extern unsigned short launchbasewater_color[64];
extern unsigned short launchbasewater2_color[48];
extern unsigned short mushroomhill1_color[48];
extern unsigned short mushroomhill2_color[48];
extern unsigned short sandopolis1_color[48];
extern unsigned short sandopolis2_color[48];
extern unsigned short sandopolis12_color[48];
extern unsigned short sandopolis22_color[48];
extern unsigned short lavareef1_color[48];
extern unsigned short lavareef2_color[48];
extern unsigned short skysanctuary1_color[48];
extern unsigned short skysanctuary2_color[48];
extern unsigned short ending1_color[48];
extern unsigned short ending2_color[48];
extern unsigned short deathegg1_color[48];
extern unsigned short deathegg2_color[48];
extern unsigned short doomsday_color[48];
extern unsigned short azurelake_color[48];
extern unsigned short balloonpark_color[48];
extern unsigned short desertpalace_color[48];
extern unsigned short chromegadget_color[48];
extern unsigned short endlessmine_color[48];
extern unsigned short gumballmachine_color[48];
extern unsigned short rollingjump_color[48];
extern unsigned short slotmachine_color[48];
extern unsigned short lavareefboss_color[48];
extern unsigned short hiddenpalace_color[48];
extern unsigned short deatheggboss_color[48];

#endif
