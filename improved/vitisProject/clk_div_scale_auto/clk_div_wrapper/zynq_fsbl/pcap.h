/******************************************************************************
* Copyright (c) 2012 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file pcap.h
*
* This file contains the interface for intiializing and accessing the PCAP
*
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver	Who	Date		Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a ecm	02/10/10 Initial release
* 2.00a mb  16/08/12 Added the macros and function prototypes
* 15.00a gan 07/21/16   953654 -(2016.3)FSBL -In pcap.c/pcap.h/main.c,
* 						Fabric Initialization sequence is modified to check
* 						the PL power before sequence starts and checking INIT_B
* 						reset status twice in case of failure.
* </pre>
*
* @note
*
******************************************************************************/
#ifndef ___PCAP_H___
#define ___PCAP_H___


#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xdevcfg.h"

/************************** Function Prototypes ******************************/


/* Multiboot register offset mask */
#define PCAP_MBOOT_REG_REBOOT_OFFSET_MASK	0x1FFF
#define PCAP_CTRL_PCFG_AES_FUSE_EFUSE_MASK	0x1000
/*Miscellaneous Control Register mask*/
#define XDCFG_MCTRL_PCAP_PCFG_POR_B_MASK    0x00000100
#define COUNTS_PER_MILLI_SECOND (COUNTS_PER_SECOND/1000)

#define PCAP_LAST_TRANSFER 1
#define MAX_COUNT 1000000000
#define LVL_PL_PS 0x0000000F
#define LVL_PS_PL 0x0000000A

/* Fix for #672779 */
#define FSBL_XDCFG_IXR_ERROR_FLAGS_MASK		(XDCFG_IXR_AXI_WERR_MASK | \
						XDCFG_IXR_AXI_RTO_MASK |  \
						XDCFG_IXR_AXI_RERR_MASK | \
						XDCFG_IXR_RX_FIFO_OV_MASK | \
						XDCFG_IXR_DMA_CMD_ERR_MASK |\
						XDCFG_IXR_DMA_Q_OV_MASK |   \
						XDCFG_IXR_P2D_LEN_ERR_MASK |\
						XDCFG_IXR_PCFG_HMAC_ERR_MASK)

int InitPcap(void);
void PcapDumpRegisters(void);
u32 ClearPcapStatus(void);
u32 FabricInit(void);
int XDcfgPollDone(u32 MaskValue, u32 MaxCount);
u32 PcapLoadPartition(u32 *SourceData, u32 *DestinationData, u32 SourceLength,
		 	u32 DestinationLength, u32 Flags);
u32 PcapDataTransfer(u32 *SourceData, u32 *DestinationData, u32 SourceLength,
 			u32 DestinationLength, u32 Flags);
/************************** Variable Definitions *****************************/
#ifdef __cplusplus
}
#endif


#endif /* ___PCAP_H___ */

