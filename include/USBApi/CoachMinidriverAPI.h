#ifndef	__COACHMINIDRIVERAPI_H__
#define	__COACHMINIDRIVERAPI_H__

#ifndef __COMPILED_FOR_TWAIN__
//compiling for twain - no need for all this + it gives link errors
//what we do need is defined in the "#else"
#define	COACH_MAX_DATA_PIPE_PACKET			0x1000	// 4K packet length
#define MAX_CONTROL_PIPE_OPERATION_LENGTH	64		// Bytes length

enum	CoachCustomPropertiesSet
{
	KSPROPERTY_CUSTOM_STILL_CAPTURE_SEQUENCE_LENGTH,
	KSPROPERTY_CUSTOM_STILL_CAPTURE_BUFFER_STATUS,
	KSPROPERTY_CUSTOM_CONFIG_DESCRIPTOR,
	CUSTOM_PROPERTIES_TOTAL
} ;

struct STILL_CAPTURE_SEQUENCE_LENGTH_S
{
	ULONG		uLength	;
} ;

struct STILL_CAPTURE_BUFFER_STATUS_S
{
	PVOID		hActiveBuffer	;
	ULONG		uBytesWritten	;
} ;

typedef struct 
{
    KSPROPERTY	Property;
    USHORT		uData[0x12];                        // 12 = USB_DEVICE_DESCRIPTOR
} CUSTOM_CONFIG_DESCRIPTOR_S, *PCUSTOM_CONFIG_DESCRIPTOR_S;

// COACH Minidriver CLSID. Should be equal to one in COACH.INF
#define COACH_MINIDRIVER_CLSID	"{17CCA71B-ECD7-11D0-B908-00A0C9223196}"
DEFINE_GUID ( CLSID_CoachMinidriver,
			  0x17CCA71B, 0xECD7, 0x11D0, 0xB9, 0x08, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96
			)										;

// COACHCONTROLPIPE
DEFINE_GUID ( IID_CoachControlPipeIO,
			  0x43414F43, 0x4348, 0x4E4F, 0x54, 0x52, 0x4F, 0x4C, 0x50, 0x49, 0x50, 0x45
			)										;

// COACH DATA PIPE
DEFINE_GUID ( IID_CoachDataPipeIO,
			  0x43414F43, 0x2048, 0x4144, 0x54, 0x41, 0x20, 0x50, 0x49, 0x50, 0x45, 0x00
			)										;

// COACH MESSAGE PIPE
DEFINE_GUID ( IID_CoachMessagePipeIO,
			  0x43414F43, 0x2048, 0x4144, 0x54, 0x41, 0x20, 0x50, 0x49, 0x50, 0x45, 0x01
			)										;
	
//Adam 13/12/2001 - Add Driver Status Property
// COACH CONTROL PIPE STATUS 
// {77044BF9-3434-4465-AA34-CAF252269BA6}
DEFINE_GUID( IID_CoachDriverStatus, 
0x77044bf9, 0x3434, 0x4465, 0xaa, 0x34, 0xca, 0xf2, 0x52, 0x26, 0x9b, 0xa6);


#endif
//__COMPILED_FOR_TWAIN__
//we need thease things also for twain
// COACH CUSTOM PRP
DEFINE_GUID ( PROPSETID_CUSTOM_PROP,
			  0x43414F43, 0x2048, 0x5543, 0x53, 0x54, 0x4F, 0x4D, 0x20, 0x50, 0x52, 0x50
			)										;

#endif	// __COACHMINIDRIVERAPI_H__
