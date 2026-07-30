#ifndef SKC_SCORE_H
#define SKC_SCORE_H

typedef struct SKC_patset_work SKC_patset_work;

void vsscore(SKC_patset_work* p_work);
void score(SKC_patset_work* p_work);
void scoreup(unsigned short points);
void scoreset(void);
void scoreinit(void);

#endif
