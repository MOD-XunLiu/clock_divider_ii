/******************************************************************************
* Copyright (C) 2010 - 2021 Xilinx, Inc.  All rights reserved.
* Copyright (C) 2022 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/****************************************************************************/
/**
*
* @file xuartps_hw.c
* @addtogroup uartps Overview
* @{
*
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date	Changes
* ----- ------ -------- ----------------------------------------------
* 1.00	drg/jz 01/12/10 First Release
* 1.05a hk     08/22/13 Added reset function
* 3.00  kvn    02/13/15 Modified code for MISRA-C:2012 compliance.
* </pre>
*
*****************************************************************************/

/***************************** Include Files ********************************/
#include "xuartps_hw.h"

/************************** Constant Definitions ****************************/


/***************** Macros (Inline Functions) Definitions ********************/


/************************** Function Prototypes ******************************/


/************************** Variable Definitions *****************************/

/****************************************************************************/
/**
*
* This function sends one byte using the device. This function operates in
* polled mode and blocks until the data has been put into the TX FIFO register.
*
* @param	BaseAddress contains the base address of the device.
* @param	Data contains the byte to be sent.
*
* @return	None.
*
* @note		None.
*
*****************************************************************************/
void XUartPs_SendByte(u32 BaseAddress, u8 Data)
{
	/* Wait until there is space in TX FIFO */
	while (XUartPs_IsTransmitFull(BaseAddress)) {
		;
	}

	/* Write the byte into the TX FIFO */
	XUartPs_WriteReg(BaseAddress, XUARTPS_FIFO_OFFSET, (u32)Data);
}

/****************************************************************************/
/**
*
* This function receives a byte from the device. It operates in polled mode
* and blocks until a byte has received.
*
* @param	BaseAddress contains the base address of the device.
*
* @return	The data byte received.
*
* @note		None.
*
*****************************************************************************/
u8 XUartPs_RecvByte(u32 BaseAddress)
{
	u32 RecievedByte;
	/* Wait until there is data */
	while (!XUartPs_IsReceiveData(BaseAddress)) {
		;
	}
	RecievedByte = XUartPs_ReadReg(BaseAddress, XUARTPS_FIFO_OFFSET);
	/* Return the byte received */
	return (u8)RecievedByte;
}

/****************************************************************************/
/**
*
* This function resets UART
*
* @param	BaseAddress contains the base address of the device.
*
* @return	None
*
* @note		None.
*
*****************************************************************************/
void XUartPs_ResetHw(u32 BaseAddress)
{

	/* Disable interrupts */
	XUartPs_WriteReg(BaseAddress, XUARTPS_IDR_OFFSET, XUARTPS_IXR_MASK);

	/* Disable receive and transmit */
	XUartPs_WriteReg(BaseAddress, XUARTPS_CR_OFFSET,
				((u32)XUARTPS_CR_RX_DIS | (u32)XUARTPS_CR_TX_DIS));

	/*
	 * Software reset of receive and transmit
	 * This clears the FIFO.
	 */
	XUartPs_WriteReg(BaseAddress, XUARTPS_CR_OFFSET,
				((u32)XUARTPS_CR_TXRST | (u32)XUARTPS_CR_RXRST));

	/* Clear status flags - SW reset wont clear sticky flags. */
	XUartPs_WriteReg(BaseAddress, XUARTPS_ISR_OFFSET, XUARTPS_IXR_MASK);

	/*
	 * Mode register reset value : All zeroes
	 * Normal mode, even parity, 1 stop bit
	 */
	XUartPs_WriteReg(BaseAddress, XUARTPS_MR_OFFSET,
				XUARTPS_MR_CHMODE_NORM);

	/* Rx and TX trigger register reset values */
	XUartPs_WriteReg(BaseAddress, XUARTPS_RXWM_OFFSET,
				XUARTPS_RXWM_RESET_VAL);
	XUartPs_WriteReg(BaseAddress, XUARTPS_TXWM_OFFSET,
				XUARTPS_TXWM_RESET_VAL);

	/* Rx timeout disabled by default */
	XUartPs_WriteReg(BaseAddress, XUARTPS_RXTOUT_OFFSET,
				XUARTPS_RXTOUT_DISABLE);

	/* Baud rate generator and dividor reset values */
	XUartPs_WriteReg(BaseAddress, XUARTPS_BAUDGEN_OFFSET,
				XUARTPS_BAUDGEN_RESET_VAL);
	XUartPs_WriteReg(BaseAddress, XUARTPS_BAUDDIV_OFFSET,
				XUARTPS_BAUDDIV_RESET_VAL);

	/*
	 * Control register reset value -
	 * RX and TX are disable by default
	 */
	XUartPs_WriteReg(BaseAddress, XUARTPS_CR_OFFSET,
				((u32)XUARTPS_CR_RX_DIS | (u32)XUARTPS_CR_TX_DIS |
						(u32)XUARTPS_CR_STOPBRK));

}
/** @} */
