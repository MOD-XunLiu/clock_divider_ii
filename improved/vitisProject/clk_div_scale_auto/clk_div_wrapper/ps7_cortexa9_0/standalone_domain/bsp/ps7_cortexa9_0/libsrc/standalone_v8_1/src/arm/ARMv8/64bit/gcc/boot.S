/******************************************************************************
* Copyright (c) 2014 - 2022 Xilinx, Inc.  All rights reserved.
* Copyright (c) 2022 - 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*****************************************************************************/
/**
* @file boot.S
*
* @addtogroup a53_64_boot_code Cortex A53 64bit Processor Boot Code
* @{
* <h2> boot.S </h2>
*
* The boot code performs minimum configuration which is required for an
* application. Cortex-A53 starts by checking current exception level. If the
* current exception level is EL3 and BSP is built for EL3, it will do
* initialization required for application execution at EL3. Below is a
* sequence illustrating what all configuration is performed before control
* reaches to main function for EL3 execution.
*
* 1. Program vector table base for exception handling
* 2. Set reset vector table base address
* 3. Program stack pointer for EL3
* 4. Routing of interrupts to EL3
* 5. Enable ECC protection
* 6. Program generic counter frequency
* 7. Invalidate instruction cache, data cache and TLBs
* 8. Configure MMU registers and program base address of translation table
* 9. Transfer control to _start which clears BSS sections and runs global
*    constructor before jumping to main application
*
* If the current exception level is EL1 and BSP is also built for EL1_NONSECURE
* it will perform initialization required for application execution at EL1
* non-secure. For all other combination, the execution will go into infinite
* loop. Below is a sequence illustrating what all configuration is performed
* before control reaches to main function for EL1 execution.
*
* 1. Program vector table base for exception handling
* 2. Program stack pointer for EL1
* 3. Invalidate instruction cache, data cache and TLBs
* 4. Configure MMU registers and program base address of translation table
* 5. Transfer control to _start which clears BSS sections and runs global
*    constructor before jumping to main application
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who     Date     Changes
* ----- ------- -------- ---------------------------------------------------
* 5.00  pkp	05/21/14 Initial version
* 6.00	pkp     07/25/16 Program the counter frequency
* 6.02  pkp	01/22/17 Added support for EL1 non-secure
* 6.02	pkp	01/24/17 Clearing status of FPUStatus variable to ensure it
*			 holds correct value.
* 6.3   mus 04/20/17 CPU Cache protection bit in the L2CTLR_EL1 will be in
*                    set state on reset. So, setting that bit through boot
*                    code is redundant, hence removed the code which sets
*                    CPU cache protection bit.
* 6.4   mus      08/11/17 Implemented ARM erratum 855873.It fixes
*                         CR#982209.
* 6.6   mus      01/19/18 Added isb after writing to the cpacr_el1/cptr_el3,
*                         to ensure floating-point unit is disabled, before
*                         any subsequent instruction.
* 7.0   mus      03/26/18 Updated TCR_EL3/TCR_EL1 as per versal address map
* 7.3   mus      04/24/20 Corrected CPACR_EL1 handling at EL1 NS
* 8.0   mus      07/06/21 Added support for CortexA78 processor in VERSAL NET SoC
* 8.0   mus      10/05/21 Default translation table for VERSAL NET has been configured
*                         for 256 TB address space, due to this page tables size
*                         exceeds OCM size, hence executable size is too large
*                         to fit into OCM. This patch adds option  to reduce
*                         page table size, when OCM_ELF flag is defined in
*                         compiler flags, translation table would be configured
*                         for 1 TB address space. It would help to reduce
*                         executable size.
* 8.1   mus      11/08/22 Used ENABLE_MINIMAL_XLAT_TBL for reducing translation
*                         table size. OCM_ELF flag would be removed later.
* 8.1   mus      12/22/22 Updated TCR_EL3 to configure CortexA78 MMU for 4 TB
*                         address space.
* 8.1   mus      12/22/22 Updated TCR_EL3 to configure translation table walks
*                         as cacheable.
* 8.1   mus      02/06/23 Few registers in CMN space needs to be set up for OCM
*                         cacheability. Existing firmware is not doing that. Hence
*                         OCM cacheability is broken for VERSAL NET SoC.
*                         As user can keep translation tables in OCM, translation
*                         tables needs to be configured as non cacheable, till
*                         cacheability settings are supported from firmware end.
*                         It fixes CR#1150456.
*
* </pre>
*
******************************************************************************/

