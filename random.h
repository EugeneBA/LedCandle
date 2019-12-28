/*
 * random.h
 *
 * Created: 01.04.2018 23:36:28
 *  Author: Eugene
 */ 


#ifndef RANDOM_H_
#define RANDOM_H_

#ifdef    USE_RANDOM_SEED
#define    RANDOM_SEED_ADDRESS    0x00
#endif    /* !USE_RANDOM_SEED */

void random_init(uint16_t seed);
uint16_t random(void);

#endif /* RANDOM_H_ */