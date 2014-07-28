/* ****************************************************************** */
/*                             Api_func.h                             */
/* ****************************************************************** */
/* Copyright (c) 1997 ZORAN Corporation, All Rights Reserved          */
/* THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION               */
/*                                                                    */
/* ****************************************************************** */

#ifndef _API_FUNC_H_
#define _API_FUNC_H_

#ifndef __I43_API_H__
    #error  This file should be used inside of I43_Api.h
#endif  /* __I43_API_H__ */

#if  ( MODULE_TYPE==HCE_API )
#pragma far_seg(__API_FAR_SECT_2)
#endif

/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                            Initialization                          */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */


/* ****************************************************************** */
/*                        I43_GetImageDateTime                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function retrieves the date and time that the current image   */
/* was captured in, form the I43.                                     */
/* The data is read from the EXIF 2.0 file Tag Array.                 */
/* The Date/Time is written to a predefined memory location, where it */
/* is stored in 10 operand words which are 20 ASCII characters in the */
/* following format (from MS at the left to LS at the right):         */
/* yyyy:mm:dd[one space]hh:mm:ss:[null]. For example:                 */
/* 1999:12:24 23:55:49.                                               */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetImageDateTime                                                  */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetImageDateTime( void
                                   ) CODE_SECT;


/* ****************************************************************** */
/*                         I43_ConfigCapture                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bConfig  - Specify the configuration to apply:                    */
/*    I43_CC_HOLD_TIME   - Set the time to wait before storing the    */
/*        image. The COACH wait for wOperand and then store the image.*/
/*    I43_CC_RECORD_TYPE - Set the Recording mode of the COACH:       */
/*        wOperand sets the type:                                     */
/*        I43_JPEG - EXIF compressed form (file ext: jpg).            */
/*        I43_TIFF - EXIF uncompressed form (file ext: tif).          */
/*    I43_CC_PRE_DELAY   - Set the time between moving to Capture     */
/*        mode and the actual time the image is captured.             */
/*        The delay is given in wOperand parameter.                   */
/*    I43_CC_CLIP_TIME   - sets the length of the captured clip in    */
/*        seconds. The time is given in wOperand parameter.           */
/*    I43_CC_DATA_STAMP  - Enables/Disables the data stamping         */
/*        according to the value of wOperand:                         */
/*        0 - Disable the data stamping.                              */
/*        1 - Enable the data stamping.                               */
/*    I43_CC_CLIP_RATE   - sets the clip frame rate                   */
/*                         (0 is no frame rate control)               */
/*    I43_CC_AUDIO_TIME  - sets the length of the captured wave file  */
/*        in seconds. The time is given in wOperand parameter.        */
/*  wOperand - Additional operand for the specific configuration.     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to config the capture operation.    */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigCapture                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigCapture( I43_UINT8  bConfig,
                                  I43_UINT16 wOperand
                                ) CODE_SECT;

/* ****************************************************************** */
/*                         I43_ConfigNin1Mode                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigNin1Mode( I43_UINT8 byOp,
                                   I43_UINT32 uiWidth, 
                                   I43_UINT32 uiHeight );

/* ****************************************************************** */
/*                      I43_GetCaptureStatus                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetCaptureStatus( I43_UINT8   byCaptureMode,
									 I43_UINT16* pwDRAMStatus,
                                     I43_UINT16* pwNumOfPend
                                   ) CODE_SECT;


/* ****************************************************************** */
/*                         I43_ConfirmStore                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bConfirm - Confirms or deny the store operation:                  */
/*    I43_CSM_DELETE - Go back to View mode without storing.          */
/*    I43_CSM_STORE  - Store the image and then move back to View.    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to set the Recording Mode for       */
/* images captured in Capture Image mode.                             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfirmStore                                                      */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfirmStore( I43_UINT8 bConfirm
                               ) CODE_SECT;

/* ****************************************************************** */
/*                       I43_SetBLE					                  */
/* ****************************************************************** */

I43_ERROR_CODE I43_SetBLE( I43_SET_BLE* pConfig
                                    ) CODE_SECT;


/* ****************************************************************** */
/*                   I43_SetMeanBlackNoise                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetMeanBlackNoise( I43_UINT16 bValue) CODE_SECT;



/* ****************************************************************** */
/*                   I43_SetMeanBlackNoiseAuto                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the Mean Black Noise mode to auto. In this mode */
/* the I43 calculate automaitaclly the mean balck noise values to be  */
/* deducted from he CCD sensor inputs.                                */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetMeanBlackNoise                                                 */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_SetMeanBlackNoiseAuto(I43_BLACK_NOISE_MODE bMode 
                                      ) CODE_SECT;



/* ****************************************************************** */
/*                   I43_EnableISSPUBlock                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bBlockID - the ID of the algorithm block to be enabled/disabled.  */
/*  wParam   - parameter:				                              */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to enable/disable some of the ISSPU  */
/* algorithms ran during the image processing process.                */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  EnableISSPUBlock                                                  */
/* ****************************************************************** */
I43_ERROR_CODE I43_EnableISSPUBlock( I43_BLOCK_ID bBlockID,
                                     I43_INT16	  wParam
                                   ) CODE_SECT;

/* ****************************************************************** */
/*                   I43_InitSensor                                   */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*                                                                    */
/*        None                                                        */
/*                                                                    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to initialize the sensor related     */
/* data. Should be called in the Idle mode.                           */
/* ****************************************************************** */
I43_ERROR_CODE I43_InitSensor( I43_UINT8 wOp
                                   ) CODE_SECT;


/* ****************************************************************** */
/*                    I43_LoadGammaLUTResource                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wIndex - The index of the table to be loaded.                     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function loads the wIndex gamma LUT from the resident flash   */
/* memory.                                                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetActiveTable                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_LoadGammaLUTResource( I43_UINT16 wIndex, I43_UINT8 bGammaToSet
                                       ) CODE_SECT;


/* ****************************************************************** */
/*                    I43_LoadLscLUTResource								  */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wIndex - The index of the table to be loaded.                     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function loads the wIndex Lsc LUT from the resident flash     */
/* memory.                                                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetActiveTable                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_LoadLscLUTResource( I43_UINT16 wIndex
                                       ) CODE_SECT;


/* ****************************************************************** */
/*                    I43_LoadNLGFLUTResource                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wIndex - The index of the table to be loaded.                     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function loads the wIndex NLGF LUT from the resident flash    */
/* memory.                                                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetActiveTable                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_LoadNLGFLUTResource( I43_UINT16 wIndex
                                      ) CODE_SECT;


/* ****************************************************************** */
/*                    I43_LoadLcLUTResource                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wIndex - The index of the table to be loaded.                     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function loads the wIndex Luma correction LUT from the resident flash    */
/* memory.                                                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetActiveTable                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_LoadLcLUTResource( I43_UINT16 wIndex
                                      ) CODE_SECT;


/* ****************************************************************** */
/*                    I43_LoadBrightnessLUTResource                   */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wIndex - The index of the table to be loaded.                     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function loads the wIndex Brithness LUT from the resident     */
/* flash memory.                                                      */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetActiveTable                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_LoadBrightnessLUTResource( I43_UINT16 wIndex
                                           ) CODE_SECT;

/* ****************************************************************** */
/*                         I43_SetImageEXIF                           */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetImageEXIF(I43_UINT16 uwIfdIndex,
								I43_UINT16 uwTagId,
								I43_UINT16 uwType,
								I43_UINT16 uwCount,
								I43_UINT16 uwSupportLevel);


/* ****************************************************************** */
/*                         I43_GetImageEXIF                           */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetImageEXIF( I43_UINT16  uwDcfIndex,
                                 I43_UINT16  uwIfdIndex,
                                 I43_UINT16  uwTagId,
                                 I43_UINT32* pulCount );



/* ****************************************************************** */
/*                      I43_GetImageAttributes                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pImageAttr - Pointer to an Image attributes structure.            */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to get the attributes of the        */
/* current image.                                                     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetImageAttributes                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetImageAttributes( IMAGE_ATTRIBUTES* pImageAttr
                                     ) CODE_SECT;

/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                           Image Sensor                             */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                      I43_SetPreviewExposure                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bIndex  - The index of the entry in the EVTT to be used.          */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to control the TG in order to change */
/* the exposure of the previewed image by only specifying an entry in */
/* the EVTT.                                                          */
/* Note: The API is not allowed if the COACH is the AE master.        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetPreviewExposure                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetPreviewExposure( I43_UINT8 bIndex
                                     ) CODE_SECT;

/* ****************************************************************** */
/*                      I43_SetCustomExposure                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  byMode  - The mode of the sensor - View or Capture.               */
/*	uwIndex - The index of the entry in the EVTT to be configured/used*/
/*  bSet    - Specifies whether to set the current exposure to the    */
/*            uwIndex value.                                          */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to set the EVTT and VsyncCount table */
/* entries of the corresponding exposure for the requested mode.      */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*	SetCustomExposure                                                 */
/* ****************************************************************** */
I43_ERROR_CODE  I43_SetCustomExposure( I43_UINT8  byMode,
                                       I43_UINT16 uwIndex,
                                       I43_BOOL   bSet );

/* ****************************************************************** */
/*                      I43_SetPreviewAgc                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bIndex  - The index of the entry in the AGC View Table to be used.*/
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to control the AGC in order to change*/
/* the previewed image by only specifying an entry in the AGC View    */
/* Table.                                                             */
/* Note: The API  allowed only if the COACH is in AGC MANUAL mode     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetPreviewAgc                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetPreviewAgc( I43_UINT8 bIndex
                                     ) CODE_SECT;


/* ****************************************************************** */
/*                      I43_SetCaptureExposure                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bIndex        - The index of the entry in the EVTT to be used.    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to control the TG in order to change */
/* the exposure of the captured image by only specifying an entry in  */
/* the EVTT.                                                          */
/* Note: The API is not allowed if the COACH is the AE master.        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetCaptureExposure                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetCaptureExposure( I43_UINT8 bIndex
                                     ) CODE_SECT;

/* ****************************************************************** */
/*                      I43_SetCaptureAgc                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bIndex        - The index of the entry in the AGC Capture Table   */
/*  to be used.                                                       */
/*Return Value:                                                       */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to control the AGC in order to       */
/* change  captured image by only specifying an entry in the AGC      */
/* Capture Table .                                                    */
/* Note: The API is not allowed  if the COACH is in AGC AUTO mode     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetCaptureAgc                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetCaptureAgc( I43_UINT8 bIndex
                                     ) CODE_SECT;


/* ****************************************************************** */
/*                        I43_ConfigAEParams                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bTargetWALL   - The new Target WALL.                              */
/*  bMaxPL        - The Maximum Peak Luminance.                       */
/*  bPLPercentage - The Peak Luminance allowed percentage (1-100).    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to configure the AE parameters      */
/* related to the EV step decision. These parameters will affect the  */
/* return value of the I43_GetExposureValueStep API and the behavior  */
/* of the AE master.                                                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigAEParams                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigAEParams( I43_UINT8 bTargetWALL,
                                   I43_UINT8 bMaxPL,
                                   I43_UINT8 bPLPercentage
                                 ) CODE_SECT;



/* ****************************************************************** */
/*                             I43_SetCCD                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bNum  - The TG burst number (zero based).                         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function writes the control bits to the CCD TG.               */
/* The data is read from a predefined memory location.                */
/* Note that since the I43 works with 16bit words for every write     */
/* operation, the data at the memory location must be in 16 bit       */
/* baundery. The padding bits should be zeros.                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetCCD                                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetCCD( I43_UINT8 bNum
                         ) CODE_SECT;



/* ****************************************************************** */
/*                      I43_GetPreviewExposure                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwValue  - Pointer where to write the preview exposure value.     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to read the exposure value that is   */
/* set in preview modes.                                              */
/* The value is returned as an entry number to the EVTT table.        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetPreviewExposure                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetPreviewExposure( I43_UINT16* pwValue
                                     ) CODE_SECT;


/* ****************************************************************** */
/*                      I43_GetPreviewAgc                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwValue  - Pointer where to write the preview AGC value.          */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to read the AGC entry value that is  */
/* set in preview modes.                                              */
/* The value is returned as an entry number to the AGC View table.    */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetPreviewAgc                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetPreviewAgc( I43_UINT16* pwValue
                                     ) CODE_SECT;


/* ****************************************************************** */
/*                      I43_GetCaptureExposure                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwValue  - Pointer where to write the capture exposure value.     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to read the exposure value that is   */
/* set in capture modes.                                              */
/* The value is returned as an entry number to the EVTT table.        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetCaptureExposure                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetCaptureExposure( I43_UINT16* pwValue
                                     ) CODE_SECT;

/* ****************************************************************** */
/*                      I43_GetCaptureAgc                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwValue  - Pointer where to write the AGC exposure value.         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to read the AGC value that is        */
/* set in capture modes.                                              */
/* The value is returned as an entry number to the AGC Capture table. */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetCaptureAgc                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetCaptureAgc( I43_UINT16* pwValue
                                     ) CODE_SECT;


/* ****************************************************************** */
/*                   I43_SetPreviewExposureLimits                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bMin  - The minimum exposure value (range: 0-127).                */
/*  bMax  - The maximum exposure value (range: 0-127).                */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to set the limits for the COACH      */
/* exposure algorithm in preview modes.                               */
/* Note: the following restriction must be satisfied:                 */
/*       0 <= bMin <= bMax <= 127                                     */
/* Note: A value of 0xFF in either of the parameters means that this  */
/*       limit should not be changed.                                 */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetPreviewExposureLimits                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetPreviewExposureLimits( I43_UINT8 bMin,
                                             I43_UINT8 bMax
                                           ) CODE_SECT;



/* ****************************************************************** */
/*                   I43_SetCaptureExposureLimits                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bMin  - The minimum exposure value.                               */
/*  bMax  - The maximum exposure value.                               */
/*  bFlashThreshold  - The flash activation threshold.                */
/*  bFlashMin  - The minimum exposure value when flash light is       */
/*               activated.                                           */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to set the limits for the COACH      */
/* exposure algorithm in capture modes.                               */
/* Note: All parameters are in the range of 0 to 127.                 */
/* Note: the following restrictions must be satisfied:                */
/*       0 <= bMin <= bFlashMin <= bMax <= 127                        */
/*       bMin <= bFlashMin <= bMax                                    */
/* Note: A value of 0xFF in either of the parameters means that this  */
/*       limit should not be changed.                                 */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetCaptureExposure                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetCaptureExposureLimits( I43_UINT8 bMin,
                                             I43_UINT8 bMax,
                                             I43_UINT8 bFlashThreshold,
                                             I43_UINT8 bFlashMin
                                           ) CODE_SECT;

/* ****************************************************************** */
/*                          I43_SetAWBCTC                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  waCTC - The Color Temperature Curve table.                        */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to set the Color Temperature Curve   */
/* which is used in the COACH AWB algorithm.                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetAWBCTC                                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetAWBCTC( I43_UINT16 waCTC[10]
                            ) CODE_SECT;


/* ****************************************************************** */
/*                       I43_SetAWBWeightLUTs                         */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_LoadAWBCTLUT(I43_UINT8 bValue);


