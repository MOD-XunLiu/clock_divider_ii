/******************************************************************************
* Copyright (c) 1995 - 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
*******************************************************************************/
 #ifndef XIL_PRINTF_H
 #define XIL_PRINTF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include "xil_types.h"
#include "xparameters.h"
#include "bspconfig.h"
#if defined (__aarch64__) && HYP_GUEST && EL1_NONSECURE && XEN_USE_PV_CONSOLE
#include "xen_console.h"
#endif

/*----------------------------------------------------*/
/* Use the following parameter passing structure to   */
/* make xil_printf re-entrant.                        */
/*----------------------------------------------------*/

struct params_s;


/*---------------------------------------------------*/
/* The purpose of this routine is to output data the */
/* same as the standard printf function without the  */
/* overhead most run-time libraries involve. Usually */
/* the printf brings in many kilobytes of code and   */
/* that is unacceptable in most embedded systems.    */
/*---------------------------------------------------*/

typedef char8* charptr;
typedef s32 (*func_ptr)(int c);

/*                                                   */

void xil_printf( const char8 *ctrl1, ...);
void xil_vprintf(const char8 *ctrl1, va_list argp);
void print( const char8 *ptr);
extern void outbyte (char c);
extern char inbyte(void);

#ifdef __cplusplus
}
#endif

#endif	/* end of protection macro */
