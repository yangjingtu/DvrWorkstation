/* ****************************************************************** */
/*                              Protocol.h                            */
/* ****************************************************************** */
/* Copyright (c) 1997 ZORAN Corporation, All Rights Reserved          */
/* THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION               */
/*                                                                    */
/* ****************************************************************** */

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#ifndef	__I43_API_H__
	#error	This file should be used inside of I43_Api.h
#endif	/* __I43_API_H__ */


#ifdef _I43_DEBUG_
#define CALL_AND_RETURN_ON_ERROR(function, szString)            \
    if (I43ERR_OK != (wErrorCode = (function)))                 \
    {                                                           \
        MyOutputDebugString("%s %d\n", (szString), wErrorCode); \
        return wErrorCode;                                      \
    }

#define DECLARE_ERRORCODE_VAR I43_ERROR_CODE wErrorCode;

#else /* _I43_DEBUG_ */

#define CALL_AND_RETURN_ON_ERROR(function, szString)    \
    if ((function))                                     \
    {                                                   \
        return I43ERR_UNKNOWN;                          \
    }

#define DECLARE_ERRORCODE_VAR


#endif


#define RETURN_ON_ERROR(szString, wErrorCode)      \
    if (I43ERR_OK != (wErrorCode))                 \
    {                                              \
        I43IO_DbgPrint((szString), (wErrorCode));  \
        return (wErrorCode);                       \
    }


/* ****************************************************************** */
/*                          I43PR_CheckSR2Flag                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wEvent - the flag to be checked.                                */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function polles the required flag for up to I43_POLL_TIMES    */
/* before returning a failior. If the flag is asserted before         */
/* I43_POLL_TIMES polls, the function returns immidately with a       */
/* success return value.                                              */
/* Between each poll this function wait for I43_POLL_WAIT micro       */
/* seconds.                                                           */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_CheckSR2Flag( I43_SR2_EVENT wEvent
                                 ) CODE_SECT;


/* ****************************************************************** */
/*                        I43PR_GetStatusRegister                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    bRegister - the register to be read.                            */
/*    pwValue   - the returned register value.                        */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function reads the value of the specified status register.    */
/* The read value is written to the pwValue operand.                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*    None.                                                           */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_GetStatusRegister( I43_STATUS_REGISTER bRegister,
                                        I43_UINT16*         pwValue
                                      ) CODE_SECT;


/* ****************************************************************** */
/*                       I43PR_SendCommandOpCode                      */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wHostCommand - The host command to be send to the I43.          */
/*    bLSByte      - The Less Segnificant Byte of the command OpCode. */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function checks if the mode allows the command and if so, it  */
/* constructs the opcode from the input parmetes and sends it to the  */
/* I43.                                                               */
/* The function polles the CA flag and when it is asserted, the       */
/* function sends the OpCode to the I43.                              */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_SendCommandOpCode( I43_HOST_COMMAND wHostCommand,
                                        I43_UINT8        bLSByte
                                      ) CODE_SECT;



/* ****************************************************************** */
/*                    I43PR_TransactionCompleted                      */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    None.                                                           */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sends the Transaction Completeed command to the I43. */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*    TransactionCompleted                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_TransactionCompleted( void
                                         ) CODE_SECT;


/* ****************************************************************** */
/*                       I43PR_WriteDataToI43                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pwBuffer - The buffer to be written to the I43 DTR.             */
/*    bLength  - The number of words in the buffer to write to the I43.*/
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function writes the specified number of words from the given  */
/* buffer to the I43 Data Transfer Register.                          */
/* Before each word is written the DIA flag is checked.               */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_WriteDataToI43( I43_UINT16* pwBuffer,
                                     I43_UINT8   bLength
                                   ) CODE_SECT;


/* ****************************************************************** */
/*                       I43PR_WriteChunkToI43                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pwBuffer - The buffer to be written to the I43 DTR.             */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function writes the buffer to the I43 Data Transfer Register  */
/* word by word without checking the DIA flag each time.              */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_WriteChunkToI43( I43_UINT16 pchBuffer[I43_CHUNK_SIZE]
                                    ) CODE_SECT;


