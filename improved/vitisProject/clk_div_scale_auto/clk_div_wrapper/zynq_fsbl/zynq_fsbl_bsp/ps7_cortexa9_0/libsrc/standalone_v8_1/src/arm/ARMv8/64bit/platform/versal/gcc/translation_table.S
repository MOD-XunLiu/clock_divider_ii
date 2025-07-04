/******************************************************************************
* Copyright (C) 2018 - 2022 Xilinx, Inc.  All rights reserved.
* Copyright (c) 2022 - 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*****************************************************************************/
/**
* @file translation_table.s
*
* @addtogroup a53_64_boot_code
* @{
* <h2> translation_table.S </h2>
* The translation_table.S contains a static page table required by MMU for
* cortex-A72. This translation table is flat mapped (input address = output
* address) with default memory attributes defined for Versal
* architecture. It utilizes translation granual size of 4KB with 2MB section
* size for initial 5GB memory and 1GB section size for memory after 5GB.
* The overview of translation table memory attributes is described below.
*
*| Name                  | Memory Range                      | Def. in Translation Table   |
*|-----------------------|-----------------------------------|-----------------------------|
*| DDR                   | 0x000_0000_0000 - 0x000_7FFF_FFFF | Normal WB Cacheable         |
*| LPD_AFI_FS            | 0x000_8000_0000 - 0x000_9FFF_FFFF | Strongly Ordered            |
*| Reserved              | 0x000_A000_0000 - 0x000_A3FF_FFFF | Unassigned                  |
*| FPD_AFI_0             | 0x000_A400_0000 - 0x000_AFFF_FFFF | Strongly Ordered            |
*| FPD_AFI_1             | 0x000_B000_0000 - 0x000_BFFF_FFFF | Strongly Ordered            |
*| QSPI                  | 0x000_C000_0000 - 0x000_DFFF_FFFF | Strongly Ordered            |
*| PCIE region 0         | 0x000_E000_0000 - 0x000_EFFF_FFFF | Strongly Ordered            |
*| PMC                   | 0x000_F000_0000 - 0x000_F7FF_FFFF | Strongly Ordered            |
*| STM_CORESIGHT         | 0x000_F800_0000 - 0x000_F8FF_FFFF | Strongly Ordered            |
*| GIC                   | 0x000_F900_0000 - 0x000_F90F_FFFF | Strongly Ordered            |
*| Reserved              | 0x000_F910_0000 - 0x000_FBFF_FFFF | Unassigned                  |
*| CPM                   | 0x000_FC00_0000 - 0x000_FCFF_FFFF | Strongly Ordered            |
*| FPD slaves            | 0x000_FD00_0000 - 0x000_FDFF_FFFF | Strongly Ordered            |
*| LPD slaves            | 0x000_FE00_0000 - 0x000_FFDF_FFFF | Strongly Ordered            |
*| OCM                   | 0x000_FFE0_0000 - 0xFFF_FFFF_FFFF | Normal WB Cacheable         |
*| PMC region 0-3        | 0x001_0000_0000 - 0x001_1FFF_FFFF | Strongly Ordered            |
*| Reserved              | 0x001_2000_0000 - 0x001_FFFF_FFFF | Unassigned                  |
*| ME Array 0-3          | 0x002_0000_0000 - 0x002_FFFF_FFFF | Strongly Ordered            |
*| Reserved              | 0x003_0000_0000 - 0x003_FFFF_FFFF | Unassigned                  |
*| PL- via PS            | 0x004_0000_0000 - 0x005_FFFF_FFFF | Strongly Ordered            |
*| PCIe region 1         | 0x006_0000_0000 - 0x007_FFFF_FFFF | Strongly Ordered            |
*| DDR                   | 0x008_0000_0000 - 0x00F_FFFF_FFFF | Normal WB Cacheable         |
*| Reserved              | 0x010_0000_0000 - 0x03F_FFFF_FFFF | Unassigned                  |
*| HBM 0-3               | 0x040_0000_0000 - 0x07F_FFFF_FFFF | Strongly Ordered            |
*| PCIe region 2         | 0x080_0000_0000 - 0x0BF_FFFF_FFFF | Strongly Ordered            |
*| DDR                   | 0x0C0_0000_0000 - 0x1B7_7FFF_FFFF | Normal WB Cacheable         |
*| Reserved              | 0x1B7_8000_0000 - 0x1FF_FFFF_FFFF | Unassigned                  |
*| PL- Via NoC           | 0x200_0000_0000 - 0x3FF_FFFF_FFFF | Strongly Ordered            |
*| PL- Via PS            | 0x400_0000_0000 - 0x4FF_FFFF_FFFF | Strongly Ordered            |
*| DDR CH1-CH3           | 0x500_0000_0000 - 0x7FF_FFFF_FFFF | Normal WB Cacheable         |
*| PL- Via NoC           | 0x800_0000_0000 - 0xFFF_FFFF_FFFF | Strongly Ordered            |
*
* @note
*
* For DDR region 0x0000000000 - 0x007FFFFFFF, a system where DDR is less than
* 2GB, region after DDR and before PL is marked as undefined/reserved in
* translation table. Region 0xF9100000 - 0xF91FFFFF is reserved memory in
* 0x00F9000000 - 0x00F91FFFFF range, but it is marked as strongly ordered
* because minimum section size in translation table section is 2MB.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- ---------------------------------------------------
* 7.00  mus  05/21/14 Initial version
* 7.00  mus  03/16/19 Updated translation table to mark DDR regions as
*                     memory, based on the DDR size in hdf
* 7.1   mus  08/29/19 Updated translation table entries for DDR_CH_1,
*                     DDR_CH_2 and DDR_CH_3 based on respective size in hdf
* 7.3   mus  09/10/20 Updated translation table entries for DDR regions, to
*                     support HW designs, where DDR memory is mapped at
*                     address other than DDR region base address. It fixes
*                     CR#1073099.
* 8.0   mus  07/06/21 Added support for VERSAL NET
* 8.0   mus  10/05/21 Updated VERSAL NET translation table to configure 1 TB address
*                     space (default is 256 TB) when OCM_ELF flag is defined
*                     in compiler flags.
* 8.1   mus  11/08/22 Used ENABLE_MINIMAL_XLAT_TBL flag to reduce translation
*                     table size. OCM_ELF flag checking would be removed later.
* 8.1   mus  12/22/22 Updated VERSAL NET translation table to configure 4 TB
*                     address space when ENABLE_MINIMAL_XLAT_TBL is defined.
*                     This is default behavior, since ENABLE_MINIMAL_XLAT_TBL
*                     would be defined by default.
* 8.1   mus  12/22/22 Updated VERSAL NET translation table to configure lower
*                     DDR and OCM as cacheable memory.
* 8.1   mus  12/22/22 Updated VERSAL NET translation table to configure PCIE
*                     region as device memory.
* 8.1   mus  02/06/23 Few registers in CMN space needs to be set up for OCM
*                     cacheability. Existing firmware is not doing that. Hence,
*                     OCM cacheability is broken for VERSAL NET SoC.
*                     Updated VERSAL NET translation table to configure OCM
*                     as non cacheable, till that support is added in firmware.
*                     It fixes CR#1150456.
*
******************************************************************************/
#include "xparameters.h"
#include "bspconfig.h"

	.globl  MMUTableL0
	.globl  MMUTableL1
	.globl  MMUTableL2

	.set UNDEF_START, 0

	/* Base addresses for all DDR regions in Versal SoC */
	.set DDR_LOW_0_REGION_START_ADDR, 0x0000000000		/* 0x0000_0000_0000 */
	.set DDR_LOW_1_REGION_START_ADDR, 0x800000000		/* 0x0008_0000_0000 */
	.set DDR_LOW_2_REGION_START_ADDR, 0xC000000000		/* 0x00C0_0000_0000 */
	.set DDR_LOW_3_REGION_START_ADDR, 0x10000000000		/* 0x0100_0000_0000 */
	.set DDR_CH_1_REGION_START_ADDR, 0x50000000000		/* 0x0500_0000_0000 */
	.set DDR_CH_2_REGION_START_ADDR, 0x60000000000		/* 0x0600_0000_0000 */
	.set DDR_CH_3_REGION_START_ADDR, 0x70000000000		/* 0x0700_0000_0000 */

	.set reserved,	0x0 					/* Fault*/
	.set Memory_NonCacheable,	0x401 		/* normal non-cacheable */
	#if EL1_NONSECURE
	.set Memory,	0x405 | (2 << 8) | (0x0)		/* normal writeback write allocate outer shared read write */
	#else
	.set Memory,	0x405 | (3 << 8) | (0x0)		/* normal writeback write allocate inner shared read write */
	#endif
	.set Device,	0x409 | (1 << 53)| (1 << 54) |(0x0)	/* strongly ordered read write non executable*/

