/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/****************************************************************************/
/**
*
* @file xscutimer.c
* @addtogroup scutimer_v2_4
* @{
*
* Contains the implementation of interface functions of the SCU Timer driver.
* See xscutimer.h for a description of the driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who Date     Changes
* ----- --- -------- ---------------------------------------------
* 1.00a nm  03/10/10 First release
* 2.1 	sk  02/26/15 Modified the code for MISRA-C:2012 compliance.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xscutimer.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/****************************************************************************/
/**
*
* Initialize a specific timer instance/driver. This function  must be called
* before other functions of the driver are called.
*
* @param	InstancePtr is a pointer to the XScuTimer instance.
* @param	ConfigPtr points to the XScuTimer configuration structure.
* @param	EffectiveAddress is the base address for the device. It could be
*		a virtual address if address translation is supported in the
*		system, otherwise it is the physical address.
*
* @return
*		- XST_SUCCESS if initialization was successful.
*		- XST_DEVICE_IS_STARTED if the device has already been started.
*
* @note		None.
*
******************************************************************************/
s32 XScuTimer_CfgInitialize(XScuTimer *InstancePtr,
			 XScuTimer_Config *ConfigPtr, u32 EffectiveAddress)
{
	s32 Status;
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(ConfigPtr != NULL);

	/*
	 * If the device is started, disallow the initialize and return a
	 * status indicating it is started. This allows the user to stop the
	 * device and reinitialize, but prevents a user from inadvertently
	 * initializing.
	 */
	if (InstancePtr->IsStarted != XIL_COMPONENT_IS_STARTED) {
		/*
		 * Copy configuration into the instance structure.
		 */
		InstancePtr->Config.DeviceId = ConfigPtr->DeviceId;

		/*
		 * Save the base address pointer such that the registers of the block
		 * can be accessed and indicate it has not been started yet.
		 */
		InstancePtr->Config.BaseAddr = EffectiveAddress;

		InstancePtr->IsStarted = (u32)0;

		/*
		 * Indicate the instance is ready to use, successfully initialized.
		 */
		InstancePtr->IsReady = XIL_COMPONENT_IS_READY;
#ifdef XIL_INTERRUPT
		InstancePtr->Config.IntrId = ConfigPtr->IntrId;
		InstancePtr->Config.IntrParent = ConfigPtr->IntrParent;
#endif

		Status =(s32)XST_SUCCESS;
	}
	else {
		Status = (s32)XST_DEVICE_IS_STARTED;
	}
	return Status;
}

/****************************************************************************/
/**
*
* Start the timer.
*
* @param	InstancePtr is a pointer to the XScuTimer instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void XScuTimer_Start(XScuTimer *InstancePtr)
{
	u32 Register;

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Read the contents of the Control register.
	 */
	Register = XScuTimer_ReadReg(InstancePtr->Config.BaseAddr,
				  XSCUTIMER_CONTROL_OFFSET);

	/*
	 * Set the 'timer enable' bit in the register.
	 */
	Register |= XSCUTIMER_CONTROL_ENABLE_MASK;

	/*
	 * Update the Control register with the new value.
	 */
	XScuTimer_WriteReg(InstancePtr->Config.BaseAddr,
			XSCUTIMER_CONTROL_OFFSET, Register);

	/*
	 * Indicate that the device is started.
	 */
	InstancePtr->IsStarted = XIL_COMPONENT_IS_STARTED;
}

/****************************************************************************/
/**
*
* Stop the timer.
*
* @param	InstancePtr is a pointer to the XScuTimer instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void XScuTimer_Stop(XScuTimer *InstancePtr)
{
	u32 Register;

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Read the contents of the Control register.
	 */
	Register = XScuTimer_ReadReg(InstancePtr->Config.BaseAddr,
				  XSCUTIMER_CONTROL_OFFSET);

	/*
	 * Clear the 'timer enable' bit in the register.
	 */
	Register &= (u32)(~XSCUTIMER_CONTROL_ENABLE_MASK);

	/*
	 * Update the Control register with the new value.
	 */
	XScuTimer_WriteReg(InstancePtr->Config.BaseAddr,
			XSCUTIMER_CONTROL_OFFSET, Register);

	/*
	 * Indicate that the device is stopped.
	 */
	InstancePtr->IsStarted = (u32)0;
}

/*****************************************************************************/
/**
*
* This function sets the prescaler bits in the timer control register.
*
* @param	InstancePtr is a pointer to the XScuTimer instance.
* @param	PrescalerValue is a 8 bit value that sets the prescaler to use.
*
* @return	None
*
* @note		None
*
****************************************************************************/
void XScuTimer_SetPrescaler(XScuTimer *InstancePtr, u8 PrescalerValue)
{
	u32 ControlReg;

	/*
	 * Assert to validate input arguments.
	 */
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	/*
	 * Read the Timer control register.
	 */
	ControlReg = XScuTimer_ReadReg(InstancePtr->Config.BaseAddr,
					XSCUTIMER_CONTROL_OFFSET);

	/*
	 * Clear all of the prescaler control bits in the register.
	 */
	ControlReg &= (u32)(~XSCUTIMER_CONTROL_PRESCALER_MASK);

	/*
	 * Set the prescaler value.
	 */
	ControlReg |= (((u32)PrescalerValue) << XSCUTIMER_CONTROL_PRESCALER_SHIFT);

	/*
	 * Write the register with the new values.
	 */
	XScuTimer_WriteReg(InstancePtr->Config.BaseAddr,
			  XSCUTIMER_CONTROL_OFFSET, ControlReg);
}

/*****************************************************************************/
/**
*
* This function returns the current prescaler value.
*
* @param	InstancePtr is a pointer to the XScuTimer instance.
*
* @return	The prescaler value.
*
* @note		None.
*
****************************************************************************/
u8 XScuTimer_GetPrescaler(XScuTimer *InstancePtr)
{
	u32 ControlReg;

	/*
	 * Assert to validate input arguments.
	 */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Read the Timer control register.
	 */
	ControlReg = XScuTimer_ReadReg(InstancePtr->Config.BaseAddr,
				    XSCUTIMER_CONTROL_OFFSET);
	ControlReg &= XSCUTIMER_CONTROL_PRESCALER_MASK;

	return (u8)(ControlReg >> XSCUTIMER_CONTROL_PRESCALER_SHIFT);
}
/** @} */
