/* ****************************************************************** */
/*                             Api_def.h                              */
/* ****************************************************************** */
/* Copyright (c) 1997 ZORAN Corporation, All Rights Reserved          */
/* THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION               */
/*                                                                    */
/* ****************************************************************** */

#ifndef _API_DEF_H_
#define _API_DEF_H_

typedef char             I43_INT8;
typedef short            I43_INT16;
typedef long             I43_INT32;

typedef unsigned char    I43_UINT8;
typedef unsigned short   I43_UINT16;
typedef unsigned long    I43_UINT32;

#ifndef INT8
#define INT8  I43_INT8
#endif

#ifndef UINT8
#define UINT8  I43_UINT8
#endif

#ifndef INT16
#define INT16  I43_INT16
#endif

#ifndef UINT16
#define UINT16  I43_UINT16
#endif

#ifndef INT32
#define INT32  I43_INT32
#endif

#ifndef UINT32
#define UINT32 I43_UINT32
#endif

typedef enum _I43_BOOL
{
    I43_FALSE    = (unsigned char )0x0,
    I43_TRUE     = (unsigned char )0x1

} I43_BOOL;


typedef enum _I43_UINT2
{
    I43_UINT2_0                    = (char )0x00,
    I43_UINT2_1                    = (char )0x01,
    I43_UINT2_2                    = (char )0x02,
    I43_UINT2_3                    = (char )0x03

} I43_UINT2;


typedef enum _I43_UINT3
{
    I43_UINT3_0                    = (char )0x00,
    I43_UINT3_1                    = (char )0x01,
    I43_UINT3_2                    = (char )0x02,
    I43_UINT3_3                    = (char )0x03,
    I43_UINT3_4                    = (char )0x04,
    I43_UINT3_5                    = (char )0x05,
    I43_UINT3_6                    = (char )0x06,
    I43_UINT3_7                    = (char )0x07

} I43_UINT3;

typedef enum _I43_UINT4
{
    I43_UINT4_0                    = (char )0x00,
    I43_UINT4_1                    = (char )0x01,
    I43_UINT4_2                    = (char )0x02,
    I43_UINT4_3                    = (char )0x03,
    I43_UINT4_4                    = (char )0x04,
    I43_UINT4_5                    = (char )0x05,
    I43_UINT4_6                    = (char )0x06,
    I43_UINT4_7                    = (char )0x07,
    I43_UINT4_8                    = (char )0x08,
    I43_UINT4_9                    = (char )0x09,
    I43_UINT4_A                    = (char )0x0A,
    I43_UINT4_B                    = (char )0x0B,
    I43_UINT4_C                    = (char )0x0C,
    I43_UINT4_D                    = (char )0x0D,
    I43_UINT4_E                    = (char )0x0E,
    I43_UINT4_F                    = (char )0x0F

} I43_UINT4;

#define    I43HR_SR0                 0x00
#define    I43HR_SR1                 0x01
#define    I43HR_SR2                 0x02

typedef enum _I43_STATUS_REGISTER
{
    I43_STATUS_REG1        = 0x01,
    I43_STATUS_REG2        = 0x02

} I43_STATUS_REGISTER;



/* ****************************************************************** */
/*                   Status Register 1 values                         */
/* ****************************************************************** */

/* ****************************************************************** */
/*                    Status Register 1 Modes                         */
/* ****************************************************************** */
/* These values represent the deifferent states of the I43 state      */
/* machine (the values are taken from the I43 spec).                  */
/* ****************************************************************** */
typedef enum _I43_MODE
{
    I43_MENU_MODE                   = (unsigned char )0x00,
    I43_BOOT_MODE                   = (unsigned char )0x10,
    I43_POWER_DOWN_MODE             = (unsigned char )0x20,
    I43_IDLE_MODE                   = (unsigned char )0x30,
    I43_VIEW_MODE                   = (unsigned char )0x40,
    I43_CAPTURE_IMAGE_MODE          = (unsigned char )0x50,
    I43_CAPTURE_SEQUENCE_MODE       = (unsigned char )0x60,
    I43_VIDEO_CAPTURE_MODE          = (unsigned char )0x70,
    I43_STORE_IMAGE_FLASH_MODE      = (unsigned char )0x80,
    I43_RESTORE_IMAGE_FLASH_MODE    = (unsigned char )0x90,
    I43_RESTORE_IMAGE_THUMB_MODE    = (unsigned char )0x91,
    I43_CAPTURE_CLIP_MODE           = (unsigned char )0xA0,
    I43_CAPTURE_CLIP_VONLY_MODE     = (unsigned char )0xA1,
    I43_CAPTURE_CLIP_AONLY_MODE     = (unsigned char )0xA2,
    I43_PLAYBACK_IMAGE_MODE         = (unsigned char )0xC0,
    I43_RESTORE_THUMBNAILS_MODE     = (unsigned char )0xD0,
    I43_PLAYBACK_THUMBNAILS_MODE    = (unsigned char )0xE0,
    I43_CALIBRATION1_MODE           = (unsigned char )0xF0,
    I43_CALIBRATION2_MODE           = (unsigned char )0xF1,
    I43_CALIBRATION3_MODE           = (unsigned char )0xF2

} I43_MODE;

/* ****************************************************************** */
/*                    Status Register 1 Codes                         */
/* ****************************************************************** */
/* These values represent the different codes that may be in SR1.     */
/* ****************************************************************** */
typedef enum _I43_SR1_CODE
{
    I43SR1_NULL                     = (short )0x0000,
    I43SR1_SUCCESS                  = (short )0x0001,
    I43SR1_FAILURE                  = (short )0x0002,
    I43SR1_FILE_TRANSFER_BUSY       = (short )0x000A,
    I43SR1_FILE_TRANSFER_READY      = (short )0x000B,
    I43SR1_FILE_TRANSFER_ERROR      = (short )0x000C,
    I43SR1_FILE_NOT_FOUND           = (short )0x000D,
    I43SR1_NON_COMP_IMAGE_FILE      = (short )0x0010,
    I43SR1_NON_COMP_AUDIO_FILE      = (short )0x0011,
    I43SR1_RECORDING_AUDIO          = (short )0x0012,
    I43SR1_PLAYING_AUDIO            = (short )0x0013,
    I43SR1_ERASING_FILES            = (short )0x0014,
    I43SR1_NO_AUDIO_FILE            = (short )0x0016,
    I43SR1_RECOVER_POWERDOWN        = (short )0x0017,
    I43SR1_PROGRAM_CHECKSUM_ERROR   = (short )0x0018,
    I43SR1_I2C_TRANS_SUCCEEDED      = (short )0x0019,
    I43SR1_I2C_TRANS_FAILED         = (short )0x001A,
    I43SR1_SET_CUR_PATH_SUCCEEDED   = (short )0x001B,
    I43SR1_SET_CUR_PATH_FAILED      = (short )0x001C,

} I43_SR1_CODE;


/* ****************************************************************** */
/*                   Status Register 2 values                         */
/* ****************************************************************** */
/* These values represent the various events that may be reported     */
/* in status register 2.                                              */
/* ****************************************************************** */
typedef enum _I43_SR2_EVENT
{
    I43SR2_BOOT_PEND_AWB_CONVERGED  = (short )0x8000,
    I43SR2_FLASH_CARD_CHANGE        = (short )0x4000,
    I43SR2_FLASH_CARD_EXIST         = (short )0x2000,
    I43SR2_AE_CONVERGED_AUDIO_EXIST = (short )0x0400,
    I43SR2_FLASH_LIGHT_REQUIRED     = (short )0x0200,
    I43SR2_MODE_COMPLETED           = (short )0x0080,
    I43SR2_NEW_FRAME_PROCESSED      = (short )0x0040,
    I43SR2_NOT_ENOUGH_FLASH_MEMORY  = (short )0x0008,
    I43SR2_OPERATION_COMPLETE       = (short )0x0004,
    I43SR2_NOT_ENOUGH_AUDIO_DRAM    = (short )0x0002,
    I43SR2_FLASH_MEMORY_ERROR       = (short )0x0001,
    I43SR2_DIGITAL_ZOOM_COMPLETE    = (short )0x0001,    
    I43SR2_NO_EVENTS                = (short )0x0000

} I43_SR2_EVENT;


/* ****************************************************************** */
/*                        API Error Codes                             */
/* ****************************************************************** */
/* These values represent the different error codes that are used     */
/* in the API function.                                               */
/* ****************************************************************** */
typedef enum _I43_ERROR_CODE
{
    I43ERR_OK                       = (char )0x00,
    /* SR2 Error Code. */
    I43ERR_BOOT_AWB_NOT_ASSERTED    = (char )0x41,

    /* General Error Codes. */
    I43ERR_NOT_STATUS_REGISTER      = (char )0x51,
    I43ERR_MEMORY_LOCATION_ERROR    = (char )0x52,

    I43ERR_FAIL                     = (char )0xFE,
    I43ERR_UNKNOWN                  = (char )0xFF

} I43_ERROR_CODE;


