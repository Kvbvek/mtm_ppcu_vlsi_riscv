# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# Copyright 2021 AGH University of Science and Technology
# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
set sdc_version 2.0

# Specify units used in SDC file
set_units -capacitance 1.0pF
set_units -time 1.0ns
set_time_unit -nanoseconds
set_load_unit -picofarads

# TODO: Create a clock object and define its waveform (freq = 50 MHz)
# You can get the source clock tree pin with the command: [get_pins u_pads_in/u_clk/C]
# Command: create_clock
create_clock -name clk -period 20 -waveform {0 10} [get_pins u_pads_in/u_clk/C]

# TODO: Specify the uncertainty on the clock network (setup: 0.1 Tclk,
# hold: 4-5x or T_hold_dff, e.g. 50ps)
# Command: set_clock_uncertainty
set_clock_uncertainty -setup 2 [get_clocks clk]
set_clock_uncertainty -hold 0.05 [get_clocks clk]

# TODO: Specify the clock transition (slew) on the specified clock (100 ps for TSMC 40n)
# Command: set_clock_transition
set_clock_transition 0.1 [get_clocks clk]

# TODO: Specify the rise/fall time of 0.5 ns for all the input signals except the clock
# Command: set_input_transition
set_input_transition 0.5 [all_inputs]

# TODO: Constrain input ports within the desing relative to the clock edge (try 1/4 of Tclk)
# Command: set_input_delay
set_input_delay 5.0 -clock [get_clocks clk] [all_inputs]

# TODO: Constrain output ports within the design relative to a clock edge (try 1/4 of Tclk)
# Command: set_output_delay
set_output_delay 5.0 -clock [get_clocks clk] [all_outputs]

# TODO: Constrain the output rise time to 1/5 of the clock period
# Command: set_max_transition
set_max_transition 4.0 [all_outputs]

# TODO: Set the maximum fanout load limit to 4 for all the input ports
# Command: set_max_fanout
set_max_fanout 4.0 [all_inputs]

# TODO: Set the output capacitance connected to all the output ports to 30pF
# Command: set_load
set_load 30.0 [all_outputs]

# Do not modify power pads (they are not connected during the synthesis).
set_dont_touch [get_cells u_pads_pwr]
