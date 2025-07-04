/******************************************************************************
* Copyright (c) 2014 - 2022 Xilinx, Inc.  All rights reserved.
* Copyright (c) 2022 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xil_cache.c
*
* Contains required functions for the ARM cache functionality.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver    Who Date     Changes
* ----- ---- -------- -----------------------------------------------
* 5.0 	pkp  05/29/14 First release
* 5.5	pkp	 04/15/16 Updated the Xil_DCacheInvalidate,
*					  Xil_DCacheInvalidateLine and Xil_DCacheInvalidateRange
*					  functions description for proper explanation
* 6.2   pkp	 01/22/17 Added support for EL1 non-secure
* 6.2   asa  01/31/17 The existing Xil_DCacheDisable API first flushes the
*					  D caches and then disables it. The problem with that is,
*					  potentially there will be a small window after the cache
*					  flush operation and before the we disable D caches where
*					  we might have valid data in cache lines. In such a
*					  scenario disabling the D cache can lead to unknown behavior.
*					  The ideal solution to this is to use assembly code for
*					  the complete API and avoid any memory accesses. But with
*					  that we will end up having a huge amount on assembly code
*					  which is not maintainable. Changes are done to use a mix
*					  of assembly and C code. All local variables are put in
*					  registers. Also function calls are avoided in the API to
*					  avoid using stack memory.
*					  These changes fix CR#966220.
* 6.2  mus  02/13/17  The new api Xil_ConfigureL1Prefetch is added to disable pre-fetching/configure
*                     the maximum number of outstanding data prefetches allowed in
*                     L1 cache system.It fixes CR#967864.
* 6.6  mus  02/27/18  Updated Xil_DCacheInvalidateRange and
*					  Xil_ICacheInvalidateRange APIs to change the data type of
*					  "cacheline" variable as "INTPTR", This change has been done
*					  to avoid the truncation of upper DDR addresses to 32 bit.It
*					  fixes CR#995581.
* 6.6  mus  03/15/18  By default CPUACTLR_EL1 is accessible only from EL3, it
*					  results into abort if accessed from EL1 non secure privilege
*					  level. Updated Xil_ConfigureL1Prefetch function to access
*					  CPUACTLR_EL1 only for EL3.
* 6.8  mn   08/01/18  Optimize the Xil_DCacheInvalidateRange() function to remove
*                     redundant operations
* 6.8  asa  09/15/18  Fix bug in the Xil_DCacheInvalidateRange API introduced while
*                     making optimizations in the previous patch. This change fixes
*                     CR-1008926.
* 7.0 mus  10/12/18  Updated Xil_DCacheInvalidateLine and Xil_DCacheInvalidateRange
*                    APIs to replace IVAC instruction with CIVAC. So that, these
*                    APIs will always do flush + invalidate in case of Cortexa53 as
*                    well as Cortexa72 processor.
* 7.1 mus  09/17/19  Xil_DCacheFlushRange and Xil_DCacheInvalidateRange are executing 
*                    same functionality (clean + validate). Removed 
*                    Xil_DCacheFlushRange function implementation and defined it as
*                    macro. Xil_DCacheFlushRange macro points to the
*                    Xil_DCacheInvalidateRange API to avoid code duplication.
* 8.0 mus  02/24/22  Added support for CortexA78 processor in VERSAL NET SoC
* 8.1 mus  12/22/22  Removed workaround added to Xil_DCacheInvalidateRange for
*                    VERSAL NET.
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xil_cache.h"
#include "xil_io.h"
#include "xpseudo_asm.h"
#include "xparameters.h"
#include "xreg_cortexa53.h"
#include "xil_exception.h"
#include "bspconfig.h"

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/
#define IRQ_FIQ_MASK 0xC0U	/* Mask IRQ and FIQ interrupts in cpsr */

