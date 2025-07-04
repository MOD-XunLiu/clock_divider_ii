/******************************************************************************
* Copyright (c) 2014 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
* @file xil_mmu.h
*
* @addtogroup r5_mpu_apis Cortex R5 Processor MPU specific APIs
*
* MPU functions provides access to MPU operations such as enable MPU, disable
* MPU and set attribute for section of memory.
* Boot code invokes Init_MPU function to configure the MPU. A total of 10 MPU
* regions are allocated with another 6 being free for users. Overview of the
* memory attributes for different MPU regions is as given below,
*
*|                       | Memory Range            | Attributes of MPURegion     |
*|-----------------------|-------------------------|-----------------------------|
*| DDR                   | 0x00000000 - 0x7FFFFFFF | Normal write-back Cacheable |
*| PL                    | 0x80000000 - 0xBFFFFFFF | Strongly Ordered            |
*| QSPI                  | 0xC0000000 - 0xDFFFFFFF | Device Memory               |
*| PCIe                  | 0xE0000000 - 0xEFFFFFFF | Device Memory               |
*| STM_CORESIGHT         | 0xF8000000 - 0xF8FFFFFF | Device Memory               |
*| RPU_R5_GIC            | 0xF9000000 - 0xF90FFFFF | Device memory               |
*| FPS                   | 0xFD000000 - 0xFDFFFFFF | Device Memory               |
*| LPS                   | 0xFE000000 - 0xFFFFFFFF | Device Memory               |
*| OCM                   | 0xFFFC0000 - 0xFFFFFFFF | Normal write-back Cacheable |
*
*
* @note
* For a system where DDR is less than 2GB, region after DDR and before PL is
* marked as undefined in translation table. Memory range 0xFE000000-0xFEFFFFFF is
* allocated for upper LPS slaves, where as memory region 0xFF000000-0xFFFFFFFF is
* allocated for lower LPS slaves.
*
* @{
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- ---------------------------------------------------
* 5.00  pkp  02/10/14 Initial version
* 6.4   asa  08/16/17 Added many APIs for MPU access to make MPU usage
* 					  user-friendly. The APIs added are: Xil_UpdateMPUConfig,
* 					  Xil_GetMPUConfig, Xil_GetNumOfFreeRegions,
* 					  Xil_GetNextMPURegion, Xil_DisableMPURegionByRegNum,
* 					  Xil_GetMPUFreeRegMask, Xil_SetMPURegionByRegNum, and
* 					  Xil_InitializeExistingMPURegConfig.
* 					  Added a new array of structure of type XMpuConfig to
* 					  represent the MPU configuration table.
* 7.7	sk   01/10/22 Modify Xil_SetTlbAttributes function argument name to fix
* 		      misra_c_2012_rule_8_3 violation.
* 8.0   mus  05/09/22  Updated MPU related APIs to support CortexR52 processor.
* </pre>
*

*
*
******************************************************************************/
/**
 *@cond nocomments
 */

#ifndef XIL_MPU_H
#define XIL_MPU_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "xil_types.h"
/***************************** Include Files *********************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define MPU_REG_DISABLED		0U
#define MPU_REG_ENABLED			1U
#define MAX_POSSIBLE_MPU_REGS	16U

#if defined(ARMR52)
#define XMPU_LIMIT_REG_ATTRIBUTE_SHIFT 8U
#define XMPU_LIMIT_REG_ATTRIBUTE_MASK 0xEU
#define XMPU_64BYTE_ALIGNMENT_MASK	0xFFFFFFC0U
#define XMPU_BASE_REG_ATTRIBUTE_MASK	0x1FU
#endif
/**************************** Type Definitions *******************************/
struct XMpuConfig{
	u32 RegionStatus; /* Enabled or disabled */
	INTPTR BaseAddress;/* MPU region base address */
	u64 Size; /* MPU region size address */
	u32 Attribute; /* MPU region size attribute */
};

typedef struct XMpuConfig XMpu_Config[MAX_POSSIBLE_MPU_REGS];

extern XMpu_Config Mpu_Config;
/************************** Constant Definitions *****************************/

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/
/**
 *@endcond
 */

void Xil_SetTlbAttributes(INTPTR addr, u32 attrib);
void Xil_EnableMPU(void);
void Xil_DisableMPU(void);
u32 Xil_SetMPURegion(INTPTR addr, u64 size, u32 attrib);
u32 Xil_UpdateMPUConfig(u32 reg_num, INTPTR address, u32 size, u32 attrib);
void Xil_GetMPUConfig (XMpu_Config mpuconfig);
u32 Xil_GetNumOfFreeRegions (void);
u32 Xil_GetNextMPURegion(void);
u32 Xil_DisableMPURegionByRegNum (u32 reg_num);
u16 Xil_GetMPUFreeRegMask (void);
u32 Xil_SetMPURegionByRegNum (u32 reg_num, INTPTR addr, u64 size, u32 attrib);
void* Xil_MemMap(UINTPTR Physaddr, size_t size, u32 flags);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XIL_MPU_H */
/**
* @} End of "addtogroup r5_mpu_apis".
*/