#ifdef VERSAL_NET
	.section .mmu_tbl0,"a"

MMUTableL0:

/*
 * 256 sections each with 512 GB size covers 0 - 128 TB.
 * 128TB - 256TB is reserved in VERSAL NET address map,
 * so not defining sections for that region.
 */

.set SECT, MMUTableL1		/* 0x0000_0000 -  0x7F_FFFF_FFFF */
.8byte	SECT + 0x3

#if ! defined  (OCM_ELF) && ! defined (ENABLE_MINIMAL_XLAT_TBL)
.rept	0xff
.set SECT, SECT + 0x1000	/* 0x80_0000_0000 - 0xFFF_FFFF_FFFF */
.8byte	SECT + 0x3
.endr
#else
.rept	0x7
.set SECT, SECT + 0x1000        /* 0x80_0000_0000 - 0xFFF_FFFF_FFFF */
.8byte  SECT + 0x3
.endr
#endif

	.section .mmu_tbl1,"a"

MMUTableL1:

/*
 * For first 4GB of address space provide granularity
 * of 2MB.
 */

.set SECT, MMUTableL2		/* 0x0000_0000 - 0x3FFF_FFFF */
.8byte	SECT + 0x3		/* 1GB DDR */

.rept	0x3			/* 0x4000_0000 - 0x1_3FFF_FFFF */
.set SECT, SECT + 0x1000	/* DDR, PS_LPD_AFI_FS, PCIE_REGION0, PS_FPD_AFI_FS, OCM, xSPI, FPD_STM_CORESIGHT,*/
.8byte	SECT + 0x3              /* FPD GIC, PS_FPD_CMN, PMC, CPM, FPD slaves, LPD slaves, PMC_ALIAS_REGION0-3, FPD_PKI */
.endr                           /* HNIC, Multimedia tiles */

