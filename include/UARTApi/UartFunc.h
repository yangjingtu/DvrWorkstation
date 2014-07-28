/* ****************************************************************** */
/*                            UartFunc.h                              */
/* ****************************************************************** */

#ifndef _UARTFUNC_H_
#define _UARTFUNC_H_



/* ****************************************************************** */
/*                         Functions prototype                        */
/* ****************************************************************** */
I43_ERROR_CODE Wait4Ack();

I43_ERROR_CODE SendACK();

I43_ERROR_CODE SendCommand(WORD wOpCode);

I43_ERROR_CODE SendCommandData(BYTE bPacketLength, I43_BOOL bLastPacket);

I43_ERROR_CODE GetReturnedData();


/* ****************************************************************** */
/*                         I43_MemCopySwap                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pSrc    - The source buffer.                                    */
/*    pDst    - The destination buffer.                               */
/*    bLength - The number of chars to copy.                          */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function copies the source buffer to the destination buffer   */
/* and switches the bytes in every word that is copeid.               */
/* ****************************************************************** */
I43_ERROR_CODE I43_MemCopySwap(I43_UINT8* pDst,
                               I43_UINT8* pSrc,
                               I43_UINT8  bLength);




#endif // _UARTFUNC_H_


