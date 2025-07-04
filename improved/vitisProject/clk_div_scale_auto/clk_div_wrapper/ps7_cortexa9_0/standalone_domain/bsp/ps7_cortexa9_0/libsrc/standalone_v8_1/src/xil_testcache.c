/******************************************************************************
* Copyright (c) 2009 - 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xil_testcache.c
* @addtogroup common_test_utils
*
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date	 Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a hbm  07/28/09 Initial release
* 4.1   asa  05/09/14 Ensured that the address uses for cache test is aligned
*				      cache line.
* </pre>
*
******************************************************************************/
#ifdef __ARM__
#include "xil_cache.h"
#include "xil_testcache.h"
#include "xil_types.h"
#include "xpseudo_asm.h"
#ifdef __aarch64__
#include "xreg_cortexa53.h"
#else
#include "xreg_cortexr5.h"
#endif

#include "xil_types.h"

extern void xil_printf(const char8 *ctrl1, ...);

#define DATA_LENGTH 128

#ifdef __aarch64__
static INTPTR Data[DATA_LENGTH] __attribute__ ((aligned(64)));
#else
static INTPTR Data[DATA_LENGTH] __attribute__ ((aligned(32)));
#endif


/*****************************************************************************/
/**
*
* @brief    Perform DCache range related API test such as Xil_DCacheFlushRange
*           and Xil_DCacheInvalidateRange. This test function writes a constant
*           value to the Data array, flushes the range, writes a new value, then
*           invalidates the corresponding range.
*
* @return
*      - -1 is returned for a failure
*      - 0 is returned for a pass
*
*****************************************************************************/
s32 Xil_TestDCacheRange(void)
{
	s32 Index;
	s32 Status = 0;
	u32 CtrlReg;
	INTPTR Value;

	xil_printf("-- Cache Range Test --\n\r");

	for (Index = 0; Index < DATA_LENGTH; Index++)
		Data[Index] = 0xA0A00505;

	xil_printf("    initialize Data done:\r\n");

	Xil_DCacheFlushRange((INTPTR)Data, DATA_LENGTH * sizeof(INTPTR));

	xil_printf("    flush range done\r\n");

	dsb();
	#ifdef __aarch64__
			CtrlReg = mfcp(SCTLR_EL3);
			CtrlReg &= ~(XREG_CONTROL_DCACHE_BIT);
			mtcp(SCTLR_EL3,CtrlReg);
	#else
			CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
			CtrlReg &= ~(XREG_CP15_CONTROL_C_BIT);
			mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
	#endif
	dsb();

	Status = 0;

	for (Index = 0; Index < DATA_LENGTH; Index++) {
		Value = Data[Index];
		if (Value != 0xA0A00505) {
			Status = -1;
			xil_printf("Data[%d] = %x\r\n", Index, Value);
			break;
		}
	}

	if (!Status) {
		xil_printf("	Flush worked\r\n");
	}
	else {
		xil_printf("Error: flush dcache range not working\r\n");
	}
	dsb();
	#ifdef __aarch64__
			CtrlReg = mfcp(SCTLR_EL3);
			CtrlReg |= (XREG_CONTROL_DCACHE_BIT);
			mtcp(SCTLR_EL3,CtrlReg);
		#else
			CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
			CtrlReg |= (XREG_CP15_CONTROL_C_BIT);
			mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
		#endif
	dsb();
	for (Index = 0; Index < DATA_LENGTH; Index++)
		Data[Index] = 0xA0A0C505;



	Xil_DCacheFlushRange((INTPTR)Data, DATA_LENGTH * sizeof(INTPTR));

	for (Index = 0; Index < DATA_LENGTH; Index++)
		Data[Index] = Index + 3;

	Xil_DCacheInvalidateRange((INTPTR)Data, DATA_LENGTH * sizeof(INTPTR));

	xil_printf("    invalidate dcache range done\r\n");
	dsb();
	#ifdef __aarch64__
			CtrlReg = mfcp(SCTLR_EL3);
			CtrlReg &= ~(XREG_CONTROL_DCACHE_BIT);
			mtcp(SCTLR_EL3,CtrlReg);
	#else
			CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
			CtrlReg &= ~(XREG_CP15_CONTROL_C_BIT);
			mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
	#endif
	dsb();
	for (Index = 0; Index < DATA_LENGTH; Index++)
		Data[Index] = 0xA0A0A05;
	dsb();
	#ifdef __aarch64__
			CtrlReg = mfcp(SCTLR_EL3);
			CtrlReg |= (XREG_CONTROL_DCACHE_BIT);
			mtcp(SCTLR_EL3,CtrlReg);
	#else
			CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
			CtrlReg |= (XREG_CP15_CONTROL_C_BIT);
			mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
	#endif
	dsb();

	Status = 0;

	for (Index = 0; Index < DATA_LENGTH; Index++) {
		Value = Data[Index];
		if (Value != 0xA0A0A05) {
			Status = -1;
			xil_printf("Data[%d] = %x\r\n", Index, Value);
			break;
		}
	}


	if (!Status) {
		xil_printf("    Invalidate worked\r\n");
	}
	else {
		xil_printf("Error: Invalidate dcache range not working\r\n");
	}
	xil_printf("-- Cache Range Test Complete --\r\n");
	return Status;

}