/****************************************************************************/
/**
* @brief	Enable the Data cache.
*
* @return	None.
*
****************************************************************************/
void Xil_DCacheEnable(void)
{
	u32 CtrlReg;

	if (EL3 == 1) {
		CtrlReg = mfcp(SCTLR_EL3);
	} else if (EL1_NONSECURE == 1) {
		CtrlReg = mfcp(SCTLR_EL1);
	} else {
		CtrlReg = 0U;
	}

	/* enable caches only if they are disabled */
	if((CtrlReg & XREG_CONTROL_DCACHE_BIT) == 0X00000000U){

		/* invalidate the Data cache */
		Xil_DCacheInvalidate();

		CtrlReg |= XREG_CONTROL_DCACHE_BIT;

		if (EL3 == 1) {
			/* enable the Data cache for el3*/
			mtcp(SCTLR_EL3,CtrlReg);
		} else if (EL1_NONSECURE == 1) {
			/* enable the Data cache for el1*/
			mtcp(SCTLR_EL1,CtrlReg);
		}
	}
}

/****************************************************************************/
/**
* @brief	Disable the Data cache.
*
* @return	None.
*
****************************************************************************/
void Xil_DCacheDisable(void)
{
	register u32 CsidReg;
	register u32 C7Reg;
	register u32 LineSize;
	register u32 NumWays;
	register u32 Way;
	register u32 WayIndex;
	register u32 WayAdjust;
	register u32 Set;
	register u32 SetIndex;
	register u32 NumSet;
	register u32 CacheLevel;

	dsb();
	asm(
	"mov 	x0, #0\n\t"
#if EL3==1
	"mrs	x0, sctlr_el3 \n\t"
	"and	w0, w0, #0xfffffffb\n\t"
	"msr	sctlr_el3, x0\n\t"
#elif EL1_NONSECURE==1
	"mrs	x0, sctlr_el1 \n\t"
	"and	w0, w0, #0xfffffffb\n\t"
	"msr	sctlr_el1, x0\n\t"
#endif
	"dsb sy\n\t"
	);

	/* Number of level of cache*/
	CacheLevel = 0U;
	/* Select cache level 0 and D cache in CSSR */
	mtcp(CSSELR_EL1,CacheLevel);
	isb();

	CsidReg = mfcp(CCSIDR_EL1);

	/* Get the cacheline size, way size, index size from csidr */
	LineSize = (CsidReg & 0x00000007U) + 0x00000004U;

	/* Number of Ways */
	NumWays = (CsidReg & 0x00001FFFU) >> 3U;
	NumWays += 0x00000001U;

	/*Number of Set*/
	NumSet = (CsidReg >> 13U) & 0x00007FFFU;
	NumSet += 0x00000001U;

	WayAdjust = clz(NumWays) - (u32)0x0000001FU;

	Way = 0U;
	Set = 0U;

	/* Flush all the cachelines */
	for (WayIndex = 0U; WayIndex < NumWays; WayIndex++) {
		for (SetIndex = 0U; SetIndex < NumSet; SetIndex++) {
			C7Reg = Way | Set | CacheLevel;
			mtcpdc(CISW,C7Reg);
			Set += (0x00000001U << LineSize);
		}
		Set = 0U;
		Way += (0x00000001U << WayAdjust);
	}

	/* Wait for Flush to complete */
	dsb();

	/* Select cache level 1 and D cache in CSSR */
	CacheLevel += (0x00000001U << 1U);
	mtcp(CSSELR_EL1,CacheLevel);
	isb();

	CsidReg = mfcp(CCSIDR_EL1);

	/* Get the cacheline size, way size, index size from csidr */
	LineSize = (CsidReg & 0x00000007U) + 0x00000004U;

	/* Number of Ways */
	NumWays = (CsidReg & 0x00001FFFU) >> 3U;
	NumWays += 0x00000001U;

	/* Number of Sets */
	NumSet = (CsidReg >> 13U) & 0x00007FFFU;
	NumSet += 0x00000001U;

	WayAdjust=clz(NumWays) - (u32)0x0000001FU;

	Way = 0U;
	Set = 0U;

	/* Flush all the cachelines */
	for (WayIndex =0U; WayIndex < NumWays; WayIndex++) {
		for (SetIndex =0U; SetIndex < NumSet; SetIndex++) {
			C7Reg = Way | Set | CacheLevel;
			mtcpdc(CISW,C7Reg);
			Set += (0x00000001U << LineSize);
		}
		Set=0U;
		Way += (0x00000001U<<WayAdjust);
	}
	/* Wait for Flush to complete */
	dsb();

#if defined (VERSAL_NET)
	/* Select cache level 2 and D cache in CSSR */
	CacheLevel += (0x00000001U << 1U);
	mtcp(CSSELR_EL1,CacheLevel);
	isb();

	CsidReg = mfcp(CCSIDR_EL1);

	/* Get the cacheline size, way size, index size from csidr */
	LineSize = (CsidReg & 0x00000007U) + 0x00000004U;

	/* Number of Ways */
	NumWays = (CsidReg & 0x00001FFFU) >> 3U;
	NumWays += 0x00000001U;

	/* Number of Sets */
	NumSet = (CsidReg >> 13U) & 0x00007FFFU;
	NumSet += 0x00000001U;

	WayAdjust=clz(NumWays) - (u32)0x0000001FU;
	Way = 0U;
	Set = 0U;

	/* Flush all the cachelines */
	for (WayIndex =0U; WayIndex < NumWays; WayIndex++) {
		for (SetIndex =0U; SetIndex < NumSet; SetIndex++) {
			C7Reg = Way | Set | CacheLevel;
			mtcpdc(CISW,C7Reg);
			Set += (0x00000001U << LineSize);
		}
		Set=0U;
		Way += (0x00000001U<<WayAdjust);
	}
	/* Wait for Flush to complete */
	dsb();
#endif
	asm(
#if EL3==1
		"tlbi 	ALLE3\n\t"
#elif EL1_NONSECURE==1
		"tlbi 	VMALLE1\n\t"
#endif
		"dsb sy\r\n"
		"isb\n\t"
	);
}