/* ****************************************************************** */
/*                             Host Commands                          */
/* ****************************************************************** */
typedef enum _I43_HOST_COMMAND
{
    /* Special Processing-flow Control Commands. */
    I43HC_RESERVED_00               = (char )0x00,
    I43HC_TRANSACTION_COMPLETED     = (char )0x01,
    I43HC_TRANSACTION_ABORT         = (char )0x02,
    I43HC_GET_PARAM_LONG            = (char )0x03,
    I43HC_SET_PARAM_ARRAY           = (char )0x04,
    I43HC_GET_PARAM_ARRAY           = (char )0x05,
    I43HC_RESTORE_USP               = (char )0x06,
    I43HC_UPDATE_USP                = (char )0x07,
    I43HC_UPDATE_FSP                = (char )0x08,
    I43HC_REVERT_FSP                = (char )0x09,
    I43HC_GET_FREE_PARAMS           = (char )0x0A,
    I43HC_SET_FREE_PARAMS           = (char )0x0B,
    I43HC_SET_PARAM                 = (char )0x0C,
    I43HC_GET_PARAM                 = (char )0x0D,
    I43HC_SEND_HCE_MESSAGE          = (char )0x0E,
    I43HC_SET_TIMER                 = (char )0x0F,

    /* System Control and Configuration Commands. */
    I43HC_POWER_OFF                 = (char )0x10,
    I43HC_CONFIGSYS                 = (char )0x11,
    I43HC_CONFIG_UART               = (char )0x12,
    I43HC_RESERVED_13               = (char )0x13,
    I43HC_UART_LIB_CONFIG           = (char )0x14,
    I43HC_UART_LIB_READ             = (char )0x15,
    I43HC_UART_LIB_WRITE            = (char )0x16,
    I43HC_LOAD_AWB_CT_LUT           = (char )0x17,
    I43HC_SEND_I2C                  = (char )0x18,
    I43HC_GET_I2C                   = (char )0x19,
    I43HC_CONFIG_I2C_ACCESS         = (char )0x1A,
    I43HC_WRITE_I2C_BURST           = (char )0x1B,
    I43HC_READ_I2C_BURST            = (char )0x1C,
    I43HC_RESERVED_1D		        = (char )0x1D,
    I43HC_SET_WB_VALUES             = (char )0x1E,
    I43HC_SET_MODE                  = (char )0x1F,

    /* Image Processing Control Commands. */
    I43HC_SET_AE_MODE               = (char )0x20,
    I43HC_SET_MEAN_BLACK_NOISE      = (char )0x21,
    I43HC_ENABLE_ISSPU_BLOCK        = (char )0x22,
    I43HC_INIT_SENSOR               = (char )0x23,
    I43HC_SET_BLE                   = (char )0x24,
    I43HC_SET_EDGE_ENHANCEMENT      = (char )0x25,
    I43HC_SET_WHITE_BALANCE         = (char )0x26,
    I43HC_GET_WHITE_BALANCE         = (char )0x27,
    I43HC_CONFIG_AF                 = (char )0x28,
    I43HC_SET_ACTIVE_TABLE          = (char )0x29,
    I43HC_GET_AF_VALUE              = (char )0x2A,
    I43HC_RESERVED_2B               = (char )0x2B,
    I43HC_GET_LUMA_HISTOGRAM        = (char )0x2C,
    I43HC_GET_WEIGHTED_LUMA         = (char )0x2D,
    I43HC_GET_EXPOSURE_VALUE_STEP   = (char )0x2E,
    I43HC_SET_EXPOSURE_DEVIATION    = (char )0x2F,

    /* Display Control Commands. */
    I43HC_PLAYBACK_ZOOM             = (char )0x30,
    I43HC_LOAD_FONT_FILE            = (char )0x31,
    I43HC_TUNE_DISPLAY              = (char )0x32,
    I43HC_DISPLAY_WINDOW	        = (char )0x33,
    I43HC_CONFIG_IMAGE_RESIZE       = (char )0x34,
    I43HC_CONFIG_COUNTER            = (char )0x35,
    I43HC_SET_COUNTER               = (char )0x36,
    I43HC_SELECT_GPIO_EX            = (char )0x37,
    I43HC_CONFIG_GPIO_EX            = (char )0x38,
    I43HC_GET_GPIO_EX               = (char )0x39,
    I43HC_SET_GPIO_EX               = (char )0x3A,

    /* Graphic Commands. */
    I43HC_DRAW_TEXT                 = (char )0x3B,
    I43HC_DRAW_FILE                 = (char )0x3C,
    I43HC_SET_GDA                   = (char )0x3D,
    I43HC_DRAW_SHAPE                = (char )0x3E,
    I43HC_DRAW_TEXT_ID              = (char )0x3F,

    /* Thumbnail and OSD Commands. */
    I43HC_SENSOR_WINDOW_CONFIG      = (char )0x40,
    I43HC_CONFIG_THUMBNAIL          = (char )0x41,
    I43HC_THUMBNAIL_SHIFT_UP        = (char )0x42,
    I43HC_THUMBNAIL_SHIFT_DOWN      = (char )0x43,
    I43HC_GET_FIRST_THUMBNAIL       = (char )0x44,
    I43HC_SET_OSD_CLUT              = (char )0x45,
    I43HC_SET_IMAGE_SIZE            = (char )0x46,
    I43HC_SET_FORMAT_CONVERT        = (char )0x47,
    I43HC_CONFIG_SUB_WIN_AF         = (char )0x48,
    I43HC_GET_SUB_WIN_AF            = (char )0x49,
    I43HC_CONFIG_OSD_RECT           = (char )0x4A,
    I43HC_SET_OSD_RECT              = (char )0x4B,
    I43HC_SHOW_OSD_RECT             = (char )0x4C,
    I43HC_LOAD_STRING_FILE          = (char )0x4D,
    I43HC_SET_CHROMA_CORRECTION  	= (char )0x4E,
    I43HC_RESERVED_4F               = (char )0x4F,

    /* Audio Control Commands. */
    I43HC_CAPTURE_AUDIO_MESSAGE     = (char )0x50,
    I43HC_STOP_RECORDING            = (char )0x51,
    I43HC_AUDIO_CONFIG              = (char )0x52,
    I43HC_PLAYBACK_AUDIO_MESSAGE    = (char )0x53,
    I43HC_RECORD_PLAY_AUDIO         = (char )0x54,
    I43HC_BEEP                      = (char )0x55,
    I43HC_RESERVED_56               = (char )0x56,
    
	/* DPOF Commands. */
    I43HC_DPOF_ADD_JOB_A2C          = (char )0x57,	// A2C - API TO COACH
    I43HC_DPOF_ADD_JOB_C2A          = (char )0x58,  // C2A - COACH TO API
    I43HC_DPOF_READ_WRITE_FILE      = (char )0x59,
    I43HC_DPOF_RELEASE				= (char )0x5A,
    I43HC_DPOF_REMOVE_JOB			= (char )0x5B,
    I43HC_DPOF_GET_FIRST_JOB_IN_FILE= (char )0x5C,
    I43HC_DPOF_GET_NEXT_JOB_A2C     = (char )0x5D, // A2C - API TO COACH
    I43HC_DPOF_GET_NEXT_JOB_C2A     = (char )0x5E, // C2A - COACH TO API
    I43HC_DPOF_INIT                 = (char )0x5F,

    /* Image Sensor Control Commands. */
    I43HC_SET_PREVIEW_EXPOSURE      = (char )0x60,
    I43HC_SET_CAPTURE_EXPOSURE      = (char )0x61,
    I43HC_CONFIG_AE_PARAMS          = (char )0x62,
    I43HC_SET_CCD                   = (char )0x63,
    I43HC_GET_PREVIEW_EXPOSURE      = (char )0x64,
    I43HC_GET_CAPTURE_EXPOSURE      = (char )0x65,
    I43HC_SET_PREVIEW_EXP_LIMITS    = (char )0x66,
    I43HC_SET_CAPTURE_EXP_LIMITS    = (char )0x67,
    I43HC_PIP_MODE_ACTIVATE			= (char )0x68,
    I43HC_GET_DRAM_IMG_PARAMS		= (char )0x69,
    I43HC_SET_AWB_CTC               = (char )0x6A,
    I43HC_SET_AWB_WEIGHT_LUTS       = (char )0x6B,
    I43HC_PIP_LAYER_CREATE          = (char )0x6C,
    I43HC_PIP_LAYER_DESTROY         = (char )0x6D,
    I43HC_PIP_LAYER_SHOW            = (char )0x6E,
    I43HC_PIP_SET_ATTRIB            = (char )0x6F,

    /* Flash Light Control Commands. */
    I43HC_SENSOR_SHUTTER_CONFIG     = (char )0x70,
    I43HC_CONFIG_STROBE_PIN         = (char )0x71,
    I43HC_CONFIG_RED_EYE_REDUCTION  = (char )0x72,
    I43HC_ENABLE_RED_EYE_REDUCTION  = (char )0x73,
    I43HC_CONFIG_FLASH_TRIGGER      = (char )0x74,
    I43HC_SET_FLASH_TRIGGER         = (char )0x75,

    /* New OSD Commands */
    I43HC_SET_CUSTOM_EXPOSURE	    = (char )0x76,
    I43HC_SET_OSD_DISPLAY_ATTR      = (char )0x77,
    I43HC_OSD_DRAW_FILE             = (char )0x78,
    I43HC_OSD_DRAW_SHAPE            = (char )0x79,
    I43HC_OSD_TEXT_OUT_ID           = (char )0x7A,
    I43HC_OSD_TEXT_OUT              = (char )0x7B,
    I43HC_OSD_DRAW_TEXT_ID          = (char )0x7C,
    I43HC_OSD_DRAW_TEXT             = (char )0x7D,
    I43HC_DPOF_SET_HEADER_PARAM     = (char )0x7E,
    I43HC_DPOF_GET_HEADER_PARAM     = (char )0x7F,

    /* DPOF Commands - cont. */
    I43HC_DPOF_GET_PREV_JOB_A2C     = (char )0x80, // A2C - API TO COACH
    I43HC_DPOF_GET_PREV_JOB_C2A     = (char )0x81, // C2A - COACH TO API
    I43HC_DPOF_SET_JOB_PARAM_INT    = (char )0x82,
    I43HC_DPOF_GET_JOB_PARAM_INT_A2C= (char )0x83, // A2C - API TO COACH
    I43HC_DPOF_GET_JOB_PARAM_INT_C2A= (char )0x84, // C2A - COACH TO API
    I43HC_DPOF_SET_JOB_PARAM_STR    = (char )0x85,
    I43HC_DPOF_ADD_SRC_2_JOB_A2C    = (char )0x86, // A2C - API TO COACH
    I43HC_DPOF_ADD_SRC_2_JOB_C2A    = (char )0x87, // C2A - COACH TO API
    I43HC_DPOF_REMOVE_SRC           = (char )0x88,
    I43HC_DPOF_REMOVE_IMAGE         = (char )0x89,
    I43HC_DPOF_GET_IMAGE_DATA       = (char )0x8A,
    I43HC_DPOF_SET_SRC_PARAM        = (char )0x8B,
    I43HC_DPOF_GET_FIRST_SRC_A2C    = (char )0x8C,
    I43HC_DPOF_GET_FIRST_SRC_C2A    = (char )0x8D,
    I43HC_DPOF_GET_NEXT_SRC_A2C     = (char )0x8E,
    I43HC_DPOF_GET_NEXT_SRC_C2A     = (char )0x8F,

    /* File Transfer Commands. */
    I43HC_DPOF_GET_PREV_SRC_A2C     = (char )0x90,
    I43HC_DPOF_GET_PREV_SRC_C2A     = (char )0x91,
    I43HC_GET_VIDEO_CAP_IMAGE_SIZE  = (char )0x92,
    I43HC_XMT_FILE                  = (char )0x93,
    I43HC_RESERVED_94               = (char )0x94,
    I43HC_RCV_FILE                  = (char )0x95,
    I43HC_DPOF_GET_JOB_PARAM_STR	= (char )0x96,
    I43HC_DPOF_GET_SRC_PARAM		= (char )0x97,
    I43HC_GET_IMAGE					= (char )0x98,
    I43HC_RESERVED_99               = (char )0x99,
    I43HC_GET_VIDEO                 = (char )0x9A,
    I43HC_XMT_THUMBNAIL             = (char )0x9B,
    I43HC_RESERVED_9C               = (char )0x9C,
    I43HC_RESERVED_9D               = (char )0x9D,
    I43HC_RESERVED_9E               = (char )0x9E,
    I43HC_RESERVED_9F               = (char )0x9F,

    /* Storage Media management Commands. */
    I43HC_RESERVED_A0               = (char )0xA0,
    I43HC_RESERVED_A1               = (char )0xA1,
    I43HC_RESERVED_A2               = (char )0xA2,
    I43HC_RESERVED_A3               = (char )0xA3,
    I43HC_RESERVED_A4               = (char )0xA4,
    I43HC_RESERVED_A5               = (char )0xA5,
    I43HC_RESERVED_A6               = (char )0xA6,
    I43HC_RESERVED_A7               = (char )0xA7,
    I43HC_RESERVED_A8               = (char )0xA8,
    I43HC_RESERVED_A9               = (char )0xA9,
    I43HC_RESERVED_AA               = (char )0xAA,
    I43HC_SET_DCF_FREE_CHARS        = (char )0xAB,
    I43HC_SET_NEXT_DCF_KEY          = (char )0xAC,
    I43HC_GET_DCF_KEY               = (char )0xAD,
    I43HC_SET_FILE_TYPE             = (char )0xAE,
    I43HC_RESERVED_AF               = (char )0xAF,

    /* Storage Media management Commands. */
    I43HC_SET_STATISTICS_PATTERN    = (char )0xB0,
    I43HC_SET_FILE_NAME             = (char )0xB1,
    I43HC_SET_CURRENT_IMAGE         = (char )0xB2,
    I43HC_GET_CURRENT_IMAGE         = (char )0xB3,
    I43HC_RESERVED_B4               = (char )0xB4,
    I43HC_REGISTER_MEDIA            = (char )0xB5,
    I43HC_GET_STORAGE_MEDIA_STATUS  = (char )0xB6,
    I43HC_FORMAT_STORAGE_MEDIA      = (char )0xB7,
    I43HC_SET_CURRENT_PATH          = (char )0xB8,
    I43HC_GET_FILE_ATTRIBUTES       = (char )0xB9,
    I43HC_FILE_OPERATION            = (char )0xBA,
    I43HC_RESERVED_BB               = (char )0xBB,
    I43HC_GET_FIRST_FILE_ATTRIBUTE  = (char )0xBC,
    I43HC_GET_NEXT_FILE_ATTRIBUTE   = (char )0xBD,
    I43HC_RESERVED_BE               = (char )0xBE,
    I43HC_MOUNT_STORAGE_MEDIA       = (char )0xBF,

    /* System Calibration Commands. */
    I43HC_RESERVED_C0               = (char )0xC0,
    I43HC_RESERVED_C1               = (char )0xC1,
    I43HC_RESERVED_C2               = (char )0xC2,
    I43HC_RESERVED_C3               = (char )0xC3,
    I43HC_RESERVED_C4               = (char )0xC4,
    I43HC_RESERVED_C5               = (char )0xC5,
    I43HC_AUDIO_LOOP                = (char )0xC6,
    I43HC_RESERVED_C7               = (char )0xC7,
    I43HC_RESERVED_C8               = (char )0xC8,
    I43HC_RESERVED_C9               = (char )0xC9,
    I43HC_MOTOR_GO                  = (char )0xCA,
    I43HC_SET_CLOCK                 = (char )0xCB,
    I43HC_GET_CLOCK                 = (char )0xCC,
    I43HC_MOTOR_SET                 = (char )0xCD,
    I43HC_MOTOR_CONFIG              = (char )0xCE,

    /* HCE Commands. */
    I43HC_CONFIG_BUTTON_DRV         = (char )0xCF,

    /* USB Configuration & Protocol Commands. */
    I43HC_QUERY_STATUS              = (char )0xD0,
    I43HC_RESERVED_D1               = (char )0xD1,
    I43HC_USB_CONNECT               = (char )0xD2,
    I43HC_SET_USB_MODE              = (char )0xD3,
    I43HC_RESERVED_D4               = (char )0xD4,
    I43HC_RESERVED_D5               = (char )0xD5,
    I43HC_RESERVED_D6               = (char )0xD6,
    I43HC_RESERVED_D7               = (char )0xD7,
    I43HC_RESERVED_D8               = (char )0xD8,
    I43HC_RESERVED_D9               = (char )0xD9,
    I43HC_WAIT_HOST_COM_SEM         = (char )0xDA,
    I43HC_SIGNAL_HOST_COM_SEM       = (char )0xDB,
    I43HC_SET_HOST_COM_DATA         = (char )0xDC,
    I43HC_GET_HOST_COM_DATA         = (char )0xDD,
    I43HC_RESERVED_DE               = (char )0xDE,
    I43HC_PTP_CONTROL               = (char )0xDF,

    /* Capture and Compression Control Commands. */
    I43HC_PLAYBACK_CLIP_CMD         = (char )0xE0,
    I43HC_SET_COMPRESSION_RATIO     = (char )0xE1,
    I43HC_SET_SEQUENCE_LENGTH       = (char )0xE2,
    I43HC_GET_SEQUENCE_LENGTH       = (char )0xE3,
    I43HC_SET_IMAGE_EXIF            = (char )0xE4,
    I43HC_GET_IMAGE_EXIF            = (char )0xE5,
    I43HC_GET_IMAGE_ATTRIBUTES      = (char )0xE6,
    I43HC_RESERVED_E7               = (char )0xE7,
    I43HC_GET_IMAGE_EXIF_READ_COUNT = (char )0xE8,
    I43HC_GET_IMAGE_DATE_TIME       = (char )0xE9,
    I43HC_CONFIG_DRAM_CAPTURE       = (char )0xEA,
    I43HC_CONFIG_CAPTURE            = (char )0xEB,
    I43HC_CONFIG_N_IN_1_MODE        = (char )0xEC,
    I43HC_CONFIRM_STORE             = (char )0xED,
    I43HC_GET_CAPTURE_STATUS        = (char )0xEE,
    I43HC_MONITOR_CMD               = (char )0xEF,

    /* Debug Commands. */
    I43HC_WRITE_FLASH_BURST         = (char )0xF0,
    I43HC_CONFIG_HOST_MEM_ACCESS    = (char )0xF1,
    I43HC_SET_MEM                   = (char )0xF2,
    I43HC_GET_MEM                   = (char )0xF3,
    I43HC_DEBUG_OTR1                = (char )0xF4,
    I43HC_DEBUG_OTR2                = (char )0xF5,
    I43HC_DEBUG_OTR3                = (char )0xF6,
    I43HC_DEBUG_OTR4                = (char )0xF7,
    I43HC_GET_COACH_VERSION         = (char )0xF8,
    I43HC_UPGRADE_FLASH_FROM_CARD   = (char )0xF9,
    I43HC_SET_LONG                  = (char )0xFA,
    I43HC_RESERVED_FB               = (char )0xFB,
    I43HC_UPGRADE_WAV               = (char )0xFC,
    I43HC_EDIT_IMAGE                = (char )0xFD,
	I43HC_GET_LONG_A2C				= (char )0xFE,	// A2C - API TO COACH
    I43HC_GET_LONG_C2A			    = (char )0xFF,  // C2A - COACH TO API
    

} I43_HOST_COMMAND;


