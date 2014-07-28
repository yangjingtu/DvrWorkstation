/* ****************************************************************** */
/*                             Api_vars.h                             */
/*                                                                    */
/* This header contains all the Global variables in the API functions.*/
/* ****************************************************************** */

#ifndef _API_VARS_H_
#define _API_VARS_H_

#ifndef __I43_API_H__
    #error  This file should be used inside of I43_Api.h
#endif  /* __I43_API_H__ */

#ifndef I43OOP
    #ifndef DECLARE_API_VARS
        #define I43EXTERN   extern
    #else
        #define I43EXTERN
    #endif /* DECLARE_API_VARS */
#else
    #define	I43EXTERN
#endif  /* I43OOP */

#endif /* _API_VARS_H_ */