.set SECT,0x100000000

.rept	0x1C			/* 0x1_0000_0000 - 0x7_FFFF_FFFF */
.8byte	SECT + reserved		/* 28GB Reserved */
.set SECT, SECT + 0x40000000
.endr

/* TODO: Mark DDR_CH0_MED as normal memory based on HW design */
.rept	0x20			/* 0x8_0000_0000 - 0xF_FFFF_FFFF */
.8byte	SECT + reserved		/* 32GB DDR_CH0_MED marked as reserved for now */
.set SECT, SECT + 0x40000000
.endr

.rept	0x40			/* 0x10_0000_0000 - 0x1F_FFFF_FFFF */
.8byte	SECT + reserved		/* 64GB Reserved */
.set SECT, SECT + 0x40000000
.endr

.rept	0x80			/* 0x20_0000_0000 - 0x3F_FFFF_FFFF */
.8byte	SECT + Device		/* 128GB C2C_MED */
.set SECT, SECT + 0x40000000
.endr

/* TODO: Mark HBM regions as normal memory based on the HW design */
.rept	0x100			/* 0x40_0000_0000 - 0x7F_FFFF_FFFF */
.8byte	SECT + reserved		/* 256GB device */
.set SECT, SECT + 0x40000000
.endr

.rept	0x100			/* 0x80_0000_0000 - 0xBF_FFFF_FFFF */
.8byte	SECT + reserved		/* 256GB reserved */
.set SECT, SECT + 0x40000000
.endr

/* TODO: Mark this region as normal memory based on HW design */
.rept	0x100			/* 0xC0_0000_0000 - 0xFF_FFFF_FFFF */
.8byte	SECT + reserved		/* 256GB DDR (DDR_CH0_HIGH_0: 256GB + DDR_CH0_HIGH_1: 734GB) */
.set SECT, SECT + 0x40000000
.endr

.rept   0x2DE                   /* 0x100_0000_0000 - 0x1B7_7FFF_FFFF */
.8byte  SECT + reserved         /* 790GB DDR (DDR_CH0_HIGH_1) */
.set SECT, SECT + 0x40000000
.endr

.rept   0x122                   /* 0x1B8_0000_0000 - 0x1FF_FFFF_FFFF */
.8byte  SECT + reserved         /* 290GB DDR */
.set SECT, SECT + 0x40000000
.endr


.rept	0x4			/* 0x200_0000_0000 - 0x200_FFFF_FFFF */
.8byte	SECT + Device		/* 4GB ME Programming */
.set SECT, SECT + 0x40000000
.endr

.rept   0x4                     /* 0x201_0000_0000 - 0x201_FFFF_FFFF */
.8byte  SECT + reserved         /* 4GB reserved */
.set SECT, SECT + 0x40000000
.endr

.rept   0x7                     /* 0x202_0000_0000 - 0x203_BFFF_FFFF */
.8byte  SECT + Device           /* 2GB PS_FPD_AFI_FS_CONFIG + 2GB C2C_CONFIG + 2GB PL_VIA_NOC_CONFIG + 512MB PMC_ALIAS0-3 */
.set SECT, SECT + 0x40000000
.endr

.8byte  SECT + reserved         /* 1GB reserved  0x203_C000_0000 - 0x203_FFFF_FFFF */
.set SECT, SECT + 0x40000000

.8byte  SECT + Device           /* 8MB PKI, 1016MB reserved from next section  0x204_0000_0000 - 0x204_3FFF_FFFF */
.set SECT, SECT + 0x40000000

.rept	0x7EF			/* 0x204_4000_0000 - 0x3ffffffffff */
.8byte	SECT + Device		/* 2031GB reserved */
.set SECT, SECT + 0x40000000
.endr

#if ! defined (OCM_ELF) && ! defined (ENABLE_MINIMAL_XLAT_TBL)
.rept	0x400			/* 0x400_0000_0000 - 0x4FF_FFFF_FFFF */
.8byte	SECT + Device		/* 1TB PS_FPD_AFI_FS_HIGH */
.set SECT, SECT + 0x40000000
.endr

