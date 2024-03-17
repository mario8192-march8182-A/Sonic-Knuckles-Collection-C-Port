#ifndef A004xxxxx_H
#define A004xxxxx_H

#include <stdbool.h>

void PlaySoundRegister(long id);
void Copy_Data_To_VRAM(unsigned short d1, unsigned short d2, unsigned short d3);
void Load_PLC_Raw(sprite_status* pActwk, cg_data* pData);
void LoadEnemyArt();
void soundset(long id);
void speedset2(sprite_status* pActwk);
void frameout(sprite_status* pActwk);
void actionsub(sprite_status* pActwk);
void playdamageset(sprite_status* pPlayerwk, sprite_status* pAttackActwk);
void Add_Object_To_Collision_Response_List(sprite_status* pActwk);
unsigned long random();
bool Create_New_Sprite(sprite_status** ppNewActwk);
bool Create_New_Sprite3(sprite_status* pActwk, sprite_status** ppNewActwk);
bool Create_New_Sprite_Int(sprite_status** ppNewActwk, short slot_cnt);

#endif
