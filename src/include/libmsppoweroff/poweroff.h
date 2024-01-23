#ifndef INCLUDE_POWEROFF_H
#define INCLUDE_POWEROFF_H
#include <libmsp/macro_basics.h>
#include <stdint.h>
#include <string.h>

#ifndef CONFIG_INTERMITTENT_TIMER
#define CONFIG_INTERMITTENT_TIMER 0
#endif

void intermittent_init();
void intermittent_stop();

/* set intermittent timer in microsecond */
void start_intermittent_tests_us(uint32_t us);

/* set intermittent timer in millisecond */
void start_intermittent_tests_ms(uint32_t ms);

void restart();

void stop_intermittent_tests();

#endif