/* TODO: Mark this region as normal memory based on the HW design */
.rept	0xc00			/* 0x500_0000_0000 - 0x7FF_FFFF_FFFF */
.8byte	SECT + reserved		/* 3TB DDR: DDR_CH1, DDr_CH2 and DDR_CH3 each with 1TB */
.set SECT, SECT + 0x40000000
.endr

.rept	0x2000			/* 0x800_0000_0000 - 0xFFF_FFFF_FFFF */
.8byte	SECT + Device		/* 8TB PL_VIA_NOC_HIGH*/
.set SECT, SECT + 0x40000000
.endr

.rept	0x2000			/* 0x800_0000_0000 - 0xFFF_FFFF_FFFF */
.8byte	SECT + Device		/* 8TB CPM_CDX_DPU_HIGH */
.set SECT, SECT + 0x40000000
.endr

/* TODO: Mark this region as normal memory based on the HW design */
.rept	0x1800			/* 0x400_0000_0000 - 0x4FF_FFFF_FFFF */
.8byte	SECT + reserved		/* 6TB DDR: 12 DDR regions (DDR_CH4 to DDR_CH15) each of size 512GB */
.set SECT, SECT + 0x40000000
.endr

.rept	0x800			/* 0x800_0000_0000 - 0xFFF_FFFF_FFFF */
.8byte	SECT + reserved		/* 2TB reserved */
.set SECT, SECT + 0x40000000
.endr

.rept	0x4000			/* 0x800_0000_0000 - 0xFFF_FFFF_FFFF */
.8byte	SECT + Device		/* 16TB C2C_HIGH */
.set SECT, SECT + 0x40000000
.endr

.rept	0x4000			/* 0x800_0000_0000 - 0xFFF_FFFF_FFFF */
.8byte	SECT + reserved		/* 16TB reserved */
.set SECT, SECT + 0x40000000
.endr

.rept	0x10000			/* 0x800_0000_0000 - 0xFFF_FFFF_FFFF */
.8byte	SECT + Device		/* 64TB PSX Socket 1 */
.set SECT, SECT + 0x40000000
.endr
#endif

.section .mmu_tbl2,"a"

MMUTableL2:

.set SECT, 0

/* TODO: Configure this region as normal memory/reserved based on HW design */
.rept	0x400			/* 2GB DDR 0x0 - 0x80000000 */
.8byte	SECT + Memory
.set	SECT, SECT+0x200000
.endr

.rept	0x0100			/* 0x8000_0000 - 0x9FFF_FFFF */
.8byte	SECT + Device		/* 512MB PS_LPD_AFI_FS */
.set	SECT, SECT+0x200000
.endr

.rept	0x080			/* 0xA000_0000 - 0xAFFF_FFFF */
.8byte	SECT + Device		/* 256MB PCIE_REGION */
.set	SECT, SECT+0x200000
.endr


.rept	0x040			   /* 0xB00_0000 - 0xB7FF_FFFF */
.8byte	SECT + Device              /* 128MB PS_FPD_AFI_FS */
.set	SECT, SECT+0x200000
.endr

.rept   0x01F                      /* 0xB800_0000 - 0xBBDF_FFFF */
.8byte  SECT + reserved		   /* 62MB reserved */
.set    SECT, SECT+0x200000
.endr

/*
 * Note: 1 MB OCM 0xBBF0_0000 - 0xBBFF_FFFF,
 * 0xBBE0_0000 - 0XBBEF_FFFF marked as normal
 * memory incorrectly due to 2 MB granularity limitation
 */
.rept	0x01			   /* 0xBBE0_0000 - 0xBBFF_FFFF */
.8byte	SECT + Memory_NonCacheable              /* 1 MB OCM 0xBBF0_0000 - 0xBBFF_FFFF, 0xBBE0_0000 - 0XBBEF_FFFF marked as normal memory incorrectly  */
.set	SECT, SECT+0x200000
.endr

.rept	0x020			/* 0xB000_0000 - 0xBFFF_FFFF */
.8byte	SECT + reserved		/* 64MB reserved */
.set	SECT, SECT+0x200000
.endr

.rept	0x100			/* 0xE000_0000 - 0xEFFF_FFFF */
.8byte	SECT + Device		/* 512MB xSPI */
.set	SECT, SECT+0x200000
.endr

.rept	0x08			/* 0xE000_0000 - 0xEFFF_FFFF */
.8byte	SECT + Device		/* 16MB FPD_STM_CORESIGHT */
.set	SECT, SECT+0x200000
.endr

.rept   0x08                    /* 0xe1000000 - 0xE1FF_FFFF */
.8byte  SECT + reserved         /* 16MB reserved */
.set    SECT, SECT+0x200000
.endr

.rept   0x02                    /* 0xE200_0000 - 0xE23F_FFFF */
.8byte  SECT + Device           /* 4MB GIC */
.set    SECT, SECT+0x200000
.endr

.rept	0xE			/* 0xE240_0000 - 0xE3FF_FFFF */
.8byte	SECT + reserved		/* 28MB reserved */
.set	SECT, SECT+0x200000
.endr

