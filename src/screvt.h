#ifndef SKC_SCREVT_H
#define SKC_SCREVT_H

#include "types/spritestatus.h"

void scr_evt_init(void);
void scr_evt_move(void);
void scrollwrt(void);
void SpecialVInt_LBZ2WindowCopy(void);
void SpecialVInt_LBZ2ScrollAClear(void);
void SpecialVInt_LBZ2ScrollAClear2(void);
void SpecialVInt_LBZ2WindowClear(void);
void SpecialEvents(void);
void Obj_AIZ1TreeRevealControl(SKC_sprite_status* p_actwk);

#endif