/* ****************************************************************** */
/*                           Memory Locations                         */
/* ****************************************************************** */
typedef enum _I43_MEMORY_LOCATION
{
    /* The program loaded to the I43 at I43_Initialize. */
    I43_PROGRAM_MEM_LOCATION        = (short )0x00,
    /* Place Holder. */
    I43_PLACE_HOLDER_01_MEM_LOCATION= (short )0x01,
        /* Place Holder. */
    I43_PLACE_HOLDER_02_MEM_LOCATION= (short )0x02,
    /* Place Holder. */
    I43_PLACE_HOLDER_03_MEM_LOCATION= (short )0x03,
    /* Place Holder. */
    I43_PLACE_HOLDER_04_MEM_LOCATION= (short )0x04,
    /* the strip to be written to the I43 by the I43_SetOSDStrip API. */
    I43_OSD_STRING_MEM_LOCATION     = (short )0x05,
    /* Place Holder. */
    I43_PLACE_HOLDER_06_MEM_LOCATION = (short )0x06,
    /* I43_SetCCD. */
    I43_CCD_TG_MEM_LOCATION         = (short )0x07,
    /* I43_UartLibWrite. */
    I43_UART_LIB_WRITE_MEM_LOCATION = (short )0x08,
    /* I43_UartLibRead. */
    I43_UART_LIB_READ_MEM_LOCATION  = (short )0x09,
    /* Place Holder. */
    I43_PLACE_HOLDER_0A_MEM_LOCATION= (short )0x0A,
    /* the array of parameters to be written using the I43_GetParamArray API. */
    I43_SET_PARAM_ARRAY_MEM_LOCATION = (short )0x0B,
    /* the array of parameters to read using the I43_GetParamArray API. */
    I43_GET_PARAM_ARRAY_MEM_LOCATION = (short )0x0C,
    /* I43_DPOFGetJobParamStr */
    I43_SET_DPOF_GET_JOB_PARAM_STR_MEM_LOCATION = (short )0x0D,
    /* the data to write to the I43 memory. */
    I43_SET_MEM_MEM_LOCATION        = (short )0x0E,
    /* the data to read from the I43 memory. */
    I43_GET_MEM_MEM_LOCATION        = (short )0x0F,
    /* the image read from the I43 DRAM using the I43_GetImage function. */
    I43_GET_IMAGE_MEM_LOCATION      = (short )0x10,
    /* I43_DPOFGetSrcParam */
    I43_SET_DPOF_GET_SRC_PARAM_MEM_LOCATION = (short )0x11,
    /* Place Holder. */
    I43_PLACE_HOLDER_12_MEM_LOCATION  = (short )0x12,
    /* the Time/Date information to write to the I43 (I43_SetDateTime). */
    I43_DATE_TIME_MEM_LOCATION      = (short )0x13,
    /* the data to be written to the flash memory using the I43_WriteFlashBurst API. */
    I43_FLASH_BURST_MEM_LOCATION    = (short )0x14,
    /* the Path to be set using the I43_SetCurrentPath API. */
    I43_CURRENT_PATH_MEM_LOCATION   = (short )0x15,
    /* Place Holder */
    I43_FLASH_BURST_STATUS_MEM_LOCATION = (short )0x16,
    /* the returned Luma Histogram from the I43_GetLumaHistogram API. */
    I43_LUMA_HISTOGRAM_MEM_LOCATION = (short )0x17,
    /* I43_DPOFGetHeaderParam */
    I43_SET_DPOF_GET_HEADER_PARAM_MEM_LOCATION = (short )0x18,
    /* the Time/Date information read from the I43 using the I43_GetImageDateTime API. */
    I43_GET_DATE_TIME_MEM_LOCATION  = (short )0x19,
    /* the parameters read from the I43 using the I43_GetFreeParams function. */
    I43_GET_FPARAMS_MEM_LOCATION    = (short )0x1A,
    /* the parameters written to the I43 using the I43_SetFreeParams function. */
    I43_SET_FPARAMS_MEM_LOCATION    = (short )0x1B,
    /* the AWB LUT written to the I43 using the I43_SetAWBWeightLUTs API. */
    I43_AWB_LUTS_MEM_LOCATION       = (short )0x1C,
    /* the file read from the I43 using the I43_XMTFile function. */
    I43_XMT_FILE_MEM_LOCATION       = (short )0x1D,
    /* the Thumbnails read from the I43 using the I43_XMTThumbnails function. */
    I43_XMT_THUMBNAIL_MEM_LOCATION  = (short )0x1E,
    /* the data that was read from the I43 using the I43_GetHostComData function. */
    I43_HOST_COM_READ_MEM_LOCATION  = (short )0x1F,
    /* the data to be written to the I43 using the I43_SetHostComData function. */
    I43_HOST_COM_WRITE_MEM_LOCATION = (short )0x20,
    /* the data to be written to the I43 using the I43_SetImageExif function. */
    I43_SET_EXIF_MEM_LOCATION       = (short )0x21,
    /* the data that was read from the I43 using the I43_GetImageExif function. */
    I43_GET_EXIF_MEM_LOCATION       = (short )0x22,
    /* placeholder */
    I43_PLACE_HOLDER_23_MEM_LOCATION = (short )0x23,
    /* the file to be uploaded to the I43. */
    I43_RCV_FILE_MEM_LOCATION       = (short )0x24,
    /* Place Holder. */
    I43_PLACE_HOLDER_25_MEM_LOCATION  = (short )0x25,
    /* Place Holder. */
    I43_PLACE_HOLDER_26_MEM_LOCATION  = (short )0x26,
    /* the strip to be written to the I43 by the I43_OSDTextOut API. */
    I43_OSD_TEXT_OUT_MEM_LOCATION   = (short )0x27,
    /* the strip to be written to the I43 by the I43_OSDDrawText API. */
    I43_OSD_DRAW_TEXT_MEM_LOCATION  = (short )0x28,
    /* the data to be written to the I43 by the I43_WriteI2CBurst API. */
    I43_WRITE_I2C_MEM_LOCATION      = (short )0x29,
    /* the data to be read from the I43 by the I43_ReadI2CBurst API. */
    I43_READ_I2C_MEM_LOCATION       = (short )0x2A,
    /* The text strip to be written to the I43 by the I43_DrawText API: */
    I43_DRAW_TEXT_MEM_LOCATION      = (short )0x2B,
	/* I43_GetSubWindowsAF. */
    I43_GET_SUBWIN_AF_MEM_LOCATION = (short )0x2C,
	/* I43_SetCustomExposure  */
	I43_SET_CUSTOM_EXPOSURE_MEM_LOCATION = (short )0x2D,

} I43_MEMORY_LOCATION;