.rept	0x08			/* 0xE400_0000 - 0xE4FF_FFFF_ */
.8byte  SECT + Device           /* 16MB CPM */
.set	SECT, SECT+0x200000
.endr

.rept	0x8			/* 0xE500_0000 - 0xE5FF_FFFF */
.8byte	SECT + reserved		/* 16MB reserved */
.set	SECT, SECT+0x200000
.endr

.rept	0x4			/* 0xE600_0000 - 0xE67F_FFFF */
.8byte	SECT + Device		/* 8MB HNIC */
.set	SECT, SECT+0x200000
.endr

.rept   0xC                     /* 0xE680_0000 - 0xE7FF_FFFF */
.8byte  SECT + reserved         /* 24MB reserved */
.set    SECT, SECT+0x200000
.endr

.rept   0x4                     /* 0xE800_0000 - 0xE87F_FFFF */
.8byte  SECT + Device           /* 8MB Multimedia tiles */
.set    SECT, SECT+0x200000
.endr

.rept   0xC                     /* 0xE880_0000 - 0xE9FF_FFFF */
.8byte  SECT + reserved         /* 24MB reserved */
.set    SECT, SECT+0x200000
.endr

.rept	0x18			/* 0xEA00_0000 - 0xECFF_FFFF */
.8byte	SECT + Device		/* 32MB LPD_SLAVES 16MB FPD_SLAVES */
.set	SECT, SECT+0x200000
.endr

.rept   0x18                     /* 0xED00_0000 - 0xEFFF_FFFF */
.8byte  SECT + reserved          /* 24MB reserved */
.set    SECT, SECT+0x200000
.endr

.rept   0x40                    /* 0xF000_0000 - 0xF7FF_FFFF */
.8byte  SECT + Device           /* 128MB PMC */
.set    SECT, SECT+0x200000
.endr

.rept   0x20                    /* 0xF800_0000 - 0xFBFF_FFFF */
.8byte  SECT + Device           /* 64MB PS_FPD_CMN */
.set    SECT, SECT+0x200000
.endr

.rept   0x20                     /* 0xFC00_0000 - 0xFFFF_FFFF */
.8byte  SECT + reserved         /* 32MB reserved */
.set    SECT, SECT+0x200000
.endr

.end

#else
	.section .mmu_tbl0,"a"

MMUTableL0:

.set SECT, MMUTableL1		/* 0x0000_0000 -  0x7F_FFFF_FFFF */
.8byte	SECT + 0x3

.rept	0x1f
.set SECT, SECT + 0x1000	/* 0x80_0000_0000 - 0xFFF_FFFF_FFFF */
.8byte	SECT + 0x3
.endr


	.section .mmu_tbl1,"a"

MMUTableL1:

.set SECT, MMUTableL2		/* 0x0000_0000 - 0x3FFF_FFFF */
.8byte	SECT + 0x3		/* 1GB DDR */

.rept	0x4			/* 0x4000_0000 - 0x1_3FFF_FFFF */
.set SECT, SECT + 0x1000	/*1GB DDR, 512MB LPD_AFI_FS, 448MB FPD_AFI_0, 512MB QSPI,
				  256MB PCIe region 0, PMC 128MB, GIC 1 MB, reserved 47MB,
				  2GB other devices and memory, 512 MB PMC */
.8byte	SECT + 0x3
.endr

.set SECT,0x140000000

.rept	0x3			/* 0x1_4000_0000 - 0x1_FFFF_FFFF */
.8byte	SECT + reserved		/* 3GB Reserved */
.set SECT, SECT + 0x40000000
.endr

.rept	0x4			/* 0x2_0000_0000 - 0x2_FFFF_FFFF */
.8byte	SECT + Device		/* 4GB ME Array 0-3*/
.set SECT, SECT + 0x40000000
.endr

.rept	0x4			/* 0x3_0000_0000 - 0x3_FFFF_FFFF */
.8byte	SECT + reserved		/* 4GB Reserved */
.set SECT, SECT + 0x40000000
.endr

.rept	0x10			/* 0x4_0000_0000 - 0x7_FFFF_FFFF */
.8byte	SECT + Device		/* 8GB PL - via PS, 8GB PCIe region1 */
.set SECT, SECT + 0x40000000
.endr

.set UNDEF_START, 0
#ifdef XPAR_AXI_NOC_DDR_LOW_1_BASEADDR
.set DDR_1_START, XPAR_AXI_NOC_DDR_LOW_1_BASEADDR
.set DDR_1_END, XPAR_AXI_NOC_DDR_LOW_1_HIGHADDR

.if DDR_1_START > DDR_LOW_1_REGION_START_ADDR
.set UNDEF_START, (DDR_1_START - DDR_LOW_1_REGION_START_ADDR)
.set UNDEF_START, (UNDEF_START)/0x40000000
.endif