/****************************************************************************/
/**
* @brief	Invalidate the Data cache. The contents present in the cache are
* 			cleaned and invalidated.
*
* @return	None.
*
* @note		In Cortex-A53, functionality to simply invalid the cachelines
*  			is not present. Such operations are a problem for an environment
* 			that supports virtualisation. It would allow one OS to invalidate
* 			a line belonging to another OS. This could lead to the other OS
* 			crashing because of the loss of essential data. Hence, such
* 			operations are promoted to clean and invalidate which avoids such
*			corruption.
*
****************************************************************************/
void Xil_DCacheInvalidate(void)
{
	register u32 CsidReg, C7Reg;
	u32 LineSize, NumWays;
	u32 Way, WayIndex,WayAdjust, Set, SetIndex, NumSet, CacheLevel;
	u32 currmask;

	currmask = mfcpsr();
	mtcpsr(currmask | IRQ_FIQ_MASK);


	/* Number of level of cache*/

	CacheLevel=0U;
	/* Select cache level 0 and D cache in CSSR */
	mtcp(CSSELR_EL1,CacheLevel);
	isb();

	CsidReg = mfcp(CCSIDR_EL1);

	/* Get the cacheline size, way size, index size from csidr */
	LineSize = (CsidReg & 0x00000007U) + 0x00000004U;

	/* Number of Ways */
	NumWays = (CsidReg & 0x00001FFFU) >> 3U;
	NumWays += 0X00000001U;

	/*Number of Set*/
	NumSet = (CsidReg >> 13U) & 0x00007FFFU;
	NumSet += 0X00000001U;

	WayAdjust = clz(NumWays) - (u32)0x0000001FU;

	Way = 0U;
	Set = 0U;

	/* Invalidate all the cachelines */
	for (WayIndex =0U; WayIndex < NumWays; WayIndex++) {
		for (SetIndex =0U; SetIndex < NumSet; SetIndex++) {
			C7Reg = Way | Set | CacheLevel;
			mtcpdc(ISW,C7Reg);
			Set += (0x00000001U << LineSize);
		}
		Set = 0U;
		Way += (0x00000001U << WayAdjust);
	}

	/* Wait for invalidate to complete */
	dsb();

	/* Select cache level 1 and D cache in CSSR */
	CacheLevel += (0x00000001U<<1U) ;
	mtcp(CSSELR_EL1,CacheLevel);
	isb();

	CsidReg = mfcp(CCSIDR_EL1);

	/* Get the cacheline size, way size, index size from csidr */
		LineSize = (CsidReg & 0x00000007U) + 0x00000004U;

	/* Number of Ways */
	NumWays = (CsidReg & 0x00001FFFU) >> 3U;
	NumWays += 0x00000001U;

	/* Number of Sets */
	NumSet = (CsidReg >> 13U) & 0x00007FFFU;
	NumSet += 0x00000001U;

	WayAdjust = clz(NumWays) - (u32)0x0000001FU;

	Way = 0U;
	Set = 0U;

	/* Invalidate all the cachelines */
	for (WayIndex = 0U; WayIndex < NumWays; WayIndex++) {
		for (SetIndex = 0U; SetIndex < NumSet; SetIndex++) {
			C7Reg = Way | Set | CacheLevel;
			mtcpdc(ISW,C7Reg);
			Set += (0x00000001U << LineSize);
		}
		Set = 0U;
		Way += (0x00000001U << WayAdjust);
	}
	/* Wait for invalidate to complete */
	dsb();

#if defined (VERSAL_NET)
	/* Select cache level 2 and D cache in CSSR */
	CacheLevel += (0x00000001U<<1U) ;
	mtcp(CSSELR_EL1,CacheLevel);
	isb();

	CsidReg = mfcp(CCSIDR_EL1);

	/* Get the cacheline size, way size, index size from csidr */
		LineSize = (CsidReg & 0x00000007U) + 0x00000004U;

	/* Number of Ways */
	NumWays = (CsidReg & 0x00001FFFU) >> 3U;
	NumWays += 0x00000001U;

	/* Number of Sets */
	NumSet = (CsidReg >> 13U) & 0x00007FFFU;
	NumSet += 0x00000001U;

	WayAdjust = clz(NumWays) - (u32)0x0000001FU;

	Way = 0U;
	Set = 0U;

	/* Invalidate all the cachelines */
	for (WayIndex = 0U; WayIndex < NumWays; WayIndex++) {
		for (SetIndex = 0U; SetIndex < NumSet; SetIndex++) {
			C7Reg = Way | Set | CacheLevel;
			mtcpdc(ISW,C7Reg);
			Set += (0x00000001U << LineSize);
		}
		Set = 0U;
		Way += (0x00000001U << WayAdjust);
	}
	/* Wait for invalidate to complete */
	dsb();
#endif

	mtcpsr(currmask);
}

