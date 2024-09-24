#include <msp430.h>
#include <libmsp/clock.h>
#include <libmsp/gpio.h>
#include <libmsp/timer.h>
#include <libmsp/mspbase.h>
#include <libmspio/uartio.h>
#include <libmspprintf/mspprintf.h>
#include <libmsppoweroff/poweroff.h>

static uint16_t old_csctl2 = 0;

void intermittent_init() {
  lfxt_start(old_csctl2);
}
void intermittent_stop() { lfxt_stop(old_csctl2); }

static uint32_t poweroff_tick;
static uint16_t poweroff_timer_cnt;

static unsigned int intermittent_int_state;
static uint32_t intermittent_tick;

#define CNT_MAX 65536
#define US_PER_CYCLE 15 // (1000000 / CNT_MAX)

static void set_timer_threshold(uint32_t sec, uint16_t cycles) {
  poweroff_tick = sec;
  poweroff_timer_cnt = cycles;
}

void start_intermittent_tests(uint32_t sec, uint16_t cycles) {
  intermittent_tick = 0;
  set_timer_threshold(sec, cycles);

  TA0CCTL2 = CM_1 | CCIS_1 | SCS | CAP | CCIE;

  timer_setup_cont(CONFIG_INTERMITTENT_TIMER, ACLK, 1, 1);

  intermittent_int_state = __get_interrupt_state();
  __enable_interrupt();

  // start the timer on continuous mode & run
  timer_start_cont(CONFIG_INTERMITTENT_TIMER);
}

void stop_intermittent_tests() {
  // disable the timer
  timer_halt(CONFIG_INTERMITTENT_TIMER);
  __set_interrupt_state(intermittent_int_state);

  timer_halt(CONFIG_INTERMITTENT_TIMER);
  timer_reset(CONFIG_INTERMITTENT_TIMER);
  timer_IFG_disable(CONFIG_INTERMITTENT_TIMER);
}

void
    __attribute__((interrupt(STIC3(TIMER, CONFIG_INTERMITTENT_TIMER, _A1_VECTOR))))
    STIC3(TIMER, CONFIG_INTERMITTENT_TIMER, _A1_ISR)(void) {
  switch (__even_in_range(STIC3(TA, CONFIG_INTERMITTENT_TIMER, IV), TAIV__TAIFG)) {
  case TAIV__NONE:
    break; // No interrupt
  case TAIV__TACCR1:
    break; // CCR1 not used
  case TAIV__TACCR2:
  if (intermittent_tick >= poweroff_tick && TA0CCR2 >= poweroff_timer_cnt) {
    PMMCTL0 = PMMPW | PMMSWPOR;
  }
    break;
  case TAIV__TACCR3:
    break; // reserved
  case TAIV__TACCR4:
    break; // reserved
  case TAIV__TACCR5:
    break; // reserved
  case TAIV__TACCR6:
    break;          // reserved
  case TAIV__TAIFG: // overflow
    intermittent_tick++;
    break;
  default:
    break;
  }
}