.set DDR_1_SIZE, (DDR_1_END - DDR_1_START)+1
.if DDR_1_SIZE > 0x800000000
/* If DDR size is larger than 32GB, truncate to 32GB */
.set DDR_1_REG, 0x20
.else
.set DDR_1_REG, DDR_1_SIZE/0x40000000
.endif
#else
.set DDR_1_REG, 0
#warning "There's no DDR_1 in the HW design. MMU translation table marks 32 GB DDR address space as undefined"
#endif

.set UNDEF_1_REG, (0x20 - DDR_1_REG - UNDEF_START)

.rept	UNDEF_START				/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr

.rept	DDR_1_REG			/* DDR based on size in hdf*/
.8byte	SECT + Memory
.set	SECT, SECT+0x40000000
.endr

.rept	UNDEF_1_REG		/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr
.rept	0xC0			/* 0x10_0000_0000 - 0x3F_FFFF_FFFF */
.8byte	SECT + reserved		/* 192GB Reserved */
.set SECT, SECT + 0x40000000
.endr

.rept	0x100			/* 0x40_0000_0000 - 0x7F_FFFF_FFFF */
.8byte	SECT + Device		/* 256GB HBM 0-3*/
.set SECT, SECT + 0x40000000
.endr

.rept	0x100			/* 0x80_0000_0000 - 0xBF_FFFF_FFFF */
.8byte	SECT + Device		/* 256GB PCIe 2 */
.set SECT, SECT + 0x40000000
.endr

.set UNDEF_START, 0
#ifdef XPAR_AXI_NOC_DDR_LOW_2_BASEADDR
.set DDR_2_START, XPAR_AXI_NOC_DDR_LOW_2_BASEADDR
.set DDR_2_END, XPAR_AXI_NOC_DDR_LOW_2_HIGHADDR

.if DDR_2_START > DDR_LOW_2_REGION_START_ADDR
.set UNDEF_START, (DDR_2_START - DDR_LOW_2_REGION_START_ADDR)
.set UNDEF_START, (UNDEF_START)/0x40000000
.endif

.set DDR_2_SIZE, (DDR_2_END - DDR_2_START)+1
.if DDR_2_SIZE > 0x4000000000
/* If DDR size is larger than 256 GB, truncate to 256GB */
.set DDR_2_REG, 0x100
.else
.set DDR_2_REG, DDR_2_SIZE/0x40000000
.endif
#else
.set DDR_2_REG, 0
#warning "There's no DDR_LOW_2 in the HW design. MMU translation table marks 256 GB DDR address space as undefined"
#endif

.set UNDEF_2_REG, (0x100 - DDR_2_REG - UNDEF_START)

.rept	UNDEF_START				/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr

.rept	DDR_2_REG		/*  DDR based on size in hdf 0xC0_0000_0000 - 0xFF_FFFF_FFFF */
.8byte	SECT + Memory		/* Maximum DDR region size - 256GB */
.set SECT, SECT + 0x40000000
.endr

.rept	UNDEF_2_REG		/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr

.set UNDEF_START, 0
#ifdef XPAR_AXI_NOC_DDR_LOW_3_BASEADDR
.set DDR_3_START, XPAR_AXI_NOC_DDR_LOW_3_BASEADDR
.set DDR_3_END, XPAR_AXI_NOC_DDR_LOW_3_HIGHADDR

.if DDR_3_START > DDR_LOW_3_REGION_START_ADDR
.set UNDEF_START, (DDR_3_START - DDR_LOW_3_REGION_START_ADDR)
.set UNDEF_START, (UNDEF_START)/0x40000000
.endif

.set DDR_3_SIZE, (DDR_3_END - DDR_3_START)+1
.if DDR_3_SIZE > 0xB780000000
/* If DDR size is larger than 734 GB, truncate to 734GB */
.set DDR_3_REG, 0x2de
.else
.set DDR_3_REG, DDR_3_SIZE/0x40000000
.endif
#else
.set DDR_3_REG, 0
#warning "There's no DDR_LOW_3 in the HW design. MMU translation table marks 734 GB DDR address space as undefined"
#endif

.set UNDEF_3_REG, (0x2de - DDR_3_REG - UNDEF_START)

.rept	UNDEF_START				/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr

.rept	DDR_3_REG		/* DDR based on size in hdf 0x100_0000_0000 - 0x1B7_7FFF_FFFF */
.8byte	SECT + Memory		/* Maximum DDR region size - 734GB DDR */
.set SECT, SECT + 0x40000000
.endr

.rept	UNDEF_3_REG		/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr

.rept	0x122			/* 0x1B7_8000_0000 - 0x1FF_FFFF_FFFF */
.8byte	SECT + reserved		/* 290GB reserved */
.set SECT, SECT + 0x40000000
.endr

.rept	0x800			/* 0x200_0000_0000 - 0x3FF_FFFF_FFFF */
.8byte	SECT + Device		/* 2TB PL- via NoC */
.set SECT, SECT + 0x40000000
.endr

.rept	0x400			/* 0x400_0000_0000 - 0x4FF_FFFF_FFFF */
.8byte	SECT + Device		/* 1TB PL- via PS */
.set SECT, SECT + 0x40000000
.endr