/****************************************************************************/
/**
* @brief	Invalidate a Data cache line. The cacheline is cleaned and
*			invalidated.
*
* @param	adr: 64bit address of the data to be flushed.
*
* @return	None.
*
* @note		In Cortex-A53, functionality to simply invalid the cachelines
*  			is not present. Such operations are a problem for an environment
* 			that supports virtualisation. It would allow one OS to invalidate
* 			a line belonging to another OS. This could lead to the other OS
* 			crashing because of the loss of essential data. Hence, such
* 			operations are promoted to clean and invalidate which avoids such
*			corruption.
*
****************************************************************************/
void Xil_DCacheInvalidateLine(INTPTR adr)
{

	u32 currmask;
	currmask = mfcpsr();
	mtcpsr(currmask | IRQ_FIQ_MASK);

	/* Select cache level 0 and D cache in CSSR */
	mtcp(CSSELR_EL1,0x0);
	mtcpdc(CIVAC,(adr & (~0x3F)));
	/* Wait for invalidate to complete */
	dsb();
	/* Select cache level 1 and D cache in CSSR */
	mtcp(CSSELR_EL1,0x2);
	mtcpdc(IVAC,(adr & (~0x3F)));
	/* Wait for invalidate to complete */
	dsb();
	mtcpsr(currmask);
}

