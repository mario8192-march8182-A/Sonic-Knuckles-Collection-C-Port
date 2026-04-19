#ifndef SKC_ACTION_H
#define SKC_ACTION_H

#include "types/patsetwork.h"
#include "types/spritestatus.h"

void action(void);
void speedset(SKC_sprite_status* p_actwk);
void speedset2(SKC_sprite_status* p_actwk);
void speedset_g(SKC_sprite_status* p_actwk);
void speedset2_g(SKC_sprite_status* p_actwk);
void frameout(SKC_sprite_status* p_actwk);
void actionsub(SKC_sprite_status* p_actwk);
void patchg(SKC_sprite_status* p_actwk, signed char** p_chg_data);
void time_patchg(SKC_sprite_status* p_actwk, signed char** p_chg_data);
void patset(void);
void spatset(SKC_patset_work* p_work, SKC_actflg actflg, unsigned short sproffset);
void frameoutchk(SKC_sprite_status* p_actwk);
void frameoutchk2(SKC_sprite_status* p_actwk, short xposi);
void frameoutchk3(SKC_sprite_status* p_actwk);
void frameoutchkc(SKC_sprite_status* p_actwk);
void frameoutchkc0(SKC_sprite_status* p_actwk, short xposi);

#endif