/* ****************************************************************** */
/*                       I43PR_WriteBufferToI43                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wLocation         - Memory location of the buffer (predefined). */
/*    bFirstChunkLength - Length of the first chunk to read from the  */
/*                      memory location in order to fill up the first */
/*                      I43 FIFO after sending the Op-Code and other  */
/*                      parameters not included in the buffer.        */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function writes the buffer to the I43 Data Transfer Register. */
/* At first it writes chunks of IN FIFO size and when there are less  */
/* then a FIFO size words to write it writes the rest of the data     */
/* word by word.                                                      */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_WriteBufferToI43( I43_MEMORY_LOCATION wLocation,
                                       I43_UINT8           bFirstChunkLength
                                     ) CODE_SECT;


/* ****************************************************************** */
/*                        I43PR_ReadReturnValue                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pwValue - the returned value form the I43.                      */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function polles the RDC flag and when it is asserted, the     */
/* function reads the requested data from the I43.                    */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_ReadReturnValue( I43_UINT16* pwValue
                                    ) CODE_SECT;


/* ****************************************************************** */
/*                       I43PR_ReadDataFromI43                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pwBuffer - The buffer where to write the data read from I43 DTR.*/
/*    pbLength - The number of words read to the buffer from I43 DTR. */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function reads the specified number of words the I43 DTR.     */
/* The read words are written to the given buffer.                    */
/* Before the first word is read the RDC flag is checked.             */
/* Before every word is read the RDR flag is checked.                 */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_ReadDataFromI43( I43_UINT16* pwBuffer, 
                                      I43_UINT8*  pbLength
                                    ) CODE_SECT;


/* ****************************************************************** */
/*                       I43PR_ReadChunkFromI43                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pwBuffer - The buffer to be written to the I43 DTR.             */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function reads a buffer from the I43 Data Transfer Register   */
/* word by word without checking the RDR flag each time.              */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_ReadChunkFromI43( I43_UINT16 pwBuffer[I43_CHUNK_SIZE]
                                     ) CODE_SECT;


/* ****************************************************************** */
/*                       I43PR_ReadBufferFromI43                      */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wLocation - The memory location of the output buffer (predefined).*/
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function reads a buffer from the I43 Data Transfer Register.  */
/* At first it reads chunks of OUT FIFO size and when there are less  */
/* then a FIFO size words to read it reads the rest of the data       */
/* word by word.                                                      */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_ReadBufferFromI43( I43_MEMORY_LOCATION wLocation
                                      ) CODE_SECT;


