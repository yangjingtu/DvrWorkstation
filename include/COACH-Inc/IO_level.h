/* ****************************************************************** */
/*                             IO_level.h                             */
/* ****************************************************************** */
/* Copyright (c) 1997 ZORAN Corporation, All Rights Reserved          */
/* THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION               */
/*                                                                    */
/* ****************************************************************** */

#ifndef _IO_LEVEL_H_
#define _IO_LEVEL_H_

#ifndef __I43_API_H__
    #error  This file should be used inside of I43_Api.h
#endif  /* __I43_API_H__ */


/* ****************************************************************** */
/* This file defines the IO level functions prototypes.               */
/* These functions are used to translate the Protocol Level commands  */
/* to reads and writes from the host to the I43.                      */
/* ****************************************************************** */



/* ****************************************************************** */
/*                       I43IO_WriteWakeupByte                        */
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
/* ****************************************************************** */
I43_ERROR_CODE I43IO_WriteWakeupByte( void
                                    ) CODE_SECT;



/* ****************************************************************** */
/*                       I43IO_WriteCommand                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wCommand - The command op-code to be written to the I43.        */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function writes the given command op-code to the I43 Command  */
/* Register (CR).                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_WriteCommand( I43_UINT16 wCommand
                                 ) CODE_SECT;



/* ****************************************************************** */
/*                          I43IO_WriteDTR                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wData - The data to be written to the I43 Data Transfer Register.*/
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function writes the wData value to the I43 Data Transfer      */
/* Register.                                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_WriteDTR( I43_UINT16 wData
                             ) CODE_SECT;



/* ****************************************************************** */
/*                          I43IO_ReadDTR                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pwData - Pointer where to write the data read from the I43.     */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function reads the pwData value from the I43 Data Transfer    */
/* Register.                                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ReadDTR( I43_UINT16* pwData
                            ) CODE_SECT;



/* ****************************************************************** */
/*                          I43IO_ReadSR0Byte                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pbValue - Pointer where to write the read value from the I43.   */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function reads one byte from SR0 and writes it to the         */
/* location pointed by pbValue.                                       */
/* Note that this function reads only one byte form the I43 per call. */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ReadSR0Byte( I43_UINT8* pbValue
                                ) CODE_SECT;



/* ****************************************************************** */
/*                          I43IO_ReadSR0                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pwSR0 - Pointer where to write the read SR0 value from the I43. */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function reads the value of SR0 from the I43 and writes it    */
/* to the location pointed by pwSR0                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ReadSR0( I43_UINT16* pwSR0
                            ) CODE_SECT;



/* ****************************************************************** */
/*                          I43IO_ReadSR1                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pwSR1 - Pointer where to write the read SR1 value from the I43. */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function reads the value of SR1 from the I43 and writes it    */
/* to the location pointed by pwSR1                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ReadSR1( I43_UINT16* pwSR1
                            ) CODE_SECT;



/* ****************************************************************** */
/*                          I43IO_ReadSR2                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pwSR2 - Pointer where to write the read SR2 value from the I43. */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function reads the value of SR2 from the I43 and writes it    */
/* to the location pointed by pwSR2                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ReadSR2( I43_UINT16* pwSR2
                            ) CODE_SECT;



/* ****************************************************************** */
/*                            I43IO_Wait                              */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wDelay - Specifies the time, in 0.1 melliseconds, to wait.      */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function generates a delay, by not returning until wDelay     */
/* have past since it was called.                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_Wait( I43_UINT16 wDelay
                         ) CODE_SECT;



/* ****************************************************************** */
/*                         I43IO_ReadDataChunk                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wLocation   - Constant that tells the function from which memory*/
/*                  location to read the data chunk.                  */
/*    bFirstChunk - tells the function if this is the first chunk to  */
/*                  read from this location or not.                   */
/*    pwBuffer    - Buffer where to write the data that was read form */
/*                  the host memory.                                  */
/*    bSize       - The number of words to read.                      */
/*    pbLength    - The number of words returned.                     */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function reads bSize data words from a specific memory        */
/* location in the host memory (according to the wLocation parameter).*/
/* The bFirstChunk tells the function if to read the chunk from the   */
/* beginning of the memory buffer (defined by wLocation) or from the  */
/* current location of the buffer pointer. This enables the host to   */
/* read large buffers in small chunks.                                */
/* When less than bSize words are returned, it means that this is     */
/* the end of the buffer.                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ReadDataChunk( I43_MEMORY_LOCATION wLocation,
                                    I43_BOOL            bFirstChunk,
                                    I43_UINT16          pwBuffer[I43_CHUNK_SIZE],
                                    I43_UINT8           bSize,
                                    I43_UINT8*          pbLength
                                  ) CODE_SECT;



/* ****************************************************************** */
/*                         I43IO_WriteDataChunk                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wLocation   - Constant that tells the function to which memory  */
/*                  location to write the data chunk.                 */
/*    bFirstChunk - tells the function if this is the first chunk to  */
/*                  write to this location or not.                    */
/*    pwBuffer    - Buffer of the data to write to the host memory.   */
/*    bLength     - The number of words write.                        */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function writes one data chunk to a specific memory location  */
/* in the host memory (according to the wLocation parameter).         */
/* The bFirstChunk tells the function if to write the chunk to the    */
/* beginning of the memory buffer (defined by wLocation) or to the    */
/* current location of the buffer pointer. This enables the host to   */
/* write large buffers in small chunks.                               */
/* When a samller chunk then the chunk buffer size is written, it     */
/* means that this is the end of the buffer.                          */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_WriteDataChunk( I43_MEMORY_LOCATION wLocation,
                                     I43_BOOL            bFirstChunk,
                                     I43_UINT16          pwBuffer[I43_CHUNK_SIZE],
                                     I43_UINT8           bLength
                                   ) CODE_SECT;



/* ****************************************************************** */
/*                           I43IO_DbgPrint                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pszString - the string to print.                                */
/*    dwVAlue   - the value to print.                                 */
/* Return Value:                                                      */
/*    None.                                                           */
/* ****************************************************************** */
/* This function prints a debug message to the debug output.          */
/* The function prints the string and immidiately after that the      */
/* dwValue as a hexadecimal number.                                   */
/* ****************************************************************** */
#ifndef _I43_DEBUG_
    #define I43IO_DbgPrint(pszString, dwValue)
#else
    void I43IO_DbgPrint(char* pszString, I43_UINT32 dwValue);
#endif

#endif /* _IO_LEVEL_H_ */
