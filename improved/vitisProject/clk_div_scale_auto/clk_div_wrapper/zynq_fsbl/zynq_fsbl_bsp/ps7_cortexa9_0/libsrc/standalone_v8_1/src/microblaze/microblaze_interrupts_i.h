/******************************************************************************
* Copyright (c) 2008 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file microblaze_interrupts_i.h
*
* This header file contains identifiers and low-level driver functions (or
* macros) that can be used to access the device.  The user should refer to the
* hardware device specification for more details of the device operation.
* High-level driver functions are defined in xintc.h.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Date     Changes
* ----- -------- -----------------------------------------------
* 1.00b 10/03/03 First release
* 8.0	03/17/22 Add MB_InterruptVectorTableEntry decalration to
* 		 fix misra_c_2012_rule_8_5 violation.
* </pre>
*
******************************************************************************/

/**
 *@cond nocomments
 */

#ifndef MICROBLAZE_INTERRUPTS_I_H /* prevent circular inclusions */
#define MICROBLAZE_INTERRUPTS_I_H /* by using protection macros */

/***************************** Include Files *********************************/

#include "xil_types.h"
#include "xil_assert.h"
#include "xil_exception.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
   XInterruptHandler Handler;
   void *CallBackRef;
} MB_InterruptVectorTableEntry;

#define MB_INTERRUPT_VECTOR_TABLE_ENTRIES	1

extern MB_InterruptVectorTableEntry MB_InterruptVectorTable[MB_INTERRUPT_VECTOR_TABLE_ENTRIES];

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */

/**
 *@endcond
 */
