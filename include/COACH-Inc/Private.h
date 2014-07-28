#ifndef		_PRIVATE_H_
#define		_PRIVATE_H_

#ifndef	__I43_API_H__
	#error	This file should be used inside of I43_Api.h
#endif	/* __I43_API_H__ */

#if  ( LIB_TYPE!=I43APIDLL )
#pragma far_seg(__API_FAR_SECT_2)
#endif


/* ****************************************************************** */
/*                           GetAttributes                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*	pwSuccess - Tells if the operation completed successfully:        */
/*            0 -  Operation succeeded.                               */
/*            Other values - Operation failed.                        */
/*	pAttribute - Pointer to the Attribute sturcture.                  */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function is a helper function. it is used to save             */
/* redundancies in the code.                                          */
/* This function reads the success return value from the I43 and the  */
/* file attribute structure.                                          */
/* ****************************************************************** */
/* Used by functions:                                                 */
/*	I43_GetImageFileAttribute                                         */
/*	I43_GetFirstFileAttribute                                         */
/*	I43_GetNextFileAttribute                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS GetAttributes( I43_UINT16*  pwSuccess,
                                          FILE_ATTRIB* pAttribute
										) CODE_SECT;


#if  ( LIB_TYPE!=I43APIDLL )
#pragma far_seg
#endif

#endif	/*	_PRIVATE_H_  */

