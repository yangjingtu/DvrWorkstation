/* ****************************************************************** */
/*                           I43swtch.h                               */
/* ****************************************************************** */
/* This module defines the I43 chiptest device IO control calls to    */
/* I43 API function calls.                                            */
/* ****************************************************************** */


#ifndef _I43SWTCH_H_
#define _I43SWTCH_H_

#include "I43_Api.h"


WORD __stdcall I43_Dispatch(DWORD     IoControlCode,
                      void*     pInBuffer,
                      DWORD     dwInBufferSize,
                      void*     pOutBuffer,
                      DWORD     dwOutBufferSize,
                      DWORD*    pdwBytesReturned);





#endif // _I43SWTCH_H_

