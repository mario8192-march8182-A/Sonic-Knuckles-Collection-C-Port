#ifndef A004xxxxx_H
#define A004xxxxx_H

#include <stdbool.h>

void PlaySoundRegister(long id);
void Copy_Data_To_VRAM(unsigned char* source, unsigned short destination, unsigned short words);
void Load_PLC_Raw(sprite_status* p_actwk, cg_data* p_data);
void Queue_Kos_Module(void* p_data, unsigned short act_id);
short atan(long x, long y);
void scoreup(unsigned int updata);
void LoadEnemyArt();
void bgmset(long id);
void soundset(long id);
void speedset(sprite_status* p_actwk);
void speedset2(sprite_status* p_actwk);
void speedset2g(sprite_status* p_actwk);
void frameout(sprite_status* p_actwk);
void actionsub(sprite_status* p_actwk);
void patchg(sprite_status* p_actwk, signed char** p_chg_data);
void frameoutchk(sprite_status* p_actwk);
void frameoutchkc(sprite_status* p_actwk, short xposi);
bool playdamageset(sprite_status* p_playerwk, sprite_status* p_attack_actwk);
bool playdieset(sprite_status* p_actwk, long sound_id);
void Add_Object_To_Collision_Response_List(sprite_status* p_actwk);
unsigned long random();
void sinset(unsigned char angle, short* sin, short* cos);
bool Create_New_Sprite4(sprite_status** pp_new_actwk, short remaining_slot_cnt);
bool Create_New_Sprite(sprite_status** pp_new_actwk, short* p_slot_cnt);
bool Create_New_Sprite3(sprite_status* p_actwk, sprite_status** pp_new_actwk, short* p_slot_cnt);
bool Create_New_Sprite_Int(sprite_status** pp_new_actwk, short* p_slot_cnt);
void Clear_SpriteRingMem();
void Player_TouchFloor(sprite_status* p_actwk);
short ObjCheckFloorDist(sprite_status* p_actwk);
short RingCheckFloorDist(sprite_status* p_actwk);
short RingCheckFloorDist_ReverseGravity(sprite_status* p_actwk);

#endif