/* ****************************************************************** */
/*                       I43_SetAWBWeightLUTs                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to set the Weighting LUTs used by    */
/* the COACH AWB algorithm.                                           */
/* The LUTs are read from the I43_AWB_LUTS_MEM_LOCATION memory        */
/* location. The LUTs in the memeory location should be concated one  */
/* after the other (Distance LUT first and then the Weight LUT).      */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetAWBWeightLUTs                                                  */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetAWBWeightLUTs( void
                                   ) CODE_SECT;


/* ****************************************************************** */
/*                       I43_SensorShutterConfig                      */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_SensorShutterConfig(I43_BOOL   bEnable, 
												   I43_UINT16 wLinesDelay,
												   I43_UINT16 wSubLineDelay);


/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                             General                                */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */

/* ****************************************************************** */
/*                            I43_SetMode                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bNewMode - the new mode for the I43.                              */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function moves the i43 to the specified mode.                 */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetMode                                                           */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetMode( I43_MODE bNewMode
                          ) CODE_SECT;


/* ****************************************************************** */
/*                        I43_GetStatusRegister                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bRegister - the register to be read.                              */
/*  pwValue   - the returned register value.                          */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function reads the value of the specified status register.    */
/* The read value is written to the pwValue operand.                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  None.                                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetStatusRegister( I43_STATUS_REGISTER bRegister,
                                      I43_UINT16*         pwValue
                                    ) CODE_SECT;

/* ****************************************************************** */
/*                            I43_SendI2C                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wSubAddr - the register sub address.                              */
/*  wData    - the data to be sent.                                   */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to write "through" the               */
/* I43 to an I2C slave device that is connected to the I43.           */
/* The function writes one byte/word at a time as configured in the   */
/* I43_ConfigI2CAccess API.                                           */
/* The operation result is reported in SR1 status codes.              */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SendI2C                                                           */
/* ****************************************************************** */
I43_ERROR_CODE I43_SendI2C( I43_UINT16 wSubAddr,
                            I43_UINT16 wData
                          ) CODE_SECT;


/* ****************************************************************** */
/*                            I43_GetI2C                              */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wSubAddr - the register sub address.                              */
/*  pwData   - Pointer where to write the read data.                  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to read "through" the                */
/* I43 to an I2C slave device that is connected to the I43.           */
/* The function reads one byte/word at a time as configured in the    */
/* I43_ConfigI2CAccess API.                                           */
/* The operation result is reported in SR1 status codes.              */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetI2C                                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetI2C( I43_UINT16  wSubAddr,
                           I43_UINT16* pwData
                         ) CODE_SECT;

/* ****************************************************************** */
/*                         I43_ConfigI2CAccess                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bAddrSize    - I2C device address size (0 - 8bit, 1 - 16bit).     */
/*  bSubAddrSize - I2C device sub-address size (0 - 8bit, 1 - 16bit). */
/*  bDataSize    - I2C device data size (0 - 8bit, 1 - 16bit).        */
/*  wAddress     - The I2C device address.                            */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to configure the following I2C       */
/* accesses.                                                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigI2CAccess                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigI2CAccess( I43_UINT8  bAddrSize,
                                    I43_UINT8  bSubAddrSize,
                                    I43_UINT8  bDataSize,
                                    I43_UINT16 wAddress
                                  ) CODE_SECT;



/* ****************************************************************** */
/*                       I43_WriteI2CBurst                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wSubAddr - the sub address of the I2C device.                     */
/*  wSize    - the number of words to be written.                     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function instruct the I43 to send the burst of data to the    */
/* specified I2C slave device.                                        */
/* The function writes one byte/word at a time as configured in the   */
/* I43_ConfigI2CAccess API.                                           */
/* The operation result is reported in SR1 status codes.              */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  WriteI2CBurst                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_WriteI2CBurst( I43_UINT16 wSubAddr,
                                  I43_UINT16 wSize
                                ) CODE_SECT;



/* ****************************************************************** */
/*                       I43_ReadI2CBurst                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wSubAddr - the sub address of the I2C device.                     */
/*  wSize    - the number of words to be read.                        */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function instruct the I43 to read a burst of data to the      */
/* specified I2C slave device.                                        */
/* The function reads one byte/word at a time as configured in the    */
/* I43_ConfigI2CAccess API.                                           */
/* The operation result is reported in SR1 status codes.              */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ReadI2CBurst                                                      */
/* ****************************************************************** */
I43_ERROR_CODE I43_ReadI2CBurst( I43_UINT16 wSubAddr,
                                 I43_UINT16 wSize
                               ) CODE_SECT;



