#ifndef SKC_FOX_H
#define SKC_FOX_H

typedef struct SKC_sprite_status SKC_sprite_status;

void vsfox(SKC_sprite_status* p_playerwk);
void fox00(SKC_sprite_status* p_playerwk);
void foxcpu(SKC_sprite_status* p_actwk);
void foxcpu_wait0_init(SKC_sprite_status* p_actwk);
void foxjumpcolsub0(SKC_sprite_status* p_playerwk);
void foxwrt(SKC_sprite_status* p_playerwk);
void foxwrt0(unsigned char patno);
void ev0201(SKC_sprite_status* p_actwk);

#endif