.set UNDEF_START, 0
#ifdef XPAR_AXI_NOC_DDR_CH_1_BASEADDR
.set DDR_CH_1_START, XPAR_AXI_NOC_DDR_CH_1_BASEADDR
.set DDR_CH_1_END, XPAR_AXI_NOC_DDR_CH_1_HIGHADDR

.if DDR_CH_1_START > DDR_CH_1_REGION_START_ADDR
.set UNDEF_START, (DDR_CH_1_START - DDR_CH_1_REGION_START_ADDR)
.set UNDEF_START, (UNDEF_START)/0x40000000
.endif

.set DDR_CH_1_SIZE, (DDR_CH_1_END - DDR_CH_1_START)+1
.if DDR_CH_1_SIZE > 0x010000000000
/* If DDR size is larger than 1TB, truncate to 1 TB */
.set DDR_CH_1_REG, 0x400		/* 0x500_0000_0000 - 0x5FF_FFFF_FFFF */
.else
.set DDR_CH_1_REG, DDR_CH_1_SIZE/0x40000000
.endif
#else
.set DDR_CH_1_REG, 0
#warning "There's no DDR_CH_1 in the HW design. MMU translation table marks 1 TB DDR address space as undefined"
#endif

.set UNDEF_CH_1_REG, (0x400 - DDR_CH_1_REG - UNDEF_START)

.rept	UNDEF_START				/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr

.rept	DDR_CH_1_REG			/* DDR based on size in hdf, Max size 1 TB*/
.8byte	SECT + Memory
.set	SECT, SECT+0x40000000
.endr

.rept	UNDEF_CH_1_REG		/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr

.set UNDEF_START, 0
#ifdef XPAR_AXI_NOC_DDR_CH_2_BASEADDR
.set DDR_CH_2_START, XPAR_AXI_NOC_DDR_CH_2_BASEADDR
.set DDR_CH_2_END, XPAR_AXI_NOC_DDR_CH_2_HIGHADDR

.if DDR_CH_2_START > DDR_CH_2_REGION_START_ADDR
.set UNDEF_START, (DDR_CH_2_START - DDR_CH_2_REGION_START_ADDR)
.set UNDEF_START, (UNDEF_START)/0x40000000
.endif

.set DDR_CH_2_SIZE, (DDR_CH_2_END - DDR_CH_2_START)+1
.if DDR_CH_2_SIZE > 0x010000000000
/* If DDR_CH_2 size is larger than 1TB, truncate to 1 TB */
.set DDR_CH_2_REG, 0x400		/* 0x600_0000_0000 - 0x6FF_FFFF_FFFF */
.else
.set DDR_CH_2_REG, DDR_CH_2_SIZE/0x40000000
.endif
#else
.set DDR_CH_2_REG, 0
#warning "There's no DDR_CH_2 in the HW design. MMU translation table marks 1 TB DDR address space as undefined"
#endif

.set UNDEF_CH_2_REG, (0x400 - DDR_CH_2_REG - UNDEF_START)

.rept	UNDEF_START				/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr

.rept	DDR_CH_2_REG			/* DDR based on size in hdf, Max size 1 TB*/
.8byte	SECT + Memory
.set	SECT, SECT+0x40000000
.endr

.rept	UNDEF_CH_2_REG		/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr

.set UNDEF_START, 0
#ifdef XPAR_AXI_NOC_DDR_CH_3_BASEADDR
.set DDR_CH_3_START, XPAR_AXI_NOC_DDR_CH_3_BASEADDR
.set DDR_CH_3_END, XPAR_AXI_NOC_DDR_CH_3_HIGHADDR

.if DDR_CH_3_START > DDR_CH_3_REGION_START_ADDR
.set UNDEF_START, (DDR_CH_3_START - DDR_CH_3_REGION_START_ADDR)
.set UNDEF_START, (UNDEF_START)/0x40000000
.endif

.set DDR_CH_3_SIZE, (DDR_CH_3_END - DDR_CH_3_START)+1
.if DDR_CH_3_SIZE > 0x010000000000
/* If DDR_CH_3 size is larger than 1TB, truncate to 1 TB */
.set DDR_CH_3_REG, 0x400		/* 0x700_0000_0000 - 0x7FF_FFFF_FFFF */
.else
.set DDR_CH_3_REG, DDR_CH_3_SIZE/0x40000000
.endif
#else
.set DDR_CH_3_REG, 0
#warning "There's no DDR_CH_3 in the HW design. MMU translation table marks 1 TB DDR address space as undefined"
#endif

.set UNDEF_CH_3_REG, (0x400 - DDR_CH_3_REG - UNDEF_START)

.rept	UNDEF_START				/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr

.rept	DDR_CH_3_REG			/* DDR based on size in hdf, Max size 1 TB*/
.8byte	SECT + Memory
.set	SECT, SECT+0x40000000
.endr