/* ****************************************************************** */
/*                            I43_UpdateUSP                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwSuccess  - Pointer where to write the return vlaue:             */
/*               0x0000 - failure.                                    */
/*               0x0001 - success.                                    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function tells the I43 to copy the "shadow" of the USP, that  */
/* is stored in DRAM, back to its "cold" storage area in the resident */
/* flash memory attached to the I43.                                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  UpdateUSP                                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_UpdateUSP( I43_UINT16* pwSuccess
                            ) CODE_SECT;



/* ****************************************************************** */
/*                            I43_UpdateFSP                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwSuccess  - Pointer where to write the return vlaue:             */
/*               0x0000 - failure.                                    */
/*               0x0001 - success.                                    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function tells the I43 to copy the "shadow" of the USP, that  */
/* is stored in DRAM, to the FSP resource on the resident flash and   */
/* overwrite it.                                                      */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  UpdateFSP                                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_UpdateFSP( I43_UINT16* pwSuccess
                            ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_RevertFSP                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function tells the I43 to copy the FSP that is stored on the  */
/* Non Volatile memory over the "shadow" of the USP (USPS) and then   */
/* over the USP that is stored in the non volatile memory.            */
/* The purpose of this function is to enable the user to return to    */
/* the original factory settings.                                     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  RevertFSP                                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_RevertFSP( void
                            ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_RestoreUSP                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*	None.                                                             */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function tells the I43 to copy the USP that is stored on the  */
/* Volatile memory to the DRAM. If it is failed to do so, it copy the */
/* FSP that is stored on the Non Volatile memory over the "shadow" of */
/* the USP (USPS) and then over the USP that is stored in the non     */
/* volatile memory and updates USP.                                   */
/* The purpose of this function is to enable the user to return to    */
/* the original factory settings.                                     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*	RestoreUSP                                                        */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_RestoreUSP( void
                                         ) CODE_SECT;


/* ****************************************************************** */
/*                        I43_GetFreeParams                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bSize   - The number of words to retrieve from the Free           */
/*            Parameters area.                                        */
/*  wOffset - Offset from the beginning of the Free Parameters area.  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function retrieves returns a portion of the free area space   */
/* of the host in the USPS.                                           */
/* The data is read from wOffset words from the beginning of the Free */
/* parameters area.                                                   */
/* The parameters are written to a predefined memory location.        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetFreeParams                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetFreeParams( I43_UINT8  bSize,
                                  I43_UINT16 wOffset
                                ) CODE_SECT;



/* ****************************************************************** */
/*                        I43_SetFreeParams                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bSize - The number of words to change in the Free Parameters area.*/
/*  wOffset - Offset from the beginning of the Free Parameters area.  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function updates the free area of the host in the USPS.       */
/* the first data word is written to the first location in the free   */
/* parameters area that is "Offset" words from the beginning of the   */
/* free parameters area.                                              */
/* The parameters are read from a predefined memory location.         */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetFreeParams                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetFreeParams( I43_UINT8  bSize,
                                  I43_UINT16 wOffset
                                ) CODE_SECT;



/* ****************************************************************** */
/*                             I43_SetParam                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wParamID - The identifier of the COACH parameter to be set.       */
/*  wValue   - The value to be set to the specific COACH parameter.   */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to set a specific value to some      */
/* COACH parameters.                                                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetParam                                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetParam( I43_UINT16 wParamID,
                             I43_UINT16 wValue
                           ) CODE_SECT;



/* ****************************************************************** */
/*                             I43_GetParam                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wParamID - The identifier of the COACH parameter to be set.       */
/*  pwValue  - Pointer where to write the value read from the COACH   */
/*             for the specific parameter.                            */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to get the value of a specific       */
/* COACH parameter.                                                   */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetParam                                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetParam( I43_UINT16 wParamID,
                             I43_UINT16 *pwValue
                           ) CODE_SECT;

/* ****************************************************************** */
/*                             I43_GetParamLong                       */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_GetParamLong( I43_UINT16 wParamID,
                                             I43_UINT32 *pulValue );

/* ****************************************************************** */
/*                             I43_SetTimer                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bTimerId - The ID of the timer.                                   */
/*  bStart   - Indicates whether the timer should start or stop       */
/*             counting:                                              */
/*             I43TC_START - start counting.                          */
/*             I43TC_STOP  - stop counting.                           */
/*  wTime    - The time to count (the time unit depends on the timer).*/
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to start/stop a timer in the COACH.  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetTimer                                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetTimer( I43_UINT8         bTimerId,
                             I43_TIMER_COMMAND bStart,
                             I43_UINT16        wTime
                           ) CODE_SECT;

/* ****************************************************************** */
/*                          I43_UartLibWrite						  */
/* ****************************************************************** */
I43_ERROR_CODE I43_UartLibWrite(I43_UINT16 wSizeInBytes) CODE_SECT;

/* ****************************************************************** */
/*                          I43_UartLibRead							  */
/* ****************************************************************** */
I43_ERROR_CODE I43_UartLibRead(I43_UINT16 wSizeInBytes, I43_UINT8 byFlags );


/* ****************************************************************** */
/*                          I43_UartLibConfig                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_UartLibConfig(I43_BOOL bOpen, 
                                 I43_BAUD_RATE bBaudRate, 
                                 I43_UINT16 bPolarity, 
                                 I43_UINT16 wLineCTL) CODE_SECT;

/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*              System Control and Configuration Commands.            */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                           I43_ConfigUART                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bBaudRate - The new baud rate to be set to the COACH UART port.   */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to set the baud rate of the COACH    */
/* UART port.                                                         */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigUART                                                        */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigUART( I43_BAUD_RATE bBaudRate
                             ) CODE_SECT;
                             
/* ****************************************************************** */
/*                   I43_SendHCEMessage                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bMsgId     - ID of the message                                    */
/*  bMsgParam  - Parameter of the message                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to send a message to HCE             */
/* ****************************************************************** */
I43_ERROR_CODE I43_SendHCEMessage( I43_UINT16 bMsgId,
                                   I43_UINT8 bMsgParam
                                 ) CODE_SECT;
                             

/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                        General Purpose IO                          */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/* ****************************************************************** */
/*                           I43_SelectGPIOEx                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bGroup    - The GPIO group of pins to be addressed.               */
/*  bBit      - The GPIO pin in the group to be selected.             */
/*  bFunc     - The functionality of the pin.                         */
/*  bCounter  - Currently not implemented and therefore ignored.      */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the functionality of a COACH-V selectable pin.  */
/* Pins can be selected as either functional or GPIO.                 */
/* THIS API IS APPLICABLE ONLY ON COACH-V.                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SelectGPIO                                                        */
/* ****************************************************************** */
I43_ERROR_CODE I43_SelectGPIOEx( I43_GPIO_GROUP_TYPE   bGroup,
                                I43_UINT8             bBit,
                                I43_GPIO_FUNC_TYPE    bFunc
                              ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_ConfigGPIOEx                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bGroup - The GPIO group of pins to be addressed.                  */
/*  bBit   - The GPIO pin in the group to be configured.              */
/*  bDir   - The configuration (input or output) of the pin.          */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the configuration of a COACH-V selectable pin.  */
/* Prior to configuring a pin it must first be selected as GPIO.      */
/* THIS API IS APPLICABLE ONLY ON COACH-V.                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigGPIO                                                        */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigGPIOEx( I43_GPIO_GROUP_TYPE  bGroup,
                                I43_UINT8            bBit,
                                I43_GPIO_CONFIG_TYPE bDir
                              ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_SetGPIOEx                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bGroup - The GPIO group of pins to be addressed.                  */
/*  bBit   - The GPIO pin in the group to be set.                     */
/*  bHigh  - The state (high or low) of the pin.                      */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the state of a COACH-V selectable pin. Prior to */
/* setting its state, the pin must first be selected as GPIO and      */
/* configured to output. setting the state of a pin configured to     */
/* imput has no effect.                                               */
/* THIS API IS APPLICABLE ONLY ON COACH-V.                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetGPIO                                                           */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetGPIOEx( I43_GPIO_GROUP_TYPE bGroup,
                             I43_UINT8           bBit,
                             I43_BOOL            bHigh
                           ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_GetGPIOEx                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bGroup   - The GPIO group of pins to be addressed.                */
/*  bBit     - The GPIO pin in the group to get.                      */
/*  bCluster - Wheter to get the whole GPIO group or just the         */
/*             specified bit.                                         */
/*  pwValue  - A container for storing the state of the pin.          */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function gets the state of a COACH-V selectable pin. Prior to */
/* getting its state, the pin must first be selected as GPIO and      */
/* configured to input. getting the state of a pin configured to      */
/* output will always return 0. In case bCluster is I43_GPIO_GROUP,   */
/* the whole GPIO group is retrieved as a word.                       */
/* THIS API IS APPLICABLE ONLY ON COACH-V.                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetGPIO                                                           */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetGPIOEx( I43_GPIO_GROUP_TYPE      bGroup,
                             I43_UINT8                bBit,
                             I43_UINT16*              pwValue
                           ) CODE_SECT;

/* ****************************************************************** */
/*                           I43_ConfigCounter                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bCounter - The counter to be configured.                          */
/*  bStates  - The states of the counter   			      */
/*             bit[0]  - output (0 or 1) when there is no counting    */
/*             bit[1]  - output (0 or 1) when when counting at 	      */
/*  			 TimeStamp1                                   */
/*	       bit[2]  - output (0 or 1) when when counting at 	      */
/*	                 TimeStamp2                                   */
/*  bTimeStamp1   - Number of the counter clocks of TimeStamp1        */
/*  bTimeStamp2   - Number of the counter clocks of TimeStamp2        */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the configuration of a COACH-V counters.        */
/* THIS API IS APPLICABLE ONLY ON COACH-V.                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*                                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigCounter( I43_GPIO_COUNTER_TYPE  bCounter,
                                  I43_UINT8              bStates,
                                  I43_UINT32             uiFrequency,
								  I43_UINT32             uiHighTimerPercent
                                ) CODE_SECT;

/* ****************************************************************** */
/*                           I43_SetCounter                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bCounter - The counter to be enabled/disabled.                    */
/*  bEnable  - The operation mode of the counter        :             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the configuration of a COACH-V counters.        */
/* THIS API IS APPLICABLE ONLY ON COACH-V.                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*                                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetCounter( I43_UINT8         uiId,
                               I43_COUNTER_STATUS bStatus
                             ) CODE_SECT;


/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                    Pre-capture image processing                    */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                       I43_SetEdgeEnhancement                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bEdgeEnhancement - The new EdgeEnhancement value (0-7).           */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the Edge Enhancement degree of the              */
/* captured / displayed image by the I43.                             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetEdgeEnhancement                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetEdgeEnhancement( I43_UINT3 bEdgeEnhancement
                                     ) CODE_SECT;



/* ****************************************************************** */
/*                       I43_SetEdgeEnhancementLPF                    */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bEEFilter - the new LPF to be used for edge detection:            */
/*              0 - (-1, 9,16, 9,-1) (soft)                           */
/*              1 - ( 4,10, 4,10, 4)                                  */
/*              2 - ( 8, 5, 6, 5, 8) (default)                        */
/*              3 - (14, 4,-4, 4,14) (sharp)                          */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the LPF used for edge detection by the I43.     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetEdgeEnhancement                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetEdgeEnhancementLPF( I43_UINT2 bEEFilter
                                       ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_SetWBMode                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bMode - The new White Balance Mode.                               */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the White Balance Mode (daylight, office, etc). */
/* If the caller wants to use his own WB scalers, the caller must     */
/* call the I43_SetWBValues API before calling this function.         */
/* Note that the WB scallers are set according to the last values set */
/* by the call to the I43_SetWBValues API.                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetWhiteBalance                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetWBMode( I43_WB_MODE bMode
                            ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_SetWBValues                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wScaleR - the new Scale for the R component.                      */
/*  wScaleG - the new Scale for the G component.                      */
/*  wScaleB - the new Scale for the B component.                      */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the initial White Balance scaling values.       */
/* The new values can be between 0 to 1023.                           */
/* If the caller wants to use his own WB scalers, the caller must     */
/* call this API before calling the I43_SetWBMode API.                */
/* Note that the WB scallers are set according to the last values set */
/* by the call to this API.                                           */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  None.                                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetWBValues( I43_UINT16 wScaleR,
                                I43_UINT16 wScaleG,
                                I43_UINT16 wScaleB
                              ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_GetWBValues                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwScaleR - Pointer were to write the returned Scale R value.      */
/*  pwScaleG - Pointer were to write the returned Scale G value.      */
/*  pwScaleB - Pointer were to write the returned Scale B value.      */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function returns the current values of the R,G,B scale values.*/
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetWhiteBalance                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetWBValues( I43_UINT16* pwScaleR,
                                I43_UINT16* pwScaleG,
                                I43_UINT16* pwScaleB
                              ) CODE_SECT;

/* ****************************************************************** */
/*                        I43_SetAFRectangle                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wStartX - the X start point of the ROI.                           */
/*  wSizeX  - the X size of the ROI.                                  */
/*  wStartY - the Y start point of the ROI.                           */
/*  wSizeY  - the Y size of the ROI.                                  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function defines the Region Of Interest (ROI) for the auto    */
/* focus support.                                                     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigAF                                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetAFRectangle( I43_UINT16 wStartX,
                                   I43_UINT16 wSizeX,
                                   I43_UINT16 wStartY,
                                   I43_UINT16 wSizeY
                                 ) CODE_SECT;



/* ****************************************************************** */
/*                        I43_SetAFThresholds                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetAFThresholds( I43_UINT16    wHorizontal,
									I43_UINT16    wVertical
								  ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_GetAFValues                          */
/* ****************************************************************** */

I43_ERROR_CODE I43_GetAFValues( I43_UINT16* pwG_VEDGEHigh,
                                I43_UINT16* pwG_VEDGELow,
                                I43_UINT16* pwG_HEDGEHigh,
                                I43_UINT16* pwG_HEDGELow
                              ) CODE_SECT;

/* ****************************************************************** */
/*                           I43_ConfigSubWindowsAF                   */
/* ****************************************************************** */

I43_ERROR_CODE I43_ConfigSubWindowsAF( I43_SUB_AF_MODE uiMode,
                                       I43_UINT16      uwReqGridHSize,
	  	      						   I43_UINT16      uwReqGridVSize,
                                       I43_UINT16      uwNoiseThreshold,
                                       I43_UINT16      uwCloseHighThreshold,
                                       I43_UINT16      uwCloseLowThreshold,
                                       I43_UINT16      uwFarHighThreshold,
                                       I43_UINT16      uwFarLowThreshold );

/* ****************************************************************** */
/*                           I43_GetSubWindowsAF                      */
/* ****************************************************************** */

I43_ERROR_CODE I43_GetSubWindowsAF( I43_SUBWIN_AF uiType );


/* ****************************************************************** */
/*                           I43_SetAEMode                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bMode - The COACH AE firmware mode of operation.                  */
/*   I43AE_MASTER = COACH is AE Master.                               */
/*   I43AE_ECC    = COACH is ECC (Exposure Calculator and Controller).*/
/*   I43AE_ECONLY = COACH is EC (Exposure Calculator).                */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the mode of operation of the Auto Exposure      */
/* firmware of the COACH.                                             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetAEMode                                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetAEMode( I43_AE_MODE bMode
                            ) CODE_SECT;


/* ****************************************************************** */
/*                           I43_SetAgcMode                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bMode - The COACH AGC firmware mode of operation.                 */
/*   I43AE_AUTO    = COACH updates the AGC automatically.             */
/*   I43AE_MANUAL  = AGC is done manually by host commands            */
/*   I43AE_OFF     = No AGC control.                                  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the mode of operation of the AGC control by the */
/* firmware of the COACH.                                             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetAgcMode                                                        */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetAgcMode( I43_AGC_MODE bMode
                            ) CODE_SECT;

/* ****************************************************************** */
/*                           I43_SetFormatConvert                     */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_SetFormatConvert(I43_INT16 uwConvertType,
                                                I43_INT16 wMatrix[9],
                                                I43_INT16 wOffset[2]);

/* ****************************************************************** */
/*                           I43_SetChromaCorrection                  */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_SetChromaCorrection(I43_CHROMA_CORRECTION_MODE uiMode,
                                                   I43_UINT8                  byParam[6]);


/* ****************************************************************** */
/*                        I43_GetLumaHistogram                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bBinWidth - the width of each histogram bin.                      */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This API is useful for systems where the auto exposure algorithm   */
/* is not done by the COACH, but the COACH is employed as a math      */
/* coprocessor for the calculation of the luma histogram.             */
/* The COACH always calculates a 256 bin histogram.  The number of    */
/* words which are returned to the host is 256/bBinWidth.             */
/* This is useful if the host is not interested in a very large       */
/* histogram and wants to save memory space.                          */
/* Note: The number of pixels is relative to the  image size*1/64.    */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  I43_GetLumaHistogram                                              */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetLumaHistogram( I43_UINT8 bBinWidth
                                   ) CODE_SECT;



/* ****************************************************************** */
/*                        I43_GetWeightedLuma                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pbLuma - pointer where to write the returned weighted lume value. */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function is useful for systems where the auto exposure        */
/* algorithm is not done by the I43, but the I43 is employed as a     */
/* math processor for the calculation of the weighted average of the  */
/* luminance.                                                         */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetWeightedLuma                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetWeightedLuma( I43_UINT8* pbLuma
                                  ) CODE_SECT;



/* ****************************************************************** */
/*                    I43_GetExposureValueStep                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwPreviewEV - Pointer where to write the recommended EV value     */
/*                for preview.                                        */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function is useful for systems where the I43 executes the     */
/* auto exposure algorithm, but the actual control over the exposure  */
/* mechanism, be it through shutter speed control, or aperture        */
/* control, or iris control, or a combination of these, is done by    */
/* the host microcontroller.                                          */
/* The I43 calculates an auto exposure "cycle", and returns the       */
/* recommended EV step (change).                                      */
/* The EV number is defined as                                        */
/*  EV = AV + TV                                                      */
/* where AV is the aperture value and TV is the time value.           */
/* These quantities are defined as follows:                           */
/*  AV = 2*log2(Fnumber)                                              */
/*  TV = -log2(shutter_speed)                                         */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetExposureValueStep                                              */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetExposureValueStep( I43_UINT16* pwPreviewEV
                                       ) CODE_SECT;



/* ****************************************************************** */
/*                    I43_SetExposureDeviation                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bDeviation - The deviation from the calculated  value of EV       */
/*               (exposure value), in APEX units, in steps of 1/8     */
/*               APEX.                                                */
/*               Note: The parameter values range from 0 to 32,       */
/*                     however it is mapped to the range of -16 to 16,*/
/*                     hence the value of 16 is mapped to 0.          */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to request Over or Under exposure   */
/* from the COACH. It is applicable when the COACH runs the AE        */
/* algorithm and controls the shutter / iris.                         */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetExposureDeviation                                              */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetExposureDeviation( I43_UINT8 bDeviation
                                       ) CODE_SECT;


/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                           Display Control                          */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                         I43_SetDisplayMode                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bMode - The new display mode of operation.                        */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the new display mode of operation.              */
/* bMode values description:                                          */
/* I43DM_DISABLE   - Display (both OSD and image) is "eternally"      */
/*   disabled until further notice, regardless of what is defined in  */
/*   the mode-dependent portion of the System Description Parameters  */
/*   for every mode. This situation can be changed by another issue   */
/*   of the ConfigSys command, or by resetting or re-booting the i43. */
/* I43DM_OSD_ONLY - Display is enabled for OSD (and background) only. */
/* I43DM_ENABLE   - Display is enabled for OSD (and background) and   */
/*    image as defined for the mode in the mode-dependent             */
/*    portion of the System Description Parameters.                   */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigSys                                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetDisplayMode( I43_DISPLAY_MODE bMode
                                 ) CODE_SECT;



/* ****************************************************************** */
/*                         I43_SetVideoFormat                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bFormat - The new output video format.                            */
/*          I43VF_CVBS  - CVBS Format.                                */
/*          I43VF_Y_C   - Y/C Format.                                 */
/*          I43VF_RGB   - RGB plus separate sync Format.              */
/*          I43VF_RGB_G - RGB with sync on green Format.              */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the new output video format.                    */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigSys                                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetVideoFormat( I43_VIDEO_FORMAT bFormat
                                 ) CODE_SECT;



/* ****************************************************************** */
/*                         I43_SetVideoStd                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bStandard - The new output video standard.                        */
/*          I43VS_NTSC - NTSC standard.                               */
/*          I43VS_PAL  - PAL standard.                                */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the new output video standard.                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigSys                                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetVideoStd( I43_VIDEO_STD bStandard
                              ) CODE_SECT;


/* ****************************************************************** */
/*                         I43_PlaybackZoom                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wStartX - upper left corner of the zoom window (X axis).          */
/*  wStartY  - upper left corner of the zoom window (Y axis).         */
/*  wWidth   - the width of the zoom window.                          */
/*  wHeight  - the height of the zoom window.                         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to set the zoom window.             */
/* The COACH automatically calculates the horizontal scaling needed   */
/* in order to fit the zoom window to the display size. The vertical  */
/* scale is the same as the calculated horizontal scale.              */
/* Note: All parameters are in pixels.                                */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  PlaybackZoom                                                      */
/* ****************************************************************** */
I43_ERROR_CODE I43_PlaybackZoom( I43_UINT16 wStartX,
                                 I43_UINT16 wStartY,
                                 I43_UINT16 wWidth,
                                 I43_UINT16 wHeight
                               ) CODE_SECT;


/* ****************************************************************** */
/*                         I43_TuneDisplay                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wWhiteLevel - The new White Level value (range: 1-1023).          */
/*  bCBGain     - The new CB Gain value.                              */
/*  bCRGain     - The new CR Gain value.                              */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the display Saturation and Brightness to the    */
/* given values.                                                      */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  TuneDisplay                                                       */
/* ****************************************************************** */
I43_ERROR_CODE I43_TuneDisplay( I43_UINT16 wWhiteLevel,
                                I43_UINT8  bCBGain,
                                I43_UINT8  bCRGain
                              ) CODE_SECT;


/* ****************************************************************** */
/*                        I43_SetSensorWindow                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pConfig - Pointer to a configuration structure.                   */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to configure the sensor image       */
/* window.                                                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetSensorWindow                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetSensorWindow( I43_SENSOR_WINDOW_CONFIG* pConfig );


/* ****************************************************************** */
/*                        I43_SetImageSize                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wMode  - operational mode                                         */
/*                                                                    */
/*  wSizeX - Number of pixels in a line of the image.                 */
/*  wSizeY - Number of lines of the image.                            */
/*                                                                    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to configure the size of the image  */
/* that is captured before it is compressed.                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  AppSetImageSize                                                 */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetImageSize( I43_UINT16 wMode,
                                 I43_UINT16 wSizeX,
                                 I43_UINT16 wSizeY );


/* ****************************************************************** */
/*                        I43_ConfigImageResize                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bConfig      - Enables/Disables the Image Resizing operation:     */
/*                 0x00 - disable.                                    */
/*                 0x01 - Enable.                                     */
/*  wSizeX - Number of pixels in a line of the image.                 */
/*  wSizeY - Number of lines of the image.                            */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to configure the size of the image  */
/* that is captured before it is compressed.                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigImageResize                                                 */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigImageResize( I43_UINT8  bConfig,
                                      I43_UINT16 wSizeX,
                                      I43_UINT16 wSizeY
                                    ) CODE_SECT;



/* ****************************************************************** */
/*                        I43_DisplayWindow                           */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_DisplayWindow( I43_MODE bMode,  
                                              I43_UINT16 wStartX,
						                      I43_UINT16 wStartY,
						                      I43_UINT16 wWidth,
                                              I43_UINT16 wHeight,
                                              I43_UINT16 bKeepAr);

/* ****************************************************************** */
/*                         I43_GetDramImgParams                       */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_GetDramImgParams( I43_UINT8    byDramImgType,
                                                 I43_UINT8**  ppbyImageBuffer,
                                                 I43_UINT32*  puiWidth,
                                                 I43_UINT32*  puiHeight,
                                                 I43_UINT32*  puiStep      );


/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                           Graphic Commands                         */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                             I43_DrawText                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bStringLength - Length of the text string (in chars).             */
/*  wStartX       - Top left corner of the first letter with respect  */
/*                  to the display window (X-axis).                   */
/*  wStartY       - Top left corner of the first letter with respect  */
/*                  to the display window (Y-axis).                   */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* Through this function the host instructs the COACH to draw the     */
/* given string text at a specific location.                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  DrawText                                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_DrawText( I43_UINT8  bStringLength,
                                         I43_UINT16 wStartX,
                                         I43_UINT16 wStartY
                                       ) CODE_SECT;


/* ****************************************************************** */
/*                            I43_DrawTextID                          */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_DrawTextID( I43_UINT8  bStringLength,
                                           I43_UINT16 wStringID,
                                           I43_UINT16 wStartX,
                                           I43_UINT16 wStartY);

/* ****************************************************************** */
/*                            I43_DrawFile                            */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_DrawFile( I43GR_FILE_TYPE wFileType,
                                         I43_INT8*       cFileName,
                                         I43_INT16       wStartX,
                                         I43_INT16       wStartY,
                                         I43_UINT16      uwWidth,
                                         I43_UINT16      uwHeight );


/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                       Storage Media Management                     */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                       I43_SetDCFFreeChars                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bDir       - Indicates whether to set the directory chars or the  */
/*               file chars.                                          */
/*  bOperation - Indicates the operation to do in case the accessed   */
/*               file is a directory :                                */
/*               I43_DIR_OPEN_EXIST - Open existing.                  */
/*               I43_DIR_CREATE     - Create new directory.           */
/*               I43_DIR_SET_ONLY   - Only sets the directory chars.  */
/*  baChars[6] - Array that contains the DCF characters.              */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to set the DCF free characters to   */
/* be used in file names created by the COACH.                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetDCFFreeChars                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetDCFFreeChars( I43_UINT8 bDir,
                                    I43_UINT8 bOperation,
                                    I43_UINT8 baChars[6]
                                  ) CODE_SECT;



/* ****************************************************************** */
/*                         I43_SetNextDCFKey                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wDirNum  - The directory number.                                  */
/*  wFileNum - The file number.                                       */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to set the DCF key to be used for   */
/* new DCF files and directories.                                     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetNextDCFKey                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetNextDCFKey( I43_UINT16 wDirNum,
                                  I43_UINT16 wFileNum
                                ) CODE_SECT;



/* ****************************************************************** */
/*                          I43_SetFileType                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wType - The type of files to access in future API:                */
/*          The parameter is an OR operation of the following:        */
/*          I43_JPEG, I43_TIFF, I43_WAV, I43_AVI.                     */
/* Return Value:                                                      */
/*  None.                                                             */
/* ****************************************************************** */
/* This function alllows the host to set the Type of files that he    */
/* wishes to access in future host commands.                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetFileType                                                       */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetFileType( I43_UINT16 wType
                              ) CODE_SECT;



/* ****************************************************************** */
/*                          I43_SetFileName                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pbName     - Array containing the file name. (containing the      */
/*               name + the file extention).                          */
/*               The name should comply to the 8.3 name convention.   */
/*               The file name must be ended by a NULL (0x00) char.   */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function alllows the host to set the file_name parameter      */
/* for future file or directory operations.                           */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetFileName                                                       */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetFileName( I43_UINT8 pbName[ATT_FILE_NAME_SIZE/ATT_FILE_NAME_SIZE]
                              ) CODE_SECT;


/* ****************************************************************** */
/*                          I43_SetStatisticsPattern                  */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetStatisticsPattern( I43_UINT16 uwStartId, I43_UINT8 szPattern[STATISTIC_PATTERN_SIZE]) CODE_SECT;


/* ****************************************************************** */
/*                          I43_LoadStringFile                        */
/* ****************************************************************** */
I43_ERROR_CODE I43_LoadStringFile( I43_UINT8 pbName[ATT_FILE_NAME_SIZE/ATT_FILE_NAME_SIZE]
                              ) CODE_SECT;


/* ****************************************************************** */
/*                       I43_SetCurrentImage                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wImageIndex - the new current image index.                        */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the current Image for future operations such    */
/* as Restore, Erase, Lock etc.                                       */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetCurrentPicture                                                 */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetCurrentImage( I43_UINT16 wImageIndex
                                  ) CODE_SECT;



/* ****************************************************************** */
/*                       I43_GetCurrentImage                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwImageIndex - Pointer where to write the current image index.    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function retrieves the current picture pointer from the I43.  */
/* This pointer tells the host which picture is now defined as the    */
/* current one for operations such as Restore, Erase, Lock etc.       */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetCurrentImage                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetCurrentImage( I43_UINT16* pwImageIndex
                                  ) CODE_SECT;



/* ****************************************************************** */
/*                        I43_FormatStorageMedia                      */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bTarget - Indecates whether to format the resident memory or the  */
/*    flash card memory:                                              */
/*             I43_RESIDENT_MEM - Resident memroy.                    */
/*             I43_EXTENDED_MEM - flash card memroy.                  */
/*  pwSuccess - Tells if the Storage Media was formated successfully: */
/*       0 - Format succeeded.                                        */
/*       Other values - Format failed.                                */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to format the storage media.        */
/* Note: After format all data on the storage media is lost.          */
/*       Use this function with caution. The host in an operational   */
/*       system should NEVER format the resident media. Formatting    */
/*       the resident media is allowed only in the camera             */
/*       manufacturing line and by an authorized technician.          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  FormatStorageMedia                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_FormatStorageMedia( I43_UINT8   bTarget,
                                       I43_UINT16* pwSuccess
                                     ) CODE_SECT;



/* ****************************************************************** */
/*                          I43_SetCurrentPath                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the current Path to be used for storage         */
/* media operations.                                                  */
/* The path is read from the I43_CURRENT_PATH_MEM_LOCATION memory     */
/* location.                                                          */
/* The operation result is given in SR1 as a status code.             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetCurrentPath                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetCurrentPath( void
                                 ) CODE_SECT;



/* ****************************************************************** */
/*                       I43_GetFileAttributes                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bByName - Indicates whether the file is refferenced by name or    */
/*            by Index:                                               */
/*            I43_TRUE  - Use the file_name (set in I43_SetFileName). */
/*            I43_FALSE - Use the given Index parameter.              */
/*  pwSuccess - Tells if the operation completed successfully:        */
/*            0 -  Operation succeeded.                               */
/*            Other values - Operation failed.                        */
/*  pAttribute - Pointer to the Attribute structure.                  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function returns the file attribute structure of the file     */
/* that is pointed by the current image index.                        */
/* In case the file is accessed by name, the Attributes returned are  */
/* of the file specified by the given name.                           */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetFileAttributes                                                 */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetFileAttributes( I43_BOOL     bByName,
                                      I43_UINT16*  pwSuccess,
                                      FILE_ATTRIB* pAttribute
                                    ) CODE_SECT;



/* ****************************************************************** */
/*                          I43_FileOperation                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bByName - Indicates whether the file is refferenced by name or    */
/*            by Index:                                               */
/*            I43_TRUE  - Use the file_name (set in I43_SetFileName). */
/*            I43_FALSE - Use the Index of the Current Image.         */
/*  bTarget - Indicates the scope of the operation:                   */
/*            I43_SCOPE_FILE       - Access an ordinary file.         */
/*            I43_SCOPE_DIR        - Access a directory file.         */
/*            I43_SCOPE_DCF_OBJECT - Access a DCF object.             */
/*  bOperation - Indicates the operation to do:                       */
/*            I43_FILE_OP_UNLOCK                                      */
/*            I43_FILE_OP_LOCK                                        */
/*            I43_FILE_OP_ERASE                                       */
/*            I43_FILE_OP_COPY - Applicable only on DCF file/object.  */
/*            I43_FILE_OP_MOVE - Applicable only on DCF file/object.  */
/*            I43_FILE_OP_COPY_INTERDRIVE                             */
/*  pwSuccess - Pointer to where to write the operation result.       */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to perform file system operation    */
/* on files/dirs/DCF objects.                                         */
/* The result of the operation is returned in pbResult value:         */
/*  0 - Operation succeeded.                                          */
/*  Other values - Operation failed.                                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  FileOperation                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_FileOperation( I43_BOOL    bByName,
                                  I43_UINT8   bTarget,
                                  I43_UINT16  bOperation,
                                  I43_UINT16* pwSuccess
                                ) CODE_SECT;



/* ****************************************************************** */
/*                     I43_GetFirstFileAttribute                      */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwSuccess  - Tells if the operation completed successfully:       */
/*               0 -  Operation succeeded.                            */
/*               Other values - Operation failed.                     */
/*  pAttribute - Pointer to the Attribute structure.                  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function returns the file attribute structure of the first    */
/* file in the directory.                                             */
/* The first file is selected arbitrarily. Following this command the */
/* host can issue I43_GetNextFileAttribute function calls to read the */
/* attributes of all of the files in the directory.                   */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetFirstFileAttribute                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetFirstFileAttribute( I43_UINT16*  pwSuccess,
                                          FILE_ATTRIB* pAttribure
                                        ) CODE_SECT;



/* ****************************************************************** */
/*                     I43_GetNextFileAttribute                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwSuccess  - Tells if the operation completed successfully:       */
/*               0 -  Operation succeeded.                            */
/*               Other values - Operation failed.                     */
/*  pAttribute - Pointer to the Attribute structure.                  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function returns the file attribute structure of a file in    */
/* the directory.                                                     */
/* The file is selected arbitrarily. However, its attributes were not */
/* returned since the last call to I43_GetFirstFileAttributes. If     */
/* there is no file in teh directory that its attirbutes has not been */
/* returned since the last call to I43_GetFirstFileAttributes, a      */
/* failure code is returned, accompoanied by an attribute structure   */
/* that should be ignored by the host.                                */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetNextFileAttribute                                              */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetNextFileAttribute( I43_UINT16*  pwSuccess,
                                         FILE_ATTRIB* pAttribure
                                       ) CODE_SECT;


/* ****************************************************************** */
/*                       I43_MountStorageMedia                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bTarget - Indecates whether to mount the resident memory or the   */
/*    flash card memory:                                              */
/*             I43_RESIDENT_MEM - Resident memroy.                    */
/*             I43_EXTENDED_MEM - flash card memroy.                  */
/*  pwResult - Pointer to where to write the operation result.        */
/*             0 -  Operation succeeded.                              */
/*             Other values - Operation failed.                       */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function tells the I43 to mount a new storage media.          */
/* Typically it should be applied after a card had been inserted or   */
/* when the user wants to shift between the resident memory and the   */
/* flash card memory.                                                 */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  MountStorageMedia                                                 */
/* ****************************************************************** */
I43_ERROR_CODE I43_MountStorageMedia( I43_UINT8   bTarget,
                                      I43_UINT16* pwResult
                                    ) CODE_SECT;


/* ****************************************************************** */
/*                       I43_RegisterMedia                            */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_RegisterMedia( I43_UINT16 uwMediaId,
											  I43_UINT16 uwFlashType,
											  I43_UINT16 uwDeviceType);


/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                              OSD                                   */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */


/* ****************************************************************** */
/*                          I43_SetOSDCLUTEx                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  baCLUT[Comp][Entry] - array containing the CLUT values.           */
/*    Comp is one of Y(0),U(1) or V(2) color components.              */
/*    Entry is one of 1(0),2(1) or 3(2) CLUT entry number.            */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the color lookup table to be used for OSD fonts */
/* and rectangles, background color, and auto display of image titles.*/
/* The Y0, U0, V0 set is used for transparent OSD.                    */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetOSDCLUT                                                        */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_SetOSDCLUTEx(I43_UINT8 ucCLutEntryIndex,
                                            I43_UINT8 ucYComponent,
                                            I43_UINT8 ucUComponent,
                                            I43_UINT8 ucVComponent,
											I43_UINT8 ucBlending
                                           ) CODE_SECT;

/* ****************************************************************** */
/*                        I43_LoadFontFile                            */
/* ****************************************************************** */

I43_ERROR_CODE I43_LoadFontFile(I43_INT8 *pbName);

/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                           New OSD                                  */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */


/* ****************************************************************** */
/*                      I43_OSDTextOut                                */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bDisplayID - The ID of the display memory.                        */
/*  wStartX    - X value of the first letter's top left corner.       */
/*  wStartY    - Y value of the first letter's top left corner.       */
/*  wLength    - The length of the string in chars.                   */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to display a given string at a      */
/* specific location on the display.                                  */
/* The string is given through I43_OSD_TEXT_OUT_MEM_LOCATION.         */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*    OsdTextOut                                                      */
/* ****************************************************************** */
I43_ERROR_CODE I43_OSDTextOut( I43_UINT8  bDisplayID,
                               I43_UINT16 wStartX,
                               I43_UINT16 wStartY,
                               I43_UINT16 wLength
                             ) CODE_SECT;

/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                        High Light Rectangles                       */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                           I43_SetHLRect                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pSettings - Pointer to a HL_RECT_SETTINGS structure.              */
/*  The structure has the following fields:                           */
/*  bRectID - The current rect index (range 0-1).                     */
/*  wStartX - The horizontal part of the upper left coordinate        */
/*            of the rectangle, with respect to the active            */
/*            display window.                                         */
/*  wStartY - The vertical part of the upper left coordinate.         */
/*  wWidth  - The horizontal length of the rectangle. must be even.   */
/*  wHeight - The vertical length of the rectangle. must be even.     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets some of the given OSD rectangle parameters.     */
/* The function sets the rectangles location and size.                */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetOSDRect                                                        */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetHLRect( HL_RECT_SETTINGS* pSettings
                            ) CODE_SECT;



/* ****************************************************************** */
/*                          I43_ConfigHLRect                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pConfig - pointer to a HL_RECT_CONFIGURATION structure.           */
/*  The following are fields in the structure:                        */
/*  bRectID - The current rect index (range 0-1).                     */
/*  bBlendFactor - The current rect Blend Factor.                     */
/*      I43HL_RECT_OSD_ONLY        = no blending (100% OSD).          */
/*      I43HL_RECT_OSD_IMAGE_BLEND = 50% blending.                    */
/*  bInteriorColor - Color index of the interior color.               */
/*  bFrameColor - Color index of the framework color.                 */
/*  bWidth - The frame horizontal thickness, in pairs of pixels.      */
/*  bHeight - The frame vertical thickness, in field lines.           */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function configs the chosen High Loght Rectangle.             */
/* The function sets the blending factor, colors and appearence of    */
/* the High Light Rectangle.                                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigOSDRect                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigHLRect( HL_RECT_CONFIGURATION* pConfig
                               ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_ShowHLRect                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bRectID - The current rect index (range 0-1).                     */
/*  bShow - I43_TRUE  = Show rectangle.                               */
/*          I43_FALSE = Hide rectangle.                               */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function shows or hides the chosen high light rectangle.      */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ShowOSDRect                                                       */
/* ****************************************************************** */
I43_ERROR_CODE I43_ShowHLRect( I43_HL_RECT_ID bRectID,
                               I43_BOOL       bShow
                             ) CODE_SECT;



/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                             Thumbnails                             */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                        I43_ConfigThumbnail                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  Configuration - Pointer to a THUMBNAIL_CONFIGURATION structure    */
/*                  that holds all the configuration information.     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the following parameters:                       */
/*  number of thumbnail per line.                                     */
/*  number of thumbnail per Column.                                   */
/*  The Horizontal gap size to the first thumbnail.                   */
/*  The Horizontal gap size between thumbnails.                       */
/*  The Horizontal gap size after the last thumbnail.                 */
/*  The Vertical gap size to the first thumbnail.                     */
/*  The Vertical gap  between thumbnail.                              */
/*  The Vertical gap size after the last thumbnail.                   */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigThumbnail                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigThumbnail( THUMBNAIL_CONFIGURATION* Configuration
                                  ) CODE_SECT;



/* ****************************************************************** */
/*                         I43_ThumbnailShiftUp                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bNum - The number of thumbnails to shift.                         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function shifts the displayed thumbnails bNum thumbnails up.  */
/* In case the current thumbnail is the upper left thumbnail, the I43 */
/* restores the previous thumbnails according to the Thumbnail        */
/* manipulation scheme.                                               */
/* If the number of the new current image (i.e. the current image     */
/* plus the Number Of Shifts) is larger than the last image in the    */
/* files table the Coach restarts from the first image on a modulo    */
/* bases.                                                             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ThumbnailShiftUp                                                  */
/* ****************************************************************** */
I43_ERROR_CODE I43_ThumbnailShiftUp( I43_UINT8 bNum
                                   ) CODE_SECT;



/* ****************************************************************** */
/*                        I43_ThumbnailShiftDown                      */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bNum - The number of thumbnails to shift.                         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function shifts the displayed thumbnails bNum thumbnails down.*/
/* In case the current thumbnail is the lower right thumbnail, the I43*/
/* restores the next thumbnails according to the Thumbnail            */
/* manipulation scheme.                                               */
/* If the number of the new current image (i.e. the current image     */
/* plus the Number Of Shifts) is larger than the last image in the    */
/* files table the Coach restarts from the first image on a modulo    */
/* bases.                                                             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ThumbnailShiftDown                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_ThumbnailShiftDown( I43_UINT8 bNum
                                     ) CODE_SECT;



/* ****************************************************************** */
/*                        I43_GetFirstThumbnail                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pwFirstThumbnail - Pointer to write first displayed thumbnail   */
/*                       index.                                       */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This command allows the host to retrieve the index of the first    */
/*    displayed thumbnail while the COACH is in Playback Thumbnails   */
/*    mode.                                                           */
/* The returned index is the index that is used by the COACH file     */
/*    system.                                                         */
/* This command is useful for hosts that need to know which           */
/*    thumbnails are currently displayed on the output display.       */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*    GetFirstThumbnail                                               */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetFirstThumbnail( I43_UINT16 *pwFirstThumbnail
                                    ) CODE_SECT;



/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                                Audio                               */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */

/* ****************************************************************** */
/*                        I43_CaptureAudioMessage                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None                                                              */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function tells the I43 to start capturing an audio message.   */
/* The recording terminates as a result of the                        */
/* first event of the following:                                      */
/*      1. The I43_StopRecording command was sent.                    */
/*      2. There is no more place in the the flash card.              */
/*      3. Recording time is expired.                                 */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  CaptureAudioMessage                                               */
/* ****************************************************************** */
I43_ERROR_CODE I43_CaptureAudioMessage( void
                                      ) CODE_SECT;



/* ****************************************************************** */
/*                        I43_StopRecording                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwLengthHigh - Pointer to where to write the recording length     */
/*                  (MS word).                                        */
/*  pwLengthLow  - Pointer to where to write the recording length     */
/*                  (LS word).                                        */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function tells the I43 to stop capturing an audio message.    */
/* The returned recording length is in bytes.                         */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  StopRecording                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_StopRecording( I43_UINT16* pwLengthHigh,
                                  I43_UINT16* pwLengthLow
                                ) CODE_SECT;

/* ****************************************************************** */
/*                        I43_AudioConfig                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  uwLinearCfg     - Linear configuration                            */
/*  uwSamplingRate  - Sampling rate in Herz                           */
/*  uwSDivider      - S-Divider                                       */
/*  uwSDivider      - F-Divider for speech codec, Alignment for       */
/*                    linear codec                                    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function defines audio serial port configuration.             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  AudioConfig                                                       */
/* ****************************************************************** */
I43_ERROR_CODE I43_AudioConfig( I43_UINT8  uwLinearCfg,
                                I43_UINT16 uwSamplingRate,
                                I43_UINT16 uwSDivider,
                                I43_UINT16 uwFDivider
                                ) CODE_SECT;


/* ****************************************************************** */
/*                        I43_PlayAudioMessage                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function plays back the audio message that is currently in    */
/* present in DRAM.                                                   */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  PlayAudioMessage                                                  */
/* ****************************************************************** */
I43_ERROR_CODE I43_PlayAudioMessage( void
                                   ) CODE_SECT;



/* ****************************************************************** */
/*                        I43_RecordPlayAudio                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  uwOpType     - I43_AUDIO_RECORD: record audio,                    */
/*                 I43_AUDIO_PLAY:   play audio                       */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function records or play the audio for dictaphone mode.       */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  RecordPlayAudio                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_RecordPlayAudio( I43_UINT8 uwOpType
                                  ) CODE_SECT;



/* ****************************************************************** */
/*                              I43_Beep                              */
/* ****************************************************************** */
I43_ERROR_CODE I43_Beep(I43_UINT16 uwDuration, I43_UINT16 uwFreq);


/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                            DPOF Commands                           */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */


/* ****************************************************************** */
/*                           I43_DPOFInit                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  uiDbSize        - A size of memory that is assigned for DPOF DB.  */
/*                    The size should be in bytes.                    */
/*  bPrintFile      - A flag which specifies whether the DPOF DB      */
/*                    should treat the Print file.                    */
/*  bTransferFile   - A flag which specifies whether the DPOF DB      */
/*                    should treat the Transfer file.                 */
/*  bSlideShowFile  - A flag which specifies whether the DPOF DB      */
/*                    should treat the Slide Show file.               */
/*  uiAutoPlayN     - A number of the Autoplay (SlideShow) file, in   */
/*                    range of [0..9] as defined in the DPOF standard */
/*                    If bSlideShowFile == FALSE, then this parameter */
/*                    is ignored.                                     */
/*                    GENERALLY this number is supposed to be 0.      */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/*            Possible errors - (1) Failed to allocate memory.        */
/*                              (2) Failed to load one (at least) of  */
/*                                  the DPOF files.                   */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to initialize */
/* the DPOF shadow in the COACH DRAM.                                 */
/* NOTES: (1) When calling this function, it's assumed that no DPOF   */
/*            DB was initialized before, or if it was, then it was    */
/*            released before this function was called.               */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  DPOFInit                                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFInit(I43_UINT32 uiDbSize,
                            I43_BOOL   bPrintFile,
                            I43_BOOL   bTransferFile,
                            I43_BOOL   bSlideShowFile,
                            I43_UINT8  uiAutoPlayN      );

/* ****************************************************************** */
/*                         I43_DPOFReadWriteFile                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  eFileType - Type of DPOF file to which the suitable jobs will be  */
/*              wrote.                                                */
/*              File types:                                           */
/*                  I43_DPOF_PRINT_FILE                               */
/*                  I43_DPOF_TRANSFER_FILE                            */
/*                  I43_DPOF_SLIDE_SHOW_FILE                          */
/*                  I43_DPOF_ALL_FILES - write all files              */
/*  uiOp      - Required operation - Read / Write                     */
/*                  DPOF_FILE_OP_LOAD - Loads the file and APPENDS    */
/*                                      loaded jobs to existing DB    */
/*                                      (the existing jobs will not   */
/*                                      be destroyed)                 */
/*                  DPOF_FILE_OP_OVERLOAD - Destroys the existing DB  */
/*                                          and loads the new (from   */
/*                                          the file) instead         */
/*                  DPOF_FILE_OP_WRITE - Flushes the DB to the        */
/*                                       specified file               */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to read/write */
/* the DPOF file(s) which is stored in File/DRAM, from/to the storage */
/* media.                                                             */
/* The file will be wrote to the storage media iff the file has been  */
/* changed since last "write".                                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  WriteDPOFFile                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFReadWriteFile(I43_DPOF_FILE_TYPE eFileType,
                                     I43_DPOF_FILE_OP   uiOp        );



/* ****************************************************************** */
/*                         I43_DPOFRelease()                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bNeedWrite - A boolean type, parameter. Specifies whether the     */
/*               DPOF DB should be wrote (all files) before it's      */
/*               destroyed from the memory.                           */
/*               When the value is I43_TRUE, the DPOF DB first will   */
/*               be wrote to all of the files, then destroyed.        */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to destruct   */
/* the DPOF file(s) which is stored in DRAM and to release all of the */
/* resources it occupies. The caller can to instruct to COACH to      */
/* first to store (write) the DPOF DB to the phisical files, then to  */
/* destroy it.                                                        */
/* NOTES: (1) When calling this function, it's assumed that the DPOF  */
/*            DB (represented by the given handle) has been           */
/*            initialized before.                                     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFRelease(I43_BOOL bNeedWrite);

/* ****************************************************************** */
/*                         I43_DPOFSetHeaderParam                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  eFileType   - A type of file, whose header field will be SET      */
/*  eHdrParamId - An ID of the parameter which should be set/         */
/*                Eeach parameter has its own IDentifier.             */
/*  szValue     - The pointer to string which should point to null    */
/*                  terminated string containing a new value for the  */
/*                  specified field and the string will be copied and */
/*                  can be reused later.                              */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to SET      */
/* any field of the specified file's header.                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFSetHeaderParam( I43_DPOF_FILE_TYPE      eFileType,
                                       I43_DPOF_HDR_PARAMID    eHdrParamId,
                                       I43_UINT8               szValue[]    );


/* ****************************************************************** */
/*                         I43_DPOFGetHeaderParam                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  eFileType   - A type of file, whose header field will be GET      */
/*  eHdrParamId - An ID of the parameter which should be get.         */
/*                Eeach parameter has its own IDentifier.             */
/*  szValue     - The pointer to string which has to point to an      */
/*                allocated buffer to which the parameter's value     */
/*                will be copied.                                     */
/*                  It's strongly recommended to allocate the buffer  */
/*                  at least as it's defined in the DPOF std.         */
/*                  accodring to the parameter's maximal length.      */  
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to GET      */
/* any field of the specified file's header.                          */
/* NOTE: The buffer MUST be allocated before this function is called, */
/*       while it's size has to fit the specified parameter size.     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetHeaderParam( I43_DPOF_FILE_TYPE   eFileType,
                                       I43_DPOF_HDR_PARAMID    eHdrParamId);

/* ****************************************************************** */
/*                         I43_DPOFAddJob                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  eJobType - The type of DPOF Job to create.                        */
/*      I43_DPOF_JOBTYPE_PRINT_STD - Print Standard Job               */
/*      I43_DPOF_JOBTYPE_PRINT_IDX - Print Index Job                  */
/*      I43_DPOF_JOBTYPE_PRINT_MUL - Print Multiple Job               */
/*      I43_DPOF_JOBTYPE_PRINT_SIZ - Print Specified Size Job         */
/*      I43_DPOF_JOBTYPE_TRANSFER  - Transfer Job                     */
/*      I43_DPOF_JOBTYPE_SLIDESHOW - Slide Show Job                   */
/*  uiDcfIdx - A DCF index of image file. The image will be added     */
/*      to the created job, enclosed in a new Source node, which will */
/*      be the first in the Job.                                      */
/*      This parameter is optional and in case of 0 no images will be */
/*      added to the job.                                             */
/*  szDate - A pointer to a string containing a date, which will be  */
/*      attached to the image specified in uiSrcDcfIdx parameter.     */
/*      In case no image was specified, this parameter will be        */
/*      ignored.                                                      */
/*      This parameter is optional and in case of NULL no date will   */
/*      be added to the image.                                        */
/*  phJobId - Pointer to a new job handle. If the function fails,this */
/*      parameter vill be NULL                                        */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to create   */
/* new job node, and to add it to the appropriate DB. The type of DB  */
/* to which the job will be added, is determined in respect to the    */
/* given Job Type. The job is added to the end of the DB (appropriate */
/* linked list).                                                      */
/*   The Process ID is assigned automatically to the created job, and */
/* its type is as specified in the given parameter.                   */
/*   All of the job's attributes, except of pid and type, are         */
/* initialized to default values.                                     */
/* OPTIONAL: A single image with date can be attached to the job. In  */
/*           case the image has been specified, a new source node is  */
/*           created and added to the created job as first source.    */
/*           The type of the image source will be determined in       */
/*           respect to the image file extension as follows:          */
/*              .jpg - EXIF2 -J                                       */
/*              .tif - EXIF2 -T                                       */
/*           This option is very useful when a user needs to create a */
/*           standard job.                                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE  I43_DPOFAddJob(I43_DPOF_JOB_TYPE eJobType,
                               I43_UINT16        uiDcfIdx,
                               I43_UINT8         szDate[],
                               I43_DPOF_JOBID*   phJobId   );

/* ****************************************************************** */
/*                         I43_DPOFRemoveJob                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  hJob - Handle of the job, that sould be removed                */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to destruct   */
/* the given job. It finds the job in proper DB (the DB is determined */
/* in respect to the Job type) removes it from the DB, then destroys  */
/* the job and releases the resources                                 */
/* NOTES: the PID of the job will be reused                           */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFRemoveJob(I43_DPOF_JOBID hJob);


/* ****************************************************************** */
/*                         I43_DPOFGetFirstJobInFile                  */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  eFileType - The DPOF File type, from which the first job will     */
/*              be extracted.                                         */
/*  phJobId   - Pointer to the handle of the required job.In case the */
/*              file is empty, NULL will be assigned                  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to return   */
/* the first job of the specified file.                               */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetFirstJobInFile(I43_DPOF_FILE_TYPE eFileType,
                                         I43_DPOF_JOBID* phJobId        );

/* ****************************************************************** */
/*                         I43_DPOFGetNextJob                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  hJob - A handle of job, that job next to him should be         */
/*            returned.                                               */
/*  phJobId   - Pointer to the handle of the required job.In case the */
/*              given job is last in the file, NULL will be assigned  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to return   */
/* a handle of a job, which is next in list after the given job.      */
/* NOTE: The order of jobs in the DB list is as it was added to the   */
/*       DB (in respect to the type of DB (PRINT,TRANSFER,SLIDE SHOW) */
/*       or, in case the DB has been loaded from a DPOF File, the     */
/*       order of the jobs in the list will be as it's appeared in    */
/*       the file.                                                    */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetNextJob(I43_DPOF_JOBID hJob,
                                  I43_DPOF_JOBID* phJobId        );

/* ****************************************************************** */
/*                         I43_DPOFGetPrevJob                         */
/* ****************************************************************** */
/*  hJob - A handle of job, that job previous to him should be     */
/*            returned.                                               */
/*  phJobId   - Pointer to the handle of the required job.In case the */
/*              given job is last in the file, NULL will be assigned  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to return   */
/* a handle of a job, which is previous in list before the given job. */
/* NOTE: The order of jobs in the DB list is as it was added to the   */
/*       DB (in respect to the type of DB (PRINT,TRANSFER,SLIDE SHOW) */
/*       or, in case the DB has been loaded from a DPOF File, the     */
/*       order of the jobs in the list will be as it's appeared in    */
/*       the file.                                                    */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetPrevJob(I43_DPOF_JOBID hJob,
                                  I43_DPOF_JOBID* phJobId        );

/* ****************************************************************** */
/*                         I43_DPOFSetJobParamInt                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  hJob     - A handle of a job whose parameter should be set.    */
/*  eJobParamId - An ID of the parameter which should be set.         */
/*                Eeach parameter has its own IDentifier.             */
/*                NOTE: The parameter's type should be integer.       */ 
/*  uiValue     - The New integer value that should be assigned to    */  
/*                the job's parameter.                                */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to assign an  */
/* ineger value to specified parameter (whose type has to be integer) */
/* of given job.                                                      */
/* NOTE: The MSG, DAT, VID, SND files should be set through this      */
/*       function by passing thier DCF index                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFSetJobParamInt(I43_DPOF_JOBID hJob,
                                      I43_DPOF_JOB_PARAMID eJobParamId,
                                      I43_UINT32 uiValue);

/* ****************************************************************** */
/*                         I43_DPOFGetJobParamInt                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  hJob     - A handle of a job whose parameter should be         */
/*                returned.                                           */
/*  eJobParamId - An ID of the parameter whose value should be        */
/*                returned.                                           */
/*                Eeach parameter has its own IDentifier.             */
/*                NOTE: The parameter's type should be integer.       */ 
/*  pValue      - Pointer to the buffer which will contain the        */
/*                required integer value                              */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to return   */
/* an integer value of spesicied parameter of the given job.          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetJobParamInt(I43_DPOF_JOBID hJob,
                                      I43_DPOF_JOB_PARAMID eJobParamId,
                                      I43_UINT32* pValue );

/* ****************************************************************** */
/*                         I43_DPOFSetJobParamStr                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  hJob     - A handle of a job whose parameter should be set.    */
/*  eJobParamId - An ID of the parameter which should be set.         */
/*                Eeach parameter has its own IDentifier.             */
/*                NOTE: (1) The parameter's type should be PCHAR.     */ 
/*  szValue    - The New PCHAR value that should be assigned to      */  
/*                the job's parameter.                                */
/*                NOTE: (1) The value should be a pointer to a string */
/*                      (2) Some strings have a fixed length.
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to assign an  */
/* PCHAR value to specified parameter (whose type has to be PCHAR)    */
/* of given job.                                                      */
/* NOTE: (1) The szValue shoud be a poiter to a string that (the     */
/*           string) will be COPIED to another container, so the      */
/*           string himself can be reused / destructed / changed      */
/*           the moment the function has terminated.                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFSetJobParamStr(I43_DPOF_JOBID        hJob,
                                      I43_DPOF_JOB_PARAMID  eJobParamId,
                                      I43_UINT8                 szValue[]     );

/* ****************************************************************** */
/*                         I43_DPOFGetJobParamStr                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  hJob        - A handle of a job whose parameter should be         */
/*                returned.                                           */
/*  eJobParamId - An ID of the parameter whose value should be        */
/*                returned.                                           */
/*                Eeach parameter has its own IDentifier.             */
/*                NOTE: The parameter's type should be PCHAR.         */ 
/*  pBuffer     - A buffer to which the string will be copied. It's   */
/*                recommended the size of the buffer should be at     */
/*                least as the maximal parameter length+1, as it's    */
/*                defined in the DPOF std.                            */
/* Return Value:                                                      */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to copy a   */
/* value ( \0 terminated string) of specified parameter of the given  */
/* job to the buffer                                                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetJobParamStr(I43_DPOF_JOBID hJob,
                                      I43_DPOF_JOB_PARAMID eJobParamId);

/////////////////////////////////////////////////////////////////////\\
// >>> DEFINITION: Descriptor (DSC)                                  \\
//                 ==========                                        \\
// For complete definition see DPOF v1.1 Spec.                       \\
// The DSC field is limited to length of 12 characters.              \\
// Can be one of the following types: DATE, CMT, FID                 \\
/////////////////////////////////////////////////////////////////////\\


/////////////////////////////////////////////////////////////////////\\
// >>> DEFINITION: Source (Src)                                      \\
//                 ======                                            \\
// Source is defined as data structure which contains a compressed   \\
// representation of full path of image source and 3 possible DSCs:  \\
//  1) Date                                                          \\
//  2) A pointer to CMT                                              \\
//  3) A pointer to FID                                              \\
/////////////////////////////////////////////////////////////////////\\

/* ****************************************************************** */
/*                         I43_DPOFAddSrcToJob                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  hJob     - A handle to job, to whom the source will be added   */
/*  uiSrcDcfIdx - A DCF index of the Image Source.                    */
/*  uiImgType - An image type according to the DPOF standard          */
/*              definition.                                           */
/*      I43_DPOF_IMG_FMT_CIFF1                                        */
/*      I43_DPOF_IMG_FMT_EXIF1_J                                      */
/*      I43_DPOF_IMG_FMT_EXIF1_T                                      */
/*      I43_DPOF_IMG_FMT_EXIF2_J                                      */
/*      I43_DPOF_IMG_FMT_EXIF2_T                                      */
/*      I43_DPOF_IMG_FMT_JFIF                                         */
/*      I43_DPOF_IMG_FMT_FPX1                                         */
/*  szDate     - A pointer to string containing date.                */
/*                NOTE: This parameter is optional. In case the       */
/*                      source should be created without date, the    */
/*                      value of the parameter should be NULL.        */
/*  phSrcId     - Pointer to a just created Src. In case the function */
/*                fails, this parameter will contail NULL             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to create a */
/* new source and add it to the given job, while the source node will */
/* be added at the end of the list of sources in the job.             */
/* NOTE: In Slide Show Job can be no more than one source.            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFAddSrcToJob(I43_DPOF_JOBID    hJob,
                                   I43_UINT16        uiSrcDcfIdx,
                                   I43_UINT8             szDate[],
                                   I43_DPOF_SRCID*   phSrcId   );

/* ****************************************************************** */
/*                         I43_DPOFRemoveSrc                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  hJob - A handle to the job, from which the specified source    */
/*            will be removed.                                        */
/*  psSrcId - A handle of source that should be removed.              */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to remove a   */
/* specified source from a given job. after the removal, the Source   */
/* node will be destroyed and the resources will be released.         */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFRemoveSrc(I43_DPOF_JOBID hJob,
                                 I43_DPOF_SRCID psSrcId);



/* ****************************************************************** */
/*                         I43_DPOFRemoveImage                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  hJob  - A handle of Job from which the sources containing the  */
/*             specified image source will be removed.                */
/*             Due to remove the image from the whole DPOF DB, this   */
/*             parameter must be NULL.                                */
/*  uiDcfIdx - A DCF Index of image that should be removed.           */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to remove all */
/* of the sources in the specified job that contain the given image   */
/* file.                                                              */
/* This function enables also to all such sources from the whole      */
/* DPOF DB and this is by specifing the hJob as NULL. This         */
/* function generally used when some image file is supposed to be     */
/* removed from DCF.                                                  */
/* While removing an image from the DPOF DB (all three DBs), all of   */
/* the source nodes that contain the image, will be removed too. In   */
/* case such source has been removed and the job that contained the   */
/* source, contains no more sources, this Job will be removed too.    */
/* NOTE: This function should be called BEFORE the image file has     */
/*       been removed from DCF.                                       */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFRemoveImage(I43_DPOF_JOBID hJob,
                                   I43_UINT16 uiDcfIdx);

/* ****************************************************************** */
/*                         I43_DPOFGetImageData                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  uiDcfIdx  - A DCF Index of image that should be found in the DB.  */
/*  eFileType - A type of DPOF file in which the image should looked  */
/*              for.                                                  */
/*  phsJobId  - A pointer to handle of First found Job in which the   */
/*              source containing the specified image is found.       */
/*  phsSrcId  - A pointer to handle of first found Source which       */
/*              contains the specified image.                         */
/*  NOTE: if the specified image wasn't found in the DB, the phsJobId */
/*        and phsSrcId will have NULL value.                          */
/* Return Value:                                                      */

///*  Success - I43ERR_OK (in case, the image has been found in the DB) */                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to search the */
/* DPOF DB (of specified type: PRINT / TRANSFER...) for the given     */
/* image. The function returns the "found" status and a handle of the */
/* first job in the DB that contained a sorce with the image, along   */
/* with a hadle of the source (also the first found). In case the     */
/* image isn't in the DB, the handles will have NULL values and the   */
/* function will return appropriate error status.                     */
/* NOTE: The function returns a FIRST encountered Job and Source      */
/*       containing the image.                                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetImageData(I43_UINT16 uiDcfIdx,
                                    I43_DPOF_FILE_TYPE eFileType,
                                    I43_DPOF_JOBID* phsJobId,
                                    I43_DPOF_SRCID* phsSrcId);

/* ****************************************************************** */
/*                         I43_DPOFSetSrcParam                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  psSrcId     - A handle of source whose parameter should be set.   */
/*  eSrcParamId - An ID of the parameter that should be set.          */
/*                Eeach parameter has its own IDentifier.             */
/*                NOTE: The parameter's type should be PCHAR.         */ 
/*  szValue    - The pointer to a buffer which contains a null       */
/*                terminated string. The string will be copied to     */
/*                designated buffer, so afterwards it can be          */
/*                changed / destroyed without any impact on the       */
/*                assigned value.                                     */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to assign new */
/* values to parameters of Source data structure. All of the          */
/* parameters but the image path can be assigned. All of the          */
/* parameters that this function can set must be PCHAR type.          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFSetSrcParam(I43_DPOF_SRCID psSrcId,
                                   I43_DPOF_SRC_PARAMID eSrcParamId,
                                   I43_UINT8 szValue[]);

/* ****************************************************************** */
/*                         I43_DPOFGetSrcParam                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  psSrcId     - A handle of source whose parameter's value should   */
/*                be returned.                                        */
/*  eSrcParamId - An ID of the parameter whose value should be        */
/*                returned.                                           */
/*                Eeach parameter has its own IDentifier.             */
/*                NOTE: The parameter's type should be PCHAR.         */ 
/* Return Value:                                                      */
/*  Success - A pointer to a string on which the parameter points.    */
/*  Fail    - NULL.                                                   */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to return a   */
/* value of a specified parameter of a given source.                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetSrcParam(I43_DPOF_SRCID psSrcId,
                                   I43_DPOF_SRC_PARAMID eSrcParamId);

/* ****************************************************************** */
/*                         I43_DPOFGetSrcIdx                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  psSrcId - A handle of source, whose DCF Index should be returned. */
/* Return Value:                                                      */
/*  Success - The DCF Index.                                          */
/*  Fail    - I_43_DPOF_UINT32_ERROR.                                 */
/* ****************************************************************** */
/* This function enables the host to instruct the COACH to return a   */
/* DCF Index of the image file, which is represented in the given     */
/* source.                                                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
/***
I43_UINT16 I43_DPOFGetSrcIdx(I43_DPOF_SRCID psSrcId);
***/
/* ****************************************************************** */
/*                         I43_DPOFGetFirstSrc                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  hJob - A handle of a job whose first source (his handle) will  */
/*            be returned.                                            */
/*  phFirstSrc - Pointer to the required Src handle or NULL in case   */
/*               the job is empty
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to return a */
/* handle of the first source in the given job.                       */
/* NOTE: The order of sources in the DB list is as it was added to    */
/*       the job or, in case the DB has been loaded from a DPOF File, */
/*       the order of the sources in the list will be as it's         */
/*       appeared in the file.                                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetFirstSrc(I43_DPOF_JOBID  hJob,
                                   I43_DPOF_SRCID* phFirstSrc );

/* ****************************************************************** */
/*                         I43_DPOFGetNextSrc                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  psSrcId - A handle of the source, that the next source after him  */
/*            should be returned.                                     */
/*  phNextSrc - Pointer to the required Src handle or NULL in case   */
/*              the given Src is last in the job
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to return a */
/* handle to the next source in job.                                  */
/* NOTE: The order of sources in the DB list is as it was added to    */
/*       the job or, in case the DB has been loaded from a DPOF File, */
/*       the order of the sources in the list will be as it's         */
/*       appeared in the file.                                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetNextSrc( I43_DPOF_SRCID psSrcId,
                                   I43_DPOF_SRCID* phNextSrc );

/* ****************************************************************** */
/*                         I43_DPOFGetPrevSrc                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  psSrcId - A handle of the source, that the previous source before */
/*            him should be returned.                                 */
/*  phPrevSrc - Pointer to the required Src handle or NULL in case   */
/*              the given Src is first in the job
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*   This function enables the host to instruct the COACH to return a */
/* handle to the previous source in job.                              */
/* NOTE: The order of sources in the DB list is as it was added to    */
/*       the job or, in case the DB has been loaded from a DPOF File, */
/*       the order of the sources in the list will be as it's         */
/*       appeared in the file.                                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  <><><><><><><><><> TBD                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_DPOFGetPrevSrc(I43_DPOF_SRCID psSrcId,
                                  I43_DPOF_SRCID* phPrevSrc  );


/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                        File Transfer Commands                      */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                     I43_GetVideoCaptureImageSize                   */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwSizeX  - Pointer where to write the X size of the input image.  */
/*  pwSizeY  - Pointer where to write the Y size of the input image.  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* Through this function the host can retrieve the image size.        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetVideoCaptureImageSize                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetVideoCaptureImageSize( I43_UINT16* pwSizeX,
                                             I43_UINT16* pwSizeY
                                           ) CODE_SECT;



/* ****************************************************************** */
/*                             I43_XMTFile                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bAccessMethod - Tells the I43 whether to access the file by Index */
/*    or File Name:                                                   */
/*    I43_FALSE - Access by Index. The accessed file is the file      */
/*                corresponding to the current image.                 */
/*    I43_TURE  - Access by File Name. The accessed file is the file  */
/*                corresponding to the name that was last set using   */
/*                the I43_SetFileName API.                            */
/*  bTarget     - the target where to transfer the file to:           */
/*    I43_FALSE - Current host.                                       */
/*    I43_TRUE  - SCP, IrDA.                                          */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function tells the I43 to start transferring the requested    */
/* File from the storage media through the required channel.          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  XMTFile                                                           */
/* ****************************************************************** */
I43_ERROR_CODE I43_XMTFile( I43_BOOL bAccessMethod,
                            I43_BOOL bTarget
                          ) CODE_SECT;



/* ****************************************************************** */
/*                             I43_RCVFile                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wFileSizeHigh - the file size in bytes (High Byte).               */
/*  wFileSizeLow  - the file size in bytes (Low Byte).                */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* Through this function the host can load a file to the COACH.       */
/* The file name should be set via I43_SetFileName API prior to       */
/* sending the I43_RCVFile API.                                       */
/* The file type is determined by the extension of the file name.     */
/* The file Size is given in bytes. If the file size is not even a    */
/* padding byte should be added.                                      */
/* The File itself is read from the I43_RCV_FILE_MEM_LOCATION.        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  RCVFile                                                           */
/* ****************************************************************** */
I43_ERROR_CODE I43_RCVFile( I43_UINT16 wFileSizeHigh,
                            I43_UINT16 wFileSizeLow
                          ) CODE_SECT;



/* ****************************************************************** */
/*                             I43_GetImage                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function tells the I43 to start transferring the image from   */
/* DRAM. The image fromat is EXIF 2.0 format including thumbnail.     */
/* The image is transfered to a predefined memory location.           */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetImage                                                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetImage( void
                           ) CODE_SECT;

/* ****************************************************************** */
/*                       I43_StartVideoCapture                        */
/* ****************************************************************** */
I43_ERROR_CODE I43_StartVideoCapture( I43_UINT8 bFrameRate,
                                      I43_UINT2 bFormat
                                    ) CODE_SECT;

/* ****************************************************************** */
/*                          I43_XMTThumbnail                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bAccessMethod - Tells the I43 whether to access the file by Index */
/*    or File Name:                                                   */
/*    I43_FALSE - Access by Index. The accessed file is the file      */
/*                corresponding to the current image.                 */
/*    I43_TURE  - Access by File Name. The accessed file is the file  */
/*                corresponding to the name that was last set using   */
/*                the I43_SetFileName API.                            */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function tells the I43 to start transferring the Thumbnail    */
/* of required EXIF file from the storage media to the current host.  */
/* The data is written to a predefined memory location.               */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  XMTThumbnail                                                      */
/* ****************************************************************** */
I43_ERROR_CODE I43_XMTThumbnail( I43_BOOL bAccessMethod
                               ) CODE_SECT;



/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                USB Configuration & Control Commands                */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                            I43_QueryStatus                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_QueryStatus( I43_UINT16* pwUSR1,
                                I43_UINT16* pwUSR2
                              ) CODE_SECT;

/* ****************************************************************** */
/*                            I43_SetUsbMode                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetUsbMode( I43_USB_MODE wMode
                              ) CODE_SECT;

/* ****************************************************************** */
/*                            I43_UsbConnect                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_UsbConnect(I43_BOOL bConnect);
                              
/* ****************************************************************** */
/*                          I43_WaitHostComSem                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwAccess - Pointer where to write whether access is granted or    */
/*    not:                                                            */
/*    The LS byte specify the access permition:                       */
/*    I43HSM_ACCESS_DENIED - Access denied, host is blocked.          */
/*    I43HSM_ACCESS_WRITE  - Buffer empty, host is allowed to write.  */
/*    I43HSM_ACCESS_READ   - Buffer full, host is allowed to read.    */
/*    The MS byte specify which host last accessed the HSM (the       */
/*    values are according to the I43_HOST type).                     */
/*  pbLength - Pointer where to write number of words in the buffer.  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* By calling this API the host can wait to get access to the DRAM    */
/* area that is shared between the two hosts for communication        */
/* purposes.                                                          */
/* If the return value is I43_ACCESS_DENIED, the host is not allowed  */
/* to access the DRAM and should try again later.                     */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  WaitHostComSem                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_WaitHostComSem( I43_UINT16* pwAccess,
                                   I43_UINT8*  pbLength
                                 ) CODE_SECT;



/* ****************************************************************** */
/*                        I43_SignalHostComSem                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* By calling this API the host release the semaphor that enables the */
/* access to the DRAM area that is shared between the two hosts for   */
/* communication process.                                             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SignalHostComSem                                                  */
/* ****************************************************************** */
I43_ERROR_CODE I43_SignalHostComSem(void) CODE_SECT;



/* ****************************************************************** */
/*                         I43_SetHostComData                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bLength - The length of the data to be transfered (in words).     */
/*            Note that the maximum size of data transfer is 32.      */
/*  bHostType - Indicates which host is setting the data.             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to set data in the shared DRAM area */
/* that is designated for host communication.                         */
/* The host should call this API only after it was granted access to  */
/* the DRAM area by calling the I43_WaitHostComSem API.               */
/* The data is read from a predefined memory location.                */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetHostComData                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetHostComData( I43_UINT8 bLength,
                                   I43_HOST  bHostType
                                 ) CODE_SECT;

/* ****************************************************************** */
/*                         I43_GetHostComData                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bEmptyBuffer - indicates whether to empty the buffer or not       */
/*                 after reading it.                                  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to read data from the shared DRAM   */
/* area that is designated for host communication.                    */
/* The host should call this API only after it was granted access to  */
/* the DRAM area by calling the I43_WaitHostComSem API.               */
/* The data is written to a predefined memory location.               */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetHostComData                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetHostComData( I43_BOOL bEmptyBuffer
                                 ) CODE_SECT;
                              

/* ****************************************************************** */
/*                        I43_PtpControl                              */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bCommand      - 0 - Start                                         */
/*                  1 - Stop                                          */
/*                  2 - Set Prop Value                                */
/*                  3 - Set Serial Number                             */
/*  wParam1 - Params for the commands.                                */
/*  wParam2 - Params for the commands.                                */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
I43_ERROR_CODE I43_PtpControl( I43_UINT8  bCommand,
                               I43_UINT16 wParam1,
                               I43_UINT16 wParam2) CODE_SECT;


/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                            Capture Control                         */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                         I43_PlaybackClipCmd                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bCommand - The command to be executed on the Clip.                */
/*  wOperand - Operand to be used in some of the commands.            */
/*             In commands that the operand is not needed, it's       */
/*             content is ignored.                                    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function allows the host to instruct the COACH to execute     */
/* various operations regarding the playback of the clip.             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  PlaybackClipCmd                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_PlaybackClipCmd(I43_PLAYBACK_CLIP_CMD bCommand,
                                   I43_UINT16            wOperand
                                  ) CODE_SECT;



/* ****************************************************************** */
/*                       I43_SetCompressionRatio                      */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bCompressionRatio - The required compression ratio according to   */
/*                      table in the I43 spec.                        */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the compression ratio between the active size   */
/* of the frame, in bytes, and teh total resulted file size after all */
/* compression file formatting operations.                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetCompressionRatio                                               */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetCompressionRatio( I43_COMPRESSION_RATIO bCompressionRatio
                                      ) CODE_SECT;



/* ****************************************************************** */
/*                       I43_SetSequenceLength                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bSequenceLength - the required sequence length (range: 2-127).    */
/*  bDelay          - the delay between two consequtive images in the */
/*                    sequence. The Delay is 2^bDelay readouts.       */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the required sequence length to be used when a  */
/* capture sequence mode is entered.                                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetSequenceLength                                                 */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetSequenceLength( I43_UINT8 bSequenceLength,
                                      I43_UINT8 bDelay
                                    ) CODE_SECT;



/* ****************************************************************** */
/*                       I43_GetSequenceLength                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pbSequenceLength - Pointer where to write the read sequence length*/
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function returns to the host the actual number of images that */
/* were captured in the Capture Sequence mode.                        */
/* Knowing this number, the host knows how many times it has to apply */
/* the GetImage command to acquire the compressed images from the I43.*/
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetSequenceLength                                                 */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetSequenceLength( I43_UINT8* pbSequenceLength
                                    ) CODE_SECT;



/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                         Flash Light Control                        */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                          I43_SetFlashTrigger                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bMode -                                                           */
/*    I43FOM_OFF =           Flash light disabled.                    */
/*    I43FOM_AUTO =          Flash light activated according to AE    */
/*                           algorithm.                               */
/*    I43FOM_FORCE_CAPTURE = Flash light activated by COACH for       */
/*                           every captured image, regardless of the  */
/*                           AE algorithm.                            */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the mode of operation of the flash light.       */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetFlashTrigger                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetFlashTrigger( I43_FLASH_OP_MODE bMode
                                  ) CODE_SECT;



/* ****************************************************************** */
/*                      I43_ConfigFlashTrigger                        */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigFlashTrigger( I43_UINT16 wDuration,
                                       I43_UINT16 wDelay) CODE_SECT;


/* ****************************************************************** */
/*                      I43_ConfigStrobePin                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  uiPins - number of pins that used by the strobe flash uses        */
/*  ulPolarity - the active level of each pin                         */
/*  uiFpdIn - external pin detection (disable/active high/active low) */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the polarity of the strobe flash pins.          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigFlashTrigger                                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigStrobePin( I43_UINT32 uiTrigPins,
                                    I43_UINT32 ulTrigPolarity,
                                    I43_UINT32 uiFpdIn );

/* ****************************************************************** */
/*                           I43_EnableRER                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bEnable - I43_TRUE  = RER on.                                     */
/*            I43_FALSE = RER off.                                    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables or disables the RER operation.               */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  EnableRedEyeReduction                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43_EnableRER( I43_BOOL bEnable
                            ) CODE_SECT;



/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                         General Commands                           */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */

/* ****************************************************************** */
/*                          I43_SetParamArray                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wParamID - The ID of the param array to set.                      */
/*       (See host commmand spec for details)                         */
/*  wOffset - Offset from the array base address in which data        */
/*  should be written                                                 */
/*  wSize - the size of data to write to the param array              */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets an array of parameters in the COACH.            */
/* Each parameter array which can be set via this command has a unique*/
/* ParamID.                                                           */
/* The array data is read from the I43_SET_PARAM_ARRAY_MEM_LOCATION   */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/* SetParamArray                                                      */
/* ****************************************************************** */


I43_ERROR_CODE I43_SetParamArray( I43_UINT16 wParamID,
                                  I43_UINT16 wOffset,
                                  I43_UINT16 wSize
                                ) CODE_SECT;

/* ****************************************************************** */
/*                          I43_GetParamArray                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wParamID - The ID of the param array to get.                      */
/*       (See host commmand spec for details)                         */
/*  wOffset - Offset from the array base address in which data        */
/*  should be read                                                    */
/*  wSize - the size of data to read from the param array             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function reads an array of parameters from the COACH.         */
/* Each parameter array which can be read via this command has a      */
/* unique ParamID.                                                    */
/* The array data is written into the I43_GET_PARAM_ARRAY_MEM_LOCATION*/
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/* GetParamArray                                                      */
/* ****************************************************************** */

I43_ERROR_CODE I43_GetParamArray( I43_UINT16 wParamID,
                                  I43_UINT16 wOffset,
                                  I43_UINT16 wSize
                                ) CODE_SECT;


/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                         System Calibration                         */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */

/* ****************************************************************** */
/*                           I43_AudioLoop                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bEnable - I43_TRUE  = Enable Audio Loop.                          */
/*            I43_FALSE = Disable Audio Loop.                         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables or disables the audio loop test mode.        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  AudioLoop                                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_AudioLoop( I43_BOOL bEnable
                            ) CODE_SECT;



/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                            Hce Commands                            */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */



/* ****************************************************************** */
/*                        I43_ConfigButtonDrvEx                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bConfigType - The button configuration to be applied.             */
/*  wParam1     - The parameter 1 to be used in this configuration.   */
/*  wParam2     - The parameter 2 to be used in this configuration.   */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function configures the behavior of the buttons in an         */
/* HCE system.                                                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigButtonDrv                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigButtonDrvEx( I43_BUTTON_CFG_TYPE  bConfigType,
                                      I43_UINT16           wParam1,
                                      I43_UINT32           wParam2
                                    ) CODE_SECT;


/* ****************************************************************** */
/*                         I43_ButtonEnable                           */
/* ****************************************************************** */
/*                                                                    */
/* Input Parameters:                                                  */
/*  bEnable - true - enable, false - disable.                         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables or disables buttons messages generation for  */
/* HCE system.                                                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  ConfigButtonDrv                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_ButtonEnable(I43_BOOL bEnable ) CODE_SECT;

/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                           Power Control Commands                   */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */

I43_ERROR_CODE I43_PowerOff( );

/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */
/*                           Debug Commands                           */
/* ////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////// */

/* ****************************************************************** */
/*                        I43_WriteFlashBurst                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function lets the host write a burst of data to the flash     */
/* memory.                                                            */
/* The buffer is read from the I43_FLASH_BURST_MEM_LOCATION memory    */
/* location.                                                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  WriteFlashBurst                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_WriteFlashBurst( I43_UINT16* pwStatus
                                              ) CODE_SECT;



/* ****************************************************************** */
/*                    I43_UpgradeFlashFromCard                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bDrive  -  The drive on which the external card is located.       */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This command allows the user to upgrade the CoachWare version on   */
/* resident flash memory from an external flash card.                 */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  UpgradeFlashFromCard                                              */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_UpgradeFlashFromCard( I43_UINT8 bDrive
                                                   ) CODE_SECT;


/* ****************************************************************** */
/*                    I43_UpgradeWav			                      */
/* ****************************************************************** */

I43_ERROR_CODE I43_UpgradeWav(I43_BOOL bByName, 
			   				  I43_UINT16 wIndex
               					               ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_GetMem                               */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function lets the host read free values to memory set by the  */
/* I43_ConfigMemAccess API.                                           */
/* The buffer is read to a predefined memory location.                */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetMem                                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetMem( void
                         ) CODE_SECT;



/* ****************************************************************** */
/*                           I43_SetMem                               */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function lets the host write free values to memory set by the */
/* I43_ConfigMemAccess API.                                           */
/* The buffer is read from a predefined memory location.              */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetMem                                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetMem( void
                         ) CODE_SECT;


/* ****************************************************************** */
/*                             I43_SetLong                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  lAddress - The address to write to.                               */
/*	lValue   - The value to write to the specified address.           */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function lets the host write a single word to the specified   */
/* address. The address is in the DMEM area of the oak DSP.           */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*	SetLong                                                           */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_SetLong(I43_UINT32 lAddress,
                                       I43_UINT32 lValue)CODE_SECT;


/* ****************************************************************** */
/*                             I43_GetLong                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wAddress - The address to read from.                              */
/*	pwValue  - Pointer where to write the value read from the         */
/*             specified address.                                     */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function lets the host read a single word from the specified  */
/* address. The address is in the DMEM area of the oak DSP.           */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*	GetLong                                                           */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_GetLong(I43_UINT32 lAddress,
                                       I43_UINT32* plValue)CODE_SECT;



/* ****************************************************************** */
/*                        I43_EditImage		                          */
/* ****************************************************************** */
I43_ERROR_CODE I43_EditImage( I43_EDIT_IMAGE_CONFIG_OPERATION* pConfgi
								) CODE_SECT;


#if  ( MODULE_TYPE==HCE_API )
#pragma far_seg
#endif

/* ****************************************************************** */
/*                         I43_GetCOACHVersion                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwHWVersion  - Pointer where to write the returned Hardware       */
/*                 version number.                                    */
/*  pwROMVersion - Pointer where to write the returned ROM version    */
/*                 number.                                            */
/*  pwLCVersion  - Pointer where to write the returned loadable code  */
/*                 version number.                                    */
/*  pwFSVersion  - Pointer where to write the returned file system    */
/*                 code version number.                               */
/*  pwReserved   - reseved word for future use.                       */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function returns the I43 Hardware and software version number.*/
/* The MS byte is the hardware (chip) ID and version. The value of    */
/* the first COACH version is 0x4301. Following versions will have    */
/* values of 0x43RR. The LS byte is the ROM version.                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetCOACHVersion                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetCOACHVersion( I43_UINT16* pwHWVersion,
                                    I43_UINT16* pwROMVersion,
                                    I43_UINT16* pwLCVersion,
                                    I43_UINT16* pwFSVersion,
                                    I43_UINT16* pwReserved
                                  ) CODE_SECT_MORE_4_PARAMS;



/* ****************************************************************** */
/*                              I43_SetGDA                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bAttr                          - Attribute to change.             */
/*  wParm1, wParm2, wParm3, wParm4 - Free parameters.                 */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* Through this function the host sets the different attributes of    */
/* the current GDA (Graphic Device Attributes).                       */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  SetGDA                                                            */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetGDA( I43GR_GDA_ATTR_TYPE bAttr,
                           I43_UINT16          wParm1,
                           I43_UINT16          wParm2,
                           I43_UINT16          wParm3,
                           I43_UINT16          wParm4
                         ) CODE_SECT_MORE_4_PARAMS;



/* ****************************************************************** */
/*                            I43_DrawShape                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bShapeType - Type of the shape to draw.                           */
/*  wStartX    - Top left corner pixel of the resource with respect   */
/*               to the display window (X-axis).                      */
/*  wStartY    - Top left corner pixel of the resource with respect   */
/*               to the display window (Y-axis).                      */
/*  wSizeX     - The shape size in X dimension (in pixels).           */
/*  wSizeY     - The shape size in Y dimension (in pixels).           */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* Through this function the host instructs the COACH to draw a       */
/* graphic shape at a specific location.                              */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  DrawShape                                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43_DrawShape( I43GR_SHAPE_TYPE bShapeType,
                              I43_UINT16       wStartX,
                              I43_UINT16       wStartY,
                              I43_UINT16       wSizeX,
                              I43_UINT16       wSizeY
                            ) CODE_SECT_MORE_4_PARAMS;



/* ****************************************************************** */
/*                          I43_GetDCFInfo                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wIndex    - Index of the file to query.                           */
/*  pwDirNum  - Pointer where to write the returned directory number. */
/*  pwFileNum - Pointer where to write the returned file number.      */
/*  pwItemTypes - Pointer where to write the returned Item types      */
/*              found in this DCF object                              */
/*  pwLocked  - Pointer where to write whether the file is locked.    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to get the DCF key of a file that   */
/* is pointed by the given wIndex parameter.                          */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetDCFInfo                                                        */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetDCFInfo( I43_UINT16  wIndex,
                               I43_UINT16* pwDirNum,
                               I43_UINT16* pwFileNum,
                               I43_UINT16* pwItemTypes,
                               I43_UINT16* pwLocked
                             ) CODE_SECT_MORE_4_PARAMS;




/* ****************************************************************** */
/*                      I43_GetStorageMediaStatus                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwSuccess - Pointer to where to write the operation result.       */
/*             0 - Operation succeeded.                               */
/*             Other values - Operation failed.                       */
/*  pwImageCount - Pointer to where to write how many pictures are    */
/*             there on the storage media in the current directory.   */
/*  pwImageLeft - Pointer to where to write how many more pictures    */
/*             can be stored on the storage media.                    */
/*  pwSizeMS - Pointer where to write the MS word of the available    */
/*             storage space.                                         */
/*  pwSizeLS - Pointer where to write the LS word of the available    */
/*             storage space.                                         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function returns to the host, the number of Image files       */
/* that are currently stored on the storage media and the number      */
/* of images that can be stored on the storage media.                 */
/* Also the function retunes the available storage space left in      */
/* memory (in bytes).                                                 */
/* Note: if pwSuccess is non-zero, all other return values are        */
/* invalid and should not be used.                                    */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetStorageMediaStatus                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetStorageMediaStatus( I43_UINT16* pwSuccess,
                                          I43_UINT16* pwImageCount,
                                          I43_UINT16* pwImageLeft,
                                          I43_UINT16* pwSizeMS,
                                          I43_UINT16* pwSizeLS
                                        ) CODE_SECT_MORE_4_PARAMS;



/* ****************************************************************** */
/*                     I43_GetStorageMediaGeometry                    */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  pwSuccess - Pointer to where to write the operation result.       */
/*             0 - Operation succeeded.                               */
/*             Other values - Operation failed.                       */
/*  pwBytesPerSector - Pointer to where to write how many bytes are   */
/*                     in each sector.                                */
/*  pwSectorsPerCluster - Pointer to where to write how many sectors  */
/*                        are in each cluster.                        */
/*  pwTotalClusters - Pointer where to write the total number of      */
/*                    clusters (both used and free).                  */
/*  wFreeClusters - Pointer where to write the number of free         */
/*                  clusters.                                         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function returns to the host the number of bytes per sector,  */
/* the number of sectors per cluster, the total number of clusters    */
/* and the total number of free clusters.                             */
/* Note: if pwSuccess is non-zero, all other return values are        */
/* invalid and should not be used.                                    */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  GetStorageMediaStatus                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetStorageMediaGeometry( I43_UINT16* pwSuccess,
                                            I43_UINT16* pwBytesPerSector,
                                            I43_UINT16* pwSectorsPerCluster,
                                            I43_UINT16* pwTotalClusters,
                                            I43_UINT16* wFreeClusters
                                           ) CODE_SECT_MORE_4_PARAMS;


/* ****************************************************************** */
/*                      I43_SetOSDDisplayAttr                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bDisplayID - The ID of the display memory.                        */
/*  wAttr      - The attribute to be set.                             */
/*  wParam1    - Free parameter 1.                                    */
/*  wParam2    - Free parameter 2.                                    */
/*  wParam3    - Free parameter 3.                                    */
/*  wParam4    - Free parameter 4.                                    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to set the attributes of the        */
/* display memory associated with bDisplayID.                         */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*    SetOsdDisplayAttr                                               */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetOSDDisplayAttr( I43_UINT8        bDisplayID,
                                      I43OSD_ATTR_TYPE wAttr,
                                      I43_UINT16       wParam1,
                                      I43_UINT16       wParam2,
                                      I43_UINT16       wParam3,
                                      I43_UINT16       wParam4
                                      ) CODE_SECT_MORE_4_PARAMS;

/* ****************************************************************** */
/*                      I43_OSDTextOutID                              */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bDisplayID - The ID of the display memory.                        */
/*  wStartX    - X value of the first letter's top left corner.       */
/*  wStartY    - Y value of the first letter's top left corner.       */
/*  wLength    - The length of the string in chars.                   */
/*  wStringID  - The ID of the string as assigned by the programming  */
/*               tool.                                                */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to display a string stored on the   */
/* flash memory at a specific location on the display.                */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*    OsdTextOutId                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_OSDTextOutID( I43_UINT8  bDisplayID,
                                 I43_UINT16 wStartX,
                                 I43_UINT16 wStartY,
                                 I43_UINT16 wLength,
                                 I43_UINT16 wStringID
                               ) CODE_SECT_MORE_4_PARAMS;



/* ****************************************************************** */
/*                      I43_OSDDrawTextID                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bDisplayID - The ID of the display memory.                        */
/*  wStartX    - X value of the target rectangle's top left corner.   */
/*  wStartY    - Y value of the target rectangle's top left corner.   */
/*  wWidth     - The width of the target erctangle.                   */
/*  wHeight    - The height of the target rectangle.                  */
/*  wLength    - The length of the string in chars.                   */
/*  wFlagsMS   - The MS word of the formatting flags.                 */
/*  wFlagsLS   - The LS word of the formatting flags.                 */
/*  wStringID  - The ID of the string as assigned by the programming  */
/*               tool.                                                */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to display a string stored on the   */
/* flash memory at a specific rectangle on the display.               */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*    OsdDrawTextId                                                   */
/* ****************************************************************** */
I43_ERROR_CODE I43_OSDDrawTextID( I43_UINT8  bDisplayID,
                                  I43_UINT16 wStartX,
                                  I43_UINT16 wStartY,
                                  I43_UINT16 wWidth,
                                  I43_UINT16 wHeight,
                                  I43_UINT16 wLength,
                                  I43_UINT16 wFlagsMS,
                                  I43_UINT16 wFlagsLS,
                                  I43_UINT16 wStringID
                                ) CODE_SECT_MORE_4_PARAMS;



/* ****************************************************************** */
/*                      I43_OSDDrawText                               */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bDisplayID - The ID of the display memory.                        */
/*  wStartX    - X value of the target rectangle's top left corner.   */
/*  wStartY    - Y value of the target rectangle's top left corner.   */
/*  wWidth     - The width of the target erctangle.                   */
/*  wHeight    - The height of the target rectangle.                  */
/*  wLength    - The length of the string in chars.                   */
/*  wFlagsMS   - The MS word of the formatting flags.                 */
/*  wFlagsLS   - The LS word of the formatting flags.                 */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to display a given string at a      */
/* specific rectangle on the display.                                 */
/* The string is given through I43_OSD_DRAW_TEXT_MEM_LOCATION.        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*    OsdDrawText                                                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_OSDDrawText( I43_UINT8  bDisplayID,
                                I43_UINT16 wStartX,
                                I43_UINT16 wStartY,
                                I43_UINT16 wWidth,
                                I43_UINT16 wHeight,
                                I43_UINT16 wLength,
                                I43_UINT16 wFlagsMS,
                                I43_UINT16 wFlagsLS
                              ) CODE_SECT_MORE_4_PARAMS;


/* ****************************************************************** */
/*                      I43_OSDDrawShape                              */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_OSDDrawShape( I43_UINT8          bDisplayID,
                                             I43OSD_SHAPE_TYPE  wShapeType,
                                             I43_INT16          wStartX,
                                             I43_INT16          wStartY,
                                             I43_UINT16         uwWidth,
                                             I43_UINT16         uwHeight );


/* ****************************************************************** */
/*                      I43_OSDDrawFile                               */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_OSDDrawFile( I43_UINT8         bDisplayID,
                                            I43OSD_FILE_TYPE  wFileType,
                                            I43_UINT8*        cFileName,
                                            I43_INT16         wStartX,
                                            I43_INT16         wStartY,
                                            I43_UINT16        uwWidth,
                                            I43_UINT16        uwHeight );

/* ****************************************************************** */
/*                        I43_PipLayerCreate                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*	uiLayer  - PIP Layer ID                                           */
/*  uiLeft   - Left corner of the PIP layer in the display image.     */
/*  uiTop    - Tot corner of the PIP layer in the display image.      */
/*  uiWidth  - The width of the target erctangle.                     */
/*  uiHeight - The height of the target rectangle.                    */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function create new PIP layer. The image resolution is given  */
/*	in virtual frame size (1024 x 1024 pixels).                       */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*	                                                                  */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_PipLayerCreate( I43_UINT8  bLayer,
                                               I43_UINT32 uiLeft,
                                               I43_UINT32 uiTop,
                                               I43_UINT32 uiWidth,
                                               I43_UINT32 uiHeight );

/* ****************************************************************** */
/*                         I43_PipLayerDestroy                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*	uiLayer - PIP layer ID.                                           */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function distoried existing PIP layer.                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*	                                                                  */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_PipLayerDestroy(I43_UINT8 bLayer);

/* ****************************************************************** */
/*                         I43_PipLayerShow                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*	uiLayer - PIP layer ID.                                           */
/*	bShow   - Boolean flag that enable / disable the PIP layer        */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enable or disable the given PIP layer.               */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*	                                                                  */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_PipLayerShow( I43_UINT8 bLayer, 
                                             I43_BOOL  bShow );

/* ****************************************************************** */
/*                      I43_PipSetAttrib                              */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  uiLayer     - The ID of the PIP layer.                            */
/*  uiAttribute - The attribute to be set.                            */
/*  uiValue0    - Free parameter 1.                                   */
/*  uiValue1    - Free parameter 2.                                   */
/*  uiValue2    - Free parameter 3.                                   */
/*  uiValue3    - Free parameter 4.                                   */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function enables the host to set the attributes of the        */
/* PIP related operations.                                            */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*                                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_PipSetAttrib( I43_UINT8  bLayer,
                                             I43PIP_ATTR_TYPE uiAttrib,
                                             I43_UINT32 uiValue0,
                                             I43_UINT32 uiValue1,
                                             I43_UINT32 uiValue2,
                                             I43_UINT32 uiValue3 );

/* ****************************************************************** */
/*                      I43_PipModeActivate                           */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_PipModeActivate( I43PIP_MODE  bMode, 
												I43_BOOL     bActivate );


/* ****************************************************************** */
/*                          I43_ConfigRER                             */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigRER( I43_UINT8  bCount,
            				  I43_UINT16 wDuration,
			            	  I43_UINT16 wDelay,
						      I43_UINT16 wPostDelay,
            				  I43_UINT8  bPulse);


/* ****************************************************************** */
/*                         I43_ConfigMemAccess                        */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigMemAccess( I43_MEM_TYPE wMemType,
                                    I43_UINT32   dwStartAddr,
                                    I43_UINT32   dwSizeInBytes
                                  ) CODE_SECT_MORE_4_PARAMS;



/* ****************************************************************** */
/*                           I43_DebugOtr                             */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bOpCode - The Otr opcode.                                         */
/*  wWord1  - parameter word 1.                                       */
/*  wWord2  - parameter word 2.                                       */
/*  wWord3  - parameter word 3.                                       */
/*  wWord4  - parameter word 4.                                       */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function is for debug purposes only and should be removed     */
/* in later versions from the API.                                    */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*  DebugOtr1 / DebugOtr2 / DebugOtr3 / DebugOtr4                     */
/* ****************************************************************** */
I43_ERROR_CODE I43_DebugOtr( I43_HOST_COMMAND   bOpCode,
                             I43_UINT16         wWord1,
                             I43_UINT16         wWord2,
                             I43_UINT16         wWord3,
                             I43_UINT16         wWord4
                           ) CODE_SECT_MORE_4_PARAMS;

/* ****************************************************************** */
/*                         I43_MotorConfig                            */
/* ****************************************************************** */
/*                                                                    */
/* Input Parameters:                                                  */
/*  byMotorId  - Motor port Id.                                       */
/*  byData     - Mask of data pins. The in use bits are 0-3, when bit */
/*               0 represents pin A and bit 3 represents pin D.       */
/*               If bit value is 1, it means the the corresponding    */
/*               pin is used to produce to the motor sequence.        */
/*  byControl  - Mask of control pins. The in use bits are 0-3, when  */
/*               bit 0 represents pin A and bit 3 represents pin D.   */
/*               If bit value is 1, it means the the corresponding    */
/*               pin is used as control pin and not as part of        */
/*               sequence command.                                    */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*  The function configured the selected motor poty parameters.       */
/*  The function should be called before any access to this motor     */
/*  port can be done                                                  */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*                                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_MotorConfig(I43_UINT8 byMotorId,
                               I43_UINT8 byData,
                               I43_UINT8 byControl);

/* ****************************************************************** */
/*                         I43_MotorSet                               */
/* ****************************************************************** */
/*                                                                    */
/* Input Parameters:                                                  */
/*  byMotorId          - Motor port Id.                               */
/*  pbyBuffer          - pointer to inputs buffer array. Each         */
/*                       element of the array contains a value for    */
/*                       corresponding motor pin. Value width is 8 bit*/
/*                       Element 0 contains value for pin A, element  */
/*                       3 contains value for pin D.                  */
/*  uwPulseRate        - defines the motor step time in PPS units.    */
/*  uwRepeat           - number of times for complete sequences to be */
/*                       repeated.                                    */
/*  byAddSequenceWidth - additional sequence width in bits.           */
/*  bSwTrigger         - Denotes whether the motor is triggers by     */
/*                       software                                     */
/*  bGo                - Denotes whether the command should be        */
/*                       executed immediatly.                         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/*  The function programmes the next sequence command. And if the     */
/*  command is triggered by software and immediate command execution  */
/*  was selected, the function executes the command                   */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*                                                                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_MotorSet(I43_UINT8 byMotorId,
                            I43_UINT8 byData[4],
                            I43_INT16 uwPulseRate,
                            I43_INT16 uwRepeat,
                            I43_UINT8 byAddSequenceWidth,
							I43_BOOL  bHoldFinalState,
                            I43_BOOL  bSwTrigger,
                            I43_BOOL  bGo);


/* ****************************************************************** */
/*                         I43_MotorGo                                */
/* ****************************************************************** */
I43_ERROR_CODE I43_MotorGo();


/* ****************************************************************** */
/*                           I43_MonitorCmd                           */
/* ****************************************************************** */

I43_ERROR_CODE I43_MonitorCmd( I43_UINT8 pbCommand[]
                              ) CODE_SECT;

/* ****************************************************************** */
/*                           I43_SetClock                             */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_SetClock( I43_UINT16 uwYear,
                                         I43_UINT16 uwMonth,
                                         I43_UINT16 uwDay,
                                         I43_UINT16 uwHour,
                                         I43_UINT16 uwMinute,
                                         I43_UINT16 uwSecond );


/* ****************************************************************** */
/*                           I43_GetClock                             */
/* ****************************************************************** */
I43_ERROR_CODE I43APICLASS I43_GetClock( I43_UINT16 *puwYear,
                                         I43_UINT16 *puwMonth,
                                         I43_UINT16 *puwDay,
                                         I43_UINT16 *puwHour,
                                         I43_UINT16 *puwMinute,
                                         I43_UINT16 *puwSecond,
										 I43_UINT16 *puwWeekDay);

/* ****************************************************************** */
/*                           I43_ConfigDRAMCapture                    */
/* ****************************************************************** */
I43_ERROR_CODE I43_ConfigDRAMCapture( I43_UINT8   byOpen,
			                          I43_UINT8** ppbyBuffer );


#endif /* _API_FUNC_H_ */
