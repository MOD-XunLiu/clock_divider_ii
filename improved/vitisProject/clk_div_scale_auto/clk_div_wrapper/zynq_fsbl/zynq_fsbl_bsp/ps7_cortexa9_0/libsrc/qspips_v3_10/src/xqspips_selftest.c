/******************************************************************************
* Copyright (C) 2010 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xqspips_selftest.c
* @addtogroup qspips_v3_10
* @{
*
* This file contains the implementation of selftest function for the QSPI
* device.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who Date     Changes
* ----- --- -------- -----------------------------------------------
* 1.00  sdm 11/25/10 First release
* 2.01a sg  02/03/13 Delay Register test is added with DelayNss parameter.
* 3.1   hk  06/19/14 Remove checks for CR and ISR register values as they are
*                    reset in the previous step.
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xqspips.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
*
* Runs a self-test on the driver/device. The self-test is destructive in that
* a reset of the device is performed in order to check the reset values of
* the registers and to get the device into a known state.
*
* Upon successful return from the self-test, the device is reset.
*
* @param	InstancePtr is a pointer to the XQspiPs instance.
*
* @return
* 		- XST_SUCCESS if successful
*		- XST_REGISTER_ERROR indicates a register did not read or write
*		correctly.
*
* @note		None.
*
******************************************************************************/
int XQspiPs_SelfTest(XQspiPs *InstancePtr)
{
	int Status;
	u8 DelayTestNss;
	u8 DelayTestBtwn;
	u8 DelayTestAfter;
	u8 DelayTestInit;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Reset the QSPI device to leave it in a known good state
	 */
	XQspiPs_Reset(InstancePtr);

	DelayTestNss = 0x5A;
	DelayTestBtwn = 0xA5;
	DelayTestAfter = 0xAA;
	DelayTestInit = 0x55;

	/*
	 * Write and read the delay register, just to be sure there is some
	 * hardware out there.
	 */
	Status = XQspiPs_SetDelays(InstancePtr, DelayTestNss, DelayTestBtwn,
				DelayTestAfter, DelayTestInit);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	XQspiPs_GetDelays(InstancePtr, &DelayTestNss, &DelayTestBtwn,
				&DelayTestAfter, &DelayTestInit);
	if ((0x5A != DelayTestNss) || (0xA5 != DelayTestBtwn) ||
		(0xAA != DelayTestAfter) || (0x55 != DelayTestInit)) {
		return XST_REGISTER_ERROR;
	}

	Status = XQspiPs_SetDelays(InstancePtr, 0, 0, 0, 0);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	/*
	 * Reset the QSPI device to leave it in a known good state
	 */
	XQspiPs_Reset(InstancePtr);

	return XST_SUCCESS;
}
/** @} */