.rept	UNDEF_CH_3_REG		/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x40000000
.endr


.rept	0x2000			/* 0x800_0000_0000 - 0xFFF_FFFF_FFFF */
.8byte	SECT + Device		/* 8TB PL- via NoC*/
.set SECT, SECT + 0x40000000
.endr

.section .mmu_tbl2,"a"

MMUTableL2:

.set SECT, 0

.set UNDEF_START, 0
#ifdef XPAR_AXI_NOC_DDR_LOW_0_BASEADDR
.set DDR_0_START, XPAR_AXI_NOC_DDR_LOW_0_BASEADDR
.set DDR_0_END, XPAR_AXI_NOC_DDR_LOW_0_HIGHADDR

.if DDR_0_START > DDR_LOW_0_REGION_START_ADDR
.set UNDEF_START, (DDR_0_START - DDR_LOW_0_REGION_START_ADDR)
.set UNDEF_START, (UNDEF_START)/0x200000
.endif

.set DDR_0_SIZE, (DDR_0_END - DDR_0_START)+1
.if DDR_0_SIZE > 0x80000000
/* If DDR size is larger than 2GB, truncate to 2GB */
.set DDR_0_REG, 0x400
.else
.set DDR_0_REG, DDR_0_SIZE/0x200000
.endif
#else
.set DDR_0_REG, 0
#warning "There's no DDR_0 in the HW design. MMU translation table marks 2 GB DDR address space as undefined"
#endif

.set UNDEF_0_REG, (0x400 - DDR_0_REG - UNDEF_START)

.rept	UNDEF_START				/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x200000
.endr

.rept	DDR_0_REG			/* DDR based on size in hdf*/
.8byte	SECT + Memory
.set	SECT, SECT+0x200000
.endr

.rept	UNDEF_0_REG		/* reserved for region where ddr is absent */
.8byte	SECT + reserved
.set	SECT, SECT+0x200000
.endr


.rept	0x0100			/* 0x8000_0000 - 0xBFFF_FFFF */
.8byte	SECT + Device		/* 512MB LPD AFI */
.set	SECT, SECT+0x200000
.endr

.rept	0x020			/* 0xA000_0000 - 0xA3FF_FFFF */
.8byte	SECT + reserved		/* 64MB reserved*/
.set	SECT, SECT+0x200000
.endr


.rept	0x60			/* 0xA400_0000 - 0xAFFF_FFFF */
.8byte	SECT + Device		/* 192MB FPD AFI 0 */
.set	SECT, SECT+0x200000
.endr

.rept	0x80			/* 0xB000_0000 - 0xBFFF_FFFF */
.8byte	SECT + Device		/* 192MB FPD AFI 1 */
.set	SECT, SECT+0x200000
.endr

.rept	0x100			/* 0xC000_0000 - 0xDFFF_FFFF */
.8byte	SECT + Device		/* 512MB QSPI */
.set	SECT, SECT+0x200000
.endr

.rept	0x080			/* 0xE000_0000 - 0xEFFF_FFFF */
.8byte	SECT + Device		/* 256MB lower PCIe */
.set	SECT, SECT+0x200000
.endr

.rept	0x040			/* 0xF000_0000 - 0xF7FF_FFFF */
.8byte	SECT + Device		/* 128MB PMC */
.set	SECT, SECT+0x200000
.endr

.rept	0x08			/* 0xF800_0000 - 0xF8FF_FFFF */
.8byte	SECT + Device		/* 16MB coresight */
.set	SECT, SECT+0x200000
.endr

/* 1MB GIC is marked for 2MB region as the minimum block size in
   translation table is 2MB and adjacent 47MB reserved region is
   converted to 46MB */
.8byte	SECT + Device		/* 0xF910_0000 - 0xF90F_FFFF */

/* Reserved 46MB  0xF91FFFFF - 0xFBFFFFFF*/
.rept	0x17			/* 0xF91F_FFFF - 0xFBFF_FFFF */
.set	SECT, SECT+0x200000
.8byte	SECT + reserved		/* 46MB reserved */
.endr

.rept	0x1F			/* 0xFC00_0000 - 0xFFDF_FFFF */
.set	SECT, SECT+0x200000
.8byte	SECT + Device		/* 16MB CPM,16MB FPS, 30MB LPS slaves */
.endr

.set	SECT, SECT+0x200000	/* 0xFFE0_0000 - 0xFFFF_FFFF*/
.8byte  SECT + Memory		/*2MB OCM/TCM*/

.rept	0x100			/* 0x1_0000_0000  - 0x1_1FFF_FFFF */
.set	SECT, SECT+0x200000
.8byte	SECT + Device		/* 512MB PMC 0-3 */
.endr

.rept	0x100			/* 0x1_2000_0000  - 0x1_3FFF_FFFF */
.set	SECT, SECT+0x200000
.8byte	SECT + reserved		/* 512MB reserved */
.endr
.end
#endif
/**
* @} End of "addtogroup a53_64_boot_code".
*/
