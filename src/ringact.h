#ifndef SKC_RINGACT_H
#define SKC_RINGACT_H

typedef struct SKC_patset_work SKC_patset_work;
typedef struct SKC_sprite_status SKC_sprite_status;

typedef struct SKC_ringwk_entry {
  signed char pattim;
  signed char patno;
}
SKC_ringwk_entry;

void ringactsetchk(void);
void ringcol(SKC_sprite_status* p_playerwk);
void ringpatset(SKC_patset_work* p_work);

#endif