#include "xparameters.h"
#include "bspconfig.h"
#include "xil_errata.h"

.globl MMUTableL0
.globl MMUTableL1
.globl MMUTableL2
.global _prestart
.global _boot

.global __el3_stack
.global __el2_stack
.global __el1_stack
.global __el0_stack
.global _vector_table

.set EL3_stack,		__el3_stack
.set EL2_stack,		__el2_stack
.set EL1_stack,		__el1_stack
.set EL0_stack,		__el0_stack

.set TT_S1_FAULT,	0x0
.set TT_S1_TABLE,	0x3

.set L0Table,	MMUTableL0
.set L1Table,	MMUTableL1
.set L2Table,	MMUTableL2
.set vector_base,	_vector_table
.set rvbar_base,	0xFD5C0040

#if defined (VERSAL_NET)
.set counterfreq,       XPAR_CPU_CORTEXA78_0_TIMESTAMP_CLK_FREQ
#elif defined (versal)
.set counterfreq,       XPAR_CPU_CORTEXA72_0_TIMESTAMP_CLK_FREQ
#else
.set counterfreq,	XPAR_CPU_CORTEXA53_0_TIMESTAMP_CLK_FREQ
#endif

.set MODE_EL1, 0x5
.set DAIF_BIT,	0x1C0

.section .boot,"ax"


/* this initializes the various processor modes */

_prestart:
_boot:
	mov      x0, #0
	mov      x1, #0
	mov      x2, #0
	mov      x3, #0
	mov      x4, #0
	mov      x5, #0
	mov      x6, #0
	mov      x7, #0
	mov      x8, #0
	mov      x9, #0
	mov      x10, #0
	mov      x11, #0
	mov      x12, #0
	mov      x13, #0
	mov      x14, #0
	mov      x15, #0
	mov      x16, #0
	mov      x17, #0
	mov      x18, #0
	mov      x19, #0
	mov      x20, #0
	mov      x21, #0
	mov      x22, #0
	mov      x23, #0
	mov      x24, #0
	mov      x25, #0
	mov      x26, #0
	mov      x27, #0
	mov      x28, #0
	mov      x29, #0
	mov      x30, #0
#if 0 //don't put other a53 cpus in wfi
   //Which core am I
   // ----------------
	mrs      x0, MPIDR_EL1
	and      x0, x0, #0xFF                        //Mask off to leave Aff0
	cbz      x0, OKToRun                          //If core 0, run the primary init code
EndlessLoop0:
	wfi
	b        EndlessLoop0
#endif
OKToRun:

	mrs	x0, currentEL
	cmp	x0, #0xC
	beq	InitEL3

	cmp	x0, #0x4
	beq	InitEL1

	b 	error			// go to error if current exception level is neither EL3 nor EL1
InitEL3:
.if (EL3 == 1)
	/*Set vector table base address*/
	ldr	x1, =vector_base
	msr	VBAR_EL3,x1

	/* Set reset vector address */
	/* Get the cpu ID */
	mrs  x0, MPIDR_EL1
	and  x0, x0, #0xFF
	mov  w0, w0
#ifndef VERSAL_NET
	ldr	 w2, =rvbar_base
	/* calculate the rvbar base address for particular CPU core */
	mov	 w3, #0x8
	mul	 w0, w0, w3
	add	 w2, w2, w0
	/* store vector base address to RVBAR */
	str  x1, [x2]
#endif
	/*Define stack pointer for current exception level*/
	ldr	 x2,=EL3_stack
	mov	 sp,x2

	/* Enable Trapping of SIMD/FPU register for standalone BSP */
	mov      x0, #0
