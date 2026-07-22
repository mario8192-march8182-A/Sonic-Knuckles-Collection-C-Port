#include "sound.h"

extern void execute_bgm_command(short command);
extern void execute_sound_command(short command);


void bgmset(short command) {
  execute_bgm_command(command);
}


void soundset(short command) {
  execute_sound_command(command);
}