#define NUMBER_OF_MEM_LOCATIONS         0x30
#define FILE_NAME_SIZE                  256

/* ****************************************************************** */
/*                         Global Enumerators                         */
/* ****************************************************************** */
typedef enum _I43_RGB
{
    I43_R                           = (short )0x0000,
    I43_G                           = (short )0x0001,
    I43_B                           = (short )0x0002

} I43_RGB;


typedef enum _I43_YUV
{
    I43_Y                           = (short )0x0000,
    I43_U                           = (short )0x0001,
    I43_V                           = (short )0x0002

} I43_YUV;


/* ****************************************************************** */
/*                     Config Auto Focus                              */
/* ****************************************************************** */
typedef enum _I43_CONFIG_AF
{
    I43CAF_SET_ROI                   = (char )0x00,    
    I43CAF_SET_THRESHOLDS            = (char )0x01,

} I43_CONFIG_AF;


typedef enum _I43_SUB_AF_MODE
{
	I43SAM_SET_MODE_SUM_OF_ABS_GRAD  = (char )0x00,
    I43SAM_SET_MODE_SUM_OF_ABS_DIFF  = (char )0x01,

} I43_SUB_AF_MODE;


typedef enum _I43_SUBWIN_AF
{
    I43SWAF_CLOSE_HIGH               = (char )0x00,
    I43SWAF_CLOSE_LOW                = (char )0x01,
    I43SWAF_FAR_HIGH                 = (char )0x02,
    I43SWAF_FAR_LOW                  = (char )0x03

} I43_SUBWIN_AF;

/* ****************************************************************** */
/*                         Display Modes                              */
/* ****************************************************************** */
typedef enum _I43_DISPLAY_MODE
{
    I43DM_DISABLE                   = (char )0x00,
    I43DM_IMAGE_ONLY                = (char )0x01,
    I43DM_OSD_ONLY                  = (char )0x02,
    I43DM_ENABLE                    = (char )0x03

} I43_DISPLAY_MODE;


/* ****************************************************************** */
/*                         Video Standards                            */
/* ****************************************************************** */
typedef enum _I43_VIDEO_STD
{
    I43VS_NTSC                      = (char )0x00,
    I43VS_PAL                       = (char )0x01

} I43_VIDEO_STD;


/* ****************************************************************** */
/*                           Video Formats                            */
/* ****************************************************************** */
typedef enum _I43_VIDEO_FORMAT
{
    I43VF_TV                        = (char )0x00,
    I43VF_EPSON_L2E1812B            = (char )0x04,
    I43VF_EPSON_LF18DB2             = (char )0x05,
    I43VF_CASIO_COM16T1151          = (char )0x06,
    I43VF_UNIPAC_UPS051             = (char )0x07,
    I43VF_UNIPAC_UPS052             = (char )0x08,
    I43VF_GIANTPLUS_GPG24163IS      = (char )0x09,

} I43_VIDEO_FORMAT;

/* ****************************************************************** */
/*                   Config Sys field enumarator                      */
/* ****************************************************************** */
#define I43_CONFIGSYS_VIDEO_DISPLAY     (char )0x0
#define I43_CONFIGSYS_VIDEO_OUT_FORMAT  (char )0x1
#define I43_CONFIGSYS_VIDEO_STANDARD    (char )0x2

/* ****************************************************************** */
/*                         Compression Ratios                         */
/* ****************************************************************** */
typedef enum _I43_COMPRESSION_RATIO
{
    I43CR_4_0                       = (short )0x0000,
    I43CR_4_5                       = (short )0x0001,
    I43CR_5_0                       = (short )0x0002,
    I43CR_5_5                       = (short )0x0003,
    I43CR_6_0                       = (short )0x0004,
    I43CR_6_5                       = (short )0x0005,
    I43CR_7_0                       = (short )0x0006,
    I43CR_7_5                       = (short )0x0007,
    I43CR_8_0                       = (short )0x0008,
    I43CR_8_5                       = (short )0x0009,
    I43CR_9_0                       = (short )0x000A,
    I43CR_9_5                       = (short )0x000B,
    I43CR_10_0                      = (short )0x000C,
    I43CR_12_0                      = (short )0x000D,
    I43CR_14_0                      = (short )0x000E,
    I43CR_16_0                      = (short )0x000F,
    I43CR_17_0                      = (short )0x0010,
    I43CR_18_0                      = (short )0x0011,
    I43CR_19_0                      = (short )0x0012,
    I43CR_20_0                      = (short )0x0013,
    I43CR_21_0                      = (short )0x0014,
    I43CR_22_0                      = (short )0x0015,
    I43CR_23_0                      = (short )0x0016,
    I43CR_24_0                      = (short )0x0017,
    I43CR_25_0                      = (short )0x0018,
    I43CR_26_0                      = (short )0x0019,
    I43CR_27_0                      = (short )0x001A,
    I43CR_28_0                      = (short )0x001B,
    I43CR_29_0                      = (short )0x001C,
    I43CR_30_0                      = (short )0x001D,
    I43CR_31_0                      = (short )0x001E,
    I43CR_32_0                      = (short )0x001F,
    I43CR_33_0                      = (short )0x0020,
    I43CR_34_0                      = (short )0x0021,
    I43CR_35_0                      = (short )0x0022,
    I43CR_36_0                      = (short )0x0023,
    I43CR_37_0                      = (short )0x0024,
    I43CR_38_0                      = (short )0x0025,
    I43CR_39_0                      = (short )0x0026,
    I43CR_40_0                      = (short )0x0027

} I43_COMPRESSION_RATIO;

