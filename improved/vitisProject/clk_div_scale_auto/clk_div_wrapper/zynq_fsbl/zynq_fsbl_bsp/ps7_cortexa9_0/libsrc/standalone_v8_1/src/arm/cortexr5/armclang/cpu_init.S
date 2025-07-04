;/******************************************************************************
;* Copyright (c) 2020 - 2021 Xilinx, Inc.  All rights reserved.
;* SPDX-License-Identifier: MIT
;******************************************************************************/
;/*****************************************************************************/
;/**
;* @file cpu_init.S
;*
;* This file contains CPU specific initialization. Invoked from main CRT
;*
;* <pre>
;* MODIFICATION HISTORY:
;*
;* Ver   Who     Date     Changes
;* ----- ------- -------- ---------------------------------------------------
;* 7.3  dp  06/25/20   Initial version for armclang
;*
;* </pre>
;*
;* @note
;*
;* None.
;*
******************************************************************************/

	EXPORT __cpu_init

	AREA |.text|, CODE
	REQUIRE8 {TRUE}
	PRESERVE8 {TRUE}
	ENTRY

__cpu_init

;Clear cp15 regs with unknown reset values
	mov	r0, #0x0
	mcr	p15, 0, r0, c5, c0, 0	;DFSR
	mcr	p15, 0, r0, c5, c0, 1	;IFSR
	mcr	p15, 0, r0, c6, c0, 0	;DFAR
	mcr	p15, 0, r0, c6, c0, 2	;IFAR
	mcr	p15, 0, r0, c9, c13, 2	;PMXEVCNTR
	mcr	p15, 0, r0, c13, c0, 2	;TPIDRURW
	mcr	p15, 0, r0, c13, c0, 3	;TPIDRURO


;Reset and start Cycle Counter
	mov	r2, #0x80000000		;clear overflow
	mcr	p15, 0, r2, c9, c12, 3
	mov	r2, #0xd		;D, C, E
	mcr	p15, 0, r2, c9, c12, 0
	mov	r2, #0x80000000		;enable cycle counter
	mcr	p15, 0, r2, c9, c12, 1

	bx	lr

	END
