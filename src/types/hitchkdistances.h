#ifndef SKC_HITCHKDISTANCES_H
#define SKC_HITCHKDISTANCES_H

typedef struct SKC_hitchk_distances {
  short left_edge;
  unsigned char max_top;
  unsigned char min_bottom;
  short max_top_coli;
  short nearest_edge_hori;
  short nearest_edge_vert;
}
SKC_hitchk_distances;

#endif