#ifndef FREERTOS_BSP
	orr      x0, x0, #(0x1 << 10)
#endif
	msr      CPTR_EL3, x0
	isb

	/*
	 * Clear FPUStatus variable to make sure that it contains current
	 * status of FPU i.e. disabled. In case of a warm restart execution
	 * when bss sections are not cleared, it may contain previously updated
	 * value which does not hold true now.
	 */
#ifndef FREERTOS_BSP
	 ldr x0,=FPUStatus
	 str xzr, [x0]
#endif
	/* Configure SCR_EL3 */
	mov      w1, #0              	//; Initial value of register is unknown
	orr      w1, w1, #(1 << 11)  	//; Set ST bit (Secure EL1 can access CNTPS_TVAL_EL1, CNTPS_CTL_EL1 & CNTPS_CVAL_EL1)
	orr      w1, w1, #(1 << 10)  	//; Set RW bit (EL1 is AArch64, as this is the Secure world)
	orr      w1, w1, #(1 << 3)   	//; Set EA bit (SError routed to EL3)
	orr      w1, w1, #(1 << 2)   	//; Set FIQ bit (FIQs routed to EL3)
	orr      w1, w1, #(1 << 1)   	//; Set IRQ bit (IRQs routed to EL3)
	msr      SCR_EL3, x1

/* As per A78 TRM, CPUACTLR_EL1 is reserved for ARM internal use */
#if !defined (VERSAL_NET)
	/*configure cpu auxiliary control register EL1 */
	ldr	x0,=0x80CA000 		// L1 Data prefetch control - 5, Enable device split throttle, 2 independent data prefetch streams
#if CONFIG_ARM_ERRATA_855873
        /*
	 *  Set ENDCCASCI bit in CPUACTLR_EL1 register, to execute data
	 *  cache clean operations as data cache clean and invalidate
	 *
	 */
        orr     x0, x0, #(1 << 44)      //; Set ENDCCASCI bit
#endif
	msr	S3_1_C15_C2_0, x0 	//CPUACTLR_EL1
#endif

	/* program the counter frequency */
	ldr	x0,=counterfreq
	msr	CNTFRQ_EL0, x0

/* There is no SMPEN bit in A78, TODO: Check for equivalent bit */
#if !defined (VERSAL_NET)
	/*Enable hardware coherency between cores*/
	mrs      x0, S3_1_c15_c2_1  	//Read EL1 CPU Extended Control Register
	orr      x0, x0, #(1 << 6)  	//Set the SMPEN bit
	msr      S3_1_c15_c2_1, x0  	//Write EL1 CPU Extended Control Register
	isb
#endif

	tlbi 	ALLE3
	ic      IALLU                  	//; Invalidate I cache to PoU
	bl 	invalidate_dcaches
	dsb	 sy
	isb

	ldr      x1, =L0Table 		//; Get address of level 0 for TTBR0_EL3
	msr      TTBR0_EL3, x1		//; Set TTBR0_EL3

	/**********************************************
	* Set up memory attributes
	* This equates to:
	* 0 = b01000100 = Normal, Inner/Outer Non-Cacheable
	* 1 = b11111111 = Normal, Inner/Outer WB/WA/RA
	* 2 = b00000000 = Device-nGnRnE
	* 3 = b00000100 = Device-nGnRE
	* 4 = b10111011 = Normal, Inner/Outer WT/WA/RA
	**********************************************/
	ldr      x1, =0x000000BB0400FF44
	msr      MAIR_EL3, x1

#if defined (VERSAL_NET) && (defined (OCM_ELF) || defined (ENABLE_MINIMAL_XLAT_TBL))
        /**********************************************
         * Set up TCR_EL3
         * Physical Address Size PS =  011 -> 42 bits 4TB
         * Granual Size TG0 = 00 -> 4KB
         * Attributes for page table walks = 00 -> non cacheable
         * size offset of the memory region T0SZ = 22 -> (region size 2^(64-22) = 2^42)
         ***************************************************/
        ldr     x1,=0x80833016

