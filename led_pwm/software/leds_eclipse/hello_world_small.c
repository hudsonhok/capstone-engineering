#include <stdio.h>
#include <system.h>
#include <math.h>
#include <io.h>
#include <alt_types.h>
#include "sys/alt_stdio.h"
#include <altera_avalon_performance_counter.h>

#define LEDS_BASE 0x10001050
#define PERFORMANCE_COUNTER_0_BASE 0x10001000

int main() {

	float pwm_freq = 10e3f;
	float dim_period = 2.0f;

	alt_u64 pwm_duty_cycle;
	alt_u64 temp;
	alt_u64 count;
	alt_u64 pwm_period_cycles, duty_cycle_cycles, dim_period_cycles;
	alt_u32 leds;

	// Keep track of previous cycles
	alt_u64 last_count_cycles = 0;
	alt_u64 dim_adj_cycles = dim_period / ALT_CPU_CPU_FREQ;

	// Periods to clock cycles
	dim_period_cycles = dim_period * ALT_CPU_CPU_FREQ;
	pwm_period_cycles = 1.f/pwm_freq * ALT_CPU_CPU_FREQ;

	// Start performance counter
	IOWR(PERFORMANCE_COUNTER_0_BASE, 1, 0);

    while (1) {
    	// Split 64-bit counter into two 32-bit
    	union {
            struct {
                alt_u32 low;
                alt_u32 high;
            } parts;
            alt_u64 combined;
        } temp;

        temp.parts.high = IORD(PERFORMANCE_COUNTER_0_BASE, 1);
        temp.parts.low = IORD(PERFORMANCE_COUNTER_0_BASE, 0);
        count = temp.combined;

        // If enough time has passed (in clock cycles) since the last adjustment, time to calculate new pwm_duty_cycle
        if (count - last_count_cycles > dim_adj_cycles) {
            // Convert pwm_duty_cycle percentage to decimal
            float pwm_duty_cycle = fabs((count % dim_period_cycles) * (-2.f/dim_period_cycles) + 1.0f);

            duty_cycle_cycles = (float)pwm_duty_cycle * pwm_period_cycles;
            last_count_cycles = count; // update last cycles
        }

        // Turn on/off LEDs depending on the PWM cycle we're on
        if (count % pwm_period_cycles < duty_cycle_cycles) // if the current time is less than the duration of the "on" portion of the PWM cycle
            leds = 1;
        else
            leds = 0;

        IOWR(LEDS_BASE,0,0x3FFFFFFF * leds);
    }

    return 0;
}