/* ****************************************************************** */
/*                         Set Mean Black                             */
/* ****************************************************************** */
typedef enum _I43_TOP_COLOR {
        
    I43TC_FIRST_RED_THREE_COLORS    = (short) 0x0,
    I43TC_FIRST_GREEN_THREE_COLORS  = (short) 0x1,
    I43TC_FIRST_RED_TWO_COLORS      = (short) 0x2,
    I43TC_FIRST_GREEN_TWO_COLORS    = (short) 0x3
        
} I43_TOP_COLOR;

typedef struct _I43_SET_BLE {
        
        I43_UINT16       uwBleSide;
        I43_UINT16       uwBleTop;
        I43_UINT16       uwTopStartX;
        I43_UINT16       uwTopStartY;
        I43_UINT16       uwTopWidth;
        I43_UINT16       uwTopHeight;
        I43_TOP_COLOR    uwTopColor;
        I43_UINT16       uwSideStartX;
        I43_UINT16       uwSideWidth;
        I43_UINT16       uwBlcSideScale;
        I43_MODE         bMode;
        
} I43_SET_BLE;


/* ****************************************************************** */
/*                    Mean Black Noise Mode                           */
/* ****************************************************************** */
typedef enum _I43_BLACK_NOISE_MODE
{
    I43BNM_MANUAL_MODE              = (char )0x00,
    I43BNM_AUTO_MODE_RGB            = (char )0x01,
    I43BNM_AUTO_MODE_GREEN          = (char )0x02
} I43_BLACK_NOISE_MODE;

/* ****************************************************************** */
/*                   ISSPU Block ID                                   */
/* ****************************************************************** */
typedef enum _I43_BLOCK_ID
{
    I43BID_LENS_SHADING             = (char )0x02,
    I43BID_GAMMA_CORRECTION         = (char )0x03,
    I43BID_EDGE_ENHANCEMENT         = (char )0x04,
    I43BID_COLOR_LPF                = (char )0x05,
    I43BID_CCLK_GEN                 = (char )0x06
} I43_BLOCK_ID;

/* ****************************************************************** */
/*                      Image Quality LUT                             */
/* ****************************************************************** */
typedef enum _I43_TABLE_TYPE
{
    I43TT_GAMMA_LUT                 = (char )0x00,
    I43TT_NLGF_LUT                  = (char )0x01,
    I43TT_BRIGHTNESS_LUT            = (char )0x02,
    I43TT_LSC_LUT                   = (char )0x03,
	I43TT_LC_LUT                    = (char )0x04,
} I43_TABLE_TYPE;


/* ****************************************************************** */
/*                       White Balance Modes                          */
/* ****************************************************************** */
typedef enum _I43_WB_MODE
{
    I43WBM_MANUAL                   = (char )0x00,
    I43WBM_MANUAL_DAYLIGHT          = (char )0x01,
    I43WBM_MANUAL_DAYLIGHT_SCALE    = (char )0x21,
    I43WBM_MANUAL_OFFICE            = (char )0x02,
    I43WBM_MANUAL_OFFICE_SCALE      = (char )0x22,
    I43WBM_MANUAL_SUNSET            = (char )0x03,
    I43WBM_MANUAL_SUNSET_SCALE      = (char )0x23,
    I43WBM_MANUAL_FLASH             = (char )0x04,
    I43WBM_MANUAL_FLASH_SCALE       = (char )0x24,
    I43WBM_AUTO                     = (char )0x10,
    I43WBM_AUTO_RGB_CAPTURE         = (char )0x50,
    I43WBM_LOCKED                   = (char )0xFF

} I43_WB_MODE;

/* ****************************************************************** */
/*                     High Light Rectangles ID's                     */
/* ****************************************************************** */
typedef enum _I43_HL_RECT_ID
{
    I43HL_RECT_ID_0                 = (char )0x00,
    I43HL_RECT_ID_1                 = (char )0x01

} I43_HL_RECT_ID;


/* ****************************************************************** */
/*                 High Light Rectangles Blend Factor                 */
/* ****************************************************************** */
typedef enum _I43_HL_BF
{
    I43HL_RECT_OSD_ONLY             = (short )0x0000,
    I43HL_RECT_OSD_IMAGE_BLEND      = (short )0x4000

} I43_HL_BF;


/* ****************************************************************** */
/*                           Flash Polarity                           */
/* ****************************************************************** */
typedef enum _I43_FLASH_POLARITY
{
    I43FP_LOW                       = (short )0x0000,
    I43FP_HIGH                      = (short )0x0001

} I43_FLASH_POLARITY;


/* ****************************************************************** */
/*                         Flash Enable Flag                          */
/* ****************************************************************** */
#define I43FL_EABLE                 (short )0x0001
#define I43FL_DISABLE               (short )0x0000


/* ****************************************************************** */
/*                         Flash Operation Mode                       */
/* ****************************************************************** */
typedef enum _I43_FLASH_OP_MODE
{
    I43FOM_OFF                      = (char )0x00,
    I43FOM_AUTO                     = (char )0x01,
    I43FOM_FORCE_CAPTURE            = (char )0x02,

} I43_FLASH_OP_MODE;


/* ****************************************************************** */
/*                       Auto Exposure Operation Mode                 */
/* ****************************************************************** */
typedef enum _I43_AE_MODE
{
    I43AE_MASTER                    = (char )0x00,
    I43AE_ECC                       = (char )0x01,
    I43AE_ECONLY                    = (char )0x02

} I43_AE_MODE;

/* ****************************************************************** */
/*                       AGC Operation Mode                           */
/* ****************************************************************** */
typedef enum _I43_AGC_MODE
{
    I43AGC_AUTO                    = (char )0x00,
    I43AGC_MANUAL                  = (char )0x01,
    I43AGC_OFF                     = (char )0x02

} I43_AGC_MODE;

/* ****************************************************************** */
/*                       Playback Clip commands                       */
/* ****************************************************************** */
typedef enum _I43_PLAYBACK_CLIP_CMD
{
    I43PCC_PAUSE_AVI                = (char )0x01,
    I43PCC_RESUME_AVI               = (char )0x02,
    I43PCC_SLOW_MOTION_AVI          = (char )0x04,
    I43PCC_NEXT_IMAGE_AVI           = (char )0x05,
        I43PCC_PAUSE_WAV_OR_MP3         = (char )0x07,
    I43PCC_RESUME_WAV_OR_MP3        = (char )0x08,
        I43PCC_SEEK_TIME_WAV            = (char )0x09,
        I43PCC_SEEK_START_WAV           = (char )0x0A,
        I43PCC_SEEK_END_WAV             = (char )0x0B,
    I43PCC_STOP_WAV_OR_MP3          = (char )0x0C

} I43_PLAYBACK_CLIP_CMD;


/* ****************************************************************** */
/*                           UART baud rates                          */
/* ****************************************************************** */
typedef enum _I43_BAUD_RATE
{
    I43CBR_9600                = (char )0x00,
    I43CBR_14400               = (char )0x01,
    I43CBR_19200               = (char )0x02,
    I43CBR_38400               = (char )0x03,
    I43CBR_57600               = (char )0x04,
    I43CBR_115200              = (char )0x05

} I43_BAUD_RATE;


/* ****************************************************************** */
/*                           USB modes                                */
/* ****************************************************************** */
typedef enum _I43_USB_MODE
{
    I43USB_COACH_WDM_MODE      = (char )0x00,
    I43USB_CBI_STORAGE_MODE    = (char )0x03,
    I43USB_PTP_MODE            = (char )0x04,
    I43USB_MS_BULK_ONLY_MODE   = (char )0x05,

} I43_USB_MODE;

/* ****************************************************************** */
/*                            Host types                              */
/* ****************************************************************** */
typedef enum _I43_HOST
{
 
    I43HOST_USB                     = (char )0x01,
    I43HOST_UART                    = (char )0x02

} I43_HOST;


/* ****************************************************************** */
/*                         HCE definitions                            */
/* ****************************************************************** */
typedef enum _I43_BUTTON_CFG_TYPE
{
    I43BT_BUTTON_MASK               = (char )0x02,
    I43BT_PRESS_DELAY               = (char )0x03,
    I43BT_ADC_REPEAT_DELAY          = (char )0x05,
    I43BT_ADC_REPEAT_MASK           = (char )0x06,
    I43BT_GPIO_REPEAT_DELAY         = (char )0x07,
    I43BT_GPIO_REPEAT_MASK          = (char )0x08,
    I43BT_GPIO_REPEAT_POLARITY      = (char )0x09,
    I43BT_PWR_BUTTON_ENABLE         = (char )0x0a


} I43_BUTTON_CFG_TYPE;

/* ****************************************************************** */
/*                        DPOF definitions                            */
/* ****************************************************************** */
typedef enum _I43_DPOF_FILE_TYPE
{
    I43_DPOF_FILE_TYPE_ALL          = (char) 0x00,
    I43_DPOF_FILE_TYPE_PRINT        = (char) 0x01,
    I43_DPOF_FILE_TYPE_TRANSFER     = (char) 0x02,
    I43_DPOF_FILE_TYPE_SLIDESHOW    = (char) 0x03,

    I43_DPOF_FILE_TYPE_UNDEFINED
} I43_DPOF_FILE_TYPE;


