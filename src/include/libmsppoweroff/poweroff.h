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

/* set intermittent timer in microsecond */
void start_intermittent_tests_us(uint32_t us);

/* set intermittent timer in millisecond */
void start_intermittent_tests_ms(uint32_t ms);

void restart();

void stop_intermittent_tests();

#endif