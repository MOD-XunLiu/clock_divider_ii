/******************************************************************************
* Copyright (c) 2014 - 2021 Xilinx, Inc.  All rights reserved.
* Copyright (c) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xreg_cortexa53.h
*
* This header file contains definitions for using inline assembler code. It is
* written specifically for the GNU compiler.
*
* All of the ARM Cortex A53 GPRs, SPRs, and Debug Registers are defined along
* with the positions of the bits within the registers.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who      Date     Changes
* ----- -------- -------- -----------------------------------------------
* 5.00 	pkp  05/29/14 First release
* 8.1   mus  02/20/23 Added #defines related to CPU affinity.
* </pre>
*
******************************************************************************/
#ifndef XREG_CORTEXA53_H
#define XREG_CORTEXA53_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 *@cond nocomments
 */

/* GPRs */
#define XREG_GPR0				x0
#define XREG_GPR1				x1
#define XREG_GPR2				x2
#define XREG_GPR3				x3
#define XREG_GPR4				x4
#define XREG_GPR5				x5
#define XREG_GPR6				x6
#define XREG_GPR7				x7
#define XREG_GPR8				x8
#define XREG_GPR9				x9
#define XREG_GPR10				x10
#define XREG_GPR11				x11
#define XREG_GPR12				x12
#define XREG_GPR13				x13
#define XREG_GPR14				x14
#define XREG_GPR15				x15
#define XREG_GPR16				x16
#define XREG_GPR17				x17
#define XREG_GPR18				x18
#define XREG_GPR19				x19
#define XREG_GPR20				x20
#define XREG_GPR21				x21
#define XREG_GPR22				x22
#define XREG_GPR23				x23
#define XREG_GPR24				x24
#define XREG_GPR25				x25
#define XREG_GPR26				x26
#define XREG_GPR27				x27
#define XREG_GPR28				x28
#define XREG_GPR29				x29
#define XREG_GPR30				x30
#define XREG_CPSR				cpsr

/* Current Processor Status Register (CPSR) Bits */
#define XREG_CPSR_MODE_BITS			0x1FU
#define XREG_CPSR_EL3h_MODE			0xDU
#define XREG_CPSR_EL3t_MODE			0xCU
#define XREG_CPSR_EL2h_MODE			0x9U
#define XREG_CPSR_EL2t_MODE			0x8U
#define XREG_CPSR_EL1h_MODE			0x5U
#define XREG_CPSR_EL1t_MODE			0x4U
#define XREG_CPSR_EL0t_MODE			0x0U

#define XREG_CPSR_IRQ_ENABLE		0x80U
#define XREG_CPSR_FIQ_ENABLE		0x40U

#define XREG_CPSR_N_BIT				0x80000000U
#define XREG_CPSR_Z_BIT				0x40000000U
#define XREG_CPSR_C_BIT				0x20000000U
#define XREG_CPSR_V_BIT				0x10000000U

/* FPSID bits */
#define XREG_FPSID_IMPLEMENTER_BIT	(24U)
#define XREG_FPSID_IMPLEMENTER_MASK	(0x000000FFU << FPSID_IMPLEMENTER_BIT)
#define XREG_FPSID_SOFTWARE		(0X00000001U<<23U)
#define XREG_FPSID_ARCH_BIT		(16U)
#define XREG_FPSID_ARCH_MASK		(0x0000000FU  << FPSID_ARCH_BIT)
#define XREG_FPSID_PART_BIT		(8U)
#define XREG_FPSID_PART_MASK		(0x000000FFU << FPSID_PART_BIT)
#define XREG_FPSID_VARIANT_BIT		(4U)
#define XREG_FPSID_VARIANT_MASK		(0x0000000FU  << FPSID_VARIANT_BIT)
#define XREG_FPSID_REV_BIT		(0U)
#define XREG_FPSID_REV_MASK		(0x0000000FU  << FPSID_REV_BIT)