/****************************************************************************/
/**
* @brief	Invalidate the Data cache for the given address range.
* 			The cachelines present in the adderss range are cleaned and
*			invalidated
*
* @param	adr: 64bit start address of the range to be invalidated.
* @param	len: Length of the range to be invalidated in bytes.
*
* @return	None.
*
* @note		In Cortex-A53, functionality to simply invalid the cachelines
*  			is not present. Such operations are a problem for an environment
* 			that supports virtualisation. It would allow one OS to invalidate
* 			a line belonging to another OS. This could lead to the other OS
* 			crashing because of the loss of essential data. Hence, such
* 			operations are promoted to clean and invalidate which avoids such
*			corruption.
*
****************************************************************************/
void Xil_DCacheInvalidateRange(INTPTR  adr, INTPTR len)
{
	const INTPTR cacheline = 64U;
	INTPTR end = adr + len;
	adr = adr & (~0x3F);
	u32 currmask = mfcpsr();
	mtcpsr(currmask | IRQ_FIQ_MASK);
	if (len != 0U) {
		while (adr < end) {
			mtcpdc(CIVAC,adr);
			adr += cacheline;
		}
	}
	/* Wait for invalidate to complete */
	dsb();
	mtcpsr(currmask);
}

/****************************************************************************/
/**
* @brief	Flush the Data cache.
*
* @return	None.
*
****************************************************************************/
void Xil_DCacheFlush(void)
{
	register u32 CsidReg, C7Reg;
	u32 LineSize, NumWays;
	u32 Way, WayIndex,WayAdjust, Set, SetIndex, NumSet, CacheLevel;
	u32 currmask;

	currmask = mfcpsr();
	mtcpsr(currmask | IRQ_FIQ_MASK);


	/* Number of level of cache*/

	CacheLevel = 0U;
	/* Select cache level 0 and D cache in CSSR */
	mtcp(CSSELR_EL1,CacheLevel);
	isb();

	CsidReg = mfcp(CCSIDR_EL1);

	/* Get the cacheline size, way size, index size from csidr */
	LineSize = (CsidReg & 0x00000007U) + 0x00000004U;

	/* Number of Ways */
	NumWays = (CsidReg & 0x00001FFFU) >> 3U;
	NumWays += 0x00000001U;

	/*Number of Set*/
	NumSet = (CsidReg >> 13U) & 0x00007FFFU;
	NumSet += 0x00000001U;

	WayAdjust = clz(NumWays) - (u32)0x0000001FU;

	Way = 0U;
	Set = 0U;

	/* Flush all the cachelines */
	for (WayIndex = 0U; WayIndex < NumWays; WayIndex++) {
		for (SetIndex = 0U; SetIndex < NumSet; SetIndex++) {
			C7Reg = Way | Set | CacheLevel;
			mtcpdc(CISW,C7Reg);
			Set += (0x00000001U << LineSize);
		}
		Set = 0U;
		Way += (0x00000001U << WayAdjust);
	}

	/* Wait for Flush to complete */
	dsb();

	/* Select cache level 1 and D cache in CSSR */
	CacheLevel += (0x00000001U << 1U);
	mtcp(CSSELR_EL1,CacheLevel);
	isb();

	CsidReg = mfcp(CCSIDR_EL1);

	/* Get the cacheline size, way size, index size from csidr */
		LineSize = (CsidReg & 0x00000007U) + 0x00000004U;

	/* Number of Ways */
	NumWays = (CsidReg & 0x00001FFFU) >> 3U;
	NumWays += 0x00000001U;

	/* Number of Sets */
	NumSet = (CsidReg >> 13U) & 0x00007FFFU;
	NumSet += 0x00000001U;

	WayAdjust=clz(NumWays) - (u32)0x0000001FU;

	Way = 0U;
	Set = 0U;

	/* Flush all the cachelines */
	for (WayIndex =0U; WayIndex < NumWays; WayIndex++) {
		for (SetIndex =0U; SetIndex < NumSet; SetIndex++) {
			C7Reg = Way | Set | CacheLevel;
			mtcpdc(CISW,C7Reg);
			Set += (0x00000001U << LineSize);
		}
		Set=0U;
		Way += (0x00000001U<<WayAdjust);
	}
	/* Wait for Flush to complete */
	dsb();

#if defined(VERSAL_NET)
	/* Select cache level 1 and D cache in CSSR */
	CacheLevel += (0x00000001U << 1U);
	mtcp(CSSELR_EL1,CacheLevel);
	isb();

	CsidReg = mfcp(CCSIDR_EL1);

	/* Get the cacheline size, way size, index size from csidr */
		LineSize = (CsidReg & 0x00000007U) + 0x00000004U;

	/* Number of Ways */
	NumWays = (CsidReg & 0x00001FFFU) >> 3U;
	NumWays += 0x00000001U;

	/* Number of Sets */
	NumSet = (CsidReg >> 13U) & 0x00007FFFU;
	NumSet += 0x00000001U;

	WayAdjust=clz(NumWays) - (u32)0x0000001FU;

	Way = 0U;
	Set = 0U;

	/* Flush all the cachelines */
	for (WayIndex =0U; WayIndex < NumWays; WayIndex++) {
		for (SetIndex =0U; SetIndex < NumSet; SetIndex++) {
			C7Reg = Way | Set | CacheLevel;
			mtcpdc(CISW,C7Reg);
			Set += (0x00000001U << LineSize);
		}
		Set=0U;
		Way += (0x00000001U<<WayAdjust);
	}
	/* Wait for Flush to complete */
	dsb();
#endif

	mtcpsr(currmask);
}

