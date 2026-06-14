#ifndef ACTTIMER_H
#define ACTTIMER_H

typedef struct act_timer {
  unsigned char reserved;
  unsigned char minutes;
  unsigned char seconds;
  unsigned char frames;
}
act_timer;

#endif