/* ****************************************************************** */
/*                       I43PR_WriteWakeupByte                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    None.                                                           */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function writes ONE byte to the Reseverd Register (address    */
/* 0x01 of the host interface).                                       */
/* This write operation wakes up the I43 from power down mode.        */
/* Note: Use this command with caution. There is no way to syncronize */
/* the write operation if sychronization is lost.                     */
/* The right way to wake up the I43 will be to call this function once*/
/* and after that to call the I43PR_ReadSynchronize fucntion. When    */
/* the I43PR_ReadSynchronize returns, normal work with the I43 can    */
/* resume.                                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_WriteWakeupByte( void
                                    ) CODE_SECT;


/* ****************************************************************** */
/*                       I43PR_ReadSynchronize                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    None.                                                           */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function syncronizes the RD/WR operations of the COACH after  */
/* waking up from Power Down mode.                                    */
/* The function reads SR0 and check whether the bytes are reversed. if*/
/* so, it makes an additional write operation to the "Reserved" host  */
/* interface write register and then checks that the syncronization   */
/* is resumed.                                                        */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_ReadSynchronize( void
                                    ) CODE_SECT;


/* ****************************************************************** */
/*                              I43PR_Wait                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wDelay - The number of 0.1*Milli Seconds to wait                */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function generates a delay, by not returning until wDelay     */
/* Micro Seconds have past since it was called.                       */
/* ****************************************************************** */
I43_ERROR_CODE I43PR_Wait( I43_UINT16 wDelay
                         ) CODE_SECT;







/* ****************************************************************** */
/*                      Protocol Level Variables                      */
/* ****************************************************************** */

/* Global for Buffer Read/Write. */
I43EXTERN I43_UINT16    gpwChunkBuffer[I43_CHUNK_SIZE] DATA_SECT;

#if ((MODULE_TYPE != BASIC_API) && (MODULE_TYPE != HCE_API))
    /* Define a global array that will be a LUT for translation from 
       memory locations to file names.                                */
    I43EXTERN char MemoryLocationNames[NUMBER_OF_MEM_LOCATIONS][FILE_NAME_SIZE] DATA_SECT;
#endif

#if (MODULE_TYPE == PCI_VXD)

    /* Define an array that will be a LUT for translation from 
       memory locations to file Pointers.                              */
    I43EXTERN CAppendFile* FilePointers[NUMBER_OF_MEM_LOCATIONS]                DATA_SECT; 

#elif (MODULE_TYPE == USB_DLL)

    /* Global structure that holds the operation to send to the I43.
       Note that since we use this global, only one API call can be
       made at a time.                                               */
    I43EXTERN USB_CONTROL_OPERATION_BLOCK gCommandBuffer                        DATA_SECT;

    /* This counter counts the number of data bytes that were placed in 
       the command buffer data array for a write operation.              */
    I43EXTERN I43_UINT8 bWriteDataCount                                         DATA_SECT;

    /* This counter counts the number of data bytes that were read from 
       the command buffer data array for a read operation.              */
    I43EXTERN I43_UINT8 bReadDataCount                                          DATA_SECT;

    /* This global holds the current host command that is being processed. */
    I43EXTERN I43_HOST_COMMAND gCurrentHostCommand                              DATA_SECT;

    /* Define an array that will be a LUT for translation from 
       memory locations to file Pointers.                              */
    I43EXTERN FILE* FilePointers[NUMBER_OF_MEM_LOCATIONS]                       DATA_SECT; 

    /* Memory pointer managing class. */
    I43EXTERN CMemPtr MemPtrClass                                               DATA_SECT;

#elif (MODULE_TYPE == SIM_DLL)

    /* Define an array that will be a LUT for translation from 
       memory locations to file Pointers.                              */
    I43EXTERN FILE* FilePointers[NUMBER_OF_MEM_LOCATIONS]                       DATA_SECT; 

#elif (MODULE_TYPE == UART_DLL)

    //
    // Global buffer for holding immediate operands of the current command.
    // The extra two bytes are for the packet header.
    //
    I43EXTERN I43_UINT8    gbaPacketBuffer[2*I43_CHUNK_SIZE+PACKET_HEADER_SIZE] DATA_SECT;

    /* This counter counts the number of data bytes that were placed in 
       gbaPacketBuffer data array for a write operation.                       */
    I43EXTERN I43_UINT8 bWriteDataCount                                         DATA_SECT;

    /* This counter counts the number of data bytes that were read from 
       gbaPacketBuffer data array for a read operation.                        */
    I43EXTERN I43_UINT8 bReadDataCount                                          DATA_SECT;

    /* This global holds the current host command that is being processed.  */
    I43EXTERN I43_HOST_COMMAND gCurrentHostCommand                              DATA_SECT;

    /* Define an array that will be a LUT for translation from 
       memory locations to file Pointers.                                   */
    I43EXTERN FILE* FilePointers[NUMBER_OF_MEM_LOCATIONS]                       DATA_SECT; 

    /* Memory pointer managing class. */
    I43EXTERN CMemPtr MemPtrClass                                               DATA_SECT;

#elif (MODULE_TYPE == HCE_API)

    I43EXTERN bool bFirstRead                                                   DATA_SECT;
    
    I43EXTERN short* pwMemoryLocation                                           DATA_SECT;
    
    I43EXTERN ushort uwMemoryLocationSize                                       DATA_SECT;

#endif

#endif /* _PROTOCOL_H_ */

