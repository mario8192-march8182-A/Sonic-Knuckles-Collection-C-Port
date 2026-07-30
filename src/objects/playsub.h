#ifndef SKC_PLAYSUB_H
#define SKC_PLAYSUB_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void plawa(SKC_sprite_status* p_actwk);
extern signed char awasintbl[128];
void plairset(SKC_sprite_status* p_playerwk);
void baria(SKC_sprite_status* p_actwk);
void muteki(SKC_sprite_status* p_actwk);
void effect(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* effectpat[30];
extern unsigned short* effectwrtpat[30];
void vseffect(SKC_sprite_status* p_actwk);
void sstartrail(SKC_sprite_status* p_actwk);
void hstars(SKC_sprite_status* p_actwk);
void wspin(SKC_sprite_status* p_actwk);
void fbaria(SKC_sprite_status* p_actwk);
void tbaria(SKC_sprite_status* p_actwk);
void abaria(SKC_sprite_status* p_actwk);
void sflickies(SKC_sprite_status* p_actwk);
void imagetrail(SKC_sprite_status* p_actwk);

#endif
