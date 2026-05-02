#ifndef SKC_DIRCOL_H
#define SKC_DIRCOL_H

#include "types/spritestatus.h"

typedef struct SKC_dircol_result {
  signed char offset;
  signed char offset2;
  unsigned char direc;
}
SKC_dircol_result;

SKC_dircol_result dircolm(SKC_sprite_status* p_actwk, unsigned char direc);
SKC_dircol_result dircol2(SKC_sprite_status* p_actwk, unsigned char direc);
SKC_dircol_result dircol_d(SKC_sprite_status* p_actwk);
SKC_dircol_result dircol_d2(SKC_sprite_status* p_actwk);
SKC_dircol_result dircol_d3(SKC_sprite_status* p_actwk, short xposi, short yposi);
SKC_dircol_result vsdircol_d(SKC_sprite_status* p_actwk, short xposi, short yposi);
SKC_dircol_result crushchk_d(SKC_sprite_status* p_actwk);
SKC_dircol_result edgechk_d(SKC_sprite_status* p_actwk);
SKC_dircol_result edgechk_d2(SKC_sprite_status* p_actwk, short xposi);
SKC_dircol_result edgechk_d3(SKC_sprite_status* p_actwk, short xposi, short yposi);
SKC_dircol_result landchk_d(SKC_sprite_status* p_actwk);
SKC_dircol_result emycol_d(SKC_sprite_status* p_actwk);
SKC_dircol_result emycol_d2(SKC_sprite_status* p_actwk, short xposi);
SKC_dircol_result emycol_d3(SKC_sprite_status* p_actwk, short xposi, short yposi);
SKC_dircol_result flyringcol_d(SKC_sprite_status* p_actwk);
SKC_dircol_result dircol_r(SKC_sprite_status* p_actwk);
SKC_dircol_result rideobjcol_r(SKC_sprite_status* p_actwk, unsigned char solid_bit);
SKC_dircol_result dircol_r2(SKC_sprite_status* p_actwk);
SKC_dircol_result dircol_r3(SKC_sprite_status* p_actwk, short xposi, short yposi);
SKC_dircol_result vsdircol_r(SKC_sprite_status* p_actwk, short xposi, short yposi);
SKC_dircol_result emycol_r(SKC_sprite_status* p_actwk, short sprhs);
SKC_dircol_result dircol_u(SKC_sprite_status* p_actwk);
SKC_dircol_result rideobjcol_u(SKC_sprite_status* p_actwk, unsigned char solid_bit);
SKC_dircol_result dircol_u2(SKC_sprite_status* p_actwk);
SKC_dircol_result dircol_u3(SKC_sprite_status* p_actwk, short xposi, short yposi);
SKC_dircol_result vsdircol_u(SKC_sprite_status* p_actwk, short xposi, short yposi);
SKC_dircol_result emycol_u(SKC_sprite_status* p_actwk);
SKC_dircol_result flyringcol_u(SKC_sprite_status* p_actwk);
SKC_dircol_result dircol_l(SKC_sprite_status* p_actwk);
SKC_dircol_result rideobjcol_l(SKC_sprite_status* p_actwk, unsigned char solid_bit);
SKC_dircol_result dircol_l2(SKC_sprite_status* p_actwk);
SKC_dircol_result dircol_l3(SKC_sprite_status* p_actwk, short xposi, short yposi);
SKC_dircol_result vsdircol_l(SKC_sprite_status* p_actwk, short xposi, short yposi);
SKC_dircol_result vsdircol_l2(SKC_sprite_status* p_actwk);
SKC_dircol_result emycol_l(SKC_sprite_status* p_actwk, short sprhs);
SKC_dircol_result emycol_l2(SKC_sprite_status* p_actwk, short xposi);
SKC_dircol_result emycol_l3(SKC_sprite_status* p_actwk, short xposi, short yposi);

#endif