/*****************************************************************************/
/**
* @brief   Perform DCache all related API test such as Xil_DCacheFlush and
*           Xil_DCacheInvalidate. This test function writes a constant value
*           to the Data array, flushes the DCache, writes a new value,
*           then invalidates the DCache.
*
* @return
*          - 0 is returned for a pass
*          - -1 is returned for a failure
*****************************************************************************/
s32 Xil_TestDCacheAll(void)
{
	s32 Index;
	s32 Status;
	INTPTR Value;
	u32 CtrlReg;

	xil_printf("-- Cache All Test --\n\r");

	for (Index = 0; Index < DATA_LENGTH; Index++)
		Data[Index] = 0x50500A0A;
	xil_printf("    initialize Data done:\r\n");

	Xil_DCacheFlush();
	xil_printf("    flush all done\r\n");
	dsb();
	#ifdef __aarch64__
		CtrlReg = mfcp(SCTLR_EL3);
		CtrlReg &= ~(XREG_CONTROL_DCACHE_BIT);
		mtcp(SCTLR_EL3,CtrlReg);
	#else
		CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
		CtrlReg &= ~(XREG_CP15_CONTROL_C_BIT);
		mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
	#endif
	dsb();
	Status = 0;

	for (Index = 0; Index < DATA_LENGTH; Index++) {
		Value = Data[Index];

		if (Value != 0x50500A0A) {
			Status = -1;
			xil_printf("Data[%d] = %x\r\n", Index, Value);
			break;
		}
	}

	if (!Status) {
		xil_printf("    Flush all worked\r\n");
	}
	else {
		xil_printf("Error: Flush dcache all not working\r\n");
	}
	dsb();
	#ifdef __aarch64__
		CtrlReg = mfcp(SCTLR_EL3);
		CtrlReg |= (XREG_CONTROL_DCACHE_BIT);
		mtcp(SCTLR_EL3,CtrlReg);
	#else
		CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
			CtrlReg |= (XREG_CP15_CONTROL_C_BIT);
			mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
	#endif
	dsb();
	for (Index = 0; Index < DATA_LENGTH; Index++)
		Data[Index] = 0x505FFA0A;

	Xil_DCacheFlush();


	for (Index = 0; Index < DATA_LENGTH; Index++)
		Data[Index] = Index + 3;

	Xil_DCacheInvalidate();

	xil_printf("    invalidate all done\r\n");
	dsb();
	#ifdef __aarch64__
		CtrlReg = mfcp(SCTLR_EL3);
		CtrlReg &= ~(XREG_CONTROL_DCACHE_BIT);
		mtcp(SCTLR_EL3,CtrlReg);
	#else
		CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
		CtrlReg &= ~(XREG_CP15_CONTROL_C_BIT);
		mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
	#endif
	dsb();
	for (Index = 0; Index < DATA_LENGTH; Index++)
		Data[Index] = 0x50CFA0A;
	dsb();
	#ifdef __aarch64__
		CtrlReg = mfcp(SCTLR_EL3);
		CtrlReg |= (XREG_CONTROL_DCACHE_BIT);
		mtcp(SCTLR_EL3,CtrlReg);
	#else
		CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
		CtrlReg |= (XREG_CP15_CONTROL_C_BIT);
		mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
	#endif
	dsb();
	Status = 0;

	for (Index = 0; Index < DATA_LENGTH; Index++) {
		Value = Data[Index];
		if (Value != 0x50CFA0A) {
			Status = -1;
			xil_printf("Data[%d] = %x\r\n", Index, Value);
			break;
		}
	}

	if (!Status) {
		xil_printf("    Invalidate all worked\r\n");
	}
	else {
			xil_printf("Error: Invalidate dcache all not working\r\n");
	}

	xil_printf("-- DCache all Test Complete --\n\r");

	return Status;
}

/*****************************************************************************/
/**
* @brief   Perform Xil_ICacheInvalidateRange() on a few function pointers.
*
* @return
*     - 0 is returned for a pass
*
* @note		 The function will hang if it fails.
*****************************************************************************/
s32 Xil_TestICacheRange(void)
{

	Xil_ICacheInvalidateRange((INTPTR)Xil_TestICacheRange, 1024);
	Xil_ICacheInvalidateRange((INTPTR)Xil_TestDCacheRange, 1024);
	Xil_ICacheInvalidateRange((INTPTR)Xil_TestDCacheAll, 1024);

	xil_printf("-- Invalidate icache range done --\r\n");

	return 0;
}

/*****************************************************************************/
/**
* @brief     Perform Xil_ICacheInvalidate() on a few function pointers.
*
* @return
*           - 0 is returned for a pass
*
* @note		The function will hang if it fails.
*****************************************************************************/
s32 Xil_TestICacheAll(void)
{
	Xil_ICacheInvalidate();
	xil_printf("-- Invalidate icache all done --\r\n");
	return 0;
}
#endif
