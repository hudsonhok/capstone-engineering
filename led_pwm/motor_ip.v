// motor_ip.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.

`timescale 1 ps / 1 ps
module motor_ip (
		input  wire [1:0]  encoder_in,             //   encoder_in.new_signal
		input  wire        avalon_slave_read,      // avalon_slave.read
		input  wire        avalon_slave_write,     //             .write
		output wire [31:0] avalon_slave_readdata,  //             .readdata
		input  wire [31:0] avalon_slave_writedata, //             .writedata
		output wire [1:0]  pwm_out                 //      pwm_out.new_signal
	);

	// TODO: Auto-generated HDL template
// Speed in revolutions/min = (1 / period) / GEARING / PULSES_PER_ROTATION * 60
// GEARING = 50, PULSES_PER_ROTATION = 12
	assign avalon_slave_readdata = 32'b00000000000000000000000000000000;

	assign pwm_out = 2'b00;
	
