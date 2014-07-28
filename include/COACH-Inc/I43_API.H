#ifndef		__I43_API_H__
#define		__I43_API_H__

/********************************************************************
*	Main (and only) include that should be used in the all files    *
*	  that are part of I43 API. This include should also be			*
*		used in each file that calls to I43 API functions.			*
*																	*
*	Possible compiler definitions:									*
*	  I43OOP -	        the class CI43Api that incapsulates all 	*
*						the API functionality should be defined.	*
*						Use this definition when the multiinstance	*
*						support is need.							*
*	  DEFINE_VARS -		Create instance of internal API variables.	*
*						Should be declared in the one of API files.	*
********************************************************************/


#ifndef MODULE_TYPE

    #define PCI_VXD     0
    #define USB_DLL     1
    #define BASIC_API   2
    #define SIM_DLL     3
    #define UART_DLL    4
    #define HCE_API     5
    #define MODULE_TYPE USB_DLL

    #pragma message ("Compiling for BASIC API")

#endif  /* of ifndef MODULE_TYPE */


#ifndef LIB_TYPE

    #define I43APIDLL   1
    #define I43APILIB   2
    #define LIB_TYPE    I43APIDLL

    #pragma message ("Compiling for BASIC API functions")

#endif  /* of ifndef LIB_TYPE */



#define  CODE_SECT
#define  CODE_SECT_MORE_4_PARAMS

#define  DATA_SECT    


#if (MODULE_TYPE == PCI_VXD)
    #pragma message ("Compiled for PCI VxD")
    #include <vtoolscp.h>
    #include "Api_Def.h"		                /* General API definitions			*/
    #include "Common.h"		                    /* Common API functions				*/
    #include "..\Api_VxD\i2xio\cr0file.h"
#elif (MODULE_TYPE == BASIC_API)
    #include "Api_Def.h"		                /* General API definitions			*/
    #include "Common.h"		                    /* Common API functions				*/
#elif (MODULE_TYPE == USB_DLL)
    #if (LIB_TYPE == I43APIDLL)
        #pragma message ("Compiled for USB DLL")
    #elif (LIB_TYPE == I43APILIB)
        #pragma message ("Compiled for USB Static LIB")
    #endif
    #include <stdio.h>
    #include <stdarg.h>
    #include <windows.h>
    #include "Api_Def.h"		                /* General API definitions			*/
    #include "Common.h"		                    /* Common API functions				*/
    #include "ComType.h"
    #include "..\USBApi\Usb_def.h"
    #include "CMemPtr.h"
    #include "..\USBApi\CallSys.h"
#elif (MODULE_TYPE == SIM_DLL)
    #pragma message ("Compiled for SIM DLL")
    #include <stdio.h>
    #include <stdarg.h>
    #include <windows.h>
    #include "Api_Def.h"		                /* General API definitions			*/
    #include "Common.h"		                    /* Common API functions				*/
#elif (MODULE_TYPE == UART_DLL)
    #if (LIB_TYPE == I43APIDLL)
        #pragma message ("Compiled for UART DLL")
    #elif (LIB_TYPE == I43APILIB)
        #pragma message ("Compiled for UART Static LIB")
    #endif
    #include <stdio.h>
    #include <stdarg.h>
    #include <windows.h>
    #include "Api_Def.h"		                /* General API definitions			*/
    #include "Common.h"		                    /* Common API functions				*/
    #include "ComType.h"
    #include "..\USBApi\Usb_def.h"
    #include "..\UARTApi\UartHost.h"
    #include "CMemPtr.h"
#elif (MODULE_TYPE == HCE_API)
    #include "Coach.h"

	/* cancelation the default empty definition */
	#undef  CODE_SECT							
	#undef  DATA_SECT

    #define  CODE_SECT      __hce(API);
    #define  DATA_SECT      __cache(API)
    
    #include "Api_Def.h"		                /* General API definitions			*/
    #include "Usb_func.h"

    /* no debug functions in Coach */
    #undef   _I43_DEBUG_ 
    #undef   _DEBUG     
#endif

#ifdef _I43_DEBUG_
    #pragma message ("Compiled for DEBUG")
#endif


#ifdef	__cplusplus
	#ifndef	I43OOP
		#define	I43APICLASS
		extern "C" {
	#else
		#pragma	message ( "OBJECT ORIENTED compilation : CI43Api Class" )
		#define	I43APICLASS	CI43Api::
		class	CI43Api { public:
	#endif	/* I43OOP */
#else
	#define	I43APICLASS
#endif	/* __cplusplus */

/* API includes */
#include	"Api_func.h"	/* Application level API functions	*/
#include	"API_Vars.h"	/* Interal API variables			*/
#include	"Protocol.h"	/* Protocol level API function		*/
#include	"Private.h"	    /* Private API functions.			*/

/* Bus - depended includes */
#if (MODULE_TYPE == PCI_VXD)
    #include "IO_Level.h"
#elif (MODULE_TYPE == BASIC_API)
    #include "IO_Level.h"
#elif (MODULE_TYPE == USB_DLL)
    #include "..\USBApi\IO_Level.h"
    #include "..\USBApi\Usb_func.h"
#elif (MODULE_TYPE == SIM_DLL)
    /* nothing for now */
#elif (MODULE_TYPE == UART_DLL)
    #include "..\UARTApi\IO_Level.h"
    #include "..\UARTApi\UartFunc.h"
    #include "..\USBApi\Usb_func.h"
#elif (MODULE_TYPE == HCE_API)
    /* nothing for now */
#endif

#ifdef	__cplusplus
} ;
#endif	/* __cplusplus */

#endif	/* __I43_API_H__ */
