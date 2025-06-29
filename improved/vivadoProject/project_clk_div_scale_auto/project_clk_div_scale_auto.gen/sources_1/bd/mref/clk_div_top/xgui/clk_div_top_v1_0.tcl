# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "NUM_WIN" -parent ${Page_0}
  ipgui::add_param $IPINST -name "THRESHOLD" -parent ${Page_0}


}

proc update_PARAM_VALUE.NUM_WIN { PARAM_VALUE.NUM_WIN } {
	# Procedure called to update NUM_WIN when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.NUM_WIN { PARAM_VALUE.NUM_WIN } {
	# Procedure called to validate NUM_WIN
	return true
}

proc update_PARAM_VALUE.THRESHOLD { PARAM_VALUE.THRESHOLD } {
	# Procedure called to update THRESHOLD when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.THRESHOLD { PARAM_VALUE.THRESHOLD } {
	# Procedure called to validate THRESHOLD
	return true
}


proc update_MODELPARAM_VALUE.THRESHOLD { MODELPARAM_VALUE.THRESHOLD PARAM_VALUE.THRESHOLD } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.THRESHOLD}] ${MODELPARAM_VALUE.THRESHOLD}
}

proc update_MODELPARAM_VALUE.NUM_WIN { MODELPARAM_VALUE.NUM_WIN PARAM_VALUE.NUM_WIN } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.NUM_WIN}] ${MODELPARAM_VALUE.NUM_WIN}
}

