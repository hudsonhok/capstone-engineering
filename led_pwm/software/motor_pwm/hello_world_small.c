/* 
 * "Small Hello World" example. 
 * 
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example 
 * designs. It requires a STDOUT  device in your system's hardware. 
 *
 * The purpose of this example is to demonstrate the smallest possible Hello 
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard 
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete 
 * description.
 * 
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION 
 *      This removes software exception handling, which means that you cannot 
 *      run code compiled for Nios II cpu with a hardware multiplier on a core 
 *      without a the multiply unit. Check the Nios II Software Developers 
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks  
 *      support for buffering, file IO, floating point and getch(), etc. 
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program 
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */
#include <iostream>
#include <cmath>
#include "sys/alt_stdio.h"

// Constants
const double CPU_FREQ = 50000000.0; // Replace with the actual CPU frequency
const double T_s = 1.0; // Replace with the desired time interval
const double k_p = 0.1; // Replace with the proportional gain
const double k_d = 0.01; // Replace with the derivative gain
const double k_i = 0.001; // Replace with the integral gain
const double setpoint = 100.0; // Replace with the desired setpoint
const double time = 10.0; // Replace with the desired total time

// Function to read motor RPM (replace with actual implementation)
double READ_MOTOR_RPM() {
    // Replace this with the actual code to read motor RPM
    return 0.0;
}

// Function to read cycle counter (replace with actual implementation)
double READ_CYCLE_COUNTER() {
    // Replace this with the actual code to read the cycle counter
    return 0.0;
}

int main()
{ 
  alt_putstr("Hello from Nios II!\n");
  // Variables
  double cycle_counter, prev_control_action_cycles = 0.0;
  double cycles_since_last_control, time_since_last_control, time_since_start;
  double current_motor_rpm, error_old = 0.0, error = 0.0, error_accum = 0.0, error_delta = 0.0;
  double motor_input;

  while (1) {
      // Determine if we should perform control
      cycle_counter = READ_CYCLE_COUNTER();
      cycles_since_last_control = cycle_counter - prev_control_action_cycles;
      time_since_last_control = cycles_since_last_control / CPU_FREQ;
      time_since_start = cycle_counter / CPU_FREQ;

      if (time_since_last_control >= T_s) {
          current_motor_rpm = READ_MOTOR_RPM();

          error_old = error;
          error = current_motor_rpm - setpoint;
          error_accum += error;
          error_delta = error - error_old;

          motor_input = k_p * error + k_d * error_delta + k_i * error_accum;

          // Log time_since_start, motor_input, current_motor_rpm using alt_putstr
          char logMessage[100];
          snprintf(logMessage, sizeof(logMessage), "Time: %f, Motor Input: %f, Motor RPM: %f\n", time_since_start, motor_input, current_motor_rpm);
          alt_putstr(logMessage);

          prev_control_action_cycles = cycle_counter;

          if (time_since_start > time) {
              break;
          }
      }
  }

  return 0;
}
/*
	  cycle_counter = READ_CYCLE_COUNTER
	  cycles_since_last_control = cycle_counter - prev_control_action_cycles
	  time_since_last_control = cycles_since_last_control / CPU_FREQ
	  time_since_start = cycle_counter / CPU_FREQ

	  if time_since_last_control >= T_s:
	  	  current_motor_rpm = READ_MOTOR_RPM

		  error_old = error
		  error = current_motor_rpm - setpoint
		  error_accum += error
		  error_delta = error - error_old

		  motor_input = k_p * error + k_d * error_delta + k_i*error_accum

		  log time_since_start
		  log motor_input
		  log current_motor_rpm

		  prev_control_action_cycles = cycle_counter

		  if time_since_start > time:
		  	  break
 */