typedef enum
{
    I43_DPOF_OP_SET,
    I43_DPOF_OP_GET
} I43_DPOF_OP;


typedef enum
{
    I43_DPOF_FILE_OP_LOAD      = (char) 0x00,
    I43_DPOF_FILE_OP_OVERLOAD,
    I43_DPOF_FILE_OP_WRITE
} I43_DPOF_FILE_OP;


typedef enum
{
    // GENeral Information
    I43_DPOF_HDR_PARAMID_REV = (char) 0x00,
    I43_DPOF_HDR_PARAMID_CRT,
    //// Date & Time
    I43_DPOF_HDR_PARAMID_DTM,

    // User Information
    //// User Name
    I43_DPOF_HDR_PARAMID_NAM_FAMILY,
    I43_DPOF_HDR_PARAMID_NAM_GIVEN,
    I43_DPOF_HDR_PARAMID_NAM_MIDDLE,
    //// Address
    I43_DPOF_HDR_PARAMID_ADR_COUNTRY,
    I43_DPOF_HDR_PARAMID_ADR_ZIP,
    I43_DPOF_HDR_PARAMID_ADR_STATE,
    I43_DPOF_HDR_PARAMID_ADR_CITY,
    I43_DPOF_HDR_PARAMID_ADR_ADDRESS,
    //// Tel
    I43_DPOF_HDR_PARAMID_TEL_COUNTRY,
    I43_DPOF_HDR_PARAMID_TEL_AREA,
    I43_DPOF_HDR_PARAMID_TEL_LOCAL,
    //// SIG - in Transfer file only
    I43_DPOF_HDR_PARAMID_SIGFILE
} I43_DPOF_HDR_PARAMID;


typedef enum _I43_DPOF_JOB_TYPE
{
    I43_DPOF_JOBTYPE_PRINT_STD  = (char) 0x01,
    I43_DPOF_JOBTYPE_PRINT_IDX  = (char) 0x02,
    I43_DPOF_JOBTYPE_PRINT_MUL  = (char) 0x03,
    I43_DPOF_JOBTYPE_PRINT_SIZ  = (char) 0x04,

    I43_DPOF_JOBTYPE_TRANSFER   = (char) 0x05,

    I43_DPOF_JOBTYPE_SLIDESHOW  = (char) 0x06,

    I43_DPOF_JOBTYPE_UNDEFINED,
} I43_DPOF_JOB_TYPE;



typedef enum _I43_DPOF_JOB_PARAMID
{
    /* common job parameters */
    /* read only patrameters */
    I43_DPOF_JOB_PARAMID_ID         = (char) 0x01,
    I43_DPOF_JOB_PARAMID_TYPE       = (char) 0x02,
    /*--------------------------------------------------*/
    /* print job parameters */
    I43_DPOF_JOB_PARAMID_QUANTITY   = (char) 0x04,
    I43_DPOF_JOB_PARAMID_NN         = (char) 0x09,
    I43_DPOF_JOB_PARAMID_SSSS       = (char) 0x0a,
/*    I43_DPOF_JOB_PARAMID_PSL        = (char) 0x0b,   // CURRENTLY NOT SUPPORTED */
    I43_DPOF_JOB_PARAMID_FAL        = (char) 0x0c,
    I43_DPOF_JOB_PARAMID_TRM        = (char) 0x0d,
    I43_DPOF_JOB_PARAMID_TRMX       = (char) 0x0e,
    I43_DPOF_JOB_PARAMID_TRMY       = (char) 0x0f,
    I43_DPOF_JOB_PARAMID_TRMW       = (char) 0x10,
    I43_DPOF_JOB_PARAMID_TRMH       = (char) 0x11,
    I43_DPOF_JOB_PARAMID_ROT        = (char) 0x12,

    /* transfer job parameters */
    /*--------------------------------------------------*/
    I43_DPOF_JOB_PARAMID_MSGTYPE    = (char) 0x13,
    I43_DPOF_JOB_PARAMID_MSG        = (char) 0x14,
    I43_DPOF_JOB_PARAMID_EML        = (char) 0x15,
    I43_DPOF_JOB_PARAMID_FAX        = (char) 0x16,
    I43_DPOF_JOB_PARAMID_MSGFILE    = (char) 0x17,
/*    I43_DPOF_JOB_PARAMID_DATFILE    = (char) 0x18, // CURRENTLY NOT SUPPORTED */

    /* side show job parameters */
    I43_DPOF_JOB_PARAM_TOPBOUND_SLIDESHOW       = (char) 0x19,
    /*-------------------------------------------------*/
    I43_DPOF_JOB_PARAMID_DUR        = (char) 0x1b,
    I43_DPOF_JOB_PARAMID_VIDFILE    = (char) 0x1c,
    I43_DPOF_JOB_PARAMID_SNDFILE    = (char) 0x1d,

    I43_DPOF_JOB_PARAMID_LAST
} I43_DPOF_JOB_PARAMID;


typedef enum
{
    I43_DPOF_SRC_PARAMID_DATE   = (char) 0x01,
    I43_DPOF_SRC_PARAMID_FID    = (char) 0x02,
    I43_DPOF_SRC_PARAMID_CMT    = (char) 0x03,
    
    I43_DPOF_SRC_PARAMID_UNDEFINED
} I43_DPOF_SRC_PARAMID;


typedef I43_UINT32 I43_DPOF_JOBID;
typedef I43_UINT32 I43_DPOF_SRCID;

/* FOR TRANSFER JOB */
#define I43_DPOF_TYP_MSG_TXT  0
#define I43_DPOF_TYP_MSG_HTM  1

/* MAXIMAL LENGTH OF LINE IN DPOF FILE */
#define I43_DPOF_MAX_LINE_LENGTH 635

#define I43_DPOF_DATE_SIZE		  14
#define I43_DPOF_JOB_PARAM_STR	  50
#define I43_DPOF_SRC_PARAM_STR	  14
#define I43_DPOF_HEADER_PARAM	  50
	
#define I43_DPOF_NO_DCF_FILE 0xFFFF

/* ****************************************************************** */
/*                     Storage Media Definitions                      */
/* ****************************************************************** */

/* ****************************************************************** */
/*           Storage Media directory attributes definitions           */
/* ****************************************************************** */
#define I43_DIR_OPEN_EXIST          (char )0x00
#define I43_DIR_CREATE              (char )0x02
#define I43_DIR_SET_ONLY            (char )0x04


/* ****************************************************************** */
/*              Storage Media Operation Scope Definitions             */
/* ****************************************************************** */
#define I43_SCOPE_FILE              (char )0x00
#define I43_SCOPE_DIR               (char )0x08
#define I43_SCOPE_DCF_OBJECT        (char )0x10


/* ****************************************************************** */
/*              Storage Media Operation Types Definitions             */
/* ****************************************************************** */
#define I43_FILE_OP_UNLOCK				0x00
#define I43_FILE_OP_LOCK				0x20
#define I43_FILE_OP_ERASE				0x40
#define I43_FILE_OP_COPY				0x60
#define I43_FILE_OP_MOVE				0x80
#define I43_FILE_OP_COPY_INTERDRIVE		0xA0
#define I43_FILE_OP_DELETE_ALL			0xC0
#define I43_FILE_OP_LOCK_ALL			0xE0
#define I43_FILE_OP_UNLOCK_ALL   		0x100

/* ****************************************************************** */
/*                 Get Storage Media Status Definitions               */
/* ****************************************************************** */
#define I43_STORAGE_MEDIA_STATUS     (char )0x00
#define I43_STORAGE_MEDIA_GEOMETRY   (char )0x01

/* ****************************************************************** */
/*                          Audio Loop Flag                           */
/* ****************************************************************** */
#define I43_AUDIO_LOOP_ON           (short )0x0001
#define I43_AUDIO_LOOP_OFF          (short )0x0000

/* ****************************************************************** */
/*                          Audio Record/Play Flag                    */
/* ****************************************************************** */
#define I43_AUDIO_RECORD            (short )0x0000
#define I43_AUDIO_PLAY_WAV          (short )0x0001
#define I43_AUDIO_PLAY_MP3          (short )0x0002

/* ****************************************************************** */
/*                          Memory Type Flag                          */
/* ****************************************************************** */
#define I43_RESIDENT_MEM            (unsigned char )0x00
#define I43_EXTENDED_MEM            (unsigned char )0x01


/* ****************************************************************** */
/*                             File Types                             */
/* ****************************************************************** */
#define I43_JPEG                    (short )0x0001
#define I43_TIFF                    (short )0x0002
#define I43_WAV                     (short )0x0004
#define I43_AVI                     (short )0x0008


/* ****************************************************************** */
/*                           Confirm Store                            */
/* ****************************************************************** */
#define I43_CSM_DELETE              (unsigned char )0x00
#define I43_CSM_STORE               (unsigned char )0x01


/* ****************************************************************** */
/*                          Config Capture                            */
/* ****************************************************************** */
#define I43_CC_HOLD_TIME            (unsigned char )0x00
#define I43_CC_RECORD_TYPE          (unsigned char )0x01
#define I43_CC_PRE_DELAY            (unsigned char )0x02
#define I43_CC_CLIP_TIME            (unsigned char )0x03
#define I43_CC_DATA_STAMP           (unsigned char )0x04
#define I43_CC_CLIP_RATE            (unsigned char )0x05
#define I43_CC_AUDIO_COMP_MODE      (unsigned char )0x06

/* ****************************************************************** */
/*           Access rights to shared memory definitions               */
/* ****************************************************************** */
#define I43HSM_ACCESS_DENIED        ((unsigned char) 0x00)
#define I43HSM_ACCESS_WRITE         ((unsigned char) 0x01)
#define I43HSM_ACCESS_READ          ((unsigned char) 0x02)

