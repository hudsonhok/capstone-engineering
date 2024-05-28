// led_pwm.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.

`timescale 1 ps / 1 ps
module led_pwm (
		input  wire        clk,                    //          clk.clk
		input  wire        rst,                    //          rst.reset
		input  wire        avalon_slave_address,   // avalon_slave.address
		input  wire [31:0] avalon_slave_writedata, //             .writedata
		input  wire        avalon_slave_write,     //             .write
		output  wire [25:0] leds,                    //         leds.new_signal
		input wire [3:0] key
	);

	// TODO: Auto-generated HDL template
	reg [10:0] clk_2;
	reg [675:0] duty_cycles;
	
	always @(posedge clk) clk_2 <= clk_2 + 11'b1;
		genvar i;
			generate for (i = 0; i < 26; i = i + 1) begin:forloop
				always @(posedge clk) begin
					// Reset any duty cycle value to 0x3FFFFFF if its corresponding bit is set to 1 after an Avalon write
					if(avalon_slave_write && avalon_slave_writedata[i]) begin
						duty_cycles[26*i+25 : 26*i] <= 26'h3FFFFFF;
					end
					// Decrement each duty cycle value containing a value greater than zero by 1 every clock cycle.
					if(duty_cycles[26*i+25 : 26*i] > 0) begin
						duty_cycles[26*i+25: 26*i] <= duty_cycles[26*i+25: 26*i] - 26'b1;
					end
				end
				assign leds[i]= (clk_2 < duty_cycles[26*i+25: 26*i+15]) ? 1'b1 : 1'b0;
			end
			endgenerate
endmodule