#elif defined (VERSAL_NET)
        /**********************************************
         * Set up TCR_EL3
         * Physical Address Size PS =  101 -> 48bits 256 TB
         * Granual Size TG0 = 00 -> 4KB
         * Attributes for page table walks = 00 -> non cacheable
         * size offset of the memory region T0SZ = 16 -> (region size 2^(64-16) = 2^48)
         ***************************************************/
        /* ldr     x1,=0x80853510 */
        ldr     x1,=0x80853010
#elif defined (versal)
	/**********************************************
	 * Set up TCR_EL3
	 * Physical Address Size PS =  100 -> 44bits 16 TB
	 * Granual Size TG0 = 00 -> 4KB
	 * size offset of the memory region T0SZ = 20 -> (region size 2^(64-20) = 2^44)
	 ***************************************************/
	ldr     x1,=0x80843514
#else
	/**********************************************
	 * Set up TCR_EL3
	 * Physical Address Size PS =  010 -> 40bits 1TB
	 * Granual Size TG0 = 00 -> 4KB
	 * size offset of the memory region T0SZ = 24 -> (region size 2^(64-24) = 2^40)
	 ***************************************************/
	ldr     x1,=0x80823518
#endif
	msr     TCR_EL3, x1
	isb

	/* Enable SError Exception for asynchronous abort */
	mrs 	x1,DAIF
	bic	x1,x1,#(0x1<<8)
        msr	DAIF,x1

	/* Configure SCTLR_EL3 */
	mov      x1, #0                //Most of the SCTLR_EL3 bits are unknown at reset
	orr      x1, x1, #(1 << 12)	//Enable I cache
	orr      x1, x1, #(1 << 3)	//Enable SP alignment check
	orr      x1, x1, #(1 << 2)	//Enable caches
	orr      x1, x1, #(1 << 0)	//Enable MMU
	msr      SCTLR_EL3, x1
	dsb	 sy
	isb

	b 	 _startup		//jump to start
.else
	b 	error			// present exception level and selected exception level mismatch
.endif

InitEL1:
.if (EL1_NONSECURE == 1)
	/*Set vector table base address*/
	ldr	x1, =vector_base
	msr	VBAR_EL1,x1

	/* Trap floating point access only in case of standalone BSP */
#ifdef FREERTOS_BSP
        mrs     x0, CPACR_EL1
        orr     x0, x0, #(0x3 << 20)
        msr     CPACR_EL1, x0
#else
	mrs	x0, CPACR_EL1
	bic	x0, x0, #(0x3 << 20)
	msr	CPACR_EL1, x0
#endif
	isb

	/*
	 * Clear FPUStatus variable to make sure that it contains current
	 * status of FPU i.e. disabled. In case of a warm restart execution
	 * when bss sections are not cleared, it may contain previously updated
	 * value which does not hold true now.
	 */
#ifndef FREERTOS_BSP
	 ldr x0,=FPUStatus
	 str xzr, [x0]
