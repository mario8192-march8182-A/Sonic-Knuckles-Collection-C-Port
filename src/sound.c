#include "sound.h"


void bgmset(short command) {
  execute_bgm_command(command);
}


void soundset(short command) {
  execute_sound_command(command);
}
