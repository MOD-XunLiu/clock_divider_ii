/*******************************************************************************
* Copyright (c) 2018 - 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
*******************************************************************************/


#ifndef __XLPD_SLCR_H__
#define __XLPD_SLCR_H__


#ifdef __cplusplus
extern "C" {
#endif

/**
 *@cond nocomments
 */

/**
 * XlpdSlcr Base Address
 */
#define XLPD_SLCR_BASEADDR      0xFF410000UL

/**
 * Register: XlpdSlcrWprot0
 */
#define XLPD_SLCR_WPROT0    ( ( XLPD_SLCR_BASEADDR ) + 0x00000000UL )
#define XLPD_SLCR_WPROT0_RSTVAL   0x00000000UL

#define XLPD_SLCR_WPROT0_ACT_SHIFT   0UL
#define XLPD_SLCR_WPROT0_ACT_WIDTH   1UL
#define XLPD_SLCR_WPROT0_ACT_MASK    0x00000001UL
#define XLPD_SLCR_WPROT0_ACT_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrCtrl
 */
#define XLPD_SLCR_CTRL    ( ( XLPD_SLCR_BASEADDR ) + 0x00000004UL )
#define XLPD_SLCR_CTRL_RSTVAL   0x00000000UL

#define XLPD_SLCR_CTRL_SLVERR_EN_SHIFT   0UL
#define XLPD_SLCR_CTRL_SLVERR_EN_WIDTH   1UL
#define XLPD_SLCR_CTRL_SLVERR_EN_MASK    0x00000001UL
#define XLPD_SLCR_CTRL_SLVERR_EN_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrIsr
 */
#define XLPD_SLCR_ISR    ( ( XLPD_SLCR_BASEADDR ) + 0x00000008UL )
#define XLPD_SLCR_ISR_RSTVAL   0x00000000UL

#define XLPD_SLCR_ISR_ADDR_DECODE_ERR_SHIFT   0UL
#define XLPD_SLCR_ISR_ADDR_DECODE_ERR_WIDTH   1UL
#define XLPD_SLCR_ISR_ADDR_DECODE_ERR_MASK    0x00000001UL
#define XLPD_SLCR_ISR_ADDR_DECODE_ERR_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrImr
 */
#define XLPD_SLCR_IMR    ( ( XLPD_SLCR_BASEADDR ) + 0x0000000CUL )
#define XLPD_SLCR_IMR_RSTVAL   0x00000001UL

#define XLPD_SLCR_IMR_ADDR_DECODE_ERR_SHIFT   0UL
#define XLPD_SLCR_IMR_ADDR_DECODE_ERR_WIDTH   1UL
#define XLPD_SLCR_IMR_ADDR_DECODE_ERR_MASK    0x00000001UL
#define XLPD_SLCR_IMR_ADDR_DECODE_ERR_DEFVAL  0x1UL

/**
 * Register: XlpdSlcrIer
 */
#define XLPD_SLCR_IER    ( ( XLPD_SLCR_BASEADDR ) + 0x00000010UL )
#define XLPD_SLCR_IER_RSTVAL   0x00000000UL

#define XLPD_SLCR_IER_ADDR_DECODE_ERR_SHIFT   0UL
#define XLPD_SLCR_IER_ADDR_DECODE_ERR_WIDTH   1UL
#define XLPD_SLCR_IER_ADDR_DECODE_ERR_MASK    0x00000001UL
#define XLPD_SLCR_IER_ADDR_DECODE_ERR_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrIdr
 */
#define XLPD_SLCR_IDR    ( ( XLPD_SLCR_BASEADDR ) + 0x00000014UL )
#define XLPD_SLCR_IDR_RSTVAL   0x00000000UL

#define XLPD_SLCR_IDR_ADDR_DECODE_ERR_SHIFT   0UL
#define XLPD_SLCR_IDR_ADDR_DECODE_ERR_WIDTH   1UL
#define XLPD_SLCR_IDR_ADDR_DECODE_ERR_MASK    0x00000001UL
#define XLPD_SLCR_IDR_ADDR_DECODE_ERR_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrItr
 */
#define XLPD_SLCR_ITR    ( ( XLPD_SLCR_BASEADDR ) + 0x00000018UL )
#define XLPD_SLCR_ITR_RSTVAL   0x00000000UL

#define XLPD_SLCR_ITR_ADDR_DECODE_ERR_SHIFT   0UL
#define XLPD_SLCR_ITR_ADDR_DECODE_ERR_WIDTH   1UL
#define XLPD_SLCR_ITR_ADDR_DECODE_ERR_MASK    0x00000001UL
#define XLPD_SLCR_ITR_ADDR_DECODE_ERR_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrSafetyChk0
 */
#define XLPD_SLCR_SAFETY_CHK0    ( ( XLPD_SLCR_BASEADDR ) + 0x00000060UL )
#define XLPD_SLCR_SAFETY_CHK0_RSTVAL   0x00000000UL

#define XLPD_SLCR_SAFETY_CHK0_CHK_VAL_SHIFT   0UL
#define XLPD_SLCR_SAFETY_CHK0_CHK_VAL_WIDTH   32UL
#define XLPD_SLCR_SAFETY_CHK0_CHK_VAL_MASK    0xffffffffUL
#define XLPD_SLCR_SAFETY_CHK0_CHK_VAL_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrSafetyChk1
 */
#define XLPD_SLCR_SAFETY_CHK1    ( ( XLPD_SLCR_BASEADDR ) + 0x00000064UL )
#define XLPD_SLCR_SAFETY_CHK1_RSTVAL   0x00000000UL

#define XLPD_SLCR_SAFETY_CHK1_CHK_VAL_SHIFT   0UL
#define XLPD_SLCR_SAFETY_CHK1_CHK_VAL_WIDTH   32UL
#define XLPD_SLCR_SAFETY_CHK1_CHK_VAL_MASK    0xffffffffUL
#define XLPD_SLCR_SAFETY_CHK1_CHK_VAL_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrSafetyChk2
 */
#define XLPD_SLCR_SAFETY_CHK2    ( ( XLPD_SLCR_BASEADDR ) + 0x00000068UL )
#define XLPD_SLCR_SAFETY_CHK2_RSTVAL   0x00000000UL

#define XLPD_SLCR_SAFETY_CHK2_CHK_VAL_SHIFT   0UL
#define XLPD_SLCR_SAFETY_CHK2_CHK_VAL_WIDTH   32UL
#define XLPD_SLCR_SAFETY_CHK2_CHK_VAL_MASK    0xffffffffUL
#define XLPD_SLCR_SAFETY_CHK2_CHK_VAL_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrSafetyChk3
 */
#define XLPD_SLCR_SAFETY_CHK3    ( ( XLPD_SLCR_BASEADDR ) + 0x0000006CUL )
#define XLPD_SLCR_SAFETY_CHK3_RSTVAL   0x00000000UL

#define XLPD_SLCR_SAFETY_CHK3_CHK_VAL_SHIFT   0UL
#define XLPD_SLCR_SAFETY_CHK3_CHK_VAL_WIDTH   32UL
#define XLPD_SLCR_SAFETY_CHK3_CHK_VAL_MASK    0xffffffffUL
#define XLPD_SLCR_SAFETY_CHK3_CHK_VAL_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrSmidCfgAdma0
 */
#define XLPD_SLCR_SMID_CFG_ADMA0    ( ( XLPD_SLCR_BASEADDR ) + 0x00000074UL )
#define XLPD_SLCR_SMID_CFG_ADMA0_RSTVAL   0x00000000UL

#define XLPD_SLCR_SMID_CFG_ADMA0_CH7_SHIFT   7UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH7_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH7_MASK    0x00000080UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH7_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA0_CH6_SHIFT   6UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH6_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH6_MASK    0x00000040UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH6_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA0_CH5_SHIFT   5UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH5_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH5_MASK    0x00000020UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH5_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA0_CH4_SHIFT   4UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH4_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH4_MASK    0x00000010UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH4_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA0_CH3_SHIFT   3UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH3_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH3_MASK    0x00000008UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH3_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA0_CH2_SHIFT   2UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH2_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH2_MASK    0x00000004UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH2_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA0_CH1_SHIFT   1UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH1_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH1_MASK    0x00000002UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH1_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA0_CH0_SHIFT   0UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH0_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH0_MASK    0x00000001UL
#define XLPD_SLCR_SMID_CFG_ADMA0_CH0_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrSmidCfgAdma1
 */
#define XLPD_SLCR_SMID_CFG_ADMA1    ( ( XLPD_SLCR_BASEADDR ) + 0x00000078UL )
#define XLPD_SLCR_SMID_CFG_ADMA1_RSTVAL   0x00000000UL

#define XLPD_SLCR_SMID_CFG_ADMA1_CH7_SHIFT   7UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH7_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH7_MASK    0x00000080UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH7_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA1_CH6_SHIFT   6UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH6_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH6_MASK    0x00000040UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH6_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA1_CH5_SHIFT   5UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH5_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH5_MASK    0x00000020UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH5_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA1_CH4_SHIFT   4UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH4_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH4_MASK    0x00000010UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH4_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA1_CH3_SHIFT   3UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH3_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH3_MASK    0x00000008UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH3_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA1_CH2_SHIFT   2UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH2_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH2_MASK    0x00000004UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH2_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA1_CH1_SHIFT   1UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH1_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH1_MASK    0x00000002UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH1_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_ADMA1_CH0_SHIFT   0UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH0_WIDTH   1UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH0_MASK    0x00000001UL
#define XLPD_SLCR_SMID_CFG_ADMA1_CH0_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrSmidCfgRpu0
 */
#define XLPD_SLCR_SMID_CFG_RPU0    ( ( XLPD_SLCR_BASEADDR ) + 0x0000007CUL )
#define XLPD_SLCR_SMID_CFG_RPU0_RSTVAL   0x00000000UL

#define XLPD_SLCR_SMID_CFG_RPU0_CH3_SHIFT   6UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH3_WIDTH   2UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH3_MASK    0x000000c0UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH3_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_RPU0_CH2_SHIFT   4UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH2_WIDTH   2UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH2_MASK    0x00000030UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH2_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_RPU0_CH1_SHIFT   2UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH1_WIDTH   2UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH1_MASK    0x0000000cUL
#define XLPD_SLCR_SMID_CFG_RPU0_CH1_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_RPU0_CH0_SHIFT   0UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH0_WIDTH   2UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH0_MASK    0x00000003UL
#define XLPD_SLCR_SMID_CFG_RPU0_CH0_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrSmidCfgRpu1
 */
#define XLPD_SLCR_SMID_CFG_RPU1    ( ( XLPD_SLCR_BASEADDR ) + 0x00000080UL )
#define XLPD_SLCR_SMID_CFG_RPU1_RSTVAL   0x00000000UL

#define XLPD_SLCR_SMID_CFG_RPU1_CH3_SHIFT   6UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH3_WIDTH   2UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH3_MASK    0x000000c0UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH3_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_RPU1_CH2_SHIFT   4UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH2_WIDTH   2UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH2_MASK    0x00000030UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH2_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_RPU1_CH1_SHIFT   2UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH1_WIDTH   2UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH1_MASK    0x0000000cUL
#define XLPD_SLCR_SMID_CFG_RPU1_CH1_DEFVAL  0x0UL

#define XLPD_SLCR_SMID_CFG_RPU1_CH0_SHIFT   0UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH0_WIDTH   2UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH0_MASK    0x00000003UL
#define XLPD_SLCR_SMID_CFG_RPU1_CH0_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrHsdpCfg
 */
#define XLPD_SLCR_HSDP_CFG    ( ( XLPD_SLCR_BASEADDR ) + 0x00000088UL )
#define XLPD_SLCR_HSDP_CFG_RSTVAL   0x00000000UL

#define XLPD_SLCR_HSDP_CFG_LINK_REACH_SHIFT   3UL
#define XLPD_SLCR_HSDP_CFG_LINK_REACH_WIDTH   1UL
#define XLPD_SLCR_HSDP_CFG_LINK_REACH_MASK    0x00000008UL
#define XLPD_SLCR_HSDP_CFG_LINK_REACH_DEFVAL  0x0UL

#define XLPD_SLCR_HSDP_CFG_AURORA_XPIPE_SEL_SHIFT   2UL
#define XLPD_SLCR_HSDP_CFG_AURORA_XPIPE_SEL_WIDTH   1UL
#define XLPD_SLCR_HSDP_CFG_AURORA_XPIPE_SEL_MASK    0x00000004UL
#define XLPD_SLCR_HSDP_CFG_AURORA_XPIPE_SEL_DEFVAL  0x0UL

#define XLPD_SLCR_HSDP_CFG_SEL_AUR_PCIE_SHIFT   1UL
#define XLPD_SLCR_HSDP_CFG_SEL_AUR_PCIE_WIDTH   1UL
#define XLPD_SLCR_HSDP_CFG_SEL_AUR_PCIE_MASK    0x00000002UL
#define XLPD_SLCR_HSDP_CFG_SEL_AUR_PCIE_DEFVAL  0x0UL

#define XLPD_SLCR_HSDP_CFG_SEL_AUR_PL_SHIFT   0UL
#define XLPD_SLCR_HSDP_CFG_SEL_AUR_PL_WIDTH   1UL
#define XLPD_SLCR_HSDP_CFG_SEL_AUR_PL_MASK    0x00000001UL
#define XLPD_SLCR_HSDP_CFG_SEL_AUR_PL_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrXocm2Cfg
 */
#define XLPD_SLCR_XOCM2_CFG    ( ( XLPD_SLCR_BASEADDR ) + 0x0000008CUL )
#define XLPD_SLCR_XOCM2_CFG_RSTVAL   0x00000000UL

#define XLPD_SLCR_XOCM2_CFG_PRESENT_SHIFT   0UL
#define XLPD_SLCR_XOCM2_CFG_PRESENT_WIDTH   1UL
#define XLPD_SLCR_XOCM2_CFG_PRESENT_MASK    0x00000001UL
#define XLPD_SLCR_XOCM2_CFG_PRESENT_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrAdmaCfg
 */
#define XLPD_SLCR_ADMA_CFG    ( ( XLPD_SLCR_BASEADDR ) + 0x0000200CUL )
#define XLPD_SLCR_ADMA_CFG_RSTVAL   0x00000048UL

#define XLPD_SLCR_ADMA_CFG_BUS_WIDTH_SHIFT   5UL
#define XLPD_SLCR_ADMA_CFG_BUS_WIDTH_WIDTH   2UL
#define XLPD_SLCR_ADMA_CFG_BUS_WIDTH_MASK    0x00000060UL
#define XLPD_SLCR_ADMA_CFG_BUS_WIDTH_DEFVAL  0x2UL

#define XLPD_SLCR_ADMA_CFG_NUM_CH_SHIFT   0UL
#define XLPD_SLCR_ADMA_CFG_NUM_CH_WIDTH   5UL
#define XLPD_SLCR_ADMA_CFG_NUM_CH_MASK    0x0000001fUL
#define XLPD_SLCR_ADMA_CFG_NUM_CH_DEFVAL  0x8UL

/**
 * Register: XlpdSlcrAfiFs
 */
#define XLPD_SLCR_AFI_FS    ( ( XLPD_SLCR_BASEADDR ) + 0x00009000UL )
#define XLPD_SLCR_AFI_FS_RSTVAL   0x00000200UL

#define XLPD_SLCR_AFI_FS_DW_SS2_SEL_SHIFT   8UL
#define XLPD_SLCR_AFI_FS_DW_SS2_SEL_WIDTH   2UL
#define XLPD_SLCR_AFI_FS_DW_SS2_SEL_MASK    0x00000300UL
#define XLPD_SLCR_AFI_FS_DW_SS2_SEL_DEFVAL  0x2UL

/**
 * Register: XlpdSlcrCciCfg0
 */
#define XLPD_SLCR_CCI_CFG_0    ( ( XLPD_SLCR_BASEADDR ) + 0x0000A000UL )
#define XLPD_SLCR_CCI_CFG_0_RSTVAL   0x00030fc0UL

#define XLPD_SLCR_CCI_CFG_0_SPR_SHIFT   28UL
#define XLPD_SLCR_CCI_CFG_0_SPR_WIDTH   4UL
#define XLPD_SLCR_CCI_CFG_0_SPR_MASK    0xf0000000UL
#define XLPD_SLCR_CCI_CFG_0_SPR_DEFVAL  0x0UL

#define XLPD_SLCR_CCI_CFG_0_ACCHANNEL_EN_MSB_SHIFT   12UL
#define XLPD_SLCR_CCI_CFG_0_ACCHANNEL_EN_MSB_WIDTH   6UL
#define XLPD_SLCR_CCI_CFG_0_ACCHANNEL_EN_MSB_MASK    0x0003f000UL
#define XLPD_SLCR_CCI_CFG_0_ACCHANNEL_EN_MSB_DEFVAL  0x30UL

#define XLPD_SLCR_CCI_CFG_0_ACCHANNEL_EN_LSB_SHIFT   6UL
#define XLPD_SLCR_CCI_CFG_0_ACCHANNEL_EN_LSB_WIDTH   6UL
#define XLPD_SLCR_CCI_CFG_0_ACCHANNEL_EN_LSB_MASK    0x00000fc0UL
#define XLPD_SLCR_CCI_CFG_0_ACCHANNEL_EN_LSB_DEFVAL  0x3fUL

#define XLPD_SLCR_CCI_CFG_0_QOS_OVERRIDE_SHIFT   0UL
#define XLPD_SLCR_CCI_CFG_0_QOS_OVERRIDE_WIDTH   6UL
#define XLPD_SLCR_CCI_CFG_0_QOS_OVERRIDE_MASK    0x0000003fUL
#define XLPD_SLCR_CCI_CFG_0_QOS_OVERRIDE_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrCciCfg1
 */
#define XLPD_SLCR_CCI_CFG_1    ( ( XLPD_SLCR_BASEADDR ) + 0x0000A004UL )
#define XLPD_SLCR_CCI_CFG_1_RSTVAL   0x000023c0UL

#define XLPD_SLCR_CCI_CFG_1_MST_DEPEND_ON_SL_SHIFT   12UL
#define XLPD_SLCR_CCI_CFG_1_MST_DEPEND_ON_SL_WIDTH   6UL
#define XLPD_SLCR_CCI_CFG_1_MST_DEPEND_ON_SL_MASK    0x0003f000UL
#define XLPD_SLCR_CCI_CFG_1_MST_DEPEND_ON_SL_DEFVAL  0x2UL

#define XLPD_SLCR_CCI_CFG_1_BRST_SPLIT_ALL_SHIFT   6UL
#define XLPD_SLCR_CCI_CFG_1_BRST_SPLIT_ALL_WIDTH   6UL
#define XLPD_SLCR_CCI_CFG_1_BRST_SPLIT_ALL_MASK    0x00000fc0UL
#define XLPD_SLCR_CCI_CFG_1_BRST_SPLIT_ALL_DEFVAL  0xfUL

#define XLPD_SLCR_CCI_CFG_1_ORDERED_WR_OBSERVE_SHIFT   0UL
#define XLPD_SLCR_CCI_CFG_1_ORDERED_WR_OBSERVE_WIDTH   6UL
#define XLPD_SLCR_CCI_CFG_1_ORDERED_WR_OBSERVE_MASK    0x0000003fUL
#define XLPD_SLCR_CCI_CFG_1_ORDERED_WR_OBSERVE_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrCci
 */
#define XLPD_SLCR_CCI    ( ( XLPD_SLCR_BASEADDR ) + 0x0000A008UL )
#define XLPD_SLCR_CCI_RSTVAL   0x00000000UL

#define XLPD_SLCR_CCI_ADDRMAP_SHIFT   0UL
#define XLPD_SLCR_CCI_ADDRMAP_WIDTH   25UL
#define XLPD_SLCR_CCI_ADDRMAP_MASK    0x01ffffffUL
#define XLPD_SLCR_CCI_ADDRMAP_DEFVAL  0x0UL

/**
 * Register: XlpdSlcrSmmu
 */
#define XLPD_SLCR_SMMU    ( ( XLPD_SLCR_BASEADDR ) + 0x0000A020UL )
#define XLPD_SLCR_SMMU_RSTVAL   0x0000007fUL

#define XLPD_SLCR_SMMU_CFG_NORMIZE_SHIFT   9UL
#define XLPD_SLCR_SMMU_CFG_NORMIZE_WIDTH   1UL
#define XLPD_SLCR_SMMU_CFG_NORMIZE_MASK    0x00000200UL
#define XLPD_SLCR_SMMU_CFG_NORMIZE_DEFVAL  0x0UL

#define XLPD_SLCR_SMMU_INTEG_SEC_OVERRIDE_SHIFT   8UL
#define XLPD_SLCR_SMMU_INTEG_SEC_OVERRIDE_WIDTH   1UL
#define XLPD_SLCR_SMMU_INTEG_SEC_OVERRIDE_MASK    0x00000100UL
#define XLPD_SLCR_SMMU_INTEG_SEC_OVERRIDE_DEFVAL  0x0UL

#define XLPD_SLCR_SMMU_CFG_CTTW_SHIFT   7UL
#define XLPD_SLCR_SMMU_CFG_CTTW_WIDTH   1UL
#define XLPD_SLCR_SMMU_CFG_CTTW_MASK    0x00000080UL
#define XLPD_SLCR_SMMU_CFG_CTTW_DEFVAL  0x0UL

#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU6_SHIFT   6UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU6_WIDTH   1UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU6_MASK    0x00000040UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU6_DEFVAL  0x1UL

#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU5_SHIFT   5UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU5_WIDTH   1UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU5_MASK    0x00000020UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU5_DEFVAL  0x1UL

#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU4_SHIFT   4UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU4_WIDTH   1UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU4_MASK    0x00000010UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU4_DEFVAL  0x1UL

#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU3_SHIFT   3UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU3_WIDTH   1UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU3_MASK    0x00000008UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU3_DEFVAL  0x1UL

#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU2_SHIFT   2UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU2_WIDTH   1UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU2_MASK    0x00000004UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU2_DEFVAL  0x1UL

#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU1_SHIFT   1UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU1_WIDTH   1UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU1_MASK    0x00000002UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU1_DEFVAL  0x1UL

#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU0_SHIFT   0UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU0_WIDTH   1UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU0_MASK    0x00000001UL
#define XLPD_SLCR_SMMU_SYSBARDISABLE_TBU0_DEFVAL  0x1UL

/**
 * Register: XlpdSlcrApu
 */
#define XLPD_SLCR_APU    ( ( XLPD_SLCR_BASEADDR ) + 0x0000A040UL )
#define XLPD_SLCR_APU_RSTVAL   0x00000001UL

#define XLPD_SLCR_APU_BRDC_BARRIER_SHIFT   3UL
#define XLPD_SLCR_APU_BRDC_BARRIER_WIDTH   1UL
#define XLPD_SLCR_APU_BRDC_BARRIER_MASK    0x00000008UL
#define XLPD_SLCR_APU_BRDC_BARRIER_DEFVAL  0x0UL

#define XLPD_SLCR_APU_BRDC_CMNT_SHIFT   2UL
#define XLPD_SLCR_APU_BRDC_CMNT_WIDTH   1UL
#define XLPD_SLCR_APU_BRDC_CMNT_MASK    0x00000004UL
#define XLPD_SLCR_APU_BRDC_CMNT_DEFVAL  0x0UL

#define XLPD_SLCR_APU_BRDC_INNER_SHIFT   1UL
#define XLPD_SLCR_APU_BRDC_INNER_WIDTH   1UL
#define XLPD_SLCR_APU_BRDC_INNER_MASK    0x00000002UL
#define XLPD_SLCR_APU_BRDC_INNER_DEFVAL  0x0UL

#define XLPD_SLCR_APU_BRDC_OUTER_SHIFT   0UL
#define XLPD_SLCR_APU_BRDC_OUTER_WIDTH   1UL
#define XLPD_SLCR_APU_BRDC_OUTER_MASK    0x00000001UL
#define XLPD_SLCR_APU_BRDC_OUTER_DEFVAL  0x1UL

/**
 *@endcond
 */

#ifdef __cplusplus
}
#endif

#endif /* __XLPD_SLCR_H__ */