/****************************************************************************/
/**
* @brief	Flush a Data cache line. If the byte specified by the address (adr)
* 			is cached by the Data cache, the cacheline containing that byte is
*			invalidated. If the cacheline is modified (dirty), the entire
*			contents of the cacheline are written to system memory before the
* 			line is invalidated.
*
* @param	adr: 64bit address of the data to be flushed.
*
* @return	None.
*
* @note		The bottom 6 bits are set to 0, forced by architecture.
*
****************************************************************************/
void Xil_DCacheFlushLine(INTPTR  adr)
{
	u32 currmask;
	currmask = mfcpsr();
	mtcpsr(currmask | IRQ_FIQ_MASK);
	/* Select cache level 0 and D cache in CSSR */
	mtcp(CSSELR_EL1,0x0);
	mtcpdc(CIVAC,(adr & (~0x3F)));
	/* Wait for flush to complete */
	dsb();
	/* Select cache level 1 and D cache in CSSR */
	mtcp(CSSELR_EL1,0x2);
	mtcpdc(CIVAC,(adr & (~0x3F)));
	/* Wait for flush to complete */
	dsb();
	mtcpsr(currmask);
}

/****************************************************************************/
/**
* @brief	Enable the instruction cache.
*
* @return	None.
*
****************************************************************************/
void Xil_ICacheEnable(void)
{
	u32 CtrlReg;

	if (EL3 == 1) {
		CtrlReg = mfcp(SCTLR_EL3);
	} else if (EL1_NONSECURE == 1) {
		CtrlReg = mfcp(SCTLR_EL1);
	} else {
		CtrlReg = 0U;
	}

	/* enable caches only if they are disabled */
	if((CtrlReg & XREG_CONTROL_ICACHE_BIT)==0x00000000U){
		/* invalidate the instruction cache */
		Xil_ICacheInvalidate();

		CtrlReg |= XREG_CONTROL_ICACHE_BIT;

		if (EL3 == 1) {
			/* enable the instruction cache for el3*/
			mtcp(SCTLR_EL3,CtrlReg);
		} else if (EL1_NONSECURE == 1) {
			/* enable the instruction cache for el1*/
			mtcp(SCTLR_EL1,CtrlReg);
		}
	}
}