#endif
	/*Define stack pointer for current exception level*/
	ldr	 x2,=EL1_stack
	mov	 sp,x2

	/* Disable MMU first */
	mov	x1,#0x0
	msr     SCTLR_EL1, x1
	isb

	TLBI    VMALLE1

	ic      IALLU                  	//; Invalidate I cache to PoU
	bl 	invalidate_dcaches
	dsb	 sy
	isb

	ldr      x1, =L0Table 		//; Get address of level 0 for TTBR0_EL1
	msr      TTBR0_EL1, x1		//; Set TTBR0_EL1

	/**********************************************
	* Set up memory attributes
	* This equates to:
	* 0 = b01000100 = Normal, Inner/Outer Non-Cacheable
	* 1 = b11111111 = Normal, Inner/Outer WB/WA/RA
	* 2 = b00000000 = Device-nGnRnE
	* 3 = b00000100 = Device-nGnRE
	* 4 = b10111011 = Normal, Inner/Outer WT/WA/RA
	**********************************************/
	ldr      x1, =0x000000BB0400FF44
	msr      MAIR_EL1, x1

        #if defined (versal)
        /**********************************************
        * Set up TCR_EL1
	* Physical Address Size PS =  100 -> 44bits 16TB
	* Granual Size TG0 = 00 -> 4KB
        * size offset of the memory region T0SZ = 20 -> (region size 2^(64-20) = 2^44)
        ***************************************************/
        ldr     x1,=0x485800514
        #else
        /**********************************************
        * Set up TCR_EL1
        * Physical Address Size PS =  010 -> 44bits 16TB
        * Granual Size TG0 = 00 -> 4KB
        * size offset of the memory region T0SZ = 24 -> (region size 2^(64-24) = 2^40)
        ***************************************************/
        ldr     x1,=0x285800518
        #endif
        msr     TCR_EL1, x1
        isb
	/* Enable SError Exception for asynchronous abort */
	mrs 	x1,DAIF
        bic	x1,x1,#(0x1<<8)
        msr	DAIF,x1

	//; Enable MMU
	mov	x1,#0x0
	orr     x1, x1, #(1 << 18)    // ; Set WFE non trapping
	orr     x1, x1, #(1 << 17)    // ; Set WFI non trapping
	orr     x1, x1, #(1 << 5)    // ; Set CP15 barrier enabled
	orr     x1, x1, #(1 << 12)    // ; Set I bit
	orr     x1, x1, #(1 << 2)    // ; Set C bit
	orr     x1, x1, #(1 << 0)    // ; Set M bit
	msr     SCTLR_EL1, x1
	isb

	bl 	 _startup		//jump to start
.else
	b 	error			// present exception level and selected exception level mismatch
.endif

error: 	b	error


invalidate_dcaches:

	dmb     ISH
	mrs     x0, CLIDR_EL1          //; x0 = CLIDR
	ubfx    w2, w0, #24, #3        //; w2 = CLIDR.LoC
	cmp     w2, #0                 //; LoC is 0?
	b.eq    invalidateCaches_end   //; No cleaning required and enable MMU
	mov     w1, #0                 //; w1 = level iterator

invalidateCaches_flush_level:
	add     w3, w1, w1, lsl #1     //; w3 = w1 * 3 (right-shift for cache type)
	lsr     w3, w0, w3             //; w3 = w0 >> w3
	ubfx    w3, w3, #0, #3         //; w3 = cache type of this level
	cmp     w3, #2                 //; No cache at this level?
	b.lt    invalidateCaches_next_level

	lsl     w4, w1, #1
	msr     CSSELR_EL1, x4         //; Select current cache level in CSSELR
	isb                            //; ISB required to reflect new CSIDR
	mrs     x4, CCSIDR_EL1         //; w4 = CSIDR

	ubfx    w3, w4, #0, #3
	add    	w3, w3, #2             //; w3 = log2(line size)
	ubfx    w5, w4, #13, #15
	ubfx    w4, w4, #3, #10        //; w4 = Way number
	clz     w6, w4                 //; w6 = 32 - log2(number of ways)

invalidateCaches_flush_set:
	mov     w8, w4                 //; w8 = Way number
invalidateCaches_flush_way:
	lsl     w7, w1, #1             //; Fill level field
	lsl     w9, w5, w3
	orr     w7, w7, w9             //; Fill index field
	lsl     w9, w8, w6
	orr     w7, w7, w9             //; Fill way field
	dc      CISW, x7               //; Invalidate by set/way to point of coherency
	subs    w8, w8, #1             //; Decrement way
	b.ge    invalidateCaches_flush_way
	subs    w5, w5, #1             //; Descrement set
	b.ge    invalidateCaches_flush_set

invalidateCaches_next_level:
	add     w1, w1, #1             //; Next level
	cmp     w2, w1
	b.gt    invalidateCaches_flush_level

invalidateCaches_end:
	ret

.end
/**
* @} End of "addtogroup a53_64_boot_code".
*/