/* ****************************************************************** */
/*               Storage Media operation return values                */
/* ****************************************************************** */
/* The file does not exist, although the directory exist. */
#define I43_FL_FILE_NOT_FOUND       (short )0x0002
/* The directory specified does not exist. */
#define I43_FL_PATH_NOT_FOUND       (short )0x0003
/* The file is read only. */
#define I43_FL_NO_WRITE_ACCESS      (short )0x0005
/* The storage media is formated in an unknown format. */
#define I43_FL_NON_FAT_FORMAT       (short )0x000A
/* The storage media is formated in an unknown format. */
#define I43_FL_FORMAT_NOT_SUPPORTED (short )0x000B
/* Returned by I43_GetFirstFileAttribute or I43_GetNextFileAttribute
   when there are no more files in the directory scaned.              */
#define I43_FL_NO_MORE_FILES        (short )0x0012
/* It is not possible to write to the flash media. */
#define I43_FL_WRITE_PROTECT        (short )0x0013
/* Specified drive is invalid. */
#define I43_FL_BAD_DRIVE_HANDLE     (short )0x0014
/* Problems were found in the format of the media. */
#define I43_FL_BAD_FORMAT           (short )0x0017
#define I43_FL_UNKNOWN_MEDIA        (short )0x001A
/* FAT format is damaged. */
#define I43_FL_SECTOR_NOT_FOUND     (short )0x001B
/* FAT format is damaged. */
#define I43_FL_INVALID_FAT_CHAIN    (short )0x0035
/* The storage media was not mounted. */
#define I43_FL_NOT_MOUNTED          (short )0x0037
/* The specified file is NOT a directory. */
#define I43_FL_NOT_A_DIRECTORY      (short )0x0039
/* The specified directory to be erased is not empty. */
#define I43_FL_DIRECTORY_NOT_EMPTY  (short )0x003A
/* The specified file is a directory. */
#define I43_FL_FILE_IS_A_DIRECTORY  (short )0x003B

#define I43_FL_DCF_VALIDATE_FAIL    (short )0x0060

/* ****************************************************************** */
/*                    Set/Get memory supported types                  */
/* ****************************************************************** */
typedef enum _I43_MEM_TYPE
{
    I43_MEM_DRAM		= 0x00,
    I43_MEM_RESOURCE	= 0x01,
    I43_MEM_MEDIA		= 0x02,

} I43_MEM_TYPE;


/* ****************************************************************** */
/*                     Image Attributes definitions                   */
/* ****************************************************************** */
#define I43_ATTR_NONE               0x00
#define I43_ATTR_READ_ONLY          0x01
#define I43_ATTR_HIDDEN             0x02
#define I43_ATTR_SYSTEM             0x04
#define I43_ATTR_VOL_LABEL          0x08
#define I43_ATTR_DIRECTORY          0x10
#define I43_ATTR_ARCHIVE            0x20


/* ****************************************************************** */
/*                            GPIO definitions                        */
/* ****************************************************************** */

typedef enum {
    I43_XLGPIO                      = 0x00,
    I43_DVGPIO                      = 0x01,
    I43_FAGPIO                      = 0x02,
    I43_AUDGPIO                     = 0x03,
    I43_FDGPIO                      = 0x04,
    I43_FCGPIO                      = 0x05,
    I43_VIDGPIO                     = 0x06,
    I43_CCDGPIO                     = 0x07,
    I43_UARTGPIO                    = 0x08
} I43_GPIO_GROUP_TYPE;

typedef enum {
    I43_GPIO_FUNCTIONAL             = 0x00,
    I43_GPIO_GPIO                   = 0x40,
} I43_GPIO_FUNC_TYPE;

typedef enum {
    I43_GPIO_COUNTER_GCNT1          = 0x00,
    I43_GPIO_COUNTER_GCNT2          = 0x10,
    I43_GPIO_COUNTER_CCPWM1         = 0x20,
    I43_GPIO_COUNTER_CCPWM2         = 0x30,
} I43_GPIO_COUNTER_TYPE;

typedef enum {
    I43_MODE_DUTY_CYLE              = 0x00,
    I43_MODE_FREQUENCY              = 0x01,
    I43_MODE_SINGLE                 = 0x00,
    I43_MODE_CONTINUES              = 0x02,
} I43_COUNTER_MODE;

typedef enum {
    I43_COUNTER_DISABLE             = 0x00,
    I43_COUNTER_ENABLE              = 0x01,
} I43_COUNTER_STATUS;

typedef enum {
    I43_GPIO_CONFIG_OUT             = 0x00,
    I43_GPIO_CONFIG_IN              = 0x80
} I43_GPIO_CONFIG_TYPE;

typedef enum {
    I43_GPIO_PIN					= 0x00,
	I43_GPIO_GROUP					= 0x80,
} I43_GPIO_CLUSTERING_TYPE;

/* ****************************************************************** */
/*                    PIP functions definitions                       */
/* ****************************************************************** */
typedef enum {
    I43PIP_ATTR_TRANSPARENT         = 0x00,
    I43PIP_ATTR_EFFECT              = 0x01,
    I43PIP_ATTR_STEP                = 0x02,
    I43PIP_ATTR_CAPTURE_EFFECT      = 0x03,
    I43PIP_ATTR_CAPTURE_RECT        = 0x04,
    I43PIP_ATTR_GDI_LAYER           = 0x05
} I43PIP_ATTR_TYPE;

typedef enum {
    I43PIP_EFFECT_NORMAL            = 0x00,
    I43PIP_EFFECT_SPIN              = 0x01,
    I43PIP_EFFECT_FADE_OUT          = 0x02,
    I43PIP_EFFECT_FADE_IN           = 0x03,
    I43PIP_EFFECT_LEFT_PENETRATE    = 0x04,
    I43PIP_EFFECT_RIGHT_PENETRATE   = 0x05,
    I43PIP_EFFECT_SHRINK            = 0x06,
    I43PIP_EFFECT_LEFT_DEPART       = 0x07,
    I43PIP_EFFECT_RIGHT_DEPART      = 0x08
} I43PIP_EFFECT_TYPE;

typedef enum {
    I43PIP_MODE_PREVIEW             = 0x00,
    I43PIP_MODE_PLAYBACK            = 0x01
} I43PIP_MODE;

typedef enum {
    I43PIP_DISABLE_MODE            = 0x00,
    I43PIP_ENABLE_MODE             = 0x01,
    I43PIP_PAUSE_MODE              = 0x02
} I43PIP_ACTIVATE;

/* ****************************************************************** */
/*                    Graphic functions definitions                   */
/* ****************************************************************** */
typedef enum {
    I43GR_GDA_ATTR_TEXT_COLOR       = 0x00,
    I43GR_GDA_ATTR_BRUSH_COLOR      = 0x01,
    I43GR_GDA_ATTR_FONT_MAP         = 0x02,
    I43GR_GDA_ATTR_FONT_SIZE        = 0x03,
    I43GR_GDA_ATTR_FRAME_THICKNESS  = 0x04,
    I43GR_GDA_ATTR_BITMAP_TRANSPARENT_COLOR = 0x05,
    I43GR_GDA_ATTR_THUMBNAIL_SIZE   = 0x06
} I43GR_GDA_ATTR_TYPE;

typedef enum {
    I43GR_SHAPE_RECT                = 0x00,
    I43GR_SHAPE_RECT_FRAME          = 0x01
} I43GR_SHAPE_TYPE;

typedef enum {
    I43GR_OBJECT_BITMAP             = 0x00,
    I43GR_OBJECT_ICON               = 0x01,
    I43GR_OBJECT_JPEG               = 0x02,
    I43GR_OBJECT_TEXT               = 0x03,
    I43GR_OBJECT_BITMAP_TRANSPARENT = 0x04,
    I43GR_OBJECT_DCF_OBJECT         = 0x05,
} I43GR_OBJECT_TYPE;


/* ****************************************************************** */
/*                    OSD functions definitions                       */
/* ****************************************************************** */
typedef enum {
    I43OSD_ATTR_SHOW                = 0x00,
    I43OSD_ATTR_CENTER              = 0x01,
    I43OSD_ATTR_SCREEN_SIZE         = 0x02,
    I43OSD_ATTR_BITS_PER_PIXEL      = 0x03,
    I43OSD_ATTR_TEXT_COLOR          = 0x04,
    I43OSD_ATTR_TEXT_CLUT           = 0x05,
    I43OSD_ATTR_TEXT_SIZE           = 0x07,
    I43OSD_ATTR_TEXT_BK_MODE        = 0x08,
    I43OSD_ATTR_BRUSH_COLOR         = 0x09,
    I43OSD_ATTR_FRAME_THICKNESS     = 0x0A,
    I43OSD_ATTR_PROPORTIONAL_MODE   = 0x0B,
    I43OSD_ATTR_TEXT_SPACE          = 0x0C,
    I43OSD_ATTR_BITMAP_COLOR        = 0x0D,    
    I43OSD_ATTR_BITMAP_COLOR_2      = 0x0E    
} I43OSD_ATTR_TYPE;

typedef enum {
    I43OSD_OBJECT_BITMAP        = 0x00,
    I43OSD_OBJECT_ICON          = 0x01,
    I43OSD_OBJECT_RECT          = 0x02,
    I43OSD_OBJECT_RECT_FRAME    = 0x03

} I43OSD_OBJECT_TYPE;

#define    I43OSD_FLAG_LEFT     0x00000001L
#define    I43OSD_FLAG_RIGHT    0x00000002L
#define    I43OSD_FLAG_CENTER   0x00000004L
#define    I43OSD_FLAG_ERASE    0x00000008L
#define    I43OSD_FLAG_TOP      0x00000010L
#define    I43OSD_FLAG_BOTTOM   0x00000020L
#define    I43OSD_FLAG_VCENTER  0x00000040L



/* ****************************************************************** */
/*                        Timer API definitions                       */
/* ****************************************************************** */

