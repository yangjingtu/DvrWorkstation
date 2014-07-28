#include "I43_API.h"

/* ****************************************************************** */
/*                           ComType.cpp                              */
/* ****************************************************************** */
/* This module implements the USB Command Info table as a global      */
/* table. Needed due to the addition of I43_TempChangeComTypeEntry    */
/* API, since this array is no longer a constant.                     */
/* ****************************************************************** */


USB_COMMAND_INFO UsbCommandArray[256] =
{

    /* Special Processing-flow Control Commands. */

    /* PlaceHolder                     = (char )0x00 */  {0, 0, -1},
    /* I43HC_TRANSACTION_COMPLETED     = (char )0x01 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_TRANSACTION_ABORT         = (char )0x02 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_GET_PARAM_LONG            = (char )0x03 */  {I43_WAIT   , I43_USB_READ , 4},
    /* I43HC_SET_PARAM_ARRAY           = (char )0x04 */  {I43_DELAY  , I43_USB_WRITE, 6},
    /* I43HC_GET_PARAM_ARRAY           = (char )0x05 */  {I43_WAIT   , I43_USB_WRITE, 6},
	/* I43HC_RESTORE_USP               = (char )0x06 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_UPDATE_USP                = (char )0x07 */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* I43HC_UPDATE_FSP                = (char )0x08 */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* I43HC_REVERT_FSP                = (char )0x09 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_GET_FREE_PARAMS           = (char )0x0A */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_SET_FREE_PARAMS           = (char )0x0B */  {I43_DELAY  , I43_USB_WRITE, 2},
    /* I43HC_SET_PARAM                 = (char )0x0C */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_GET_PARAM                 = (char )0x0D */  {I43_WAIT   , I43_USB_READ,  2},
    /* I43HC_SEND_HCE_MESSAGE          = (char )0x0E */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_SET_TIMER                 = (char )0x0F */  {I43_WAIT   , I43_USB_WRITE, 2},

    /* System Control and Configuration Commands. */

    /* I43HC_POWER_OFF                 = (char )0x10 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_CONFIGSYS                 = (char )0x11 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_CONFIG_UART               = (char )0x12 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* PlaceHolder                     = (char )0x13 */  {0, 0, -1},
    /* I43HC_UART_LIB_CONFIG           = (char )0x14 */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_UART_LIB_READ             = (char )0x15 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_UART_LIB_WRITE            = (char )0x16 */  {I43_DELAY,   I43_USB_WRITE, 2},
    /* I43HC_LOAD_AWB_CT_LUT           = (char )0x17 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_SEND_I2C                  = (char )0x18 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_GET_I2C                   = (char )0x19 */  {I43_WAIT   , I43_USB_READ,  2},
    /* I43HC_CONFIG_I2C_ACCESS         = (char )0x1A */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_WRITE_I2C_BURST           = (char )0x1B */  {I43_DELAY  , I43_USB_WRITE, 4},
    /* I43HC_READ_I2C_BURST            = (char )0x1C */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* PlaceHolder                     = (char )0x1D */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_SET_WB_VALUES             = (char )0x1E */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_SET_MODE                  = (char )0x1F */  {I43_NO_WAIT, I43_USB_WRITE, 0},

    /* Image Processing Control Commands. */

    /* I43HC_SET_AE_MODE               = (char )0x20 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_SET_MEAN_BLACK_NOISE      = (char )0x21 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_ENABLE_ISSPU_BLOCK        = (char )0x22 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_INIT_SENSOR               = (char )0x23 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_SET_BLE                   = (char )0x24 */  {I43_WAIT   , I43_USB_WRITE,22},
    /* I43HC_SET_EDGE_ENHANCEMENT      = (char )0x25 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_SET_WHITE_BALANCE         = (char )0x26 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_GET_WHITE_BALANCE         = (char )0x27 */  {I43_NO_WAIT, I43_USB_READ , 6},
    /* I43HC_CONFIG_AF                 = (char )0x28 */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_SET_ACTIVE_TABLE          = (char )0x29 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_GET_AF_VALUE              = (char )0x2A */  {I43_NO_WAIT, I43_USB_READ , 8},
    /* PlaceHolder                     = (char )0x2B */  {I43_WAIT   , I43_USB_WRITE,18},
    /* I43HC_GET_LUMA_HISTOGRAM        = (char )0x2C */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_GET_WEIGHTED_LUMA         = (char )0x2D */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* I43HC_GET_EXPOSURE_VALUE_STEP   = (char )0x2E */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* I43HC_SET_EXPOSURE_DEVIATION    = (char )0x2F */  {I43_NO_WAIT, I43_USB_WRITE, 0},

    /* Display Control Commands. */

    /* I43HC_PLAYBACK_ZOOM             = (char )0x30 */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_LOAD_FONT_FILE            = (char )0x31 */  {I43_WAIT   , I43_USB_WRITE,14},
    /* I43HC_TUNE_DISPLAY              = (char )0x32 */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_DISPLAY_WINDOW            = (char )0x33 */  {I43_WAIT   , I43_USB_WRITE,10},
    /* I43HC_CONFIG_IMAGE_RESIZE       = (char )0x34 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_CONFIG_COUNTER            = (char )0x35 */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_SET_COUNTER               = (char )0x36 */  {I43_NO_WAIT, I43_USB_WRITE, 0},

    /* Graphic Commands. */

    /* I43HC_SELECT_GPIO_EX            = (char )0x37 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_CONFIG_GPIO_EX            = (char )0x38 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_GET_GPIO_EX               = (char )0x39 */  {I43_WAIT   , I43_USB_READ , 2},
    /* I43HC_SET_GPIO_EX               = (char )0x3A */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_DRAW_TEXT                 = (char )0x3B */  {I43_DELAY  , I43_USB_WRITE, 4},
    /* I43HC_DRAW_FILE                 = (char )0x3C */  {I43_WAIT   , I43_USB_WRITE, DRAW_FILE_NAME_SIZE + 8},
    /* I43HC_SET_GDA                   = (char )0x3D */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_DRAW_SHAPE                = (char )0x3E */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_DRAW_TEXT_ID              = (char )0x3F */  {I43_WAIT   , I43_USB_WRITE, 6},

    /* Thumbnail and OSD Commands. */

	/* I43HC_SENSOR_WINDOW_CONFIG      = (char )0x40 */  {I43_WAIT   , I43_USB_WRITE,10},
    /* I43HC_CONFIG_THUMBNAIL          = (char )0x41 */  {I43_WAIT   , I43_USB_WRITE,16},
    /* I43HC_THUMBNAIL_SHIFT_UP        = (char )0x42 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_THUMBNAIL_SHIFT_DOWN      = (char )0x43 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_GET_FIRST_THUMBNAIL       = (char )0x44 */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* I43HC_SET_OSD_CLUT              = (char )0x45 */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_SET_IMAGE_SIZE            = (char )0x46 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_SET_FORMAT_CONVERT        = (char )0x47 */  {I43_WAIT   , I43_USB_WRITE, 24},
    /* I43HC_CONFIG_SUB_WIN_AF         = (char )0x48 */  {I43_WAIT   , I43_USB_WRITE, 14},
    /* I43HC_GET_SUB_WIN_AF			   = (char )0x49 */  {I43_NO_WAIT, I43_USB_WRITE ,0},
    /* I43HC_CONFIG_OSD_RECT           = (char )0x4A */  {I43_WAIT   , I43_USB_WRITE,10},
    /* I43HC_SET_OSD_RECT              = (char )0x4B */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_SHOW_OSD_RECT             = (char )0x4C */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_LOAD_STRING_FILE          = (char )0x4D */  {I43_WAIT   , I43_USB_WRITE,14},
    /* I43HC_SET_CHROMA_CORRECTION     = (char )0x4E */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* PlaceHolder                     = (char )0x4F */  {I43_NO_WAIT, I43_USB_WRITE, 0},

    /* Audio Control Commands. */

    /* I43HC_CAPTURE_AUDIO_MESSAGE     = (char )0x50 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_STOP_RECORDING            = (char )0x51 */  {I43_NO_WAIT, I43_USB_READ , 4},
	/* I43HC_AUDIO_CONFIG              = (char )0x52 */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_PLAYBACK_AUDIO_MESSAGE    = (char )0x53 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_GET_AUDIO_MESSAGE         = (char )0x54 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_BEEP                      = (char )0x55 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_RESERVED_56               = (char )0x56 */  {I43_NO_WAIT, I43_USB_WRITE, 0},

    /* DPOF Commands. */

    /* I43HC_DPOF_ADD_JOB_A2C          = (char )0x57 */  {I43_WAIT   , I43_USB_WRITE, I43_DPOF_DATE_SIZE+4},
    /* I43HC_DPOF_ADD_JOB_C2A          = (char )0x58 */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_DPOF_READ_WRITE_FILE      = (char )0x59 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_DPOF_RELEASE			   = (char )0x5A */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_DPOF_REMOVE_JOB		   = (char )0x5B */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_DPOF_GET_FIRST_JOB_IN_FILE= (char )0x5C */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_DPOF_GET_NEXT_JOB_A2C     = (char )0x5D */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_DPOF_GET_NEXT_JOB_C2A     = (char )0x5E */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_DPOF_INIT                 = (char )0x5F */  {I43_WAIT,    I43_USB_WRITE, 12},

    /* Image Sensor Control Commands. */

    /* I43HC_SET_PREVIEW_EXPOSURE      = (char )0x60 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_SET_CAPTURE_EXPOSURE      = (char )0x61 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_CONFIG_AE_PARAMS          = (char )0x62 */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_SET_CCD                   = (char )0x63 */  {I43_DELAY  , I43_USB_WRITE, 0},
    /* I43HC_GET_PREVIEW_EXPOSURE      = (char )0x64 */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* I43HC_GET_CAPTURE_EXPOSURE      = (char )0x65 */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* I43HC_SET_PREVIEW_EXP_LIMITS    = (char )0x66 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_SET_CAPTURE_EXP_LIMITS    = (char )0x67 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_PIP_MODE_ACTIVATE         = (char )0x68 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_GET_DRAM_IMG_PARAMS       = (char )0x69 */  {I43_NO_WAIT, I43_USB_READ , 16},
    /* I43HC_SET_AWB_CTC               = (char )0x6A */  {I43_WAIT   , I43_USB_WRITE,20},
    /* I43HC_SET_AWB_WEIGHT_LUTS       = (char )0x6B */  {I43_DELAY  , I43_USB_WRITE, 0},
    /* I43HC_PIP_LAYER_CREATE          = (char )0x6C */  {I43_WAIT   , I43_USB_WRITE,16},
    /* I43HC_PIP_LAYER_DESTROY         = (char )0x6D */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_PIP_LAYER_SHOW            = (char )0x6E */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_PIP_SET_ATTRIB            = (char )0x6F */  {I43_WAIT   , I43_USB_WRITE,20},

    /* Flash Light Control Commands. */

    /* I43HC_SENSOR_SHUTTER_CONFIG     = (char )0x70 */  {I43_WAIT   , I43_USB_WRITE,4},
    /* I43HC_CONFIG_STROBE_PIN         = (char )0x71 */  {I43_WAIT   , I43_USB_WRITE,12},
    /* I43HC_CONFIG_RED_EYE_REDUCTION  = (char )0x72 */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_ENABLE_RED_EYE_REDUCTION  = (char )0x73 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_CONFIG_FLASH_TRIGGER      = (char )0x74 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_SET_FLASH_TRIGGER         = (char )0x75 */  {I43_NO_WAIT, I43_USB_WRITE, 0},

    /* New OSD Commands. */
    /* I43HC_SET_CUSTOM_EXPOSURE	   = (char )0x76 */  {I43_DELAY  , I43_USB_WRITE, 4},
    /* I43HC_SET_OSD_DISPLAY_ATTR      = (char )0x77 */  {I43_WAIT   , I43_USB_WRITE,10},
    /* I43HC_OSD_DRAW_FILE             = (char )0x78 */  {I43_WAIT   , I43_USB_WRITE,DRAW_FILE_NAME_SIZE + 10},
    /* I43HC_OSD_DRAW_SHAPE            = (char )0x79 */  {I43_WAIT   , I43_USB_WRITE,12},
    /* I43HC_OSD_TEXT_OUT_ID           = (char )0x7A */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_OSD_TEXT_OUT              = (char )0x7B */  {I43_DELAY  , I43_USB_WRITE, 6},
    /* I43HC_OSD_DRAW_TEXT_ID          = (char )0x7C */  {I43_WAIT   , I43_USB_WRITE,16},
    /* I43HC_OSD_DRAW_TEXT             = (char )0x7D */  {I43_DELAY  , I43_USB_WRITE,14},
    /* I43HC_DPOF_SET_HEADER_PARAM	   = (char )0x7E */  {I43_WAIT   , I43_USB_WRITE,4+I43_DPOF_HEADER_PARAM},
	/* I43HC_DPOF_GET_HEADER_PARAM     = (char )0x7F */  {I43_WAIT   , I43_USB_WRITE, 2},

    /* DPOF commands - cont. */

    /* I43HC_DPOF_GET_PREV_JOB_A2C     = (char )0x80 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_DPOF_GET_PREV_JOB_C2A     = (char )0x81 */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_DPOF_SET_JOB_PARAM_INT    = (char )0x82 */  {I43_WAIT   , I43_USB_WRITE, 10},
    /* I43HC_DPOF_GET_JOB_PARAM_INT_A2C= (char )0x83 */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_DPOF_GET_JOB_PARAM_INT_C2A= (char )0x84 */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_DPOF_SET_JOB_PARAM_STR    = (char )0x85 */  {I43_WAIT,	   I43_USB_WRITE, I43_DPOF_JOB_PARAM_STR+6},
    /* I43HC_DPOF_ADD_SRC_2_JOB_A2C    = (char )0x86 */  {I43_WAIT,    I43_USB_WRITE, I43_DPOF_DATE_SIZE+6},
    /* I43HC_DPOF_ADD_SRC_2_JOB_C2A    = (char )0x87 */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_DPOF_REMOVE_SRC           = (char )0x88 */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_DPOF_REMOVE_IMAGE         = (char )0x89 */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_DPOF_GET_IMAGE_DATA       = (char )0x8A */  {I43_WAIT   , I43_USB_READ,  8},
    /* I43HC_DPOF_SET_SRC_PARAM        = (char )0x8B */  {I43_WAIT   , I43_USB_WRITE, I43_DPOF_SRC_PARAM_STR+6},
    /* I43HC_DPOF_GET_FIRST_SRC_A2C    = (char )0x8C */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_DPOF_GET_FIRST_SRC_C2A    = (char )0x8D */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_DPOF_GET_NEXT_SRC_A2C     = (char )0x8E */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_DPOF_GET_NEXT_SRC_C2A     = (char )0x8F */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_DPOF_GET_PREV_SRC_A2C     = (char )0x90 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_DPOF_GET_PREV_SRC_C2A     = (char )0x91 */  {I43_NO_WAIT, I43_USB_READ , 4},

    /* File Transfer Commands. */

    /* I43HC_GET_VIDEO_CAP_IMAGE_SIZE  = (char )0x92 */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_XMT_FILE                  = (char )0x93 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* PlaceHolder                     = (char )0x94 */  {0, 0, -1},
    /* I43HC_RCV_FILE                  = (char )0x95 */  {I43_DELAY  , I43_USB_WRITE, 4},
    /* I43HC_DPOF_GET_JOB_PARAM_STR	   = (char )0x96 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_DPOF_GET_SRC_PARAM		   = (char )0x97 */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_GET_IMAGE                 = (char )0x98 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_LOAD_IMAGE                = (char )0x99 */  {I43_DELAY  , I43_USB_WRITE, 8},
    /* I43HC_GET_VIDEO                 = (char )0x9A */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_XMT_THUMBNAIL             = (char )0x9B */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* PlaceHolder                     = (char )0x9C */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* PlaceHolder                     = (char )0x9D */  {0, 0, -1},
    /* PlaceHolder                     = (char )0x9E */  {0, 0, -1},
    /* PlaceHolder                     = (char )0x9E */  {0, 0, -1},

    /* Configuration & Protocol Commands. */
    
    /* PlaceHolder                     = (char )0xA0 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xA1 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xA2 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xA3 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xA4 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xA5 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xA6 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xA7 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xA8 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0x35 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xAA */  {0, 0, -1},

    /* Storage Media management Commands. */

    /* I43HC_SET_DCF_CHARACTERS        = (char )0xAB */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_SET_NEXT_DCF_KEY          = (char )0xAC */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_GET_DCF_KEY               = (char )0xAD */  {I43_WAIT   , I43_USB_READ , 8},
    /* I43HC_SET_FILE_TYPE             = (char )0xAE */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* PlaceHolder                     = (char )0xAF */  {0, 0, -1},
	/* I43HC_SET_STATISTICS_PATTERN    = (char )0xB0 */  {I43_WAIT   , I43_USB_WRITE,STATISTIC_PATTERN_SIZE+2},
    /* I43HC_SET_FILE_NAME             = (char )0xB1 */  {I43_WAIT   , I43_USB_WRITE,14},
    /* I43HC_SET_CURRENT_IMAGE         = (char )0xB2 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_GET_CURRENT_IMAGE         = (char )0xB3 */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* PlaceHolder                     = (char )0xB4 */  {0, 0, -1},
    /* I43HC_REGISTER_MEDIA            = (char )0xB5 */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_GET_STORAGE_MEDIA_STATUS  = (char )0xB6 */  {I43_NO_WAIT, I43_USB_READ ,10},
    /* I43HC_FORMAT_STORAGE_MEDIA      = (char )0xB7 */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* I43HC_SET_CURRENT_PATH          = (char )0xB8 */  {I43_DELAY  , I43_USB_WRITE, 0},
    /* I43HC_GET_FILE_ATTRIBUTES       = (char )0xB9 */  {I43_NO_WAIT, I43_USB_READ ,28},
    /* I43HC_FILE_OPERATION            = (char )0xBA */  {I43_WAIT,    I43_USB_READ , 2},
    /* PlaceHolder                     = (char )0xBB */  {0, 0, -1},
    /* I43HC_GET_FIRST_FILE_ATTRIBUTE  = (char )0xBC */  {I43_NO_WAIT, I43_USB_READ ,28},
    /* I43HC_GET_NEXT_FILE_ATTRIBUTE   = (char )0xBD */  {I43_NO_WAIT, I43_USB_READ ,28},
    /* I43HC_STORE_AUDIO_MESSAGE       = (char )0xBE */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* I43HC_MOUNT_STORAGE_MEDIA       = (char )0xBF */  {I43_NO_WAIT, I43_USB_READ , 2},

    /* System Calibration Commands. */

    /* PlaceHolder                     = (char )0xC0 */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* PlaceHolder                     = (char )0xC1 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xC2 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xC3 */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* PlaceHolder                     = (char )0xC4 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xC5 */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_AUDIO_LOOP                = (char )0xC6 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* PlaceHolder                     = (char )0xC7 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xC8 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xC9 */  {0, 0, -1},
    /* I43HC_MOTOR_GO                  = (char )0xCA */  {I43_NO_WAIT, I43_USB_WRITE, 0},
	/* I43HC_SET_CLOCK                 = (char )0xCB */  {I43_WAIT   , I43_USB_WRITE, 12},
	/* I43HC_GET_CLOCK                 = (char )0xCC */  {I43_NO_WAIT, I43_USB_READ , 14},
    /* I43HC_MOTOR_SET                 = (char )0xCD */  {I43_WAIT   , I43_USB_WRITE, 20},
    /* I43HC_MOTOR_CONFIG              = (char )0xCE */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_CONFIG_BUTTON_DRV         = (char )0xCF */  {I43_WAIT   , I43_USB_WRITE, 4},

    /* USB Configuration & Protocol Commands. */

    /* I43HC_QUERY_STATUS              = (char )0xD0 */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* PlaceHolder                     = (char )0xD1 */  {0, 0, -1},
    /* I43HC_USB_CONNECT               = (char )0xD2 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_SET_USB_MODE              = (char )0xD3 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* PlaceHolder                     = (char )0xD3 */  {0, 0, -1},
    /* PlaceHolder                     = (char )0xD5 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* PlaceHolder                     = (char )0xD6 */  {0, 0, -1},
    /* PlaceHolder					   = (char )0xD7 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* PlaceHolder					   = (char )0xD8 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* PlaceHolder					   = (char )0xD9 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_WAIT_HOST_COM_SEM         = (char )0xDA */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_SIGNAL_HOST_COM_SEM       = (char )0xDB */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_SET_HOST_COM_DATA         = (char )0xDC */  {I43_DELAY  , I43_USB_WRITE, 0},
    /* I43HC_GET_HOST_COM_DATA         = (char )0xDD */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* PlaceHolder                     = (char )0xDE */  {I43_DELAY  , I43_USB_WRITE, 0},
    /* I43HC_PTP_CONTROL               = (char )0xDF */  {I43_WAIT   , I43_USB_WRITE, 4},

    /* Capture and Compression Control Commands. */

    /* I43HC_PLAYBACK_CLIP_CMD         = (char )0xE0 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_SET_COMPRESSION_RATIO     = (char )0xE1 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_SET_SEQUENCE_LENGTH       = (char )0xE2 */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_GET_SEQUENCE_LENGTH       = (char )0xE3 */  {I43_NO_WAIT, I43_USB_READ , 2},
    /* I43HC_SET_IMAGE_EXIF            = (char )0xE4 */  {I43_DELAY  , I43_USB_WRITE, 10},
    /* I43HC_GET_IMAGE_EXIF            = (char )0xE5 */  {I43_WAIT   , I43_USB_WRITE, 6},
    /* I43HC_GET_IMAGE_ATTRIBUTES      = (char )0xE6 */  {I43_NO_WAIT, I43_USB_READ, 14},
    /* PlaceHolder                     = (char )0xE7 */  {I43_DELAY  , I43_USB_WRITE, 0},
    /* I43HC_GET_IMAGE_EXIF_READ_COUNT = (char )0xE8 */  {I43_NO_WAIT, I43_USB_READ,  4},
    /* I43HC_GET_IMAGE_DATE_TIME       = (char )0xE9 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_CONFIG_DRAM_CAPTURE       = (char )0xEA */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_CONFIG_CAPTURE            = (char )0xEB */  {I43_WAIT   , I43_USB_WRITE, 2},
    /* I43HC_CONFIG_N_IN_1_MODE        = (char )0xEC */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_CONFIRM_STORE             = (char )0xED */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_GET_CAPTURE_STATUS        = (char )0xEE */  {I43_NO_WAIT, I43_USB_READ , 4},
    /* I43HC_MONITOR_CMD               = (char )0xEF */  {I43_WAIT   , I43_USB_WRITE,64},

    /* Debug Commands. */

    /* I43HC_WRITE_FLASH_BURST         = (char )0xF0 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_CONFIG_HOST_MEM_ACCESS    = (char )0xF1 */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_SET_MEM                   = (char )0xF2 */  {I43_DELAY  , I43_USB_WRITE, 0},
    /* I43HC_GET_MEM                   = (char )0xF3 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_DEBUG_OTR1                = (char )0xF4 */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_DEBUG_OTR2                = (char )0xF5 */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_DEBUG_OTR3                = (char )0xF6 */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_DEBUG_OTR4                = (char )0xF7 */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_GET_COACH_VERSION         = (char )0xF8 */  {I43_NO_WAIT, I43_USB_READ ,10},
    /* I43HC_UPGRADE_FLASH_FROM_CARD   = (char )0xF9 */  {I43_NO_WAIT, I43_USB_WRITE, 0},
    /* I43HC_SET_LONG                  = (char )0xFA */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* PlaceHolder                     = (char )0xFB */  {I43_WAIT   , I43_USB_READ , 4},
    /* I43HC_UPGRADE_WAV               = (char )0xFC */  {I43_WAIT   , I43_USB_WRITE, 2},
	/* I43HC_EDIT_IMAGE                = (char )0xFD */  {I43_WAIT   , I43_USB_WRITE, 8},
    /* I43HC_GET_LONG_A2C              = (char )0xFE */  {I43_WAIT   , I43_USB_WRITE, 4},
    /* I43HC_GET_LONG_C2A              = (char )0xFF */  {I43_NO_WAIT, I43_USB_READ , 4},
};

USB_COMMAND_INFO* gUsbCommandArray = UsbCommandArray ;
