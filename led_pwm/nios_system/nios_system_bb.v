
module nios_system (
	clk_clk,
	encoder_in_new_signal,
	key_export,
	new_sdram_controller_0_wire_addr,
	new_sdram_controller_0_wire_ba,
	new_sdram_controller_0_wire_cas_n,
	new_sdram_controller_0_wire_cke,
	new_sdram_controller_0_wire_cs_n,
	new_sdram_controller_0_wire_dq,
	new_sdram_controller_0_wire_dqm,
	new_sdram_controller_0_wire_ras_n,
	new_sdram_controller_0_wire_we_n,
	pwm_out_new_signal,
	reset_reset_n,
	sdram_clk_clk,
	leds_1_export);	

	input		clk_clk;
	input	[1:0]	encoder_in_new_signal;
	input	[3:0]	key_export;
	output	[12:0]	new_sdram_controller_0_wire_addr;
	output	[1:0]	new_sdram_controller_0_wire_ba;
	output		new_sdram_controller_0_wire_cas_n;
	output		new_sdram_controller_0_wire_cke;
	output		new_sdram_controller_0_wire_cs_n;
	inout	[31:0]	new_sdram_controller_0_wire_dq;
	output	[3:0]	new_sdram_controller_0_wire_dqm;
	output		new_sdram_controller_0_wire_ras_n;
	output		new_sdram_controller_0_wire_we_n;
	output	[1:0]	pwm_out_new_signal;
	input		reset_reset_n;
	output		sdram_clk_clk;
	output	[1:0]	leds_1_export;
endmodule
