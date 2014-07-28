/* ****************************************************************** */
/*                             Common.h                               */
/* ****************************************************************** */
/* Copyright (c) 1997 ZORAN Corporation, All Rights Reserved          */
/* THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION               */
/*                                                                    */
/* $Workfile: Common.h $                                            */
/* $Modtime: 4/15/99 3:32p $                                          */
/* $Revision: 9 $                                                    */
/* $Date: 4/18/99 11:33a $                                             */
/* ****************************************************************** */



#ifndef _COMMON_H_
#define _COMMON_H_


#ifdef __cplusplus 
extern "C" {
#endif

/* ****************************************************************** */
/*                         MyOutputDebugString                        */
/* ****************************************************************** */
/* This function is used to print formatted strings in different      */
/* modules type.                                                      */
/* ****************************************************************** */
void MyOutputDebugString(char *format, ...);



#ifdef __cplusplus 
}
#endif


#endif /* _COMMON_H_ */

