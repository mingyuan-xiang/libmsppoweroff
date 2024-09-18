#ifndef INCLUDE_POWEROFF_H
#define INCLUDE_POWEROFF_H
#include <libmsp/macro_basics.h>
#include <libmsp/nv.h>
#include <stdint.h>
#include <string.h>

#ifndef CONFIG_INTERMITTENT_TIMER
#define CONFIG_INTERMITTENT_TIMER 0
#endif

#define INTERMITTENT_STATUS_SIZE 8

extern __ro_hinv uint16_t intermittent_status[INTERMITTENT_STATUS_SIZE];

void intermittent_init();
void intermittent_stop();

/* set intermittent timer in (second and ACLK cycles (32768 Hz)) */
void start_intermittent_tests(uint32_t sec, uint16_t cycles);

void stop_intermittent_tests();

#endif