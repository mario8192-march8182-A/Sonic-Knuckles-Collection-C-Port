#ifndef SKC_FALLTREE_H
#define SKC_FALLTREE_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void falltree(SKC_sprite_status* p_actwk);
void falltreemove2(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* falltreepat[1];
extern SKC_sprite_pattern* falltreepat1[1];
extern SKC_sprite_pattern* falltreepat2[4];
extern SKC_sprite_pattern* falltreepat3[4];

#endif
