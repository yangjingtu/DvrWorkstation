/* ****************************************************************** */
/*                              CFiles.h                              */
/* ****************************************************************** */

#ifndef I43OOP

#ifndef _CFILES_H_
#define _CFILES_H_

#include "I43_Api.h"

/* ****************************************************************** */
/*                      CFiles Class Definition                       */
/* ****************************************************************** */
class CFiles
{
public:
	CFiles();
	~CFiles();

	I43_ERROR_CODE SetMemLocationFile(I43_UINT8 bLocation, char* szNewFileName);
    void CloseAll();
};



#endif // _CFILES_H_


#endif /* #ifndef I43OOP */

