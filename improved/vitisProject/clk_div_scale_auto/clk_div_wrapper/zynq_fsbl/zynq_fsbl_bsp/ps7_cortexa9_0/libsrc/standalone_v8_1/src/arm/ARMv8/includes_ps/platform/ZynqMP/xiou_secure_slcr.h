/*******************************************************************************
* Copyright (c) 2014 - 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
*******************************************************************************/


#ifndef __XIOU_SECURE_SLCR_H__
#define __XIOU_SECURE_SLCR_H__


#ifdef __cplusplus
extern "C" {
#endif

/**
 *@cond nocomments
 */

/**
 * XiouSecureSlcr Base Address
 */
#define XIOU_SECURE_SLCR_BASEADDR      0xFF240000UL

/**
 * Register: XiouSecSlcrAxiWprtcn
 */
#define XIOU_SEC_SLCR_AXI_WPRTCN    ( ( XIOU_SECURE_SLCR_BASEADDR ) + 0x00000000UL )
#define XIOU_SEC_SLCR_AXI_WPRTCN_RSTVAL   0x00000000UL

#define XIOU_SEC_SLCR_AXI_WPRTCN_XQSPIPSAXI_AWPROT_SHIFT   25UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XQSPIPSAXI_AWPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XQSPIPSAXI_AWPROT_MASK    0x0e000000UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XQSPIPSAXI_AWPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_WPRTCN_XNANDPS8_AWPROT_SHIFT   22UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XNANDPS8_AWPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XNANDPS8_AWPROT_MASK    0x01c00000UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XNANDPS8_AWPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_WPRTCN_XSDPS_AWPROT_SHIFT   19UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XSDPS_AWPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XSDPS_AWPROT_MASK    0x00380000UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XSDPS_AWPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_WPRTCN_XSDPS_AWPROT_SHIFT   16UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XSDPS_AWPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XSDPS_AWPROT_MASK    0x00070000UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XSDPS_AWPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_SHIFT   9UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_MASK    0x00000e00UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_SHIFT   6UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_MASK    0x000001c0UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_SHIFT   3UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_MASK    0x00000038UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_SHIFT   0UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_MASK    0x00000007UL
#define XIOU_SEC_SLCR_AXI_WPRTCN_XEMACPS_AWPROT_DEFVAL  0x0UL

/**
 * Register: XiouSecSlcrAxiRprtcn
 */
#define XIOU_SEC_SLCR_AXI_RPRTCN    ( ( XIOU_SECURE_SLCR_BASEADDR ) + 0x00000004UL )
#define XIOU_SEC_SLCR_AXI_RPRTCN_RSTVAL   0x00000000UL

#define XIOU_SEC_SLCR_AXI_RPRTCN_XNANDPS8_ARPROT_SHIFT   22UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XNANDPS8_ARPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XNANDPS8_ARPROT_MASK    0x01c00000UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XNANDPS8_ARPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_RPRTCN_XSDPS_ARPROT_SHIFT   19UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XSDPS_ARPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XSDPS_ARPROT_MASK    0x00380000UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XSDPS_ARPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_RPRTCN_XSDPS_ARPROT_SHIFT   16UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XSDPS_ARPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XSDPS_ARPROT_MASK    0x00070000UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XSDPS_ARPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_SHIFT   9UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_MASK    0x00000e00UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_SHIFT   6UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_MASK    0x000001c0UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_SHIFT   3UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_MASK    0x00000038UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_DEFVAL  0x0UL

#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_SHIFT   0UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_WIDTH   3UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_MASK    0x00000007UL
#define XIOU_SEC_SLCR_AXI_RPRTCN_XEMACPS_ARPROT_DEFVAL  0x0UL

/**
 * Register: XiouSecSlcrCtrl
 */
#define XIOU_SEC_SLCR_CTRL    ( ( XIOU_SECURE_SLCR_BASEADDR ) + 0x00000040UL )
#define XIOU_SEC_SLCR_CTRL_RSTVAL   0x00000000UL

#define XIOU_SEC_SLCR_CTRL_SLVERR_EN_SHIFT   0UL
#define XIOU_SEC_SLCR_CTRL_SLVERR_EN_WIDTH   1UL
#define XIOU_SEC_SLCR_CTRL_SLVERR_EN_MASK    0x00000001UL
#define XIOU_SEC_SLCR_CTRL_SLVERR_EN_DEFVAL  0x0UL

/**
 * Register: XiouSecSlcrIsr
 */
#define XIOU_SEC_SLCR_ISR    ( ( XIOU_SECURE_SLCR_BASEADDR ) + 0x00000044UL )
#define XIOU_SEC_SLCR_ISR_RSTVAL   0x00000000UL

#define XIOU_SEC_SLCR_ISR_ADDR_DECD_ERR_SHIFT   0UL
#define XIOU_SEC_SLCR_ISR_ADDR_DECD_ERR_WIDTH   1UL
#define XIOU_SEC_SLCR_ISR_ADDR_DECD_ERR_MASK    0x00000001UL
#define XIOU_SEC_SLCR_ISR_ADDR_DECD_ERR_DEFVAL  0x0UL

/**
 * Register: XiouSecSlcrImr
 */
#define XIOU_SEC_SLCR_IMR    ( ( XIOU_SECURE_SLCR_BASEADDR ) + 0x00000048UL )
#define XIOU_SEC_SLCR_IMR_RSTVAL   0x00000001UL

#define XIOU_SEC_SLCR_IMR_ADDR_DECD_ERR_SHIFT   0UL
#define XIOU_SEC_SLCR_IMR_ADDR_DECD_ERR_WIDTH   1UL
#define XIOU_SEC_SLCR_IMR_ADDR_DECD_ERR_MASK    0x00000001UL
#define XIOU_SEC_SLCR_IMR_ADDR_DECD_ERR_DEFVAL  0x1UL

/**
 * Register: XiouSecSlcrIer
 */
#define XIOU_SEC_SLCR_IER    ( ( XIOU_SECURE_SLCR_BASEADDR ) + 0x0000004CUL )
#define XIOU_SEC_SLCR_IER_RSTVAL   0x00000000UL

#define XIOU_SEC_SLCR_IER_ADDR_DECD_ERR_SHIFT   0UL
#define XIOU_SEC_SLCR_IER_ADDR_DECD_ERR_WIDTH   1UL
#define XIOU_SEC_SLCR_IER_ADDR_DECD_ERR_MASK    0x00000001UL
#define XIOU_SEC_SLCR_IER_ADDR_DECD_ERR_DEFVAL  0x0UL

/**
 * Register: XiouSecSlcrIdr
 */
#define XIOU_SEC_SLCR_IDR    ( ( XIOU_SECURE_SLCR_BASEADDR ) + 0x00000050UL )
#define XIOU_SEC_SLCR_IDR_RSTVAL   0x00000000UL

#define XIOU_SEC_SLCR_IDR_ADDR_DECD_ERR_SHIFT   0UL
#define XIOU_SEC_SLCR_IDR_ADDR_DECD_ERR_WIDTH   1UL
#define XIOU_SEC_SLCR_IDR_ADDR_DECD_ERR_MASK    0x00000001UL
#define XIOU_SEC_SLCR_IDR_ADDR_DECD_ERR_DEFVAL  0x0UL

/**
 * Register: XiouSecSlcrItr
 */
#define XIOU_SEC_SLCR_ITR    ( ( XIOU_SECURE_SLCR_BASEADDR ) + 0x00000054UL )
#define XIOU_SEC_SLCR_ITR_RSTVAL   0x00000000UL

#define XIOU_SEC_SLCR_ITR_ADDR_DECD_ERR_SHIFT   0UL
#define XIOU_SEC_SLCR_ITR_ADDR_DECD_ERR_WIDTH   1UL
#define XIOU_SEC_SLCR_ITR_ADDR_DECD_ERR_MASK    0x00000001UL
#define XIOU_SEC_SLCR_ITR_ADDR_DECD_ERR_DEFVAL  0x0UL

/**
 *@endcond
 */

#ifdef __cplusplus
}
#endif

#endif /* __XIOU_SECURE_SLCR_H__ */