typedef enum {
    I43TIC_STOP                     = 0x00,
    I43TIC_START                    = 0x10
} I43_TIMER_COMMAND;

/* ****************************************************************** */
/*                           Conversion format types                  */
/* ****************************************************************** */

typedef enum {
    I43CT_RGBTOYUV_STILL            = 1,
    I43CT_RGBTOYUV_BROWSE           = 2,
    I43CT_YUVTORGB_STILL            = 3,
    I43CT_YUVTORGB_DISPLAY          = 4

} I43_CONVERSION_TYPE;

/* ****************************************************************** */
/*                           Chroma Correction types                  */
/* ****************************************************************** */

typedef enum {

    I43CC_CORRECT            = 0,

} I43_CHROMA_CORRECTION_MODE;

/* ****************************************************************** */
/*                               Definitions                          */
/* ****************************************************************** */

/* The buffer size for chunk read and write operations. */
#define I43_CHUNK_SIZE              0x0020

/* ****************************************************************** */
/*                          API structures                            */
/* ****************************************************************** */
#if ((MODULE_TYPE != BASIC_API) && (MODULE_TYPE != HCE_API))
#include "..\inc\PSHPACK1.H"
#endif

typedef struct _THUMBNAIL_CONFIGURATION
{
    I43_UINT3 bThumbPerLine;        /* Number of thumbnails per line.                    */
    I43_UINT3 bThumbPerColumn;      /* Number of thumbnails per Column.                  */
    I43_UINT8 bFirstHGap;           /* The Horizontal gap size to the first thumbnail.   */
    I43_UINT8 bHGap;                /* The Horizontal gap size between thumbnails.       */
    I43_UINT8 bLastHGap;            /* The Horizontal gap size after the last thumbnail. */
    I43_UINT8 bFirstVGap;           /* The Vertical gap size to the first thumbnail.     */
    I43_UINT8 bVGap;                /* The Vertical gap  between thumbnail.              */
    I43_UINT8 bLastVGap;            /* The Vertical gap size after the last thumbnail.   */

} THUMBNAIL_CONFIGURATION;


typedef struct _HL_RECT_CONFIGURATION
{
    I43_HL_RECT_ID bRectID;         /*  bRectID - The current rect index (range 0-1).                     */
    I43_HL_BF      bBlendFactor;    /*  bBlendFactor - The current rect Blend Factor.                     */
                                    /*      I43HL_RECT_OSD_ONLY        = no blending (100% OSD).          */
                                    /*      I43HL_RECT_OSD_IMAGE_BLEND = 50% blending.                    */
    I43_UINT2      bInteriorColor;  /*  bInteriorColor - Color index of the interior color.               */
    I43_UINT2      bFrameColor;     /*  bFrameColor - Color index of the framework color.                 */
    I43_UINT8      bWidth;          /*  bWidth - The frame horizontal thickness, in pairs of pixels.      */
    I43_UINT8      bHeight;         /*  bHeight - The frame vertical thickness, in field lines.           */

} HL_RECT_CONFIGURATION;


typedef struct _HL_RECT_SETTINGS
{
    I43_HL_RECT_ID bRectID;         /*  bRectID - The current rect index (range 0-1).                     */
    I43_UINT16     wStartX;         /*  wStartX - The horizontal part of the upper left coordinate        */
                                    /*            of the rectangle, with respect to the active            */
                                    /*            display window.                                         */
    I43_UINT16     wStartY;         /*  wStartY - The vertical part of the upper left coordinate.         */
    I43_UINT16     wWidth;          /*  wWidth  - The horizontal length of the rectangle. must be even.   */
    I43_UINT16     wHeight;         /*  wHeight - The vertical length of the rectangle. must be even.     */

} HL_RECT_SETTINGS;


#if (MODULE_TYPE == HCE_API)
    #define ATT_FILE_NAME_SIZE	   7
	#define DRAW_FILE_NAME_SIZE	   20
	#define STATISTIC_PATTERN_SIZE 16
    #define SIZEOF_TO_WORDS_FACTOR 1
#else
    #define ATT_FILE_NAME_SIZE     14
	#define DRAW_FILE_NAME_SIZE	   40 
	#define STATISTIC_PATTERN_SIZE 32
    #define SIZEOF_TO_WORDS_FACTOR 2
#endif

typedef struct _FILE_ATTRIB
{
    char           name[ATT_FILE_NAME_SIZE];
    unsigned short attributes;
    long int       fileSize;
    unsigned short updateTime;
    unsigned short updateDate;

} FILE_ATTRIB;


typedef struct _FILE_ATTRIB_EXT
{
    unsigned short wSuccess;
	unsigned short Reserved ; // For Alignment

    FILE_ATTRIB    FileAttr;

} FILE_ATTRIB_EXT;


typedef struct _IMAGE_ATTRIBUTES
{
    I43_UINT16 wFlags;            /* Bit[15]:    Picture locked indication. 0-not locked, 1-locked.                 */
                                  /* Bit[14]:      Audio Exists. 0 - no, 1 - yes.                                     */
                                  /* Bit[13]:      Audio locked. 0- no, 1 - yes. Audio exists overrides audio locked. */
                                  /* Bit[12]:      Image was captured with flash. 0- no, 1-yes.                       */
                                  /* Bit[11]:      Thumbnail compressed. 0- no, 1-yes.                                */
                                  /* Bit[10]:      Captured By COACH (native file). 0- no, 1-yes.                     */
                                  /* Bits[9-8]:  Reserved.                                                          */
                                  /* Bits[7:0]:  image compressed bits / pixel.                                     */
    I43_UINT16 wImageHSize;       /* captured image horizontal size.             */
    I43_UINT16 wImageVSize;       /* captured image vertical size.               */
    I43_UINT16 wThumbnailSizeMS;  /* MS Word of thumbnail image size (in bytes). */
    I43_UINT16 wThumbnailSizeLS;  /* LS Word of thumbnail image size (in bytes). */
    I43_UINT16 wThumbnailHSize;   /* thumbnail horizontal size.                  */
    I43_UINT16 wThumbnailVSize;   /* thumbnail vertical size.                    */

} IMAGE_ATTRIBUTES;


typedef struct _I43_INPUT_IMAGE_CONFIG
{
    I43_MODE   bMode;             /* The COACH Operation Mode that the parameters refer to.  */
    I43_UINT16 wStartX;           /* First pixel of the input image with respect to the      */
                                  /* effective edge of HIS.                                  */
    I43_UINT16 wStartY;           /* First line of the input image (field in Interlaced      */
                                  /* sensors) with respect to the effective edge of VIS.     */
    I43_UINT16 wSizeX;            /* Number of pixels in one line of the input image.        */
    I43_UINT16 wSizeY;            /* Number of lines of the input image.                     */
    I43_UINT8  bHScaler;          /* VISM H scaler value.                                    */
    I43_UINT8  bVScaler;          /* VISM V scaler value.                                    */
                                  /* 0 - no scaling;                                         */
                                  /* 1 - no scaling;                                         */
                                  /* 2 - scale by 2;                                         */
                                  /*   .                                                     */
                                  /*   .                                                     */
                                  /* 8 - scale by 8.                                         */
                                  /* Values higher than 8 are reserved for both scalers.     */

} I43_INPUT_IMAGE_CONFIG;


typedef struct _I43_SENSOR_WINDOW_CONFIG
{
    I43_MODE   bMode;             /* The COACH Operation Mode that the parameters refer to.  */
    I43_UINT16 wStartX;           /* First pixel of the input image with respect to the      */
                                  /* active area.                                            */
    I43_UINT16 wStartY;           /* First line of the input image with respect to the       */
                                  /* active area.                                            */
    I43_UINT16 wSizeX;            /* Number of pixels in one line of the input image.        */
    I43_UINT16 wSizeY;            /* Number of lines of the input image.                     */

} I43_SENSOR_WINDOW_CONFIG;


typedef enum _I43_EDIT_IMAGE_OPERATION
{
        I43_EDIT_IMAGE_OPEN               = 0x0,
        I43_EDIT_IMAGE_CROP                    ,
        I43_EDIT_IMAGE_SCALE                   ,
        I43_EDIT_IMAGE_COMPRESS                ,
        I43_EDIT_IMAGE_SAVE_RESOURCE           ,
        I43_EDIT_IMAGE_DRAW_PIC                ,
        I43_EDIT_IMAGE_ROTATE                  ,
        I43_EDIT_IMAGE_SAVE_FILE               ,              
		I43_EDIT_IMAGE_DISPLAY				   ,
} I43_EDIT_IMAGE_OPERATION;

typedef struct _I43_EDIT_IMAGE_CONFIG_OPERATION
{
        I43_EDIT_IMAGE_OPERATION bOperation;
        I43_UINT16                               puwParam[4];
} I43_EDIT_IMAGE_CONFIG_OPERATION;


#if (MODULE_TYPE == HCE_API)
    #define MONITOR_CMD_LENGTH 32
#else
    #define MONITOR_CMD_LENGTH 64
#endif


typedef enum {
    I43OSD_SHAPE_RECT               = 0x00,
    I43OSD_SHAPE_RECT_FRAME         = 0x01,
    I43OSD_SHAPE_FILLED_RECT_FRAME  = 0x02,
    I43OSD_SHAPE_CIRCLE             = 0x03,
    I43OSD_SHAPE_FILLED_CIRCLE      = 0x04,
    I43OSD_SHAPE_ROUND_FRAME        = 0x05,
    I43OSD_SHAPE_FILLED_ROUND_FRAME = 0x06
} I43OSD_SHAPE_TYPE;

typedef enum {
    I43GR_FILE_JPEG                 = 0x00

} I43GR_FILE_TYPE;

typedef enum {
    I43OSD_FILE_BITMAP              = 0x00,

} I43OSD_FILE_TYPE;

#if ((MODULE_TYPE != BASIC_API) && (MODULE_TYPE != HCE_API))
#include "..\inc\POPPACK.H"
#endif


#endif /* _API_DEF_H_ */
