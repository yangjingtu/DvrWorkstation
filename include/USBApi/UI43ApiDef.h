#ifndef __UI43ApiDEF_H__
#define __UI43ApiDEF_H__


#if (MODULE_TYPE == USB_DLL)

    #ifndef EXT_CLASS_UI43Api

		#ifdef NO_DLL
		   #define EXT_CLASS_UI43Api
		#else

			#ifdef _UI43Api_IMPL
			   #define EXT_CLASS_UI43Api  __declspec(dllexport)
			#else
			   #define EXT_CLASS_UI43Api  __declspec(dllimport)
			#endif // _UI43Api_IMPL
		#endif // NO_DLL

    #endif // EXT_CLASS_UI43Api

#else // (MODULE_TYPE == USB_DLL)

   #define EXT_CLASS_UI43Api

#endif // (MODULE_TYPE == USB_DLL)

#endif
