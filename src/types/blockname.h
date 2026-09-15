#ifndef SKC_BLOCKNAME_H
#define SKC_BLOCKNAME_H

#define BLOCKNAME_BIT_HF 10
#define BLOCKNAME_BIT_VF 11
#define BLOCKNAME_BIT_SCD 12

typedef struct SKC_block_name {
  unsigned int index : 10;
  unsigned int hf : 1;
  unsigned int vf : 1;
  unsigned int scd : 4;
}
SKC_block_name;

inline SKC_block_name get_block_name(unsigned short raw_block_name) {
  SKC_block_name name = {
    .index = raw_block_name,
    .hf = raw_block_name >> BLOCKNAME_BIT_HF,
    .vf = raw_block_name >> BLOCKNAME_BIT_VF,
    .scd = raw_block_name >> BLOCKNAME_BIT_SCD
  };
  return name;
}

#endif
