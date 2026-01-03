#ifndef SKC_CCHGCNT_H
#define SKC_CCHGCNT_H

typedef struct SKC_cchg_cnt_command {
  signed char items_index;
  signed char timer_init;
}
SKC_cchg_cnt_command;

typedef struct SKC_cchg_cnt_info {
  unsigned short** items_ptr;
  unsigned short color_cnt_per_command;
  SKC_cchg_cnt_command commands[];
}
SKC_cchg_cnt_info;

#endif