/* FPSCR bits */
#define XREG_FPSCR_N_BIT		(0X00000001U << 31U)
#define XREG_FPSCR_Z_BIT		(0X00000001U << 30U)
#define XREG_FPSCR_C_BIT		(0X00000001U << 29U)
#define XREG_FPSCR_V_BIT		(0X00000001U << 28U)
#define XREG_FPSCR_QC			(0X00000001U << 27U)
#define XREG_FPSCR_AHP			(0X00000001U << 26U)
#define XREG_FPSCR_DEFAULT_NAN		(0X00000001U << 25U)
#define XREG_FPSCR_FLUSHTOZERO		(0X00000001U << 24U)
#define XREG_FPSCR_ROUND_NEAREST	(0X00000000U << 22U)
#define XREG_FPSCR_ROUND_PLUSINF	(0X00000001U << 22U)
#define XREG_FPSCR_ROUND_MINUSINF	(0X00000002U << 22U)
#define XREG_FPSCR_ROUND_TOZERO		(0X00000003U << 22U)
#define XREG_FPSCR_RMODE_BIT		(22U)
#define XREG_FPSCR_RMODE_MASK		(0X00000003U << FPSCR_RMODE_BIT)
#define XREG_FPSCR_STRIDE_BIT		(20U)
#define XREG_FPSCR_STRIDE_MASK		(0X00000003U << FPSCR_STRIDE_BIT)
#define XREG_FPSCR_LENGTH_BIT		(16U)
#define XREG_FPSCR_LENGTH_MASK		(0X00000007U << FPSCR_LENGTH_BIT)
#define XREG_FPSCR_IDC			(0X00000001U << 7U)
#define XREG_FPSCR_IXC			(0X00000001U << 4U)
#define XREG_FPSCR_UFC			(0X00000001U << 3U)
#define XREG_FPSCR_OFC			(0X00000001U << 2U)
#define XREG_FPSCR_DZC			(0X00000001U << 1U)
#define XREG_FPSCR_IOC			(0X00000001U << 0U)

/* MVFR0 bits */
#define XREG_MVFR0_RMODE_BIT		(28U)
#define XREG_MVFR0_RMODE_MASK		(0x0000000FU << XREG_MVFR0_RMODE_BIT)
#define XREG_MVFR0_SHORT_VEC_BIT	(24U)
#define XREG_MVFR0_SHORT_VEC_MASK	(0x0000000FU << XREG_MVFR0_SHORT_VEC_BIT)
#define XREG_MVFR0_SQRT_BIT		(20U)
#define XREG_MVFR0_SQRT_MASK		(0x0000000FU << XREG_MVFR0_SQRT_BIT)
#define XREG_MVFR0_DIVIDE_BIT		(16U)
#define XREG_MVFR0_DIVIDE_MASK		(0x0000000FU << XREG_MVFR0_DIVIDE_BIT)
#define XREG_MVFR0_EXEC_TRAP_BIT	(0X00000012U)
#define XREG_MVFR0_EXEC_TRAP_MASK	(0X0000000FU << XREG_MVFR0_EXEC_TRAP_BIT)
#define XREG_MVFR0_DP_BIT		(8U)
#define XREG_MVFR0_DP_MASK		(0x0000000FU << XREG_MVFR0_DP_BIT)
#define XREG_MVFR0_SP_BIT		(4U)
#define XREG_MVFR0_SP_MASK		(0x0000000FU << XREG_MVFR0_SP_BIT)
#define XREG_MVFR0_A_SIMD_BIT		(0U)
#define XREG_MVFR0_A_SIMD_MASK		(0x0000000FU << MVFR0_A_SIMD_BIT)

/* FPEXC bits */
#define XREG_FPEXC_EX			(0X00000001U << 31U)
#define XREG_FPEXC_EN			(0X00000001U << 30U)
#define XREG_FPEXC_DEX			(0X00000001U << 29U)


#define XREG_CONTROL_DCACHE_BIT	(0X00000001U<<2U)
#define XREG_CONTROL_ICACHE_BIT	(0X00000001U<<12U)

/* MPIDR Mask */
#define XREG_MPIDR_MASK                         0xFFFFFF
#define XREG_MPIDR_AFFINITY0_MASK               0xFF
#define XREG_MPIDR_AFFINITY1_MASK               0xFF00U
#define XREG_MPIDR_AFFINITY2_MASK               0xFF0000U
#define XREG_MPIDR_AFFINITY0_SHIFT              0x0U
#define XREG_MPIDR_AFFINITY1_SHIFT              0x8U
#define XREG_MPIDR_AFFINITY2_SHIFT              16U

/**
 *@endcond
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XREG_CORTEXA53_H */