/****************************************************************************/
/**
* @brief	Disable the instruction cache.
*
* @return	None.
*
****************************************************************************/
void Xil_ICacheDisable(void)
{
	u32 CtrlReg;

	if (EL3 == 1) {
		CtrlReg = mfcp(SCTLR_EL3);
	} else if (EL1_NONSECURE == 1) {
		CtrlReg = mfcp(SCTLR_EL1);
	} else {
		CtrlReg = 0U;
	}
	/* invalidate the instruction cache */
	Xil_ICacheInvalidate();
	CtrlReg &= ~(XREG_CONTROL_ICACHE_BIT);

	if (EL3 == 1) {
		/* disable the instruction cache */
		mtcp(SCTLR_EL3,CtrlReg);
	} else if (EL1_NONSECURE == 1) {
		/* disable the instruction cache */
		mtcp(SCTLR_EL1,CtrlReg);
	}


}

/****************************************************************************/
/**
* @brief	Invalidate the entire instruction cache.
*
* @return	None.
*
****************************************************************************/
void Xil_ICacheInvalidate(void)
{
	unsigned int currmask;
	currmask = mfcpsr();
	mtcpsr(currmask | IRQ_FIQ_MASK);
	mtcp(CSSELR_EL1,0x1);
	dsb();
	/* invalidate the instruction cache */
	mtcpicall(IALLU);
	/* Wait for invalidate to complete */
	dsb();
	mtcpsr(currmask);
}

/****************************************************************************/
/**
* @brief	Invalidate an instruction cache line. If the instruction specified
*			by the parameter adr is cached by the instruction cache, the
*			cacheline containing that instruction is invalidated.
*
* @param	adr: 64bit address of the instruction to be invalidated.
*
* @return	None.
*
* @note		The bottom 6 bits are set to 0, forced by architecture.
*
****************************************************************************/
void Xil_ICacheInvalidateLine(INTPTR  adr)
{
	u32 currmask;
	currmask = mfcpsr();
	mtcpsr(currmask | IRQ_FIQ_MASK);

	mtcp(CSSELR_EL1,0x1);
	/*Invalidate I Cache line*/
	mtcpic(IVAU,adr & (~0x3F));
	/* Wait for invalidate to complete */
	dsb();
	mtcpsr(currmask);
}

/****************************************************************************/
/**
* @brief	Invalidate the instruction cache for the given address range.
* 			If the instructions specified by the address range are cached by
* 			the instrunction cache, the cachelines containing those
*			instructions are invalidated.
*
* @param	adr: 64bit start address of the range to be invalidated.
* @param	len: Length of the range to be invalidated in bytes.
*
* @return	None.
*
****************************************************************************/
void Xil_ICacheInvalidateRange(INTPTR  adr, INTPTR len)
{
	const INTPTR cacheline = 64U;
	INTPTR end;
	INTPTR tempadr = adr;
	INTPTR tempend;
	u32 currmask;
	currmask = mfcpsr();
	mtcpsr(currmask | IRQ_FIQ_MASK);

	if (len != 0x00000000U) {
		end = tempadr + len;
		tempend = end;
		tempadr &= ~(cacheline - 0x00000001U);

		/* Select cache Level 0 I-cache in CSSR */
		mtcp(CSSELR_EL1,0x1);
		while (tempadr < tempend) {
			/*Invalidate I Cache line*/
			mtcpic(IVAU,adr & (~0x3F));

			tempadr += cacheline;
		}
	}
/* Wait for invalidate to complete */
	dsb();
	mtcpsr(currmask);
}

/****************************************************************************/
/**
* @brief	Configure the maximum number of outstanding data prefetches
*               allowed in L1 cache.
*
* @param	num: maximum number of outstanding data prefetches allowed,
*                    valid values are 0-7.
*
* @return	None.
*
* @note		This function is implemented only for EL3 privilege level.
*
*****************************************************************************/
void Xil_ConfigureL1Prefetch (u8 num) {
#if EL3
       u64 val=0;

       val= mfcp(S3_1_C15_C2_0 );
       val &= ~(L1_DATA_PREFETCH_CONTROL_MASK);
       val |=  (num << L1_DATA_PREFETCH_CONTROL_SHIFT);
       mtcp(S3_1_C15_C2_0,val);
#endif
}
