#include "swdata.h"
#include <stdbool.h>


extern inline bool are_any_dir_buttons_used(SKC_pad pad);
extern inline bool are_any_trg_buttons_used(SKC_pad pad);
extern inline bool are_any_face_buttons_used(SKC_pad pad);
extern inline bool are_any_buttons_used(SKC_pad pad);
extern inline bool are_same_buttons_used(SKC_pad pad0, SKC_pad1);
extern inline SKC_pad get_pad(unsigned char raw_swdata);
extern inline SKC_swdata get_swdata(unsigned short raw_swdata);
