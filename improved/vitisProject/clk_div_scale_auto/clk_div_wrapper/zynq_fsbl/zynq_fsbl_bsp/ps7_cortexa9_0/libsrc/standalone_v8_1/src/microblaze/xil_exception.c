/******************************************************************************
* Copyright (c) 2009 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xil_exception.c
*
* This file contains implementation of exception related driver functions.
*
* @addtogroup microblaze_exception_apis Microblaze exception APIs
* @{
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  hbm  07/28/09 Initial release
* 6.2   ms   02/20/17 Fixed compilation warning. This is a fix for CR-969126.
* 8.0	sk   03/17/22 Delete MB_ExceptionVectorTableEntry structure to fix
* 		      misra_c_2012_rule_5_6 violation.
* 8.0	sk   03/17/22 Move MB_ExceptionVectorTableEntry and MB_InterruptVector
* 		      TableEntry decalrations to header files and delete
* 		      interrupts and excpetion disable and enable declarations
* 		      to fix misra_c_2012_rule_8_5 violations.
*
* </pre>
*
******************************************************************************/

#include "xil_types.h"
#include "xil_exception.h"

#include "microblaze_exceptions_g.h"
#include "microblaze_interrupts_i.h"
#include "microblaze_exceptions_i.h"
#include "mb_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *@cond nocomments
 */

/**
* Currently HAL is an augmented part of standalone BSP, so the old definition
* of MB_ExceptionVectorTableEntry is used here.
*/


#ifdef __cplusplus
}
#endif

/**
 * @endcond
 */

/************************** Variable Definitions *****************************/

/****************************************************************************/
/**
 * @brief   This function is a stub handler that is the default handler that gets
 *          called if the application has not setup a handler for a specific
 *          exception. The function interface has to match the interface
 *          specified for a handler even though none of the arguments are used.
 *
 * @param	Data: unused by this function.
 *
 *****************************************************************************/
static void Xil_ExceptionNullHandler(void *Data)
{
	(void) Data;
}

/****************************************************************************/
/**
* @brief   Initialize exception handling for the processor. The exception
*          vector table is setup with the stub handler for all exceptions.
*
*****************************************************************************/
void Xil_ExceptionInit(void)
{
	/*
	 * there is no need to setup the exception table here
	 */

}

/****************************************************************************/
/**
* @brief    Enable Exceptions.
*
******************************************************************************/
void Xil_ExceptionEnable(void)
{
#ifdef MICROBLAZE_EXCEPTIONS_ENABLED
	microblaze_enable_exceptions();
#endif
	microblaze_enable_interrupts();
}

/****************************************************************************/
/**
* @brief    Disable Exceptions.
*
******************************************************************************/
void Xil_ExceptionDisable(void)
{
#ifdef MICROBLAZE_EXCEPTIONS_ENABLED
	microblaze_disable_exceptions();
#endif
	microblaze_disable_interrupts();
}

/*****************************************************************************/
/**
*@brief     Makes the connection between the Id of the exception source and the
*           associated handler that is to run when the exception is recognized.
*           The argument provided in this call as the DataPtr is used as the
*           argument for the handler when it is called.
*
* @param    Id: contains the 32 bit ID of the exception source and should
*           be XIL_EXCEPTION_INT or be in the range of 0 to XIL_EXCEPTION_LAST.
*	        See xil_mach_exception.h for further information.
* @param    Handler: handler function to be registered for exception
* @param    Data: a reference to data that will be passed to the handler
*           when it gets called.
*
****************************************************************************/
void Xil_ExceptionRegisterHandler(u32 Id, Xil_ExceptionHandler Handler,
				  void *Data)
{
	if (Id == XIL_EXCEPTION_ID_INT) {
		MB_InterruptVectorTable[0].Handler = Handler;
		MB_InterruptVectorTable[0].CallBackRef = Data;
	}
	else {
#ifdef MICROBLAZE_EXCEPTIONS_ENABLED
		MB_ExceptionVectorTable[Id].Handler = Handler;
		MB_ExceptionVectorTable[Id].CallBackRef = Data;
#endif
	}
}


/*****************************************************************************/
/**
* @brief    Removes the handler for a specific exception Id. The stub handler
*           is then registered for this exception Id.
*
* @param    Id: contains the 32 bit ID of the exception source and should
*           be XIL_EXCEPTION_INT or in the range of 0 to XIL_EXCEPTION_LAST.
*	        See xexception_l.h for further information.
*
****************************************************************************/
void Xil_ExceptionRemoveHandler(u32 Id)
{
	if (Id == XIL_EXCEPTION_ID_INT) {
		MB_InterruptVectorTable[0].Handler = Xil_ExceptionNullHandler;
		MB_InterruptVectorTable[0].CallBackRef = NULL;
	}
	else {

#ifdef MICROBLAZE_EXCEPTIONS_ENABLED
		MB_ExceptionVectorTable[Id].Handler =
			Xil_ExceptionNullHandler;
		MB_ExceptionVectorTable[Id].CallBackRef = NULL;
#endif
	}
}
/**
* @} End of "addtogroup microblaze_exception_apis".
*/
